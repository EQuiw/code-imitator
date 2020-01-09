#ifndef LIBTOOLINGAST_CONTROLFLOWGRAPHQUERIES_H
#define LIBTOOLINGAST_CONTROLFLOWGRAPHQUERIES_H

#include "ControlFlowGraphWithDataFlow.h"
#include "../include/SourceTextHelper.h"
#include "DFSVisitor.h"

//#define MYDEBUGBFS 1

class ControlDataFlowGraphQueryHandler {

public:

//    explicit ControlDataFlowGraphQueryHandler(ASTContext *Context, ControlFlowGraphWithDataFlow* cfggraph);

    static void DFSVisit(Graph::vertex_descriptor vx, std::set<Graph::vertex_descriptor> &visitedVertices,
                         ControlFlowGraphWithDataFlow *cfggraph, ASTContext* Context,
                         std::vector<std::string> &targetsourcetexts, const Stmt* &targetStmt);

    /**
     * Obtain a statement whose source text matches with one of the defined strings in the targetsourcetexts vector.
     * @param startStmt starting statement
     * @param targetsourcetexts vector of source text
     * @return a Stmt* whose source text matches with any from targetsourcetext.
     */
    static const Stmt* QueryGetStmtForSourceText(ControlFlowGraphWithDataFlow *cfggraph,
                                                 ASTContext* Context,
                                                 const Stmt* startStmt,
                                                 std::vector<std::string> targetsourcetexts);


    /**
     * For a given Decl, obtain all DeclRefExpr's that belong to this Declaration.
     * @param cfggraph
     * @param dvar
     * @return
     */
    static std::vector<const DeclRefExpr*> queryAllStmtsForDecl(ControlFlowGraphWithDataFlow* cfggraph,
                                                                const VarDecl* dvar);


    /**
     * For a given Decl Ref Expression, obtain all other DeclRefExpr that belong to the same Declaration by
     * exactly using the connection over the common Declaration.
     * @param de
     * @return
     */
    static std::vector<const DeclRefExpr*> queryAllStmtsForVariable(ControlFlowGraphWithDataFlow* cfggraph,
                                                                    const DeclRefExpr* de);


    /**
     * For a given function declaration, find all expressions (statements) that call this function.
     * @param cfggraph
     * @param dfunc
     * @return
     */
    static std::vector<const CallExpr*> queryAllCallExprsToFunction(ControlFlowGraphWithDataFlow* cfggraph,
                                                                    const FunctionDecl* dfunc);

    /**
     * Get the body = compound stmt of the main entry point, the main function.
     * So far, we assume that no args are passed to main..
     * @param cfggraph
     * @return
     */
    static const CompoundStmt* queryBodyOfMainFunction(ControlFlowGraphWithDataFlow* cfggraph);


    /**
     * Check if there is a path from startStmt to the main function. Can be used to check
     * if a function could be called / is used.
     */
    static bool isthereapathtomain(ControlFlowGraphWithDataFlow* cfggraph, ASTContext* Context, const Stmt* startStmt);


    /**
     * Check if there is a path from StartStmt to passed fct declaration.
     */
    static bool isthereapathtofct(ControlFlowGraphWithDataFlow* cfggraph,
                                  ASTContext* Context,
                                  const FunctionDecl* startFct,
                                  const FunctionDecl* fct);

    /**
     * For a given start and end Stmt, find all matching statements between.
     * @tparam S Stmt or Decl of start node
     * @tparam E Stmt or Decl of end node
     * @tparam V type of matchingNodes
     * @return
     */
    template <typename S, typename E, typename V>
    static std::vector<const V*> queryAllStmtsBetween(ControlFlowGraphWithDataFlow* cfggraph,
                                                         const S* startStmt, const E* EndDecl,
                                                         std::vector<const V*> &matchingNodes) {
        if(!cfggraph)
            throw CFGException();

        std::vector<const V*> matchednodesbetween;

        // Reverse graph not necessary here, since I go over all in-edges..

        // I. Get the vertex for the start and end
        Graph::vertex_descriptor startVertex = cfggraph->getstartingvertex(startStmt);
        Graph::vertex_descriptor endVertex = cfggraph->getstartingvertex(EndDecl);

        // II. Now do own simple iterative DFS, since we want to follow each possible path, but only until endVertex
        std::set<Graph::vertex_descriptor> visitedVertices;
        std::stack<Graph::vertex_descriptor> stackVertices;

//        cfggraph->consoleoutputOfGraph();

        stackVertices.push(startVertex);
        while(!stackVertices.empty()){
            Graph::vertex_descriptor curv = stackVertices.top();
            stackVertices.pop();
            if(visitedVertices.find(curv) == visitedVertices.end() && curv != endVertex){
                // not visited before and not end vertex that we do not want to visit

#ifdef MYDEBUGBFS
                if(cfggraph->graph[curv].stmt)
                    llvm::outs() << "S" << curv << ":" << cfggraph->graph[curv].stmt->getStmtClassName() << "\n";
#endif

                // add all adjacent vertices
                Graph::in_edge_iterator ei2, ei2_end;
                for(boost::tie(ei2, ei2_end) = in_edges(curv, cfggraph->graph); ei2 != ei2_end; ++ei2){
                    if (!DFSVisitor::islocalcontrolflowedge(*ei2, &(cfggraph->graph)))
                        continue;

                    Graph::vertex_descriptor src = boost::source(*ei2, cfggraph->graph);
                    stackVertices.push(src);
                }

                // Last, check if vertex has a function reference, so we need to go to the CFG of another fct.
                if(!cfggraph->graph[curv].calleefunctionname.empty()){
                    Graph::vertex_descriptor finalvertexofcallee;
                    if(!cfggraph->findEndVertexForFunction(cfggraph->graph[curv].calleefunctionname, finalvertexofcallee)){
                        llvm::errs() << "Error: Callee is unknown during DFSVisit:\n";
                        throw CFGException();
                    }
                    stackVertices.push(finalvertexofcallee);
                }

                if(cfggraph->graph[curv].stmt){
                    if(auto curvstmt = dyn_cast<V>(cfggraph->graph[curv].stmt)){
                        if(std::find(matchingNodes.begin(), matchingNodes.end(),
                                     curvstmt) != matchingNodes.end()){
                            matchednodesbetween.push_back(curvstmt);
#ifdef MYDEBUGBFS
                            llvm::outs() << "Match:" << curv << "\n";
#endif
                        }
                    }
                }

                visitedVertices.insert(curv);
            }
        }
        return matchednodesbetween;
    }


    static const Stmt* findLoopStmtAfterContinueStmt(ControlFlowGraphWithDataFlow* cfggraph, const Stmt* startStmt);


//protected:
//    ASTContext *Context;
//    ControlFlowGraphWithDataFlow *cfggraph;

};


#endif //LIBTOOLINGAST_CONTROLFLOWGRAPHQUERIES_H
