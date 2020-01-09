//
// Created by eq on 13.07.18.
//

#ifndef LIBTOOLINGAST_UNUSED_FUNCTIONS_UTILS_H
#define LIBTOOLINGAST_UNUSED_FUNCTIONS_UTILS_H

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

#include "../../transformers/utils_transform.h"
#include "../../transformers/ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../../transformers/ControlDataFlow/CDFGraphQueryHandler.h"

using namespace clang;

#include <string>
#include <vector>

/**
 * We use a heuristic to spot functions that are never called.
 * We look if there are calls to this function (except calls from the function itself due to recursive calls).
 * TODO we should do a proper analysis with clang and cfg
 */
std::vector<const FunctionDecl*> get_unused_functions_approximative(std::vector<const FunctionDecl*> fctdecls,
                                              ASTContext &Context,
                                              ControlFlowGraphWithDataFlow *cfggraph);

/**
* Check if code block contains a call reference to function where the code block is currently in.
*  It means that function was called recursively before, and the code block is doing this.
* @return true if compound stmt is usable, false if not usable.
*/
bool is_call_expr_reference_to_itself(const CallExpr *c, const FunctionDecl* f, ASTContext &Context);


/**
 * Spot functions that are never called.
 * We check if there is a path to the main function.
 * Depending on consider_overloaded parameter, we exclude an unused function.
 * However, if the function is a method (under a record such as struct) and is overloaded (e.g. <<),
 * then we definitely exclude it, since we cannot cover its real usage here so far.
 * This is also true for normal methods, but the probability is smaller on the GCJ dataset.
 *
 * Was added as improvement for 'get_unused_functions_approximative'.
 */
std::vector<std::pair<const FunctionDecl *, unsigned>> get_unused_functions(std::vector<const FunctionDecl*> fctdecls,
                                                                    ASTContext &Context,
                                                                    ControlFlowGraphWithDataFlow *cfggraph,
                                                                    bool consider_overloaded);

#endif //LIBTOOLINGAST_UNUSED_FUNCTIONS_UTILS_H
