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

#include "../Utilities/Utils.h"
#include "../Utilities/Utils_Declarations.h"
#include "utils_transform.h"
#include "ASTFrontendActionTemplate.inl"
#include "./ControlDataFlow/DeclRefMapping/DeclRefMapping.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "include/SourceTextHelper.h"
#include "include/RandomHelper.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace llvm::cl;

enum Strategy {move_in_decls=1, move_out_decls=2};

// ** These are the command line options **
static llvm::cl::OptionCategory MyOptionCategory("InitDecl Transformer");
static llvm::cl::opt<Strategy> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                           values(clEnumVal(move_in_decls, "Move declaration into init-statement"),
                                                  clEnumVal(move_out_decls, "Move declaration out of init-statement")),
                                           cat(MyOptionCategory));

static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
static llvm::cl::opt<bool> AllOpt("all", desc("Rewrite all possible code occurences"),
                                  init(false), cat(MyOptionCategory));


/**
 * Transforms control structures declaring their own variable to control structures referencing vars defined beforehand
 * Examples: for (int i = 0;;)  -->   int i; for (i = 0;;)
 *           if(bool b = true)  -->   bool b; if(b = true;;)
 *
 * TODO: Check for name conflict, if there is none we're able to move the declaration into the existing scope
 *       surrounding the control structure.
 */
class InitStatementVarDeclTransformer : public MatchFinder::MatchCallback {
public:
    explicit InitStatementVarDeclTransformer(Rewriter &OurRewriter) : OurRewriter(OurRewriter){};

    virtual void run(const MatchFinder::MatchResult &Result) {
        // if RewriteAll isn't set, stop after rewriting successfully once
//        if (AllOpt.getValue() || !SuccessfulRewrite) {
            ASTContext *Context = Result.Context;
            //SourceManager &SM = Context->getSourceManager();

            const Stmt *OS = Result.Nodes.getNodeAs<clang::Stmt>("outer");
            const VarDecl *IVD = Result.Nodes.getNodeAs<clang::VarDecl>("inner");

            // Don't rewrite headers!
            if(!OS || !IVD || !Context->getSourceManager().isWrittenInMainFile(OS->getLocStart())) {
                return;
            }

            // Check if auto type TODO should be part of Matcher API?
            if(isa<AutoType>(IVD->getType()))
                return;

//            if (AllOpt.getValue()) {
//                rewrite(Context, OS, IVD);
//            } else {
                Results.emplace_back(Context, OS, IVD);
//            }

//        }
    }


    /**
     * Unless AllOpt got specified, rewrite a single result here.
     * Evaluate transformation results post run, publishing any error codes applying
     */
    virtual void onEndOfTranslationUnit() {

        if(Results.empty()){
            llvm::errs() << "Code 124: Empty set\n";
            return;
        }

        if(AllOpt.getValue()){
            // Rewrite all
            for(const auto &result : Results){
                rewrite(std::get<0>(result), std::get<1>(result), std::get<2>(result));
            }
        } else {
            // Rewrite a single random result
            const auto &result = select_randomly(Results, SeedOpt.getValue());
            rewrite(std::get<0>(result), std::get<1>(result), std::get<2>(result));
        }

        if(!SuccessfulRewrite)
            llvm::errs() << "Code 123: No transformations possible\n";
    }

private:

    void rewrite(ASTContext *Context, const Stmt* Outer, const VarDecl* Inner) {

        // TODO, we need to check if upper level has a CompoundStmt, or if we need to introduce a new scope.

        // if we have a variable usage such as int (i) = ... TODO so far, we only handle it with string replacement.
        bool brace_case =
                getSourceTextStable(Inner, *Context).find("(" + Inner->getNameAsString() + ")") != std::string::npos;

        // Rewrite inner vardecl to declref.
        auto newinnerdecl = getSourceTextStable(*Context, Inner->getLocation(), Inner->getLocEnd());
        if (brace_case)
            newinnerdecl = ReplaceString(newinnerdecl, Inner->getNameAsString() + ")", Inner->getNameAsString() + " ");

        OurRewriter.ReplaceText(Inner->getSourceRange(), newinnerdecl);

        // Check for name conflicts! (We could also introduce a new scope as fallback)
        auto DeclCheck = UtilsDeclarations(*Context);
        if (!DeclCheck.check_for_name_conflict(Outer, Inner)) {
            SuccessfulRewrite = false;
            return;
        }

        auto newouterdecl = getSourceTextStable(*Context, Inner->getLocStart(), Inner->getLocation());
        if (brace_case)
            newouterdecl = ReplaceString(newouterdecl, "(" + Inner->getNameAsString(), " " + Inner->getNameAsString());
        OurRewriter.InsertTextBefore(Outer->getLocStart(), newouterdecl + ";");

    }

    Rewriter &OurRewriter;

    std::vector<std::tuple<ASTContext*, const Stmt*, const VarDecl*>> Results;
    bool SuccessfulRewrite = true;
};

/**
 * Transforms control structures referencing vars declared beforehand into ones declaring their own, if possible.
 * Rewriting might fail if the referenced var is used outside of the control structure;
 * Possible fallback: Don't remove the old declaration, declare a new var and initialize it with the old one.
 * Examples: int i; for (i = 0;;)          -->   for (int i = 0;;)
 *           bool b; ... ; if(b = true;;)  -->   if(bool b = true)
 */
class InitStatementDeclRefTransformer : public MatchFinder::MatchCallback {
public:
    explicit InitStatementDeclRefTransformer(Rewriter &OurRewriter, DeclRefMapping* DeclRefMap)
            : OurRewriter(OurRewriter), DeclRefMap(DeclRefMap) {}


    virtual void run(const MatchFinder::MatchResult &Result) {
        // if RewriteAll isn't set, stop after rewriting successfully once
//        if (AllOpt.getValue() || !SuccessfulRewrite) {
        ASTContext *Context = Result.Context;

        const DeclRefExpr *IVDR = Result.Nodes.getNodeAs<DeclRefExpr>("initVarDeclRef");
        const VarDecl *IVD = Result.Nodes.getNodeAs<VarDecl>("initVarDecl");
        //const Expr * IVE = Result.Nodes.getNodeAs<Expr>("initValue");
        const Stmt *S = Result.Nodes.getNodeAs<Stmt>("scope");

        // Don't rewrite headers!
        if (!IVDR || !IVD || !S || !Context->getSourceManager().isWrittenInMainFile(IVDR->getLocStart())) {
            return;
        }

        // Make sure the VarDecl we found is save to move.
        for (auto R : DeclRefMap->getVarDeclToDeclRefExprs(IVD)) {
            if (R->getLocStart() < S->getLocStart() || S->getLocEnd() < R->getLocEnd()) {
                // Our VarDecl is referenced outside of its new scope, abort.
                return;
            }
        }

        // Make sure that Variable is not a function parameter (TODO should be part of matcher API?)
        if (IVD->isLocalVarDeclOrParm() && !IVD->isLocalVarDecl())
            return;



//            if (AllOpt.getValue()) {
//                rewrite(Context, IVD, IVDR);
//            } else {
        Results.emplace_back(Context, IVD, IVDR);
//            }
//        }
    }

    /**
     * Unless AllOpt got specified, rewrite a single result here.
     * Evaluate transformation results post run, publishing any error codes applying
     */
    virtual void onEndOfTranslationUnit() {

        if(Results.empty()){
            llvm::errs() << "Code 124: Empty set\n";
            return;
        }

        if(AllOpt.getValue()){
            // Rewrite all
            for(const auto &result : Results){
                rewrite(std::get<0>(result), std::get<1>(result), std::get<2>(result));
            }
        } else {
            // Rewrite a single random result
            const auto &result = select_randomly(Results, SeedOpt.getValue());
            rewrite(std::get<0>(result), std::get<1>(result), std::get<2>(result));
        }

        if(!SuccessfulRewrite)
            llvm::errs() << "Code 123: No transformations possible\n";
    }


private:

    void rewrite(ASTContext *Context, const VarDecl* Outer, const DeclRefExpr* Inner) {
        //Transform inner declref to vardecl

        // We work with the vector list of var decls, obtained via SrcLocation, since the Declaration List
        //  could also be global and then we would not have a common DeclStmt above.
        std::vector<const VarDecl*> vardecls = DeclRefMap->getSourceLocationToVarDecls(Outer->getLocStart());

        UtilsDeclarations utilsDeclarations(*Context);
        try {
            // Get the source range for the Outer declaration in the list with the other declarations,
            // the following method helps us to get the range with comma and semi-colon and without for easier rewriting.
            MultipleDeclInformation mdi = utilsDeclarations.getSourceInformationForMultipleDeclarationStmt(vardecls,
                                                                                                           Outer);

            // Remove old vardecl and replace inner declref by vardecl
            if(vardecls.size() == 1){
                // simple case; we just remove entire declaration row and move it into ...
                OurRewriter.RemoveText(mdi.fullRange);
                auto srctext = getSourceTextStable(*Context, mdi.declOnlyRange.getBegin(), mdi.declOnlyRange.getEnd());
                OurRewriter.ReplaceText(Inner->getSourceRange(), srctext);
            } else {
                // more complex case. We have multiple declarations such as int a,b,c;
                // in a row, we need to get the correct one and
                // we need to delete it correctly, including to delete commas and the semi-colon if necessary.

                OurRewriter.RemoveText(mdi.fullRange);
                auto srctype = getSourceTextStable(*Context, mdi.firstDecl->getLocStart(), mdi.firstDecl->getInnerLocStart());
                auto srctext = getSourceTextStable(*Context, mdi.declOnlyRange.getBegin(), mdi.declOnlyRange.getEnd());
                OurRewriter.ReplaceText(Inner->getSourceRange(), srctype + " " + srctext);
            }

        } catch(CodeTransformationException& e) {
            SuccessfulRewrite = false;
            return;
        }
    }

    Rewriter &OurRewriter;
    DeclRefMapping *DeclRefMap;

    std::vector<std::tuple<ASTContext*, const VarDecl*, const DeclRefExpr*>> Results;
    bool SuccessfulRewrite = true;
};

/**
 * Builds DeclRefMapping by storing matched VarDecls, DeclStmts and DeclRefExprs.
 */
class DeclRefMappingBuilder : public MatchFinder::MatchCallback {
public:
    explicit DeclRefMappingBuilder(DeclRefMapping* DeclRefMap)
            : DeclRefMap(DeclRefMap) {}

    virtual void run(const MatchFinder::MatchResult &Result) {
        ASTContext *Context = Result.Context;

        const VarDecl *VD = Result.Nodes.getNodeAs<VarDecl>("varDecl");
        if (VD && Context->getSourceManager().isWrittenInMainFile(VD->getLocStart())) {
            DeclRefMap->insert_vardecl(VD);
        }

        const DeclStmt * DS = Result.Nodes.getNodeAs<DeclStmt>("declStmt");
        if (DS && Context->getSourceManager().isWrittenInMainFile(DS->getLocStart())) {
            DeclRefMap->insert_declstmt(DS);
        }

        const DeclRefExpr * DRE = Result.Nodes.getNodeAs<DeclRefExpr>("declRefExpr");
        if (DRE && Context->getSourceManager().isWrittenInMainFile(DRE->getLocStart())) {
            DeclRefMap->insert_declref(DRE);
        }
    }

private:
//    Rewriter &OurRewriter;
    DeclRefMapping *DeclRefMap;

};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter) :
            DeclRefMap(new DeclRefMapping(&Context)), VDT(OurRewriter),
            DRT(OurRewriter, DeclRefMap.get()), DRMB(DeclRefMap.get())  {


        DeclarationMatcher DeclRefMapDeclarationMatcher = varDecl().bind("varDecl");
        StatementMatcher DeclRefMapStatementMatcher = anyOf(
                declStmt().bind("declStmt"),
                declRefExpr().bind("declRefExpr"));

        /**
         * Matches control structures (if / for / while / switch) declaring their own control vars.
         * Only match single declarations for now...
         *
         * outer: the matched control structure
         * inner: the matched varDecl
         */
        StatementMatcher InitStatementVarDeclMatcher =
                anyOf(
                        ifStmt(hasConditionVariableStatement(declStmt(hasSingleDecl(varDecl().bind("inner"))))).bind("outer"),
                        forStmt(hasLoopInit(declStmt(hasSingleDecl(varDecl().bind("inner"))))).bind("outer")
                        // TODO: Find out why this doesnt work
                        //whileStmt(hasCondition(declStmt(hasSingleDecl(varDecl().bind("inner"))))).bind("outer")
                        //whileStmt(hasCondition(expr(hasParent(varDecl().bind("inner"))))).bind("outer")
                        //whileStmt(hasCondition(hasParent(declStmt(hasSingleDecl(varDecl().bind("inner")))))).bind("outer")
                );

        /**
         * Matches control structures (if / for / while / switch) referencing control vars defined beforehand.
         *
         * outer: the matched control structure
         * inner: the matched declRef
         */
        StatementMatcher InitStatementDeclRefMatcher =
//                anyOf(
                        forStmt(hasLoopInit(binaryOperator(hasOperatorName("="),
                                hasLHS(ignoringParenImpCasts(declRefExpr(to(
                                        varDecl().bind("initVarDecl")))
                                        .bind("initVarDeclRef"))),
                                hasRHS(expr()))))
                        .bind("scope");//,

//                        whileStmt(hasCondition(ignoringParenImpCasts(
//                                declRefExpr(to(
//                                        varDecl().bind("initVarDecl")))
//                                .bind("initVarDeclRef"))))
//                        .bind("scope")
//                      );

        // TODO: Add more Matchers (if, ... )

        // Register callbacks used to build declrefmapping
        PreMatcher.addMatcher(DeclRefMapDeclarationMatcher, &DRMB);
        PreMatcher.addMatcher(DeclRefMapStatementMatcher, &DRMB);

        // Register the appropriate callback, based on our option
        if (StrategyOpt.getValue() == move_out_decls) {
            Matcher.addMatcher(InitStatementVarDeclMatcher, &VDT);
        } else if (StrategyOpt.getValue() == move_in_decls) {
            Matcher.addMatcher(InitStatementDeclRefMatcher, &DRT);
        }

    }


    void HandleTranslationUnit(ASTContext &Context) override {
        PreMatcher.matchAST(Context);
        Matcher.matchAST(Context);
    }



private:
    MatchFinder PreMatcher;
    MatchFinder Matcher;

    std::unique_ptr<DeclRefMapping> DeclRefMap;

    InitStatementVarDeclTransformer VDT;
    InitStatementDeclRefTransformer DRT;
    DeclRefMappingBuilder DRMB;


};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}
