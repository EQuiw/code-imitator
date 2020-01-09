//
// Utils for IO transformers
//

#ifndef LIBTOOLINGAST_UTILS_IO_TRANSFORMERS_H
#define LIBTOOLINGAST_UTILS_IO_TRANSFORMERS_H

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

using namespace clang;

#include "../utils_transform.h"
#include "../../Utilities/Utils.h"

/**
 * Each CXXOperatorCallExpr object corresponds to a << or >> expression. Get all under current call expr in AST.
 * In this way, by using the 2nd arg of each CXXOperatorCallExpr, you can get the expression after each << or >> cmd.
 * @param e current call expr that corresponds to cout or cin command.
 * @param sm Source Manager
 * @param arrows either "<<" or ">>"
 * @return all CXX Operator Call Expressions that correspond to << or >> expressions...
 */
std::vector<const CXXOperatorCallExpr*> get_cxxopcallexprs(const CallExpr* e, SourceManager* sm,
                                                           const std::string &arrows);

/**
 * Checks if streams are mixed, e.g. cout and printf are used together.
 * @param cppexprs expressions like cout...
 * @param cppstreamexpr expressions like ofstream...
 * @param cexprs expressions like printf
 * @return true if mixed.
 */
bool check_if_streams_are_mixed(const std::vector<const Expr*> &cppexprs, const std::vector<const Expr*> &cppstreamexpr,
                                const std::vector<const CallExpr*> &cexprs);

#endif //LIBTOOLINGAST_UTILS_IO_TRANSFORMERS_H
