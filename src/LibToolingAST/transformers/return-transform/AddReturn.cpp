#include "AddReturn.h"
#include "RandomHelper.h"
#include "SourceTextHelper.h"
#include <sstream>

void AddReturnMatchHandler::run(const MatchFinder::MatchResult &Result) {
  auto &SM = Result.Context->getSourceManager();
  auto &LO = Result.Context->getLangOpts();
  if (const auto *Func = Result.Nodes.getNodeAs<FunctionDecl>("main")) {
    if (!SM.isInMainFile(Func->getLocStart()))
      return;

    if (const auto CS = dyn_cast<CompoundStmt>(Func->getBody())) {

      if (!CS->body_empty() && isa<ReturnStmt>(CS->body_back())) {
        return;
      }

      stringstream sstream;
      sstream << "{";
      for (const auto S : CS->body()) {
        sstream << getSourceText(S, SM, LO).str();
      }
      sstream << "return 0;"
              << "}";
      Replacement Replace(SM, getCharSourceRange(CS, SM, LO), sstream.str(),
                          LO);
      Replaces.push_back(Replace);
    }
  }
}

void AddReturnStatementASTConsumer::HandleTranslationUnit(ASTContext &Ctx) {
  MatchFinder Finder;
  AddReturnMatchHandler Handler;
  Finder.addMatcher(functionDecl(hasName("main")).bind("main"), &Handler);
  Finder.matchAST(Ctx);

  auto Replaces = Handler.getReplaces();
  if (!Replaces.empty()) {
    const auto &Replace = select_randomly(Replaces, Seed.getValue());
#ifdef MYDEBUG
    llvm::dbgs() << "Applying replacement " << Replace.toString() << "\n";
#endif
    llvm::Error Err = FileToReplaces[Replace.getFilePath()].add(Replace);
    if (Err) {
//#ifdef MYDEBUG
      llvm::errs() << "Transformation failed in " << Replace.getFilePath()
                   << "! " << llvm::toString(move(Err)) << "\n";
//#endif
      llvm::errs() << "Code 123: No transformations possible\n";
    }
  } else {
#ifdef MYDEBUG
    llvm::dbgs() << "Transformation not applicable"
                 << "\n";
#endif
    llvm::errs() << "Code 123: No transformations possible\n";
  }
}
