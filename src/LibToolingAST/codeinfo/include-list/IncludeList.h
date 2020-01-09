#ifndef AUTHORSHIP_EVASION_INCLUDELIST_H
#define AUTHORSHIP_EVASION_INCLUDELIST_H

#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm::cl;
using namespace clang;

static OptionCategory MyToolCategory("include-list options");

class IncludePrinter : public PPCallbacks {

public:
  explicit IncludePrinter(const CompilerInstance &CI) : CI(CI) {}

  void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok,
                          StringRef FileName, bool IsAngled,
                          CharSourceRange FilenameRange, const FileEntry *File,
                          StringRef SearchPath, StringRef RelativePath,
                          const Module *Imported) override;

private:
  const CompilerInstance &CI;
};

class IncludeListAction : public PreprocessOnlyAction {
protected:
  void ExecuteAction() override;
};

#endif // AUTHORSHIP_EVASION_INCLUDELIST_H
