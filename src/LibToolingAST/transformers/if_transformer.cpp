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
#include <string>
#include "ASTFrontendActionTemplate.inl"
//#include "ControlDataFlow/ControlFlowGraphWithDataFlow.h"
//#include "ControlDataFlow/CDFGraphQueryHandler.h"


using namespace clang;
//#define MYDEBUG 1


static llvm::cl::OptionCategory MyOptionCategory("If Stmt Transformer");

static llvm::cl::opt<int> OurCMDOption1("strategy", llvm::cl::cat(MyOptionCategory));
static llvm::cl::opt<int> OurCMDOption2("seed", llvm::cl::cat(MyOptionCategory));


enum Strategy {split_if_strategy = 1};


// TODO We thus should combine || transformation with fctcreator to prevent the same body.

/**
 * We split if-commands if there are multiple conditions and there is no else block,
 * or we try to simplify if-commands. TODO simplify
 */
class IfTransformer : public RecursiveASTVisitor<IfTransformer> {
public:

//    ControlFlowGraphWithDataFlow *cfggraph;

    explicit IfTransformer(ASTContext &Context, Rewriter &OurRewriter)
            : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()) {
//        cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~IfTransformer(){
//        delete cfggraph;
    }
    /* ******************* Collection Methods ******************* */

    /**
     * Visit all functions and store them in CFG graph.
     * @param f
     * @return
     */
//    bool VisitFunctionDecl(FunctionDecl *f) {
//        bool inmainfile = sm.isInMainFile(f->getLocation());
//        if (inmainfile) {
//            cfggraph->addFunctionDecl(f);
//        }
//        return true;
//    }

    /**
     * Save if-stmts that can be rewritten.
     * @param s
     * @return
     */
    bool VisitIfStmt(IfStmt *ifs){
        bool inmainfile = sm.isInMainFile(ifs->getLocStart());
        if (inmainfile) {

            if(!ifs->getElse() && checkformultipleconditions(ifs)){
                // if no else block, and at least two conditions combined by && or ||, we can split it.
                ifstatements.push_back(ifs);
            }
        }
        return true;
    }

    /* ******************* Rewriting Methods ******************* */

    void replacecommand(Strategy strategy, int seed) {

        assert(strategy==split_if_strategy);

        randomlySortVector<IfStmt*>(ifstatements, seed);
        switch(strategy) {
            case split_if_strategy:
                for(auto s : ifstatements){
                    if(splitif(s))
                        return;
                }
                break;
        }

        llvm::errs() << "Code 123: No transformations possible\n";
    };


private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    std::vector<IfStmt*> ifstatements;


    /**
     * Checks if if-stmt has multiple conditions, combined by && or ||.
     * @param ifs  if-stmt.
     * @return true if so.
     */
    bool checkformultipleconditions(IfStmt* ifs){

        std::vector<const BinaryOperator*> binopsvec;
        recursiveStmtTVisit<BinaryOperator>(ifs->getCond(), binopsvec);

        // the first binop with && or || is the first in the hierachy means we can process the command.
        for(auto binop : binopsvec){
            if(binop->getOpcodeStr() == "&&" || binop->getOpcodeStr() == "||")
                return true;
        }
        return false;
    }

    /**
     * Splits an if-stmt into two if-stmt's.
     * @param ifs  if-stmt.
     * @return true if no problems occured.
     */
    bool splitif(IfStmt* ifs) {

        #ifdef MYDEBUG
        for(auto cif : ifstatements){
            llvm::outs() << "Add If:" << getSourceText(Context, cif, false) << "\n";
        }
        #endif

        // A. Choose the first binary operator in the AST

        // If relevant binary operator is a ||, then
        // we cannot simply split the command into two if-stmts under each other, Take, for instance,
        //        ```if ((x > 2 && x < 10) || z == 0)``` = needs an if else-if command, as || is first evaluated.
        //        ```if ((x > 2 || x < 10) && z == 0)``` = we can create two if commands under each other.
        bool andopcode = true;
        std::vector<const BinaryOperator*> binopsvec;
        recursiveStmtTVisit<BinaryOperator>(ifs->getCond(), binopsvec);

        const BinaryOperator* chosenbinop = nullptr;
        for(auto binop : binopsvec){
            if(binop->getOpcodeStr() == "&&"){
                // We can simply put another if-command above the current.
                chosenbinop = binop;
                break;
            }
            if(binop->getOpcodeStr() == "||"){
                // We need an if ... else if ... branch.... where the second conditions goes into the else-if branch
                // with the same body.
                chosenbinop = binop;
                andopcode = false;
                break;
            }
        }

        // B. Some Checks
        if(!chosenbinop){
            llvm::errs() << "no binary operator with multiple conditions found although should be there\n";
            return false;
        }
        if(!chosenbinop->getLHS() || !chosenbinop->getRHS()){
            llvm::errs() << "no binary operator with multiple conditions found although should be there\n";
            return false;
        }

        // C. Rewriting..
        if(andopcode){
            // C-1 Rewrite. We add the if-stmt above the current if-stmt. In this way, we do not need to add curly braces.
            std::string newifstmt = "if(" + getSourceText(Context, chosenbinop->getLHS(), false) + ")\n";
            OurRewriter.InsertTextBefore(ifs->getLocStart(), newifstmt);
        } else {
            // C-2 We add a new else if stmt under the current if stmt and add the same body there.
            std::string newifstmt = "else if(" + getSourceText(Context, chosenbinop->getLHS(), false) + ")\n" +
                    getSourceText(Context, ifs->getThen(), true);
            // Consider } and ;
            //SourceLocation End(Lexer::getLocForEndOfToken(ifs->getLocEnd(), 0, sm, Context.getLangOpts()));
            unsigned int offs = Lexer::MeasureTokenLength(ifs->getLocEnd(), sm, Context.getLangOpts());
            OurRewriter.InsertTextAfter(ifs->getLocEnd().getLocWithOffset(offs+1), newifstmt);
        }
        OurRewriter.ReplaceText(ifs->getCond()->getSourceRange(), chosenbinop->getRHS()->getSourceRange());

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

        auto strategy = static_cast<Strategy>(OurCMDOption1.getValue());
        auto seed = static_cast<int>(OurCMDOption2.getValue());
        Visitor.replacecommand(strategy, seed);
    }

private:
//    commandlineoption cmdoption;
    IfTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}
