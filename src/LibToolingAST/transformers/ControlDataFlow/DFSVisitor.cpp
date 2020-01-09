#include "DFSVisitor.h"

void DFSVisitor::DFSVisit(Graph::vertex_descriptor vx){

    // Visited before?
    if(visitedVertices.find(vx) != visitedVertices.end()) {
        return;
    }

    // add it to visited vertices
    visitedVertices.insert(vx);

    // Do custom check
    oneachvertex(vx);

    // First, check if vertex has a function reference, so we need to go to the CFG of another fct.
    if(!cfggraph->graph[vx].calleefunctionname.empty()){
        Graph::vertex_descriptor finalvertexofcallee;
        if(!cfggraph->findEndVertexForFunction(cfggraph->graph[vx].calleefunctionname, finalvertexofcallee)){
            llvm::errs() << "Error: Callee is unknown during DFSVisit:\n";
            throw CFGException();
        }
        DFSVisit(finalvertexofcallee);
    }

    // Now the other vertices in current CFG, we do not leave the current fct.
    auto in_fct_vxs = DFSVisitor::get_in_vertices(vx, cfggraph, true, false);
    for(auto cvx: in_fct_vxs){
        DFSVisit(cvx);
    }

    // Now go to all caller's that call this function
    auto callervxs = DFSVisitor::get_in_vertices(vx, cfggraph, false, true);
    for(auto sc : callervxs){
        // Now if we would add sc to next visited vertices, we would go again into current function
        // sc would be the CallExpr node that calls current function.
        // thus, we add all previous nodes so we prevent to go into current function again.
        auto callervxs_before = DFSVisitor::get_in_vertices(sc, cfggraph, true, false);
        for(auto scc : callervxs_before){
            DFSVisit(scc);
        }
    }

}


bool DFSVisitor::islocalcontrolflowedge(Graph::edge_descriptor e, Graph *graph){
    return !(*graph)[e].todeclarationedge && !(*graph)[e].interprocedural;
}

bool DFSVisitor::iscontrolflowedge(Graph::edge_descriptor e, Graph *graph) {
    return !(*graph)[e].todeclarationedge;
}


std::vector<Graph::vertex_descriptor> DFSVisitor::get_in_vertices(
        Graph::vertex_descriptor node,
        ControlFlowGraphWithDataFlow *cfggraph,
        bool islocalcontrol, bool isinterprocedural) {

    Graph::in_edge_iterator ei2, ei2_end;
    std::vector<Graph::vertex_descriptor> in_vertices;

    for(boost::tie(ei2, ei2_end) = in_edges(node, cfggraph->graph); ei2 != ei2_end; ++ei2){
        if (islocalcontrol && (!DFSVisitor::islocalcontrolflowedge(*ei2, &(cfggraph->graph))))
            continue;
        if (isinterprocedural && (!(cfggraph->graph)[*ei2].interprocedural))
            continue;

        Graph::vertex_descriptor src = boost::source(*ei2, cfggraph->graph);
        in_vertices.push_back(src);
    }
    return in_vertices;
}
