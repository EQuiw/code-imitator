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
#include "Utils2.h"
#include "../RenamingGuide.h"

#include "../ASTFrontendActionTemplate.inl"
#include "../ControlDataFlow/DeclRefMapping/DeclRefMapping.h"
#include "../include/SourceTextHelper.h"

#include <string>
#include <fstream>
#include <Utils_Declarations.h>

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1


enum Strategies {remove_global_decl=2, remove_local_decl=3};

static llvm::cl::OptionCategory MyOptionCategory("Unused Declarations Transformer v2");

static llvm::cl::opt<Strategies> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                             values(
                                                     clEnumVal(remove_global_decl,
                                                               "Remove global Decl that is unused"),
                                                     clEnumVal(remove_local_decl,
                                                               "Remove local Decl that is unused")),
                                             cat(MyOptionCategory));

static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
static llvm::cl::opt<bool> AllOpt("all", desc("Rewrite all possible code occurences"),
                                  init(false), cat(MyOptionCategory));


/**
 * We remove unused declarations. It works on a row-level if all is False, so if a row such as int a,b,c;
 * and a,b, and c are unused, it will remove the entire declaration row (or all that are not used).
 *
 * TODO -- check global const problem:
 * if global and const, we could not check if there is a DeclRefExpr to it, as preprocessor replaces it already.
 * Here, it seems to work...
 */
class UnusedDeclsTransformer : public RecursiveASTVisitor<UnusedDeclsTransformer> {
public:

    DeclRefMapping *declrefmap;

    explicit UnusedDeclsTransformer(ASTContext &Context, Rewriter &OurRewriter)
            : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()) {
        declrefmap = new DeclRefMapping(&Context);

    }

    ~UnusedDeclsTransformer(){
        delete declrefmap;
    }
    /* ******************* Collection Methods ******************* */

    bool VisitVarDecl(VarDecl *d){
        bool inmainfile = sm.isInMainFile(d->getLocation());
        if (inmainfile) {
            var_declarations.push_back(d);
            declrefmap->insert_vardecl(d);
        }
        return true;
    }

    bool VisitDeclStmt(DeclStmt *d){
        bool inmainfile = sm.isInMainFile(d->getLocStart());
        if (inmainfile) {
            declrefmap->insert_declstmt(d);
        }
        return true;
    }

    bool VisitDeclRefExpr(DeclRefExpr *d){
        bool inmainfile = sm.isInMainFile(d->getLocation());
        if (inmainfile) {
            declrefmap->insert_declref(d);
        }
        return true;
    }


    /* ******************* Rewriting Methods ******************* */

    void replacecommand(Strategies strategy, int seed, bool all) {

        assert(strategy == remove_local_decl || strategy == remove_global_decl);

        auto usable_decls = collect_usable_declarations(strategy);
        remove_unused_declarations(usable_decls, seed, all);

    };


    /**
     * Go over all variable declarations and check if we should remove them (w.r.t to selected cmd line option).
     * @param strategy
     * @return
     */
    std::vector<std::vector<const VarDecl*>> collect_usable_declarations(Strategies strategy){

        std::vector<const VarDecl *> usable_decls;
        // Go over all declarations and check if never used via Decl-Reference Mapping
        for (auto dx : var_declarations) {

            // Check for input strategy
            if (strategy == remove_local_decl && !dx->isLocalVarDeclOrParm())
                continue;
            if (strategy == remove_global_decl && dx->isLocalVarDeclOrParm())
                continue;

            // Check for a rewrite that is not possible so far. Due to Preprocessor issues:
//            if (!dx->isLocalVarDeclOrParm()) {
//                // if global, check if const, then we will not have any DeclRef to it if another global var is using it.
//                if (dx->getType().getQualifiers()) {
//                    if (dx->getType().getQualifiers().getAsString().find("const") != std::string::npos) {
//                        llvm::errs() << "global variable is const. remove it:" << getSourceTextStable(dx, Context) << "\n";
//                           continue;
//                    }
//                }
//            }
            usable_decls.push_back(dx);
        }

        // Build a map with each declaration row and its declarations (1 or more).
        std::set<std::pair<unsigned,unsigned>> decl_rows;
        std::vector<std::vector<const VarDecl*>> decl_rows_vec;
        for(auto d : usable_decls) {
            auto slkey = getRowColumn(d->getLocStart(), sm, false);
            if(decl_rows.find(slkey) == decl_rows.end()) {
                auto vardecls = declrefmap->getSourceLocationToVarDecls(d->getLocStart());

                // only insert if at least one decl is not used.
                for(auto vd : vardecls){
                    if(declrefmap->getVarDeclToDeclRefExprs(vd).empty()){
                        decl_rows.insert(slkey);
                        decl_rows_vec.push_back(vardecls);
                        break;
                    }
                }

            }
        }

        return decl_rows_vec;
    }


    /**
     * Remove all declarations that are not used.
     * @param decl_rows_vec the declarations that will be considered for removal
     * @param seed seed from cmd line
     * @param all remove only one declaration or remove all that are not used.
     */
    void remove_unused_declarations(std::vector<std::vector<const VarDecl*>> decl_rows_vec, int seed, bool all){

        if(decl_rows_vec.empty()){
            llvm::errs() << "Code 124: Empty set\n";
            return;
        }

        randomlySortVector<std::vector<const VarDecl*>>(decl_rows_vec, seed);

        // Case 1. Row with single declaration.
        // Case 2. Row with multiple declarations that all need to be deleted
        // Case 3. Row with multiple delcarations, but only some of them will be deleted.
        for(auto decl_row : decl_rows_vec) {

            // Consider if we have a normal declaration or a recorddecl
            //  where variable is together with def. of struct/class.
            if(auto tr = dyn_cast<ElaboratedType>(decl_row[0]->getType()) &&
                         check_if_vardecl_ispartof_recorddecl(decl_row[0], sm)){
                handle_record_case(decl_row);
            } else {
                handle_default_case(decl_row);
            }

            // If we achieved one rewriting, and all is false, break up here.
            if (!all)
                return;

        }

    };


private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    std::vector<const VarDecl*> var_declarations;

    /**
     * Handle default cases, such as
     * int a = 0;
     * or
     * int a, c = 1e9, b = 0;
     * @param decl_row
     */
    void handle_default_case(std::vector<const VarDecl*> decl_row) {

        if (decl_row.size() == 1) {

            // Case 1
            UtilsDeclarations utilsDeclarations(Context);
            try {
                // Get the source range for the declaration,
                // the following method helps us to get the range with comma and semi-colon and without for easier rewriting.
                MultipleDeclInformation mdi = utilsDeclarations.getSourceInformationForMultipleDeclarationStmt(
                        decl_row, decl_row[0]);
                
                OurRewriter.RemoveText(mdi.fullRange);

            } catch (CodeTransformationException &e) {
                return;
            }

        } else {
            bool delete_entire_row = true;
            for (auto vd : decl_row) {
                delete_entire_row =
                        delete_entire_row && declrefmap->getVarDeclToDeclRefExprs(vd).empty();
            }

            auto sr_wholerow = SourceRange(decl_row[0]->getLocStart(),
                                           getCharSourceRange(decl_row.back(), sm,
                                                              Context.getLangOpts()).getEnd());

            if (delete_entire_row) {
                // Case 2
                OurRewriter.RemoveText(sr_wholerow);

            } else {
                // Case 3
                UtilsDeclarations utilsDeclarations(Context);
                try {
                    // a. get all decl's
                    std::vector<std::string> sts;
                    for (auto vd : decl_row) {
                        if(!declrefmap->getVarDeclToDeclRefExprs(vd).empty()) {
                            MultipleDeclInformation mdi = utilsDeclarations.getSourceInformationForMultipleDeclarationStmt(
                                    decl_row, vd);
                            sts.push_back(getSourceTextStable(Context, mdi.declOnlyRange.getBegin(),
                                                              mdi.declOnlyRange.getEnd()));
                        }
                    }

                    // b. get type
                    MultipleDeclInformation mdi = utilsDeclarations.getSourceInformationForMultipleDeclarationStmt(
                            decl_row, decl_row[0]);
                    std::string srctype;
                    // Problem: const int dx[] = {-1, 1} will have a type with code from else block incl. the name.
                    if(isa<ArrayType>(decl_row[0]->getType())) {
                        srctype = getSourceTextStable(Context, mdi.firstDecl->getLocStart(),
                                                      mdi.firstDecl->getLocation().getLocWithOffset(-1));
                    } else {
                        srctype = getSourceTextStable(Context, mdi.firstDecl->getLocStart(),
                                                      mdi.firstDecl->getTypeSourceInfo()->getTypeLoc().getLocEnd());
                    }

                    std::stringstream sst;
                    sst << "" << srctype << " ";
                    for(unsigned long ix = 0; ix < sts.size() -1 ; ix++){
                        sst << "" << sts[ix] << ",";
                    }
                    sst << "" << sts.back() << ";";
                    OurRewriter.RemoveText(mdi.fullRange);

                    OurRewriter.ReplaceText(sr_wholerow, sst.str());

                } catch (CodeTransformationException &e) {
                    return;
                }
            }
        }

    }

    /**
     * Handle record cases with structs or classes:
    struct debugger {
    template <typename T> debugger &operator,(const T &v) {
        cerr << v << " ";
        return *this;
        }
    } AA, BB;
     * @param decl_row
     */
    void handle_record_case(std::vector<const VarDecl*> decl_row) {

        // rebuild whole declarations after defining the struct body; so rebuild everything that comes after }, i.e.,
        // struct { } <here>;
        std::vector<std::string> sts;
        for(auto decl : decl_row){
            if(!declrefmap->getVarDeclToDeclRefExprs(decl).empty()){
                auto sr = SourceRange(decl->getLocation(), decl->getLocEnd());
                sts.push_back(getSourceTextStable(Context, sr.getBegin(), sr.getEnd()));
            }
        }

        std::stringstream sstr;
        if(!sts.empty()) {
            for (unsigned long ix = 0; ix < sts.size() - 1; ix++) {
                sstr << "" << sts[ix] << ",";
            }
            sstr << "" << sts.back();
        }

        OurRewriter.ReplaceText(SourceRange(decl_row.front()->getLocation(), decl_row.back()->getLocEnd()), sstr.str());

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
                               AllOpt.getValue());
    }

private:
    UnusedDeclsTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}
