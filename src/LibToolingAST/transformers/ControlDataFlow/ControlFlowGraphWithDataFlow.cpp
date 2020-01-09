//
// See ControlFlowGraphWithDataFlow.h for more information about this class.
//

#include "ControlFlowGraphWithDataFlow.h"


ControlFlowGraphWithDataFlow::ControlFlowGraphWithDataFlow(ASTContext *Context)
        : ControlFlowGraphCore(Context)  {};


void ControlFlowGraphWithDataFlow::createSpecialEdges(const Stmt *s, Graph::vertex_descriptor &fromvertex,
                                                      std::string fctname) {
    createDeclEdgeForDeclRefExpr(s, fromvertex, fctname);
}

/* ******** ******** Following Needed for Declaration Edges ******** ******** */

// Three Cases:
// A. Declaration is Local Variable Declaration, then, we should have a DeclStmt for this!
// B. Declaration is Parameter Variable Declaration, then, we just have a ParmVarDecl in AST without Stmt.
//      In this case, we add the Declaration to the first block stmt of the function
// C. Declaration is global, then there is no CFG stmt, and we create a new vertex in graph that is not connected
//      with all other vertices, just via DeclEdge from CallExprRef.
void ControlFlowGraphWithDataFlow::createDeclEdgeForDeclRefExpr(const Stmt *s, Graph::vertex_descriptor &fromvertex,
                                                    std::string fctname){
    if(!s)
        return;

    if(auto sdre = dyn_cast<DeclRefExpr>(s)){
        if(auto sdrevardecl = dyn_cast<VarDecl>(sdre->getDecl())){

            Graph::vertex_descriptor tovertex;
            // A. ******** Local Variable / Function Parameter Decl. ********
            if(sdrevardecl->isLocalVarDeclOrParm()){

                try {
                    // Find vertex that corresponds to variable; use variable declaration as
                    // a 'multi' DeclStmt may be splitted into sevaral single DeclStmts in the CFG
                    tovertex = getstartingvertex(sdrevardecl);
                } catch (CFGException &e) {

                    llvm::errs() << "Error:" << "No Vertex for DeclRefExpr\n with DeclRef Variable:"
                                 << getSourceText(*Context, s, false) << "\t"
                                 << getSourceText(*Context, sdrevardecl, false) << "\n";
                    return;
                }

            // B. ******** Global Variable Decl. ********
            } else {
                // Check that var decl is in main file
                bool inmainfile = Context->getSourceManager().isInMainFile(sdrevardecl->getLocation());
                if (inmainfile) {
                    try {
                        tovertex = getstartingvertex(sdrevardecl);
                    } catch(CFGException& e) {
                        // means we could not find the Declaration in the graph, not so unusual, since
                        // Declarations are not part of the CFG, and we add them at this point here.
                        tovertex = createNewVertex(0, 0, nullptr, false, nullptr, "global", sdrevardecl);
                    }
                } else {
                    return;
                }
            }

            // D. Finally, add edge from current vertex = DeclRefExpr to target vertex
            std::pair<Graph::edge_descriptor, bool> e01 =
                    boost::add_edge(fromvertex, tovertex, graph);
            graph[e01.first].todeclarationedge = true;
            #ifdef MYDEBUG_CFG
                        llvm::outs() << "\t\t\tDeclEdge from:" << fromvertex << "," << getSourceText(*Context, s, false) << " to "
                                     << tovertex << "," << getSourceText(*Context, sdrevardecl, false) << "\n";
            #endif

        }
    }
}


FilteredGraph ControlFlowGraphWithDataFlow::filterOutNoControlFlowEdge() {

    // filtered graph makes no copy of graph, just returns a new 'view'
    FilteredGraph fgraph(graph, [&](Graph::edge_descriptor e){
        return !graph[e].todeclarationedge;
    }, boost::keep_all{});

    return fgraph;
}
