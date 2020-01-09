//
// **** Control Flow Graph Directory Overview. ****
//
// ControlFlowGraphCore     - extracts the CFG by using clang's CFG and stores it into an own graph
//    |                     - this class represents the minimal necessary steps to get the CFG
//    |                     - this class has a virtual method 'createSpecialEdges' that is called during CFG building
//    |                       and can be useful to add new functionality, as e.g. done by ControlFlowGraphWithDataFlow.
//    |
//    | --------- uses --------> ControlFlowGraphUtilities.h -- here we have put some typedef's and definitions.
//    |
//     <-------- ControlFlowGraphWithDataFlow
//                          - represents an extension of the core functionality
//                          - adds some dataflow functionality
//              ^
//              |
//              | /*used by*/
//              |
//              v
//   ControlFlowGraphQueryHandler provides various queries that we can do on the CFG. Static Methods to do so.
//
//
//   How to start?
//      - Read the Core Class, then ControlFlowGraphWithDataFlow
//      - The latter inherits from the Core Class
//      - The ControlFlowGraphQueryHandler is static, obtains a CFG graph object each time and does some queries.

#ifndef LIBTOOLINGAST_CONTROLFLOWGRAPH_H
#define LIBTOOLINGAST_CONTROLFLOWGRAPH_H

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

#ifndef CLANG_CFGLIBS
#define CLANG_CFGLIBS
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/AST.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "llvm/IR/Constants.h"
#include <clang/Analysis/CFG.h>
//#include "clang/Analysis/Analyses/LiveVariables.h"
#include "clang/Analysis/AnalysisContext.h"
#endif

using namespace clang;
using namespace clang::tooling;
using namespace clang::driver;

// Only use this variable if you want some CFG debug messages,
// do not add it to cmakelists ;):
//#define MYDEBUG_CFG 1

#include <iostream>
#include <exception>

#include "../utils_transform.h"
#include "../../Utilities/Utils.h"

#ifndef BOOST_GRAPH_INCL
#define BOOST_GRAPH_INCL
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/reverse_graph.hpp>
//#include <boost/graph/graph_utility.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/function.hpp>
#endif

// Load our custom typedef's and structs ...
#include "ControlFlowGraphUtilities.h"


/* ************ The Graph ************ */

/**
 * Represents the Control Flow Graph extracted from clang. Each vertex represents a stmt* from a CFG Block
 * as defined by clang. In other words, each vertex stores a
 * pointer to an AST node via Stmt*. In this way, the AST and this CFG are connected to each other.
 * Moreover, one or multiple vertices belong to a particular CFG block, so that each vertex has a unique CFG Block ID.
 * Moreover, one or multiple vertices belong to the same function, so that each vertex has also a unique function name.
 * In this way, we actually have a graph with a subgraph of functions and this in turn has a subgraph of CFG blocks.
 * Boost actually has a subgraph class, but we wanted to have a quite simple approach and thus just stored
 * this properties in the vertices.
 *
 * The graph is a directed graph, each edge is a connection from one stmt* to the next stmt*.
 * If we have a connection to another function, the edge's interprocedural property is set to true.
 *
 * Now you can create simple queries. For instance, if we transform cout statements,
 * we use it to find the cout.precision statement since it defines the precision of all subsequent cout
 * statements.
 */
class ControlFlowGraphCore {

public:
    Graph graph;

    explicit ControlFlowGraphCore(ASTContext *Context);

    // make virtual so that we do not get a has-virtual-method-but-non-virtual-destructor, undefined behaviour possible
    virtual ~ControlFlowGraphCore() = default;

    /**
     * Extracts the CFG and the statements of the given function declaration to create the respective graph
     * for this function.
     * @param f
     * @return true if no errors
     */
    bool addFunctionDecl(const FunctionDecl *f);

    /**
     * Does some sanity check to ensure that we have a valid CFG graph.
     * @return true if everything is fine (at least according to the checks).
     */
    bool sanity_check();

    /**
     * Just show the graph
     */
    void consoleoutputOfGraph();


    /**
     * Returns the corresponding vertex for a given Stmt.
     * @param startStmt
     * @return vertex or exception.
     */
    Graph::vertex_descriptor getstartingvertex(const Stmt* startStmt);

    /**
     * Returns the corresponding vertex for a given Decl.
     * @param startDecl
     * @return vertex or exception.
     */
    Graph::vertex_descriptor getstartingvertex(const Decl* startDecl);

//    /**
//     * Returns the corresponding vertex for a given Stmt/Decl by using its 1) source text and 2) SourceLocation.
//     * It compares the whole source text and the row number of the respective Stmt/Decl.
//     * This function can be used as a fallback, if e.g. a DeclStmt has multiple Decl's, so that CFG creates
//     * separate DeclStmt's in the order the user defines variables, but AST just has one DeclStmt. Then we should
//     * use this function.
//     */
//    Graph::vertex_descriptor getstartingvertexViaSourceTextLocationMatch(std::string sourceTextCmp,
//                                                                         FullSourceLoc fullLocCmp);

    /**
     * Find the starting node of a function's CFG. Stores the matched vertex in targetvertex. Call by reference.
     * @param functionname
     * @param targetvertex
     * @return true if found, false if the function and its starting node was not found.
     */
    bool findStartingVertexForFunction(const std::string &functionname, Graph::vertex_descriptor &targetvertex);

    /**
     * Find the end node of a function's CFG. Even if a function has multiple Return Stmt's,
     * the clang CFG will have a final end CFGBlock that is empty. All Return Stmt's will have an edge to this final vertex.
     * This function stores the matched vertex in targetvertex.
     * @return true if found, false if the function and its final node was not found.
     */
    bool findEndVertexForFunction(const std::string &functionname, Graph::vertex_descriptor &targetvertex);

    /**
     * Returns a set that contains the visited functions as strings (their unique name, incl. args).
     * @return a set of strings
     */
    std::set<std::string> getStringSetOfVisitedFunctions();

protected:
    ASTContext *Context;
    SourceManager &sm; // Initialize me!
//    CompilerInstance &ci;  // Initialize me!
    std::vector<std::unique_ptr<CFG>> FooCFGs;

    std::set<std::string> visitedfunctions;


    /**
     * Returns vertices that correspond to the current cfg block in function f or creates new vertices.
     * @param cfgblock
     * @param f
     * @param isfirstblock bool to indicate if this block is the first block of the function
     * @return vertex_descriptor
     */
    std::vector<Graph::vertex_descriptor> findOrCreateBlock(const FunctionDecl *f, CFGBlock *cfgblock,
                                                            bool isfirstblock);

    /**
     * Stores the vertices for the given CFG block
     * @param f the current function declaration
     * @param cfgblock the CFG block
     * @param isfirstblock bool to indicate if this block is the first block of the function, if so, then we will
     * also add the function parameters as extra vertices after the first, regular function vertex.
     * @return
     */
    std::vector<Graph::vertex_descriptor> SaveCFGBlockStatements(const FunctionDecl *f, CFGBlock *cfgblock,
                                                                 bool isfirstblock);

    /**
     * Creates a new single vertex
     * @param blockid
     * @param stmtid
     * @param stmt
     * @param isterminatornode
     * @param fdecl
     * @param fctname
     * @param decl
     * @return the vertex descriptor to this new vertex.
     */
    Graph::vertex_descriptor createNewVertex(unsigned blockid, unsigned stmtid,
                                             const Stmt* stmt,
                                             bool isterminatornode, const FunctionDecl *fdecl,
                                             std::string fctname, const Decl* decl);

    /**
     * Copies the vertex properties from the from-vertex to the to-vertex. Call by reference.
     * @param from vertex
     * @param to vertex
     */
    void copyVertexPropertiesFromTo(Graph::vertex_descriptor &from, Graph::vertex_descriptor &to);

    /**
     * Cleans the vertex; can be used as replacement for removing vertices; but with care.
     * Removing vertices may produce side effects, thus this function.
     * @param to
     */
    void cleanVertexProperties(Graph::vertex_descriptor &to);


    /**
     * Returns all vertices for the given block and function. Sorted after their statement id (stmtid).
     * @param blockid
     * @param functionname
     * @return a list of vertices, can also be empty if no vertices were found.
     */
    std::vector<Graph::vertex_descriptor> getAllVerticesForBlock(std::string functionname, unsigned blockid);


    /**
     * Is called and should be overwritten if we want to add some special functionality,
     * as e.g. done by CFG dataflow class.
     * @param s
     * @param fromvertex
     * @param fctname
     */
    virtual void createSpecialEdges(const Stmt *s, Graph::vertex_descriptor &fromvertex, std::string fctname);

};

#endif //LIBTOOLINGAST_CONTROLFLOWGRAPH_H
