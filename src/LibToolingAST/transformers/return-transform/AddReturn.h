#ifndef AUTHORSHIP_EVASION_ADDRETURN_H
#define AUTHORSHIP_EVASION_ADDRETURN_H

#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/Core/Replacement.h"
#include "llvm/Support/CommandLine.h"

using namespace std;
using namespace llvm::cl;
using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

class AddReturnMatchHandler : public MatchFinder::MatchCallback {
public:
  void run(const MatchFinder::MatchResult &Result) override;

  const vector<Replacement> &getReplaces() const { return Replaces; }

private:
  vector<Replacement> Replaces;
};

class AddReturnStatementASTConsumer : public ASTConsumer {
public:
  explicit AddReturnStatementASTConsumer(map<string, Replacements> &FileToReplaces,
                                     opt<int> &Seed)
      : FileToReplaces(FileToReplaces), Seed(Seed) {}

  void HandleTranslationUnit(ASTContext &Ctx) override;

private:
  map<string, Replacements> &FileToReplaces;
  opt<int> &Seed;
};

#endif //AUTHORSHIP_EVASION_ADDRETURN_H
