#include "ReturnStatementTransform.h"
#include "ReplaceLiteral.h"
#include "AddReturn.h"
#include "StatusCodes.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"

using namespace std;

unique_ptr<ASTConsumer> ReturnStmtTransformationAction::newASTConsumer() {
  if (Strategy == Strategies::S_IntLiteral)
    return llvm::make_unique<ReplaceLiteralASTConsumer>(FileToReplaces, Seed);
  else if (Strategy == Strategies::S_AddReturnStmt)
    return llvm::make_unique<AddReturnStatementASTConsumer>(FileToReplaces, Seed);
  else {
    return llvm::make_unique<ReplaceLiteralASTConsumer>(FileToReplaces, Seed);
  }
}

int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  RefactoringTool Tool(OptionsParser.getCompilations(),
                       OptionsParser.getSourcePathList());
  ReturnStmtTransformationAction TransformAction(Tool.getReplacements());
  auto Factory = tooling::newFrontendActionFactory(&TransformAction);

  int ExitCode;
  ExitCode = Tool.run(Factory.get());
  if (Tool.getReplacements().empty()) {
    return TRANSFORMATION_NOT_APPLICABLE;
  }

  LangOptions DefaultLangOptions;
  IntrusiveRefCntPtr<DiagnosticOptions> DiagOpts = new DiagnosticOptions();
  TextDiagnosticPrinter DiagnosticPrinter(llvm::errs(), &*DiagOpts);
  DiagnosticsEngine Diagnostics(
      IntrusiveRefCntPtr<DiagnosticIDs>(new DiagnosticIDs()), &*DiagOpts,
      &DiagnosticPrinter, false);
  SourceManager Sources(Diagnostics, Tool.getFiles());
  Rewriter Rewrite(Sources, DefaultLangOptions);
  tooling::formatAndApplyAllReplacements(Tool.getReplacements(), Rewrite,
                                         Style);

  if (Inplace) {
    ExitCode = Rewrite.overwriteChangedFiles();
  } else {
    for (const auto &File : OptionsParser.getSourcePathList()) {
      const auto *Entry = Tool.getFiles().getFile(File);
      const auto ID = Sources.getOrCreateFileID(Entry, SrcMgr::C_User);
      Rewrite.getEditBuffer(ID).write(llvm::outs());
    }
  }
  return ExitCode;
}