#ifndef LLVM_REPLACELITERAL_H
#define LLVM_REPLACELITERAL_H

#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/Core/Replacement.h"
#include "llvm/Support/CommandLine.h"

using namespace std;
using namespace llvm::cl;
using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

class ReplaceLiteralMatchHandler : public MatchFinder::MatchCallback {
public:
  void run(const MatchFinder::MatchResult &Result) override;

  const vector<Replacement> &getReplaces() const { return Replaces; }

private:
  vector<Replacement> Replaces;
};

class ReplaceLiteralASTConsumer : public ASTConsumer {
public:
  explicit ReplaceLiteralASTConsumer(map<string, Replacements> &FileToReplaces,
                                     opt<int> &Seed)
      : FileToReplaces(FileToReplaces), Seed(Seed) {}

  void HandleTranslationUnit(ASTContext &Ctx) override;

private:
  map<string, Replacements> &FileToReplaces;
  opt<int> &Seed;
};

#endif // LLVM_REPLACELITERAL_H
