#ifndef LIBTOOLINGAST_IOSTREAMREWRITER_H
#define LIBTOOLINGAST_IOSTREAMREWRITER_H

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

#include "../../utils_transform.h"
#include "../../ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../../ControlDataFlow/CDFGraphQueryHandler.h"

using namespace clang;
//#define MYDEBUG 1

/**
 * Input / Output Interface Transformer: Stdin/Stdout option.
 * A class that can be used by input or output transformer to transform an ifstream or ofstream into
 * a respective cin or cout command.
 */
class InterfaceStdinOutRewriter {

public:
    explicit InterfaceStdinOutRewriter(ASTContext &Context, Rewriter &OurRewriter, ControlFlowGraphWithDataFlow* cfggraph,
        std::string &cinorcout);

    /**
     * Transform an ifstream command into a cin command.
     * @param e the respective CXXConstructExpr with input stream
     * @param inputexpr a list of all input expressions in source code. necessary to check if rewriting impacts..
     * @return true if transformation was successful
     */
    bool transformIfStream(const CXXConstructExpr* e, std::vector<const Expr*> inputexpr);

private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;
    ControlFlowGraphWithDataFlow *cfggraph;

    // specify if we aim at a cin or cout command, pass the value as we should replace it, with or without 'std'
    std::string &cinorcout;
    // will be deduced automatically, if << or >>
    std::string streamarrows;

    /**
     * Internal helper to choose the necessary rewriting depending on the current usage in code..
     * @param curdeclrefexpr
     * @return a tuple with a. the source range that we want to replace, b. the new string that will be inserted
     */
    std::tuple<SourceRange, std::string> getRewritingForCXXConstructExprRef(const DeclRefExpr* curdeclrefexpr);

};


#endif //LIBTOOLINGAST_IOSTREAMREWRITER_H
