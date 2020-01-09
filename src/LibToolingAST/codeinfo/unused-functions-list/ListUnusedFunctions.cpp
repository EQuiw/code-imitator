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

#include "../../transformers/ASTFrontendActionTemplate.inl"
#include "../../transformers/utils_transform.h"
#include "../../transformers/ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../../transformers/ControlDataFlow/CDFGraphQueryHandler.h"
#include "unused_functions_utils.h"
#include "../../transformers/include/SourceTextHelper.h"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1

static llvm::cl::OptionCategory MyOptionCategory("List-all-unused-functions");
static llvm::cl::opt<bool> OverloadedOpt("list-overloaded", desc("List all unused overloaded fcts outside of records"),
                                         init(false), cat(MyOptionCategory));

/**
 * A preprocessor to list all unused functions.. Prints the names of all unused functions.
 * Output is a json string for each unused function.
 */
class ListUnusedFunctions : public RecursiveASTVisitor<ListUnusedFunctions> {
public:

    ControlFlowGraphWithDataFlow *cfggraph;

    explicit ListUnusedFunctions(ASTContext &Context)
            : Context(Context), sm(Context.getSourceManager()) {
        cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~ListUnusedFunctions(){
        delete cfggraph;
    }

    /* ******************* Collection Methods ******************* */

    /**
     * Visit all functions and store them in CFG graph.
     * @param f
     * @return
     */
    bool VisitFunctionDecl(FunctionDecl *f) {
        bool inmainfile = sm.isInMainFile(f->getLocation());
        if (inmainfile) {

            cfggraph->addFunctionDecl(f);
            if(f->isThisDeclarationADefinition())
                fctdecls.push_back(f);
        }
        return true;
    }

//    bool VisitFunctionTemplateDecl(FunctionTemplateDecl *f){
//        bool inmainfile = sm.isInMainFile(f->getLocation());
//        if (inmainfile) {
//            llvm::errs() << getUniqueFunctionNameAsString(f->getTemplatedDecl()) << "\n";
//          for (FunctionTemplateDecl::spec_iterator db = f->spec_begin(), de = f->spec_end(); db != de; ++db) {
//              const FunctionDecl *ft = *db;
//               llvm::errs() << "jkj" << getUniqueFunctionNameAsString(ft) << "\n";
//               }
//        }
//        return true;
//    }


    /* ******************* Listing Methods ******************* */

    void list_unused_functions(bool list_overloaded) {

        auto unused_fctdecls_plus = get_unused_functions(fctdecls, Context, cfggraph, list_overloaded);
        std::vector<const FunctionDecl*> unused_fctdecls;
        for(auto fx : unused_fctdecls_plus)
            unused_fctdecls.push_back(fx.first);


        for(auto f : unused_fctdecls){
            llvm::outs() << "Unused: {\"fct-name\": \"" << getUniqueFunctionNameAsString(f) << "\"";

            // If we have a template function, include the template declaration as well.
            const NamedDecl *nd;
            if(f->getDescribedFunctionTemplate()){
                nd = f->getDescribedFunctionTemplate();
            } else {
                nd = f;
            }

            // Get row and column of function-start, and function-end
            FullSourceLoc fullLoc(nd->getLocStart(), sm);
            unsigned row_start  = fullLoc.getSpellingLineNumber();
            unsigned col_start  = fullLoc.getSpellingColumnNumber();

            FullSourceLoc fullLoc2(getSourceRange(nd, sm, Context.getLangOpts()).getEnd(), sm);
            unsigned row_end  = fullLoc2.getSpellingLineNumber();
            unsigned col_end  = fullLoc2.getSpellingColumnNumber();

            llvm::outs() << ", \"row-start\":\"" << row_start << "\",\"col-start\":\"" << col_start
                         << "\", \"row-end\":\"" << row_end << "\",\"col-end\":\"" << col_end << "\"}" << "\n";
        }
    }


private:
    ASTContext &Context;
    SourceManager &sm;

    std::vector<const FunctionDecl*> fctdecls;
};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context) : Visitor(Context) {
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        Visitor.list_unused_functions(OverloadedOpt.getValue());
    }

private:
    ListUnusedFunctions Visitor;
};


class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {

//        std::string s = InFile;
//        llvm::errs() << "** Creating AST consumer for: " << split_path(s)[1] << "\n";

        return std::unique_ptr<clang::ASTConsumer>(
                new MyASTConsumer(Compiler.getASTContext()));
    }
};


int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, MyOptionCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}