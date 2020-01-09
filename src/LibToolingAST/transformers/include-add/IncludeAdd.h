#ifndef AUTHORSHIP_EVASION_INCLUDEADD_H
#define AUTHORSHIP_EVASION_INCLUDEADD_H

#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm::cl;
using namespace clang;

class IncludeCollector : public PPCallbacks {

public:
  explicit IncludeCollector(
      const CompilerInstance &CI,
      std::vector<std::pair<llvm::StringRef, SourceLocation>> *Includes)
      : CI(CI), Includes(Includes) {}

  void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok,
                          StringRef FileName, bool IsAngled,
                          CharSourceRange FilenameRange, const FileEntry *File,
                          StringRef SearchPath, StringRef RelativePath,
                          const Module *Imported) override;

private:
  const CompilerInstance &CI;
  std::vector<std::pair<llvm::StringRef, SourceLocation>> *Includes;
};

class IncludeAddAction : public PreprocessOnlyAction {
protected:
  void ExecuteAction() override;

private:
  std::vector<std::pair<llvm::StringRef, SourceLocation>> Includes;
};

#endif // AUTHORSHIP_EVASION_INCLUDEADD_H
