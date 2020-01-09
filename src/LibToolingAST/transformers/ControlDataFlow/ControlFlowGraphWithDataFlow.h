//
// Extension of the ControlFlowGraphCore Class.
//

#ifndef LIBTOOLINGAST_CONTROLFLOWGRAPHWITHDATAFLOW_H
#define LIBTOOLINGAST_CONTROLFLOWGRAPHWITHDATAFLOW_H

#include "ControlFlowGraphCore.h"

class ControlFlowGraphWithDataFlow : public ControlFlowGraphCore {

public:
    explicit ControlFlowGraphWithDataFlow(ASTContext *Context);

    void createSpecialEdges(const Stmt *s, Graph::vertex_descriptor &fromvertex, std::string fctname) override;

    /**
     * Creates a Decl Edge for a DeclRefExpr.
     * We only save Decl's that are really used. If author, for instance, specifies a global variable that is
     * never used, we will not have a DeclRefExpr for the global variable, and thus no declaration and DeclEdge.
     * @param s
     * @param fromvertex
     * @param fctname
     */
    void createDeclEdgeForDeclRefExpr(const Stmt *s, Graph::vertex_descriptor &fromvertex, std::string fctname);

    /**
     * Returns a filtered view on the graph where only control flow edges are present. Declaration Edges are e.g.
     * not considered.
     * @return
     */
    FilteredGraph filterOutNoControlFlowEdge();


};


#endif //LIBTOOLINGAST_CONTROLFLOWGRAPHWITHDATAFLOW_H
