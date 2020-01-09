//
// Abstract class that implements a DFS visit over the CFG.
//
//

#ifndef LIBTOOLINGAST_DFSVISITOR_H
#define LIBTOOLINGAST_DFSVISITOR_H

//#ifndef CLANG_LIBS
//#define CLANG_LIBS
//#include "llvm/Support/CommandLine.h"
//#include "clang/AST/RecursiveASTVisitor.h"
//#include "clang/Frontend/FrontendAction.h"
//#include "clang/Frontend/CompilerInstance.h"
//#include "clang/Tooling/CommonOptionsParser.h"
//#include "clang/Tooling/Tooling.h"
//#include "clang/Rewrite/Core/Rewriter.h"
//#endif

//#ifndef CLANG_CFGLIBS
//#define CLANG_CFGLIBS
//#include "clang/AST/ASTConsumer.h"
//#include "clang/AST/AST.h"
//#include "clang/Frontend/ASTConsumers.h"
//#include "clang/Frontend/FrontendActions.h"
//#include "llvm/IR/Constants.h"
//#include <clang/Analysis/CFG.h>
////#include "clang/Analysis/Analyses/LiveVariables.h"
//#include "clang/Analysis/AnalysisContext.h"
//#endif

// Only use this variable if you want some CFG debug messages,
// do not add it to cmakelists ;):
//#define MYDEBUG_CFG 1

#include <iostream>
#include <exception>

#include "../include/SourceTextHelper.h"

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
#include "ControlFlowGraphWithDataFlow.h"

class DFSVisitor {

public:

    explicit DFSVisitor(ControlFlowGraphWithDataFlow *cfggraph, ASTContext* Context) {
        this->cfggraph = cfggraph;
        this->Context = Context;
    }

    virtual ~DFSVisitor() {}

    virtual void oneachvertex(Graph::vertex_descriptor vx) = 0;


    void DFSVisit(Graph::vertex_descriptor vx);

    static bool islocalcontrolflowedge(Graph::edge_descriptor e, Graph *graph);

    static bool iscontrolflowedge(Graph::edge_descriptor e, Graph *graph);

    /**
     * Small helper function to get all vertices before a given vertex (all vertices
     * that have an edge to node)
     */
    static std::vector<Graph::vertex_descriptor> get_in_vertices(
            Graph::vertex_descriptor node,
            ControlFlowGraphWithDataFlow *cfggraph,
            bool islocalcontrol, bool isinterprocedural);

protected:
    std::set<Graph::vertex_descriptor> visitedVertices;
    ControlFlowGraphWithDataFlow *cfggraph;
    ASTContext* Context;

};


#endif //LIBTOOLINGAST_DFSVISITOR_H
