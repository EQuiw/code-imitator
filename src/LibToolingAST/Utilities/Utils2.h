//
// Further utils that can be used across various transformers and ...
//

#ifndef LIBTOOLINGAST_UTILS2_H
#define LIBTOOLINGAST_UTILS2_H

#include "clang/AST/AST.h"
#include "../transformers/utils_transform.h"

#include <string>
#include <vector>


/**
 * Checks if dx is a variable declaration of a struct, such as HH:
 *  `struct debugger { ... } HH;`
 * Return true if so.
 * Otherwise, returns false for cases such as HH2:
 *  `struct debugger { ... };
 *   struct debugger HH2;`
 * @param dx declaration of interest
 * @param sm source manager
 * @return true if vardecl part of record decl.
 */
bool check_if_vardecl_ispartof_recorddecl(const VarDecl * dx, SourceManager& sm);


/**
 * Resolve a QualType with inner Types and save all inner types in the vector.
 * For example, if we have std::vector<std::vector<long long>>, then includes wills save long long.
 * For example, if we have pair<long long, int>, includes will save long long, and int.
 * It does not save the 'containers'.
 * @param ctype
 * @param includes
 */
void resolve_inner_types(QualType ctype, std::vector<QualType> &includes);



#endif //LIBTOOLINGAST_UTILS2_H
