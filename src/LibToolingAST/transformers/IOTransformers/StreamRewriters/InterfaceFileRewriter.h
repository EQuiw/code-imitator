#ifndef LIBTOOLINGAST_INTERFACEFILEREWRITER_H
#define LIBTOOLINGAST_INTERFACEFILEREWRITER_H

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
#include "../utils_io_transformers.h"
#include "../../RenamingGuide.h"

#include "../../ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../../ControlDataFlow/CDFGraphQueryHandler.h"

using namespace clang;
//#define MYDEBUG 1



/**
 *
 * Input / Output Interface Transformer: File Option.
 */
class InterfaceFileRewriter {

public:
    explicit InterfaceFileRewriter(ASTContext &Context, Rewriter &OurRewriter, ControlFlowGraphWithDataFlow* cfggraph,
    bool stdoutmode);

    bool transformCoutToOfIfstream(std::vector<const Expr*> interface_expressions,
                                 std::vector<std::string> alldeclarationnames,
                                 std::vector<UsingDirectiveDecl*> usedNamespaces,
                                 Decl* firstDeclInSrcFile,
                                 std::string stream_type
    );

    std::string newvariablename;

private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;
    ControlFlowGraphWithDataFlow *cfggraph;

    // standard name proposals for the new of/if-stream object
    std::vector<std::string> commonnameproposals;

    // will be deduced automatically, if << or >>
    std::string streamarrows;

};


#endif //LIBTOOLINGAST_INTERFACEFILEREWRITER_H
