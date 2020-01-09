#ifndef ASTFRONTENDACTIONWITHPREP_TEMPLATE
#define ASTFRONTENDACTIONWITHPREP_TEMPLATE

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

using namespace clang;

//#define OVERWRITE 1

/**
 * Custom class that is invoked at each include during preprocessing.
 * in if(inmainfile)...
 * @tparam P
 */
template<typename P>
class IncludePreprocessingCallback : public PPCallbacks
{
public:
    SourceManager &SM;
    P* preprocessingInfos;

    explicit IncludePreprocessingCallback(SourceManager& sm, P *preprocessingInfos)
            : SM(sm), preprocessingInfos(preprocessingInfos) {}

    void InclusionDirective(
            SourceLocation hash_loc,
            const Token &include_token,
            StringRef file_name,
            bool is_angled,
            CharSourceRange filename_range,
            const FileEntry *file,
            StringRef search_path,
            StringRef relative_path,
            const Module *imported)
    {
        // do something with the include
        bool inmainfile = SM.isInMainFile(hash_loc);
        if (inmainfile) {
            preprocessingInfos->headerincludes.push_back(std::pair<std::string, SourceLocation>
                                                                 (file_name, hash_loc));
        }
    }
};

/**
 * A Template for ASTFrontendAction, just used so that we do not write the same code over and over.
 * Look also at ASTFrontendActionTemplate.inl to get more information.
 * In addition to MyFrontendAction from ASTFrontendActionTemplate.inl, we have here preprocessing
 * information. So we either use MyFrontendAction or MyFrontendActionWithPrep as Frontend class.
 * @tparam T a concrete AST consumer.
 * @tparam P a struct where we store preprocessing information.
 */
template<typename T, typename P>
class MyFrontendActionWithPrep : public ASTFrontendAction {
public:

    bool BeginSourceFileAction(CompilerInstance& CI) override {

        prepinfos = new P();
        Preprocessor &PP = CI.getPreprocessor();
        PP.addPPCallbacks(llvm::make_unique<IncludePreprocessingCallback<P>>(CI.getSourceManager(), prepinfos));
//
//        std::unique_ptr<IncludePreprocessingCallback<P>> find_includes_callback(
//                new IncludePreprocessingCallback<P>(CI.getSourceManager(), prepinfos));
//        PP.addPPCallbacks(std::move(find_includes_callback));

        return true;
    }

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

        delete prepinfos;
    }

    std::unique_ptr<ASTConsumer>
    CreateASTConsumer(CompilerInstance &Compiler, llvm::StringRef InFile) override {
        OurRewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());

        return std::unique_ptr<ASTConsumer>(new T(Compiler.getASTContext(), OurRewriter, prepinfos));
    }

private:
    Rewriter OurRewriter;
    P *prepinfos = nullptr;
};

#endif // ASTFRONTENDACTIONWITHPREP_TEMPLATE