//
// Some useful functions that we may need repeatedly.
//

#ifndef LIBTOOLINGAST_UTILS_H
#define LIBTOOLINGAST_UTILS_H


#include "clang/AST/AST.h"

#include <string>
#include <vector>
#include <unordered_map>


//void printhashmap(const std::unordered_map<std::string, T> &map, const std::string &InFile);
// You will find this function in Utils.inl, since it is a template.

/**
 * This function will split the path to a source file into the directory path and the file name.
 * e.g. take /path/to/file.cpp, this function returns /path/to and file.cpp
 * @param uid
 * @return array with 2 strings, see description above.
 */
std::vector<std::string> split_path(const std::string &path);

/**
 * Extracts the name from a file
 * Take the name 2994486_5658282861527040_ZZZ.cpp from Google Contest.
 * Returns ZZZ.
 * If your IDE shows that this method is not used, look at Utils.inl where it is used.
 * @param uid
 * @return the user name from a Google Contest File.
 */
std::string extract_name(const std::string &uid);

/**
 * Iterate through the parents of a particular start node to determine its depth.
 * @param parents current parent of node that calls this method
 * @param Context context from where we called this method
 * @param currentdepth saves the current depth
 * @return the updated depth
 */
int getdepthfornode(const clang::ASTContext::DynTypedNodeList &parents,
                    clang::ASTContext *Context, int currentdepth, std::string &curfile);

/**
 * Update the average depth of the current node
 * @param map   Reference to hashmap that stores occurence count
 * @param map_avgdepth  Reference to hashmap that stores depth
 * @param str node's source code = code in ast leaf or ast node type
 * @param currentdepth its depth in AST. The average depth of 'str' will be
 * updated accordingly. For this, it also needs the this->map object, so
 * make sure you call insertinhashmap before..
 */
void insertindepthhashmap(std::unordered_map<std::string, int> &map,
                          std::unordered_map<std::string, float> &map_avgdepth,
                          const std::string &str, const int currentdepth);


/**
 * Check if currentchild node is a child of parent node. Nodes can be Stmt, Decl, ...
 * Use 'ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*vardeclr);'
 * to transform a node into DynTypedNode.
 * @param currentchild
 * @param parent
 * @param Context
 * @return true if currentchild is the child of parent.
 */
bool CheckIsChildOf(clang::ast_type_traits::DynTypedNode currentchild,
                    clang::ast_type_traits::DynTypedNode parent, clang::ASTContext *Context);


/**
 * Checks whether stmt is a code block stmt.
 * @param s Stmt.
 * @return true if it so.
 */
bool checkifcontrolstmt(const clang::Stmt *s);


/**
 * Go upwards until the next compound stmt is found. If we find a control-stmt on the way before,
 * we know that we have to add curly braces...
 * @param Context -- the current context
 * @param dtn -- some stmt, decl, or type node in AST
 * @return false if not within a compound stmt, because before, we've found some ctrl-stmt,
 * so that we have to add curly braces
 */
bool isWithinCompoundStmt(clang::ASTContext &Context, clang::ast_type_traits::DynTypedNode dtn);


#include "Utils.inl"

#endif //LIBTOOLINGAST_UTILS_H
