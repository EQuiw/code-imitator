#include "../include/SourceTextHelper.h"

using namespace clang;
using namespace clang::tooling;

SourceRange getSourceRange(const Stmt *S, const SourceManager &SM,
                           const LangOptions &LO) {
    SourceLocation LocStart = S->getLocStart();
    SourceLocation LocEnd = S->getLocEnd();
    SourceLocation LocEndEnd = Lexer::getLocForEndOfToken(LocEnd, 0, SM, LO);
    SourceRange Range(LocStart, LocEndEnd);
    return Range;
}

SourceRange getSourceRange(const Expr *S, const SourceManager &SM,
                           const LangOptions &LO) {
    SourceLocation LocStart = S->getLocStart();
    SourceLocation LocEnd = S->getLocEnd();
    SourceLocation LocEndEnd = Lexer::getLocForEndOfToken(LocEnd, 1, SM, LO);
    SourceRange Range(LocStart, LocEndEnd);
    return Range;
}

SourceRange getSourceRange(const Decl *D, const SourceManager &SM,
                           const LangOptions &LO) {
    SourceLocation LocStart = D->getLocStart();
    SourceLocation LocEnd = D->getLocEnd();
    SourceLocation LocEndEnd = Lexer::getLocForEndOfToken(LocEnd, 0, SM, LO);
    SourceRange Range(LocStart, LocEndEnd);
    return Range;
}

CharSourceRange getCharSourceRange(const Stmt *S, const SourceManager &SM,
                                   const LangOptions &LO) {
    return CharSourceRange::getTokenRange(getSourceRange(S, SM, LO));
}

CharSourceRange getCharSourceRange(const Expr *E, const SourceManager &SM,
                                   const LangOptions &LO) {
    return CharSourceRange::getTokenRange(getSourceRange(E, SM, LO));
}

CharSourceRange getCharSourceRange(const Decl *D, const SourceManager &SM,
                                   const LangOptions &LO) {
    return CharSourceRange::getTokenRange(getSourceRange(D, SM, LO));
}

StringRef getSourceText(const Stmt *S, const SourceManager &SM,
                        const LangOptions &LO) {
    return Lexer::getSourceText(getCharSourceRange(S, SM, LO), SM, LO);
}

StringRef getSourceText(const Expr *E, const SourceManager &SM,
                        const LangOptions &LO) {
    return Lexer::getSourceText(getCharSourceRange(E, SM, LO), SM, LO);
}

StringRef getSourceText(const Decl *D, const SourceManager &SM,
                        const LangOptions &LO) {
    return Lexer::getSourceText(getCharSourceRange(D, SM, LO), SM, LO);
}

StringRef getSourceTextStable(const Stmt *S, ASTContext &Context) {
    const SourceManager &sm = Context.getSourceManager();
    auto lo = Context.getLangOpts();
    return getSourceText(S, sm, lo);
}

StringRef getSourceTextStable(const Expr *E, ASTContext &Context) {
    const SourceManager &sm = Context.getSourceManager();
    auto lo = Context.getLangOpts();
    return getSourceText(E, sm, lo);
}

StringRef getSourceTextStable(const Decl *D, ASTContext &Context) {
    const SourceManager &sm = Context.getSourceManager();
    auto lo = Context.getLangOpts();
    return getSourceText(D, sm, lo);
}

std::string getSourceTextStable(ASTContext &Context, SourceLocation Start, SourceLocation End){
    const SourceManager &sm = Context.getSourceManager();
    auto lo = Context.getLangOpts();
    return std::string(Lexer::getSourceText(CharSourceRange::getTokenRange(SourceRange(Start, End)), sm, lo));
}