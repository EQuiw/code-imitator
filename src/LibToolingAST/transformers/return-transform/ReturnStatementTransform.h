#ifndef AUTHORSHIP_EVASION_RETURNSTATEMENTTRANSFORM_H
#define AUTHORSHIP_EVASION_RETURNSTATEMENTTRANSFORM_H

#include "clang/AST/ASTConsumer.h"
#include "clang/Format/Format.h"
#include "llvm/Support/CommandLine.h"

using namespace std;
using namespace llvm::cl;
using namespace clang;
using namespace clang::tooling;

enum Strategies { S_RandomStrategy, S_IntLiteral, S_AddReturnStmt };

static OptionCategory MyToolCategory("return-transform options");
static opt<bool> Inplace("i", desc("Overwrite edited <file>s."),
                         cat(MyToolCategory));
static opt<Strategies> Strategy(
    "strategy", desc("Transformation strategy:"), Required,
    values(clEnumVal(S_IntLiteral, "replace integer literal"),
           clEnumVal(S_AddReturnStmt, "add return statement to main function")),
    cat(MyToolCategory));
static opt<int> Seed("seed", desc("PRNG seed"), init(0), cat(MyToolCategory));
static opt<string> Style("style",
                         desc(clang::format::StyleOptionHelpDescription),
                         init("LLVM"), cat(MyToolCategory));

class ReturnStmtTransformationAction {
public:
  explicit ReturnStmtTransformationAction(
      map<string, Replacements> &FileToReplaces)
      : FileToReplaces(FileToReplaces) {}

  unique_ptr<ASTConsumer> newASTConsumer();

private:
  map<string, Replacements> &FileToReplaces;
};

#endif // AUTHORSHIP_EVASION_RETURNSTATEMENTTRANSFORM_H
