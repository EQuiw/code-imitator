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
//#include <clang/Analysis/CFG.h>

#include "../Utilities/Utils.h"
#include "utils_transform.h"
#include "ASTFrontendActionTemplate.inl"
#include "ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "ControlDataFlow/CDFGraphQueryHandler.h"

using namespace clang;

static llvm::cl::OptionCategory ToolingSampleCategory("While Transformer");
static llvm::cl::opt<int> OurCMDOption1("seed", llvm::cl::cat(ToolingSampleCategory));

class WhileTransformer : public RecursiveASTVisitor<WhileTransformer> {
public:

//    std::string InFile;
    ControlFlowGraphWithDataFlow *cfggraph;

    explicit WhileTransformer(ASTContext &Context, Rewriter &Rewriter)
            : Context(Context), Rewriter(Rewriter), sm(Context.getSourceManager()) {
        cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~WhileTransformer(){
        delete cfggraph;
    }


    /**
     * Visit all functions and store them in CFG graph.
     * @param f
     * @return
     */
    bool VisitFunctionDecl(FunctionDecl *f) {
        bool inmainfile = sm.isInMainFile(f->getLocation());
        if (inmainfile) {
            cfggraph->addFunctionDecl(f);
        }
        return true;
    }

    /**
     * Save all While Stmt's that have a body. Later we can easily choose a stmt to replace.
     * @param s
     * @return
     */
    bool VisitStmt(Stmt *s) {
        auto srcloc = s->getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){

            if (auto whilestmt = dyn_cast<WhileStmt>(s)) {
                if(whilestmt->getBody())
                    this->whilestatements.push_back(whilestmt);
            }
        }
        return true;
    }

    /**
     * Replace While Stmt by For Stmt.
     */
    void replacewhilestmt(int seed) {

        randomlySortVector<WhileStmt*>(this->whilestatements, seed);
        for(auto w : this->whilestatements){

            if(rewriteWhileStmt(w)){
                return;
            }
        }

        llvm::errs() << "Code 123: No transformations possible\n";
    }




private:
    ASTContext &Context;
    Rewriter &Rewriter;
    SourceManager &sm;

    // Vector to collect all while statements
    std::vector<WhileStmt*> whilestatements;

    /**
     * Rewrites a single while statement into a for statement
     * @param whilestmt the while stmt that we want to transform
     * @return true if rewriting is successful, otherwise false
     */
    bool rewriteWhileStmt(WhileStmt* whilestmt) {

        Stmt *_Body = whilestmt->getBody();
        Expr *Cond = whilestmt->getCond();
        std::string variabledecl;   // init. to empty string "" per default.
        std::string condition;
        std::string increment;

        if(auto *Body = dyn_cast<CompoundStmt>(_Body)){
            // While definition with braces {...}, one-line stmt's not considered, yet.

            // A. Create Init: by using variable in condition
            bool issimplecond = checkIfSimpleCond(Cond, Body);
//            llvm::outs() << "Simple Cond:" << issimplecond <<";"<< getSourceText(Context, whilestmt, true) << "\n";

            if(issimplecond){
                std::vector<const DeclRefExpr*> declrexplist;
                recursiveStmtTVisit<DeclRefExpr>(Cond, declrexplist);
                const DeclRefExpr* dd = declrexplist[0];
                auto ddvardecl = cast<VarDecl>(dd->getFoundDecl());

                // Save type, TODO does not work for case where arbiName(values...);
                auto tyloc = ddvardecl->getTypeSourceInfo()->getTypeLoc();
                std::string vartype = getSourceText(Context, ddvardecl->getLocStart(), tyloc.getLocEnd());
                // Save variable name
                std::string varname = ddvardecl->getQualifiedNameAsString();
                // Save its definition value
                std::string initvalue = getSourceText(Context, ddvardecl->getInit(), false);

                Rewriter.ReplaceText(SourceRange(ddvardecl->getLocStart(), ddvardecl->getLocEnd()),
                                     vartype + " " + varname);
                variabledecl = varname + " = " + initvalue;
            }

            // B. Get condition
            if(Cond) {
                condition = getSourceText(Context, Cond, false);
            }

            // C. TODO get increment statement; we simply let it in the body

            // D. Use everything that was collected
            Rewriter.ReplaceText(SourceRange(whilestmt->getLocStart(), Body->getLBracLoc()),
                                 "for(" + variabledecl + "; " + condition + ";){");
            return true;
        }

        return false;
    }


    bool checkIfSimpleCond(Expr *Cond, CompoundStmt *Body) {
        // we only rewrite a while stmt into a for stmt if
        // - the init stmt is just used for while
        //  - means definition + init before
        //            int i = 0;
        //            while (i < arr.length) { ... i++ }
        // /* becomes */
        //            int i;
        //            for (i = 0; i < arr.length; ) { ... i++ }
        std::vector<const DeclRefExpr*> declrexplist;
        recursiveStmtTVisit<DeclRefExpr>(Cond, declrexplist);

        if(declrexplist.empty()){
            // should occur if we have a condition like while(true)...
            return false;
        } else if(declrexplist.size()>1){
            // TODO better check what variable is used and changed, what is just read.
            // FOr instance, there might be while (n < m) ..., then if m is never read...
//            llvm::outs() << "Note: Multiple DeclRefExpr in Cond.\n";
            return false;
        } else {
            const DeclRefExpr* dd = declrexplist[0];

            if(auto ddn = dyn_cast<VarDecl>(dd->getFoundDecl())) {
                // Check that type is simple
                if (ddn->getType().getDesugaredType(Context).getAsString() != "int"
                    && ddn->getType().getDesugaredType(Context).getAsString() != "unsigned"
                    && ddn->getType().getDesugaredType(Context).getAsString() != "long") {
                    return false;
                }
                // check that it is a simple, local variable
                if (!ddn->isLocalVarDecl() || ddn->isExported() || ddn->isStaticLocal()) {
                    return false;
                }

                // check that it is a declaration with initialization, e.g. int c = 1;
                if(!ddn->hasInit() || !ddn->hasDefinition())
                    return false;

                // ** In the following, check that variable is not used between declaration and while stmt: **

                // Step 1) Get all DeclRefExpr of the declaration behind DeclRefExpr in Condition.
                std::vector<const DeclRefExpr *> declrefexprs =
                        ControlDataFlowGraphQueryHandler::queryAllStmtsForVariable(cfggraph, dd);

                // Step 2) Exclude all DeclRefExpr that are in the body of while stmt: These are not interesting.
                std::vector<const DeclRefExpr*> declreexprinbody;
                recursiveStmtTVisit<DeclRefExpr>(Body, declreexprinbody);
                for(auto sd : declreexprinbody){
                    auto found = std::find(declrefexprs.begin(), declrefexprs.end(), sd);
                    if(found != declrefexprs.end())
                        declrefexprs.erase(found);
                }

                // Step 3) Find out if we can move the initialization into the for loop header <= If variable is not
                // used between definition+init and while condition.
                std::vector<const DeclRefExpr *> matches =
                        ControlDataFlowGraphQueryHandler::queryAllStmtsBetween<Stmt, Decl, DeclRefExpr>(cfggraph, dd, ddn, declrefexprs);

                return (matches.empty());
            }
            return false;
        }
    }


};


class MyASTConsumer : public clang::ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter)
            : Visitor(Context, OurRewriter) {}

    void HandleTranslationUnit(clang::ASTContext &Context) override {
        //      Context.getTranslationUnitDecl()->dump();
        // Traverse through tree and prepare rewriting
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        auto seed = static_cast<int>(OurCMDOption1.getValue());
        Visitor.replacewhilestmt(seed);
    }
private:
    WhileTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser op(argc, argv, ToolingSampleCategory);
    clang::tooling::ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>().get());
}
