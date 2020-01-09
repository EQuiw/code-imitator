#include "IncludeList.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace llvm::cl;
using namespace clang;
using namespace clang::tooling;

void IncludePrinter::InclusionDirective(
    SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName,
    bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File,
    StringRef SearchPath, StringRef RelativePath, const Module *Imported) {

  const auto &SM = CI.getSourceManager();

  if (!SM.isInMainFile(HashLoc)) {
    return;
  }

  // Check filename. Includes added via `-include` pass the `isInMainFile` check
  // but have filename "<built-in>". We have to skip those includes because they
  // are not part of the source code.
  if (HashLoc.isFileID()) {
    std::string fname(SM.getPresumedLoc(HashLoc).getFilename());
    if (fname == "<built-in>") {
      return;
    }
  }

  if (IsAngled) {
    llvm::outs() << "#include"
                 << " "
                 << "<" << FileName.str() << ">"
                 << "\n";
  } else {
    llvm::outs() << "#include"
                 << " "
                 << "\"" << FileName.str() << "\""
                 << "\n";
  }
}

void IncludeListAction::ExecuteAction() {
  const auto &CI = getCompilerInstance();
  std::unique_ptr<IncludePrinter> Printer(new IncludePrinter(CI));

  CI.getPreprocessor().addPPCallbacks(std::move(Printer));

  PreprocessOnlyAction::ExecuteAction();
}

int main(int argc, const char *argv[]) {
  CommonOptionsParser optionsParser(argc, argv, MyToolCategory);
  ClangTool tool(optionsParser.getCompilations(),
                 optionsParser.getSourcePathList());

  return tool.run(newFrontendActionFactory<IncludeListAction>().get());
}
