//
// Useful functions for common operations while transforming code.
//

#ifndef LIBTOOLINGAST_UTILS_TRANSFORM_H
#define LIBTOOLINGAST_UTILS_TRANSFORM_H

#ifndef CLANG_LIBS
#define CLANG_LIBS
#include "llvm/Support/CommandLine.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#endif

#include <string>
#include <regex>
#include <algorithm>

using namespace clang;

// Custom Exception if we have problems during transformation.
struct CodeTransformationException : public std::exception {
    const char * what () const throw () {
        return "Error while transforming code";
    }
};

/**
 * Returns the source test for a given statement
 * @param Context the current ASTContext
 * @param S the current statement
 * @param checkforsemicolon if true, this function will use measureTokenLength to go to the end of the statement's token,
 * including ';' e.g.; but e.g. for a for-statement's increment stmt, it will go until the bracket ')'. Set carefully.
 * @return
 */
std::string getSourceText(ASTContext &Context, const Stmt *S, bool checkforsemicolon = false);

/**
 * See help for getSourceText with Stmt as variable.
 */
std::string getSourceText(ASTContext &Context, const Decl *D, bool checkforsemicolon = false);

std::string getSourceText(ASTContext &Context, const TypeLoc T, bool checkforsemicolon = false);

std::string getSourceText(ASTContext &Context, SourceLocation Start, SourceLocation _End);

/**
 * getSourceText uses this function as most steps are independent of Stmt, Decl, TypeLoc.
 */
std::string __getSourceTextInternal(ASTContext &Context, SourceLocation Start, SourceLocation _End, bool checkforsemicolon = false);

/**
 * Get the offset for current stmt where this stmt has its semicolon.
 * @param Context the current AST Context
 * @param s the current stmt
 * @return either -1 (if not found) or the corresponding offet...
 */
int getOffsetWithSemicolon(ASTContext &Context, const Stmt *s);

int getOffsetWithSemicolon(ASTContext &Context, const Decl *s);

/**
 * Get the SourceRange for stmt until a semicolon is found at the end of its line.
 * Be aware that you could get other statements by accident that are in the same line..
 * @param Context
 * @param s
 * @return the Source Range of s incl. semicolon
 */
SourceRange getSourceRangeWithSemicolon(ASTContext &Context, const Stmt *s);

SourceRange getSourceRangeWithSemicolon(ASTContext &Context, const Decl *s);

/**
 * Replaces all occurences of a substring in the target string. Function body taken from
 * stackoverflow. Do not use a regex here?!.
 * @param subject the string where we want to replace a substring, here replace var.
 * @param search what to look for
 * @param replace what to replace where search occurs
 * @return
 */
std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace);

/**
 * Removes the last whitespaces from a string.
 * @param s a string.
 * @return a new string with no whitespaces at the end.
 */
std::string remove_last_whitespace(std::string s);

/**
 * Trim operation for strings.
 * @param str
 * @param trimcharacter
 * @return
 */
std::string trim(const std::string& str, std::string trimcharacter);

/**
     * Splits the input string into substrings w.r.t. to the defined regex.
     * Can be used in parallel to getMatches method.
     * @param input
     * @param regex
     * @return the substrings between the splitting regex.
     */
std::vector<std::string> split(const std::string& input, const std::string& regex);

/**
* Show all matches with the regex within the input string.
* Can be used in parallel to split method.
* @param input
* @param regex
* @return a vector of substrings with all matches.
*/
std::vector<std::string> getMatches(std::string input, const std::string &regex);


/**
 * Retrieves the unique function name incl. all its parameters.
 * Consider the two functions bla(int a) and bla(int a, int b). They have the same name, but different arguments.
 * @param f function decl
 * @return a unique identifier for f
 */
std::string getUniqueFunctionNameAsString(const FunctionDecl* f);

/**
 * Returns the row and column number. If verbose is true, it will print the row and column number.
 * @param sr source range
 * @param sm source manager
 * @param verbose true if row and col should be printed to console
 * @return pair of row and column
 */
std::pair<unsigned, unsigned> getRowColumn(SourceLocation sl, SourceManager &sm, bool verbose=false);


/**
 * Saves the parent of dtn in targetdtn that subsumes the whole line where dtn is part of.
 * E.g. if we have the command std::cout << "bla" << foo(x) << "bla" << std::endl;
 * If dtn is foo(x), then we want to get the node that represents the whole command line in the AST.
 * This function would return std::cout, as if we call getSourceText(...) on it, we would get
 * the whole command.
 *
 * So far, it is based on the row number. So make sure you called clang-format on the source file.
 * Otherwise, we may get wrong results. We should rewrite this method later.
 * TODO Rewrite this Function:
 *  To do so, we should use the CFG, go further until we find the last vertex that contains the src text
 * of dtn, this will be the node that subsumes the whole line -- even if two statemens are written
 * in the same row.
 * @param dtn
 * @param targetdtn
 * @param targetrow
 * @return
 */
bool getParentOfWholeCommandLine(ast_type_traits::DynTypedNode dtn,
                                 ast_type_traits::DynTypedNode &targetdtn,
                                 const unsigned targetrow,
                                 ASTContext &context,
                                 SourceManager &sm);


/**
 * Insert the headerstr---automatically sourrounded by include---in the current source file,
 * if the header does not exist before.
 * @param headerstr  the header string
 * @param headerincludes  a vector with all defined headers in current source file
 * @param firstDeclInSrcFile  The first Decl that occured in source file. Needed to put the new header
 *  if no other headers were defined.
 * @param sm  SourceManager Instance.
 * @param OurRewriter  Rewriter Instance.
 */
void insertHeaderAtBeginningOfSourceFile(std::string headerstr,
                             std::vector<std::pair<std::string, SourceLocation>>* headerincludes,
                             Decl* firstDeclInSrcFile,
                             SourceManager &sm,
                             Rewriter &OurRewriter
);

/**
 * Checks if target namespace name is in list of namespaces (e.g. that occur in current source file).
 * @param targetns
 * @param namespaces
 * @return true if targetns is in namespaces
 */
bool namespace_defined(std::string targetns, std::vector<UsingDirectiveDecl*> namespaces);

#include "utils_transform.inl"

#endif //LIBTOOLINGAST_UTILS_TRANSFORM_H
