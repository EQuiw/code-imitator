
#ifndef AUTHORSHIP_EVASION_SOURCETEXTHELPER_H
#define AUTHORSHIP_EVASION_SOURCETEXTHELPER_H

#include "clang/AST/Expr.h"
#include "clang/AST/Stmt.h"
#include "clang/AST/Decl.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Lex/Lexer.h"
#include "clang/Tooling/Core/Replacement.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include <random>

using namespace clang;
using namespace clang::tooling;

SourceRange getSourceRange(const Stmt *S, const SourceManager &SM,
                           const LangOptions &LO);
SourceRange getSourceRange(const Expr *S, const SourceManager &SM,
                           const LangOptions &LO);
SourceRange getSourceRange(const Decl *D, const SourceManager &SM,
                           const LangOptions &LO);

CharSourceRange getCharSourceRange(const Stmt *S, const SourceManager &SM,
                                   const LangOptions &LO);
CharSourceRange getCharSourceRange(const Expr *E, const SourceManager &SM,
                                   const LangOptions &LO);
CharSourceRange getCharSourceRange(const Decl *D, const SourceManager &SM,
                                   const LangOptions &LO);

StringRef getSourceText(const Stmt *S, const SourceManager &SM,
                        const LangOptions &LO);
StringRef getSourceText(const Expr *E, const SourceManager &SM,
                        const LangOptions &LO);
StringRef getSourceText(const Decl *D, const SourceManager &SM,
                        const LangOptions &LO);

/**
 * Get source text of statement. New convenience function to use.
 */
StringRef getSourceTextStable(const Stmt *S, ASTContext &Context);
/**
 * Get source text of expression. New convenience function to use.
 */
StringRef getSourceTextStable(const Expr *E, ASTContext &Context);
/**
 * Get source text of declaration. New convenience function to use.
 */
StringRef getSourceTextStable(const Decl *D, ASTContext &Context);
/**
 * Get source text within defined source range. New convenience function to use.
 */
std::string getSourceTextStable(ASTContext &Context, SourceLocation Start, SourceLocation End);

#endif // AUTHORSHIP_EVASION_SOURCETEXTHELPER_H
