//
// ************ Structs & Typedefs for ControlFlowGraph class ************
//

#ifndef LIBTOOLINGAST_CONTROLFLOWGRAPHUTILITIES_H
#define LIBTOOLINGAST_CONTROLFLOWGRAPHUTILITIES_H

// Please include this header file at the end of the ControlFlowGraph.h includes


// Custom Exception if we have problems during the CFG creation or traversal.
struct CFGException : public std::exception {
    const char * what () const throw () {
        return "Error while creating / parsing the CFG graph";
    }
};

// Custom Exception if we find a match during BFS or DFS;
// this is the default behavior according to boost docu.
struct BFSDFSMatchException : public std::exception {
    const char * what () const throw () {
        return "Match during BFS / DFS";
    }
};


// Properties for each vertex
struct VertexProperties
{
    unsigned blockid = 0;
    unsigned stmtid = 0;
    std::string functionname;
    bool isterminatornode = false;
    const FunctionDecl *fdecl = nullptr;
    const Stmt* stmt;
    const Decl* decl;
    std::string calleefunctionname;
};

// Properties for each edge
struct EdgeProperties
{
    bool interprocedural = false;
    bool todeclarationedge = false;
};

// Typedef for our graph: directed with properties at each edge and vertex:
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef boost::filtered_graph<Graph, boost::function<bool(Graph::edge_descriptor)>, boost::keep_all > FilteredGraph;
typedef boost::reverse_graph<FilteredGraph, FilteredGraph &> GraphReversed;
typedef boost::reverse_graph<Graph, Graph &> GraphReversedNonFiltered;

// Either use these typedef's or use Graph::edge_descriptor later.. we do the latter..
//typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
//typedef boost::graph_traits<Graph>::edge_descriptor   edge_t;
//#define MYDEBUG 1;


// Useful to sort a vector of vertex_descriptor w.r.t to their statement id (stmtid).
// Used by getAllVerticesForBlock.
struct StmtIdCmp {
    explicit StmtIdCmp(Graph *graph) { this->graph = graph; }
    bool operator () (Graph::vertex_descriptor i, Graph::vertex_descriptor j) {
        return ((*graph)[i].stmtid < (*graph)[j].stmtid);
    }

    Graph *graph;
};

#endif //LIBTOOLINGAST_CONTROLFLOWGRAPHUTILITIES_H
