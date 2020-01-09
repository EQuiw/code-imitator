#ifndef LIBTOOLINGAST_INCLUDESORT_H
#define LIBTOOLINGAST_INCLUDESORT_H


#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/Support/CommandLine.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include <sstream>
#include <tuple>

#include "../utils_transform.h"

using namespace llvm::cl;
using namespace std;
using namespace clang;

extern opt<std::string> SortIncludes;


class IncludeCollector : public PPCallbacks {

public:
    explicit IncludeCollector(
            const CompilerInstance &CI,
            std::vector<std::tuple<llvm::StringRef, SourceRange, bool>> *Includes)
            : CI(CI), Includes(Includes) {}

    void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok,
                            StringRef FileName, bool IsAngled,
                            CharSourceRange FilenameRange, const FileEntry *File,
                            StringRef SearchPath, StringRef RelativePath,
                            const Module *Imported) override;

private:
    const CompilerInstance &CI;
    std::vector<std::tuple<llvm::StringRef, SourceRange, bool>> *Includes;
};


class IncludeSortAction : public PreprocessOnlyAction {
protected:
    void ExecuteAction() override;

private:
    std::vector<std::tuple<llvm::StringRef, SourceRange, bool>> Includes;
};


#endif //LIBTOOLINGAST_INCLUDESORT_H
