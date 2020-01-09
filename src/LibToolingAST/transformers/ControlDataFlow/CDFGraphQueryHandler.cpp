#include "CDFGraphQueryHandler.h"

/**
 * DFS Visitor that checks where given source text occurs.
 */
class DFSVisitorSourceText : public DFSVisitor {

public:

    explicit DFSVisitorSourceText(ControlFlowGraphWithDataFlow *cfggraph, ASTContext* Context,
                                  std::vector<std::string> &targetsourcetexts, const Stmt* &targetStmt) :
        DFSVisitor(cfggraph, Context), targetsourcetexts(targetsourcetexts), targetStmt(targetStmt) {}

    void oneachvertex(Graph::vertex_descriptor vx) override {

        if (cfggraph->graph[vx].stmt) {
#ifdef MYDEBUGBFS
            llvm::outs() << "-S" << vx << ":" << cfggraph->graph[vx].stmt->getStmtClassName() << "\t" << ""
                         << "/\t/" << getSourceTextStable(cfggraph->graph[vx].stmt, *Context) << "--end\n";
#endif

            for (std::string &sourcetextpattern : targetsourcetexts) {
                auto src = getSourceTextStable(cfggraph->graph[vx].stmt, *Context);
                if (src.find(sourcetextpattern) != std::string::npos) {
//                    nodeMatched = v;
                    targetStmt = cfggraph->graph[vx].stmt;
                    throw BFSDFSMatchException();
                }
            }
        }

    };

private:
    std::vector<std::string> &targetsourcetexts;
    const Stmt* &targetStmt;
};


/**
 * DFS Visitor that checks if main function is on the CFG path from a given start vertex.
 */
class DFSVisitorPathToMain : public DFSVisitor {

public:

    explicit DFSVisitorPathToMain(ControlFlowGraphWithDataFlow *cfggraph, ASTContext* Context,
                                  Graph::vertex_descriptor mainfct_vertex) :
            DFSVisitor(cfggraph, Context), mainfct_vertex(mainfct_vertex) {}

    void oneachvertex(Graph::vertex_descriptor vx) override {
        if(vx == mainfct_vertex)
            throw BFSDFSMatchException();
    };

private:
    Graph::vertex_descriptor mainfct_vertex;
};


const Stmt* ControlDataFlowGraphQueryHandler::QueryGetStmtForSourceText(ControlFlowGraphWithDataFlow *cfggraph,
                                                                      ASTContext* Context,
                                                                      const Stmt* startStmt,
                                                                      std::vector<std::string> targetsourcetexts) {
    if (!cfggraph)
        throw CFGException();

    const Stmt* ret = nullptr;
//    BfsVisitorFindSourceText vis2(targetsourcetexts, Context, &ret);
//    DoBFS<BfsVisitorFindSourceText>(cfggraph, startStmt, vis2);

    // II. Get the vertex for the given starting statement
    Graph::vertex_descriptor startVertex = cfggraph->getstartingvertex(startStmt);
    try {
        auto dfs = DFSVisitorSourceText(cfggraph, Context, targetsourcetexts, ret);
        dfs.DFSVisit(startVertex);

    } catch(BFSDFSMatchException& e) {
        #ifdef MYDEBUG
        llvm::outs() << "...........Match" << "\n";
        #endif
    }
    return ret;
}


std::vector<const DeclRefExpr*> ControlDataFlowGraphQueryHandler::queryAllStmtsForDecl(ControlFlowGraphWithDataFlow*
                                                                                      cfggraph, const VarDecl* dvar){
    if(!cfggraph)
        throw CFGException();

    std::vector<const DeclRefExpr*> declrefexprvector;
    Graph::vertex_descriptor tar = cfggraph->getstartingvertex(dvar);

    // Now from target Decl to all DeclRefExpr's over its incoming DeclEdge
    Graph::in_edge_iterator ei2, ei2_end;
    for (boost::tie(ei2, ei2_end) = in_edges(tar, cfggraph->graph); ei2 != ei2_end; ++ei2) {
        if (cfggraph->graph[*ei2].todeclarationedge) {
            Graph::vertex_descriptor src = boost::source(*ei2, cfggraph->graph);
            if (cfggraph->graph[src].stmt && isa<DeclRefExpr>(cfggraph->graph[src].stmt))
                declrefexprvector.push_back(cast<DeclRefExpr>(cfggraph->graph[src].stmt));
        }
    }

    return declrefexprvector;
}


std::vector<const DeclRefExpr*> ControlDataFlowGraphQueryHandler::queryAllStmtsForVariable(ControlFlowGraphWithDataFlow* cfggraph,
                                                                                  const DeclRefExpr* de){
    if(!cfggraph)
        throw CFGException();

    std::vector<const DeclRefExpr*> declrefexprvector;
    Graph::vertex_descriptor tovertex = cfggraph->getstartingvertex(de);

    // Now go over DeclEdge to Decl
    Graph::out_edge_iterator ei, ei_end;
    for(boost::tie(ei, ei_end) = out_edges(tovertex, cfggraph->graph); ei != ei_end; ++ei){
        if(!(cfggraph->graph[*ei].todeclarationedge))
            continue;

        Graph::vertex_descriptor tar = boost::target(*ei, cfggraph->graph);
        // Now from target Decl to all DeclRefExpr's over its incoming DeclEdge
        // except the input DeclRefExpr for this query, 'de'.
        Graph::in_edge_iterator ei2, ei2_end;
        for(boost::tie(ei2, ei2_end) = in_edges(tar, cfggraph->graph); ei2 != ei2_end; ++ei2){
            if(!(cfggraph->graph[*ei2].todeclarationedge))
                continue;

            Graph::vertex_descriptor src = boost::source(*ei2, cfggraph->graph);
            if(src!=tovertex && cfggraph->graph[src].stmt && isa<DeclRefExpr>(cfggraph->graph[src].stmt))
                declrefexprvector.push_back(cast<DeclRefExpr>(cfggraph->graph[src].stmt));
        }
    }
    return declrefexprvector;
}


std::vector<const CallExpr*> ControlDataFlowGraphQueryHandler::queryAllCallExprsToFunction(
        ControlFlowGraphWithDataFlow* cfggraph,  const FunctionDecl* dfunc) {
    // to find all the CallExpr, we make use of the interprocedural edges that go into the first function vertex.

    std::vector<const CallExpr*> matchednodes;

    if(!cfggraph)
        throw CFGException();

    // I. Get the vertex
    Graph::vertex_descriptor fctvertex;
    if(!cfggraph->findStartingVertexForFunction(getUniqueFunctionNameAsString(dfunc), fctvertex)){
        llvm::errs() << "Callee is unknown; in CFGQueryHandler" << "\n";
        throw CFGException();
    }

    // II. Now get all CallExpr's over interprocedural edges
    Graph::in_edge_iterator ei2, ei2_end;
    for(boost::tie(ei2, ei2_end) = in_edges(fctvertex, cfggraph->graph); ei2 != ei2_end; ++ei2){
        if(cfggraph->graph[*ei2].interprocedural){
            Graph::vertex_descriptor src = boost::source(*ei2, cfggraph->graph);
            if(cfggraph->graph[src].stmt && isa<CallExpr>(cfggraph->graph[src].stmt))
                matchednodes.push_back(cast<CallExpr>(cfggraph->graph[src].stmt));
        }
    }

    return matchednodes;
}


const CompoundStmt* ControlDataFlowGraphQueryHandler::queryBodyOfMainFunction(
        ControlFlowGraphWithDataFlow* cfggraph) {
    if(!cfggraph)
        throw CFGException();

    // I. Get the vertex, we need to consider that args are passed to main
    // I.a get unique main function name
    std::string main_fct_name;
    for (auto &s : cfggraph->getStringSetOfVisitedFunctions()){
        if (s.find("main") != std::string::npos)
           main_fct_name = s;
    }
    // I.b find vertex to main
    Graph::vertex_descriptor fctvertex;
    if(!cfggraph->findStartingVertexForFunction(main_fct_name, fctvertex)){
        llvm::errs() << "Callee 'Main' is unknown; in CFGQueryHandler, main possibly gets args" << "\n";
        throw CFGException();
    }

    // II. get the body, we need to have a CompoundStmt under each function decl..
    if(!cfggraph->graph[fctvertex].fdecl){
        llvm::errs() << "No func-decl in first function node\n";
        throw CFGException();
    }

    if(auto fb = dyn_cast<CompoundStmt>(cfggraph->graph[fctvertex].fdecl->getBody()))
        return fb;
    else
        throw CFGException();
}


bool ControlDataFlowGraphQueryHandler::isthereapathtomain(ControlFlowGraphWithDataFlow* cfggraph, ASTContext* Context,
                                                          const Stmt* startStmt) {

    if (!cfggraph)
        throw CFGException();

    // I. Get the vertex, we need to consider that args are passed to main
    // I.a get unique main function name
    std::string main_fct_name;
    for (auto &s : cfggraph->getStringSetOfVisitedFunctions()){
        if (s.find("main") != std::string::npos)
            main_fct_name = s;
    }
    // I.b find vertex to main
    Graph::vertex_descriptor fctvertex;
    if(!cfggraph->findStartingVertexForFunction(main_fct_name, fctvertex)){
        llvm::errs() << "Callee 'Main' is unknown; in CFGQueryHandler, main possibly gets args" << "\n";
        throw CFGException();
    }

    Graph::vertex_descriptor startVertex = cfggraph->getstartingvertex(startStmt);
    try {
        auto dfs = DFSVisitorPathToMain(cfggraph, Context, fctvertex);
        dfs.DFSVisit(startVertex);

    } catch(BFSDFSMatchException& e) {
#ifdef MYDEBUG
        llvm::outs() << "...........Match" << "\n";
#endif
        return true;
    }
    return false;

}


bool ControlDataFlowGraphQueryHandler::isthereapathtofct(ControlFlowGraphWithDataFlow* cfggraph,
                                                         ASTContext* Context,
                                                         const FunctionDecl* startFct,
                                                         const FunctionDecl* fct) {

    if (!cfggraph)
        throw CFGException();

    // I. Get the vertex, we need to consider that args are passed to main
    // find vertex to start and target
    Graph::vertex_descriptor fctvertex;
    if(!cfggraph->findStartingVertexForFunction(getUniqueFunctionNameAsString(fct), fctvertex)){
        llvm::errs() << "Callee " << getUniqueFunctionNameAsString(fct) << " is unknown; in CFGQueryHandler" << "\n";
        throw CFGException();
    }

    Graph::vertex_descriptor startVertex;
    if(!cfggraph->findStartingVertexForFunction(getUniqueFunctionNameAsString(startFct), startVertex)){
        llvm::errs() << "Callee " << getUniqueFunctionNameAsString(startFct) << " is unknown; in CFGQueryHandler" << "\n";
        throw CFGException();
    }

    try {
        auto dfs = DFSVisitorPathToMain(cfggraph, Context, fctvertex);
        dfs.DFSVisit(startVertex);

    } catch(BFSDFSMatchException& e) {
#ifdef MYDEBUG
        llvm::outs() << "...........Match" << "\n";
#endif
        return true;
    }
    return false;

}


const Stmt* ControlDataFlowGraphQueryHandler::findLoopStmtAfterContinueStmt(ControlFlowGraphWithDataFlow* cfggraph,
                                                                          const Stmt* startStmt){

    if(!cfggraph)
        throw CFGException();

    // I. Get vertex
    Graph::vertex_descriptor curVertex = cfggraph->getstartingvertex(startStmt);
    Graph::vertex_descriptor startVertex = curVertex;

    // II. The continue stmt will have an edge to the location where the code is executed next.
    // Thus, we follow the out edges until we get a for/while/do-while stmt. On this way,
    // we do not accept multiple paths, since we should be at a loop stmt directly.

    do {
        Graph::out_edge_iterator ei2, ei2_end;
        int outedges = 0;
        for(boost::tie(ei2, ei2_end) = out_edges(curVertex, cfggraph->graph); ei2 != ei2_end; ++ei2) {
            if (DFSVisitor::islocalcontrolflowedge(*ei2, &(cfggraph->graph))) {
                outedges++;
                curVertex = boost::target(*ei2, cfggraph->graph);
            }
        }

        if(outedges != 1) {
            llvm::errs() << "Continue stmt or following stmt until match has more than 1 out edge\n";
            throw CFGException();
        }

        if(cfggraph->graph[curVertex].stmt && (isa<ForStmt>(cfggraph->graph[curVertex].stmt) ||
                isa<WhileStmt>(cfggraph->graph[curVertex].stmt) || isa<DoStmt>(cfggraph->graph[curVertex].stmt)) ){
            return cfggraph->graph[curVertex].stmt;
        }
    } while (curVertex != startVertex);
    // hopefully this prevents that we end up in an infinite loop.

    throw CFGException();
}



















