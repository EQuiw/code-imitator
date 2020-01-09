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
#include "../../Utilities/Utils.h"
#include "../IOTransformers/utils_io_transformers.h"
#include "../ASTFrontendActionWithPrepTemplate.inl"
#include "output_transformer.cpp"
#include "../include/SourceTextHelper.h"

#include <algorithm>

using namespace clang;
using namespace llvm::cl;


enum Strategy {change_syncwithstdio=1};

// ** These are the command line options **
static llvm::cl::OptionCategory MyOptionCategory("Sync With Stdio Transformer");
static llvm::cl::opt<Strategy> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                           values(clEnumVal(change_syncwithstdio,
                                                            "Add or remove syncwithstdio")),
                                           cat(MyOptionCategory));

/**
 * Adds or remove sync_with_stdio command, based on the fact if
 *  standard C++ streams are synchronized to the standard C streams.
 */
class SyncWithStdioTransformer : public IOTransformer {
public:

    // Here, we set what streams are considered to be checked if streams are mixed due to sync_with_stdio.
    sync_with_stdio_channels sync_mode = sync_both_output_input;

    explicit SyncWithStdioTransformer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos) :
            IOTransformer(Context, OurRewriter, prepinfos) {}

    void replacecommand(Strategy cmdoption) {

        // A. Check TODO check if following two checks are necessary for this transformer
        if((!this->cxxstream_outputexpressions.empty()) &&
           (!this->coutexpressions.empty() || !this->printfexpressions.empty())){
            // we also have a problem now. The author mixed cout's and ofstream, so we do not have a unique stdout.
            // freopen is not necessary to consider...
            llvm::errs() << "Code 900: no unique stdout. mixed cout's/printfs and ofstream \n";
            return;
        }
        if((!this->cxxstream_inputexpressions.empty()) &&
           (!this->cplusplusInputExpressions.empty() || !this->cstyleInputExpressions.empty())){
            // we also have a problem now. The author mixed cin's and ifstream, so we do not have a unique stdin.
            // freopen is not necessary to consider...
            llvm::errs() << "Code 900: no unique stdout. mixed cout's/printfs and ofstream \n";
            return;
        }

        // B. Rewrite
        if(cmdoption==change_syncwithstdio){
            rewrite_syncwithstdio(sync_mode);
            return;
        }

    }

};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
            : Visitor(Context, OurRewriter, prepinfos) {
    }

    void HandleTranslationUnit(ASTContext &Context) override {

        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        Visitor.replacecommand(StrategyOpt.getValue());
    }

private:
    SyncWithStdioTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory
            <MyFrontendActionWithPrep<MyASTConsumer, PreprocessingInfos>>());
}

