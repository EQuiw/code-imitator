#ifndef CLANG_LIBS
#define CLANG_LIBS
#include "llvm/Support/CommandLine.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#endif

#include "../utils_transform.h"
#include "Utils.h"
#include "../RenamingGuide.h"
#include "../../codeinfo/unused-functions-list/unused_functions_utils.h"

#include "../ASTFrontendActionTemplate.inl"
#include "../ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../ControlDataFlow/CDFGraphQueryHandler.h"
#include "../include/SourceTextHelper.h"

#include <string>
#include <fstream>

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1


enum Strategies {add_function = 1, remove_function=2};

static llvm::cl::OptionCategory MyOptionCategory("Unused Functions Transformer");

// ** These are the command line options **, look at
// https://llvm.org/docs/CommandLine.html#selecting-an-alternative-from-a-set-of-possibilities
static llvm::cl::opt<Strategies> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                             values(clEnumVal(add_function, "Add Function Body that is unused"),
                                                    clEnumVal(remove_function,
                                                              "Remove Function Body that is unused")),
                                             cat(MyOptionCategory));

static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
static llvm::cl::opt<std::string> AddFunctionOpt("addfunction", init(""), cat(MyOptionCategory));
static llvm::cl::opt<std::string> SourceOpt("source", init(""), cat(MyOptionCategory));
static llvm::cl::opt<bool> AllOpt("all", desc("Remove all possible unused functions"),
                                  init(false), cat(MyOptionCategory));
static llvm::cl::opt<bool> OverloadedOpt("remove-overloaded",
                                         desc("Remove all overloaded fcts outside of records. "
                                              "Use with care as we cannot cover all usage cases here so far"),
                                  init(false), cat(MyOptionCategory));


/**
 * We add or remove unused function code blocks.
 * TODO function pointers are not considered so far as usages.
 */
class UnusedFunctionsTransformer : public RecursiveASTVisitor<UnusedFunctionsTransformer> {
public:

    ControlFlowGraphWithDataFlow *cfggraph;

    explicit UnusedFunctionsTransformer(ASTContext &Context, Rewriter &OurRewriter)
            : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()) {
        cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~UnusedFunctionsTransformer(){
        delete cfggraph;
    }
    /* ******************* Collection Methods ******************* */

    /**
     * Visit all functions.
     * @param f
     * @return
     */
    bool VisitFunctionDecl(FunctionDecl *f) {
        bool inmainfile = sm.isInMainFile(f->getLocation());
        if (inmainfile) {
            cfggraph->addFunctionDecl(f);
            this->fctdecls.push_back(f);
        }
        return true;
    }


    /* ******************* Rewriting Methods ******************* */

    void replacecommand(Strategies strategy, int seed, std::string addfct_name, std::string addfct_source,
                        bool all, bool remove_overloaded) {

        assert(strategy==add_function || strategy==remove_function);

        switch(strategy) {
            case add_function:
                add_function_from_srctext(addfct_name, seed, addfct_source);
                return;

            case remove_function:

                // old API:
//                auto unused_fctdecls = get_unused_functions_approximative(fctdecls, Context, cfggraph);
                // Use newer API
                try{
                    auto unused_fctdecls = get_unused_functions(fctdecls, Context, cfggraph, remove_overloaded);

                    if(unused_fctdecls.empty()){
                        llvm::errs() << "Code 124: Empty set\n";
                        return;
                    }

                    // Now if all is False, we only remove fcts that have no incoming edges, safe to delete
                    std::vector<const FunctionDecl*> unused_fctdecls_selected;
                    if(!all){
                        for(auto fx : unused_fctdecls){
                            if(fx.second == 0)
                                unused_fctdecls_selected.push_back(fx.first);
                        }
                    } else {
                        for(auto fx : unused_fctdecls)
                            unused_fctdecls_selected.push_back(fx.first);
                    }

                    // Now sort what we rewrite, if all is True, sort does not matter, as we rewrite all...
                    if(!all)
                        randomlySortVector<const FunctionDecl*>(unused_fctdecls_selected, seed);

                    // Iterate over all functions and remove
                    std::set<const FunctionDecl*> already_unused_fcts; // avoids mess with erasing stuff and iterators..

                    for(auto f : unused_fctdecls_selected){
                        if(already_unused_fcts.find(f) == already_unused_fcts.end()){
                            // we check if already considered, e.g. if f is currently the declaration for a already
                            //  visited function definition, as remove_function_from_srctext removes the def-decl-pairs always.
                            remove_function_from_srctext(f, already_unused_fcts);
                            if(!all)
                                return;
                        }
                    }

                } catch(CodeTransformationException &e){
                    return;
                }

                return;
        }

        llvm::errs() << "No valid strategy chosen/implemented?\n";
    };


private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    std::vector<const FunctionDecl*> fctdecls;

    /**
     * Removes the function body for an unused function.
     * @param f
     * @param already_unused_fcts -- set with already considered fcts; we will add def. and/or decl. of f to
     * this set if necessary. Param passed by reference.
     */
    void remove_function_from_srctext(const FunctionDecl* f, std::set<const FunctionDecl*> &already_unused_fcts){

#ifdef MYDEBUG
        llvm::errs() << "Remove-unused-function:" << f->getQualifiedNameAsString() << "\n";
#endif

        // Check if f is a function with or without declaration. We try to remove definition-declaration pairs, too.
        const FunctionDecl *f1 = nullptr, *f2 = nullptr;
        if(f->isThisDeclarationADefinition()){
            f2 = f;
            // find corresponding declaration-only
            for(auto fx : fctdecls){
                if(getUniqueFunctionNameAsString(fx) == getUniqueFunctionNameAsString(f)
                        && !fx->isThisDeclarationADefinition()){
                    f1 = fx;
                }
            }
        } else {
            f1 = f;
            // find corresponding definition
            for(auto fx : fctdecls){
                if(getUniqueFunctionNameAsString(fx) == getUniqueFunctionNameAsString(f)
                   && fx->isThisDeclarationADefinition()){
                    f2 = fx;
                }
            }
        }

        if(f1){
            auto f1t = f1->getDescribedFunctionTemplate();
            SourceRange sr;
            if(f1t) {
                sr = getSourceRange(f1t, sm, Context.getLangOpts());
            } else {
                sr = getSourceRange(f1, sm, Context.getLangOpts());
            }
            OurRewriter.RemoveText(sr);
            already_unused_fcts.insert(f1);
        }
        if(f2){
            auto f2t = f2->getDescribedFunctionTemplate();
            SourceRange sr;
            if(f2t) {
                sr = getSourceRange(f2t, sm, Context.getLangOpts());
            } else {
                sr = getSourceRange(f2, sm, Context.getLangOpts());
            }
            OurRewriter.RemoveText(sr);
            already_unused_fcts.insert(f2);
        }
//        return true;
    }

    /**
     * Adds the fct text on top of main.
     * @param fctparam the name of the new function, incl. its row start and row end
     * @param seed value used to dedice where to put the new function.
     * @return true if succ. transformation
     */
    bool add_function_from_srctext(std::string& fctparam, int seed, std::string &addfct_source){

        // I. get source; open the file
        std::ifstream in(addfct_source);

        // Object valid?
        if(!in)
        {
            llvm::errs() << "Error: Cannot open the File : "<< addfct_source << "\n";
            return false;
        }

        std::string str;
        std::vector<std::string> sourcefile;
        // Read next line from file until end
        while (std::getline(in, str))
        {
            sourcefile.push_back(str);
        }

        in.close();


        // II. Get start row and end row from fctparam
        auto reg = "[,]";
        auto splits = split(fctparam, reg);
        if(splits.size() != 3){
            llvm::errs() << "Error: splits unvalid, wrong input with fct-name, row-start and row-end?\n";
            return false;
        }
        if(std::stoi( splits[1] ) > std::stoi( splits[2] )){
            llvm::errs() << "Error: row end < row start\n";
            return false;
        }

        std::stringstream ss;
        int ra = std::stoi(splits[1]);
        int rb = std::stoi(splits[2]);
        for(int i = ra; i <= rb; i++){
            ss << "" << sourcefile[i-1] << "\n";
        }

#ifdef MYDEBUG
        llvm::outs() << "Insert:\n" << ss.str() << "\n***************\n";
#endif

        // III. Insert new function at random location
        auto fctdecls_local = fctdecls;
        randomlySortVector<const FunctionDecl*>(fctdecls_local, seed);

        auto chosenfuncdecl = fctdecls_local[0];
        OurRewriter.InsertText(chosenfuncdecl->getLocStart(), ss.str() + "\n\n");

        return true;
    }

};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter) : Visitor(Context, OurRewriter) {
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        Visitor.replacecommand(StrategyOpt.getValue(), SeedOpt.getValue(),
                               AddFunctionOpt.getValue(), SourceOpt.getValue(),
                               AllOpt.getValue(), OverloadedOpt.getValue());
    }

private:
    UnusedFunctionsTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}
