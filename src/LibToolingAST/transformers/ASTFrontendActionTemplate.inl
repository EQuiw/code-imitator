#ifndef ASTFRONTENDACTION_TEMPLATE
#define ASTFRONTENDACTION_TEMPLATE

#include "llvm/Support/CommandLine.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

using namespace clang;

//#define OVERWRITE 1

/**
 * A Template for ASTFrontendAction, just used so that we do not write the same code over and over.
 * This class is actually a standard way that we have to use to construct the whole AST based on clang.
 * Until we get to 'RecursiveASTVisitor', we have to go the way from the 'main()' to 'ASTFrontendAction' to
 * 'ASTConsumer' and arrive at 'RecursiveASTVisitor'.
 * T should be the a concrete ASTConsumer. For instance, look at the file: consoleoutput_transformer.cpp,
 * there we've created an ASTFrontendAction with T = MyASTConsumer that was defined in the same file.
 * @tparam T a concreate ASTConsumer
 */
template<typename T>
class MyFrontendAction : public ASTFrontendAction {
public:

    void EndSourceFileAction() override {
        // I. Now emit the rewritten buffer to stdout:
        {
            OurRewriter.getEditBuffer(OurRewriter.getSourceMgr().getMainFileID()).write(llvm::outs());
//            llvm::outs() << "\n";
        }
        // II. Or inplace modification
#ifdef OVERWRITE
        OurRewriter.overwriteChangedFiles();
#endif
        // III. Write to new file
        {
//            std::error_code error_code;
//            llvm::raw_fd_ostream outFile("output_while.cpp", error_code, llvm::sys::fs::F_None);
//            OurRewriter.getEditBuffer(OurRewriter.getSourceMgr().getMainFileID()).write(outFile);
//            outFile.close();
        }
    }

    std::unique_ptr<ASTConsumer>
    CreateASTConsumer(CompilerInstance &Compiler, llvm::StringRef InFile) override {
        OurRewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());

        // TODO use string file information for better error msg's... ?!
        // std::string s = InFile;
        // s = split_path(s)[1]
        return std::unique_ptr<ASTConsumer>(new T(Compiler.getASTContext(), OurRewriter));
    }

private:
    Rewriter OurRewriter;
};

#endif // ASTFRONTENDACTION_TEMPLATE