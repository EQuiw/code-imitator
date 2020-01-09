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

#include "io_transformer.cpp"
#include "../utils_transform.h"
#include "../ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../ControlDataFlow/CDFGraphQueryHandler.h"

using namespace clang;
//#define MYDEBUG 1


/**
 * A transformer to rewrite *input stream* c-style expressions such as scanf, getchar
 * into a c++-style such as cin, ifstream or the other way round.
 * In principle, the structure of the input stream transformers are similar to the ouput stream transformers.
 * This class contains methods that are relevant to the transformation from c to c++ style and from c++ to c style.
 * Then, each style direction has its own class to get a better code overview.
 *
 */
class InputTransformer : public IOTransformer {
public:

    // Here, we set what streams are considered to be checked if streams are mixed due to sync_with_stdio.
    sync_with_stdio_channels sync_mode = sync_input_only;

    explicit InputTransformer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
            : IOTransformer(Context, OurRewriter, prepinfos) {}

};
