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
#include "include/SourceTextHelper.h"
#include "../Utilities/Utils.h"
#include <string>
#include "ASTFrontendActionTemplate.inl"


using namespace clang;
//#define MYDEBUG 1


static llvm::cl::OptionCategory MyOptionCategory("CompoundStmt Curly Braces Transformer");

static llvm::cl::opt<int> OurCMDOption1("strategy", llvm::cl::cat(MyOptionCategory));
static llvm::cl::opt<int> OurCMDOption2("seed", llvm::cl::cat(MyOptionCategory));

enum Strategy {add_curly_braces = 1, remove_curly_braces = 2};


/**
 * This transformer deals with curly braces. If a statement has no curly braces, as it is a single stmt,
 * then we can add curly braces again. The other way round as well: If a statement has curly braces, but is just
 * a single stmt, then we can remove the curly braces.
 *  For example, take
 *      while(x--)
 *          printf(...)
 *  can be transformed to
 *      while(x--) {
 *          printf(...)
 *      }
 */
class CompoundStmtTransformer : public RecursiveASTVisitor<CompoundStmtTransformer> {
public:

    explicit CompoundStmtTransformer(ASTContext &Context, Rewriter &OurRewriter)
            : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()) {
    }

    /* ******************* Collection Methods ******************* */

    /**
     * Save stmt's that can be rewritten.
     * @param s
     * @return
     */
    bool VisitStmt(Stmt *s){
        bool inmainfile = sm.isInMainFile(s->getLocStart());
        if (inmainfile) {

            // Check if we have a if-stmt.
            if(auto ifs = dyn_cast<IfStmt>(s)) {

                addifrewritable(ifs->getThen());
                if (ifs->getElse())
                    addifrewritable(ifs->getElse());

                // Check if we have other control stmt's
            } else if(auto fors = dyn_cast<ForStmt>(s)){
                addifrewritable(fors->getBody());
            } else if(auto whiles = dyn_cast<WhileStmt>(s)){
                addifrewritable(whiles->getBody());
            } else if(auto dos = dyn_cast<DoStmt>(s)){
                addifrewritable(dos->getBody());
            } else if(auto forscxx = dyn_cast<CXXForRangeStmt>(s)){
                addifrewritable(forscxx->getBody());
            }
        }
        return true;
    }

    /* ******************* Rewriting Methods ******************* */

    void replacecommand(Strategy strategy, int seed) {

        assert(strategy==add_curly_braces || strategy==remove_curly_braces);

        #ifdef MYDEBUG
        for(auto cs : stmtswithaddablebraces){
            llvm::outs() << "Add Stmt:" << getSourceText(Context, cs, false) << "\n";
        }
        for(auto cs : stmtswithremovablebraces){
            llvm::outs() << "Rem Stmt:" << getSourceText(Context, cs, false) << "\n";
        }
        #endif

        switch(strategy) {
            case add_curly_braces:
                randomlySortVector<Stmt*>(stmtswithaddablebraces, seed);
                for(auto s : stmtswithaddablebraces){
                    if(addcurlybraces(s))
                        return;
                }
                break;
            case remove_curly_braces:
                randomlySortVector<Stmt*>(stmtswithremovablebraces, seed);
                for(auto s : stmtswithremovablebraces){
                    if(removecurlybraces(s))
                        return;
                }
        }

        llvm::errs() << "Code 123: No transformations possible\n";
    };


private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    // all stmts where we can add { } to create a compound stmt
    std::vector<Stmt*> stmtswithaddablebraces;
    // all stmts where we could remove the curly braces to remove a compound stmt
    std::vector<Stmt*> stmtswithremovablebraces;


    /**
     * Adds stmt to list of rewritable stmts if we can add or remove curly braces.
     * @param s
     */
    void addifrewritable(Stmt *s) {
        // A. Check where we could add curly braces.
        if (!isa<CompoundStmt>(s))
            stmtswithaddablebraces.push_back(s);

        // B. Check where we could remove curly braces, must be a single-line command
        // to this end, we simply check if the row number of the end differs by 2.
        // We exploit that clang-format will put the stmt's into a new row, the closing bracket in another new row.
        if (auto sc = dyn_cast<CompoundStmt>(s)) {
            auto rowcolstart = getRowColumn(sc->getLocStart(), sm, false);
            auto rowcolend = getRowColumn(sc->getLocEnd(), sm, false);
            if (rowcolstart.first == (rowcolend.first - 2)){
                // Moreover, check that body is not empty, e.g. if (bla) { } else ... would become
                // if (bla) else ... which would lead to an error
                if(!sc->body_empty())
                    stmtswithremovablebraces.push_back(s);
            }

        }
    }

    /**
     * Adds curly braces around a stmt.
     * @param s
     * @return
     */
    bool addcurlybraces(Stmt* s) {

        std::string srctext = getSourceText(s, sm, Context.getLangOpts());
        #ifdef MYDEBUG
        llvm::errs() << "Try Stmt:" << srctext << "\n";
        #endif

        OurRewriter.ReplaceText(getSourceRange(s, sm, Context.getLangOpts()), "{ " + srctext + " }");

//        OurRewriter.InsertTextBefore(s->getLocStart(), "{ ");
//        // Consider semicolon
//        SourceLocation End(Lexer::getLocForEndOfToken(s->getLocEnd(), 0, sm, Context.getLangOpts()));
//
//        // getOffset until newline -- we know that because clang-format will introduce a new line
//        // where we want to place a closing curly brace
//        int offs = 0;
//        for(unsigned of = 0; of <= 5; of++){
//            std::string t = getSourceText(Context, s->getLocStart(), End.getLocWithOffset(of));
//            llvm::outs() << "S:" << t << ":" << t.back() << "\n";
//            if(t.back() == '\n'){
//                offs = of;
//                break;
//            }
//        }
//        OurRewriter.InsertTextAfter(End.getLocWithOffset(offs), "}");

        return true;
    }

    /**
     * Removes the curly braces around a stmt.
     * @param s
     * @return
     */
    bool removecurlybraces(Stmt* s) {

        if(auto sc = dyn_cast<CompoundStmt>(s)){
            // get src without curly braces.
            std::string srctext = getSourceText(Context, sc->getLBracLoc().getLocWithOffset(1),
                                                sc->getRBracLoc().getLocWithOffset(-1));
            OurRewriter.ReplaceText(sc->getSourceRange(), srctext);
            return true;
        } else {
            llvm::errs() << "Stmt where we wanted to remove curly braces is not a compound stmt\n";
            return false;
        }
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
    CompoundStmtTransformer Visitor;
};

int main(int argc, const char **argv) {
    OurCMDOption1.setInitialValue(add_curly_braces);
    OurCMDOption1.setDescription("Transformation strategy");
    OurCMDOption1.setDescription("PRNG seed");
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}
