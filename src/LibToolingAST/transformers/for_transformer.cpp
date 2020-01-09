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

#include "utils_transform.h"
#include "../Utilities/Utils.h"
#include "ASTFrontendActionTemplate.inl"
#include "ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "ControlDataFlow/CDFGraphQueryHandler.h"
#include "include/SourceTextHelper.h"

static llvm::cl::OptionCategory MyOptionCategory("For-Loop Transformer");
static llvm::cl::opt<int> OurCMDOption1("seed", llvm::cl::cat(MyOptionCategory));

using namespace clang;

// Comment out if not needed; just for debugging.
//#define MYDEBUG 1

/**
 * Rewrites a for statement into a while statement.
 */
class ForTransformer : public RecursiveASTVisitor<ForTransformer> {
public:

    ControlFlowGraphWithDataFlow *cfggraph;
    explicit ForTransformer(ASTContext &Context, Rewriter &ForStmtRewriter) : Context(Context),
                                        ForStmtRewriter(ForStmtRewriter), SM(Context.getSourceManager()) {
        cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~ForTransformer(){
        delete cfggraph;
    }

    /**
     * Visit all functions and store them in CFG graph.
     * @param f
     * @return
     */
    bool VisitFunctionDecl(FunctionDecl *f) {
        bool inmainfile = SM.isInMainFile(f->getLocation());
        if (inmainfile) {
            cfggraph->addFunctionDecl(f);
        }
        return true;
    }

    /**
     * Collects all for stmts.
     * @param S
     * @return
     */
    bool VisitForStmt(ForStmt *fct) {
        auto srcloc = fct->getLocStart();
        if(SM.isWrittenInMainFile(srcloc)){
            forstmts.push_back(fct);
        }
        return true;
    }

    /**
     * Selects a for stmt that will be replaced by a while stmt.
     */
    void replacecommand(int seed) {

        bool succ = false;
        randomlySortVector<ForStmt*>(this->forstmts, seed);
        for (auto fo : this->forstmts) {
            if (rewriteForStmt(fo)){
                succ = true;
                break;
            }
        }

        if(!succ)
            llvm::errs() << "Code 123: No transformations possible\n";
    };


    /**
     * Replaces the selected for stmt by a while stmt.
     * @param ForStatement
     * @return true if replacement was successful.
     */
    bool rewriteForStmt(ForStmt *ForStatement) {

        #ifdef MYDEBUG
        llvm::errs() << "Will rewrite for-stmt at row" << getRowColumn(ForStatement->getLocStart(), SM, false).first
                     << " with:" << getSourceText(Context, ForStatement, false) << "\n**********\n";
        #endif

        Stmt *_Body = ForStatement->getBody();
        if (!_Body) return true;
        Stmt *Init = ForStatement->getInit();
        Expr *Cond = ForStatement->getCond();
        Expr *Inc = ForStatement->getInc();

//            llvm::errs() << getSourceText(S) << "\n";
        // TODO check if we need to open a new scope.

        ptrdiff_t _diff =
                SM.getCharacterData(_Body->getLocStart()) -
                SM.getCharacterData(ForStatement->getLocStart()) - 1;
        auto diff = (unsigned int) _diff;

        std::string lbrace;
        std::string rbrace;
        SourceLocation End;
        unsigned offs;
        if (!isa<CompoundStmt>(_Body)) {
            // Is not a for stmt with code block { ... }?
            // If we have a for stmt in one line, we need to add braces for the while statement.
            lbrace = "{";
            rbrace = "}";

            // Small workaround, since source location matches the token and not ";" -- so we need the following:
            SourceLocation _End(_Body->getLocEnd());
            offs = Lexer::MeasureTokenLength(_End, SM, Context.getLangOpts());
            End = Lexer::getLocForEndOfToken(_End, 0, SM, Context.getLangOpts()); 
            offs = 1;
        } else {
            // Is a for stmt without code block = one line of code?
            // We use the RBracLoc info because otherwise we would set the incr stmt
            // at the end of the body, but after the } brace.
            End = cast<CompoundStmt>(_Body)->getRBracLoc();;
            offs = 0;
        }

        /* ** Rewriting. ** */
        // Execute all commands first that ensure that rewriting will succeed, then rewrite, otherwise, we may
        // cancel the process, but we may have rewritten something.

        // if we needed to define a new scope, add } for closing this scope
        if(Init)
            rbrace += "}";

        // Insert the increment statement. First, of course, at the end of the new while-block,
        // but also at continue statements since we can continue the while-stmt before reaching the end of while.
        std::string inctext;
        if (Inc) {
            if(!dealwithcontinuestmts(ForStatement))
                return false;

            inctext = getSourceText(Context, Inc, false) + ";" + "" + "\t";
        }
        ForStmtRewriter.InsertTextAfter(End.getLocWithOffset(offs), inctext + rbrace); //rbrace

        if (Init) {
            ForStmtRewriter.InsertText(ForStatement->getLocStart(), "{\n" + getSourceText(Context, Init, true) + "\n",
                                       false, true);
        }

        if (Cond) {
            ForStmtRewriter.ReplaceText(ForStatement->getLocStart(), diff,
                                        "while (" + getSourceText(Context, Cond, false) + ")" + lbrace + "\n");
        } else {
            ForStmtRewriter.ReplaceText(ForStatement->getLocStart(), diff,
                                        "while (1)" + lbrace + "\n");
        }

        return true;
    }

private:
    ASTContext &Context;
    Rewriter &ForStmtRewriter;
    SourceManager &SM;

    std::vector<ForStmt*> forstmts;

    /**
     * We need to insert the Inc stmt at each continue stmt, since in a for loop, we would continue to the Inc stmt.
     * But in a while stmt, the Inc Stmt is at the end.
     *
     * Moreover, we only need to modify the continue statements that belong to the current for-loop. Imagine there are
     * two for loops in each other, and the continue stmt is in the inner loop. If we modify the outer for loop, we
     * do not need to change the continue stmt, since it belongs to the inner loop.
     *
     * Moreover, if we insert the Inc stmt, we have to check if we need to add curly braces, since the continue stmt
     * could be a single-line stmt after e.g. an if-stmt without { ... }.
     * @param ForStatement -- the for statement where we look out for continues
     * @return true if everything is fine.
     */
    bool dealwithcontinuestmts(ForStmt* ForStatement) {
        Stmt *_Body = ForStatement->getBody();
        Expr *Inc = ForStatement->getInc();

        // Find all continue stmt's
        std::vector<const ContinueStmt*> continues;
        recursiveStmtTVisit<ContinueStmt>(_Body, continues);

        if(!continues.empty()){
            // check for each continue stmt, if parent is a compound stmt, if so, we can directly add Inc,
            // otherwise we need to add curly braces.
            for(unsigned i = 0; i < continues.size(); i++){

                // First, use the CFG to find the loop to which this continue stmt belongs.
                try{
                    auto loopstmt = ControlDataFlowGraphQueryHandler::findLoopStmtAfterContinueStmt(this->cfggraph, continues[i]);
                    if(loopstmt != ForStatement){
                        continue;
                    }
                } catch(CFGException& ex) {
                    llvm::errs() << "Error: Could not determine loop stmt for a continue stmt\n";
                    llvm::errs() << getSourceText(Context, ForStatement, false) << "\n";
                    return false;
                }


                // Check first, go one level above, save all CompoundStmt's, if not empty, we do not need any {}
                std::vector<const CompoundStmt*> clist;
                ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*continues[i]);
                goUpstairsInAST<CompoundStmt>(dtn, clist, 1, &Context);

                std::string lcontinuebracket, rcontinuebracket;
                if(clist.empty()){
                    lcontinuebracket = "{ ";
                    rcontinuebracket = " }";
                }

                // Now rewrite
                auto srcrange = getSourceRange(continues[i], SM, Context.getLangOpts());
                ForStmtRewriter.ReplaceText(srcrange, lcontinuebracket + getSourceText(Context, Inc, false)
                                                      + "; continue;" + rcontinuebracket);

//                ForStmtRewriter.InsertTextBefore(continues[i]->getLocStart(),
//                                                 lcontinuebracket + getSourceText(Context, Inc, false) + "; ");
//                // Get the end location after the semi-colon:
//                SourceLocation End(Lexer::getLocForEndOfToken(continues[i]->getLocEnd(), 0, SM, Context.getLangOpts()));
//                ForStmtRewriter.InsertTextAfter(End.getLocWithOffset(1), rcontinuebracket);
            }
        }
        return true;
    }

};



class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &ForStmtRewriter) : Visitor(Context, ForStmtRewriter) {}

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        auto seed = static_cast<int>(OurCMDOption1.getValue());
        Visitor.replacecommand(seed);
    }

private:
    ForTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}