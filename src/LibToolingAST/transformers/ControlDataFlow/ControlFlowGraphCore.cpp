//
// Core Part of Control Flow Graph: See header file for description.
//

#include "ControlFlowGraphCore.h"

// TODO document that if we have templated functions, we only save the generic function, not each specialization.

// TODO fix problem with definition declaration separation. If author just declares function with default value,
// the definition cannot have the default value (compiler will complain about it). So actually if we
// create the new vertex for declaration-only, we need to save the function param's already..

// TODO better support for classes / structs. So far, constructors and methoddecls work, but
// there are often implicit declarations such as copy constructor = and so on...

// TODO - consider function pointers.


ControlFlowGraphCore::ControlFlowGraphCore(ASTContext *Context)
        : Context(Context), sm(Context->getSourceManager()) {};


bool ControlFlowGraphCore::addFunctionDecl(const FunctionDecl *f){

    // Consider declaration without definition.
    if(!f->isThisDeclarationADefinition()){
        // just create a placeholder for the function, since we have just a declaration without definition here.
        // we will overwrite this vertex later when we visit the declaration with definition. In the meantime,
        // in this way we can create edges to this function.
        // Moreover, we always use getUniqueFunctionNameAsString, since >1 functions may have the same name,
        // but vary due to params..
        createNewVertex(0, 0, nullptr, false, f, getUniqueFunctionNameAsString(f), nullptr);
    } else {

        if(!f->hasBody()){
            // s.th. like stall() = default; inside a struct/class will have no body. Not critical, probably.
#ifdef MYDEBUG_CFG
            FullSourceLoc fullLoc_saved(f->getLocStart(), sm);
            llvm::errs() << "Note: Visiting no body function:" << getUniqueFunctionNameAsString(f) << "\t"
                         << "row:" << fullLoc_saved.getSpellingLineNumber() << "\n";
#endif
        }
        visitedfunctions.insert( getUniqueFunctionNameAsString(f) );

#ifdef MYDEBUG_CFG
        llvm::outs() << "......... Visiting Function " << f->getQualifiedNameAsString() << " (" <<
            getUniqueFunctionNameAsString(f) << ")" << " with Def?:" << f->isThisDeclarationADefinition() << "\n";
#endif

        // I. ** Obtain CFG to whole function **
        // If you want to get all AST stmt's into the CFG, not only a high-level view, use
        //      clang::CFG::BuildOptions().setAllAlwaysAdd() .
        auto bo = clang::CFG::BuildOptions().setAlwaysAdd(clang::Stmt::DeclRefExprClass, true);
//        std::unique_ptr<CFG> FooCFG = CFG::buildCFG(f, f->getBody(),
//                                                    Context, bo); //clang::CFG::BuildOptions());

        // Keep CFG alive by adding it to a vector so that AST nodes are still visible when we add other functions later
        FooCFGs.push_back( CFG::buildCFG(f, f->getBody(), Context, bo) ); //clang::CFG::BuildOptions()););
        if (!FooCFGs.back()){
            // no need to show an error, if function is used later, then we have not created a vertex at this point,
            // so Callee is unknown exception will be thrown.
            // example: 3264486_5736519012712448_hmich.cpp (macro expanded, sz is the problem)
            FooCFGs.pop_back();
            return false;
        }

        bool isfirstblock = true;
        // II. ** A CFG consists of multiple CFG blocks, so iterate over them and add all stmt's as vertices. **
        // Consider, at least on the implementing machine, the CFG had the reversed order of the code,
        // means first CFGBlock was last block in code. Thus, we use the reverse_iterator to reverse the order again ;)
        // Note: We cannot save the current CFGBlock in vertex, since after visiting the next function,
        // this cfg block may not exist anymore. Thus, we have to save the statement pointers
        // that of course will live until we finish our analysis.
        for(CFG::reverse_iterator it = FooCFGs.back()->rbegin(); it != FooCFGs.back()->rend(); ++it){
            CFGBlock *cbl = *it;

#ifdef MYDEBUG_CFG
            llvm::outs() << "Block ID: " << cbl->getBlockID() << "\n";
#endif

            // II.A Get all vertices for current block or create them if necessary;
            // If we create the first new block, we also create extra vertices for function parameters
            // although they are not part of clang's CFG.
            std::vector<Graph::vertex_descriptor> vertexdescr = findOrCreateBlock(f, cbl, isfirstblock);
            isfirstblock = false;

            // II.B Now add edges from all predecessors to the starting node of the current block
            for(auto cpred : cbl->preds()) {
                // it can happen that preds is not defined, if block is not reachable, see below Reference (A1)
                if(!cpred)
                    continue;
#ifdef MYDEBUG_CFG
                llvm::outs() << "\tPreds: " << cpred->getBlockID() << "\n";
#endif

                std::vector<Graph::vertex_descriptor> predvertex = findOrCreateBlock(f, cpred, false);
                boost::add_edge(predvertex.back(), vertexdescr.front(), graph);
            }

            // II.C Add Special Edges
            for (auto cfgelem : vertexdescr) {
                const Stmt *CS = graph[cfgelem].stmt;

                // a. Create edge to other functions
                // To this end, check if this block has CallExpr = then we would have an
                // interprocedural edge to a block from another function
                if(CS && isa<CallExpr>(CS)){
                    auto callexp = cast<CallExpr>(CS);
                    if (auto fcallee = dyn_cast<FunctionDecl>(callexp->getCalleeDecl())) {

                        bool declinmainfile = Context->getSourceManager().isInMainFile(fcallee->getLocation());
                        if (declinmainfile) {
                            // Callee is in the same file, continue

                            // Possible that we work with a template; currently we only use the generic template version
                            auto fcallee_template = fcallee->getPrimaryTemplate();
                            if(fcallee_template){
                                fcallee = fcallee_template->getTemplatedDecl();
                            }

                            // Get vertex
                            // We assume that vertex should already exist, as functions should be defined before.
                            // If not, we could try to add this function declaration recursively. Currently, not done,
                            // as not needed, as we either have a definition or decl. before usage.
                            // TODO But for Class Methods???
                            Graph::vertex_descriptor callexprvertex;
                            if(!findStartingVertexForFunction(getUniqueFunctionNameAsString(fcallee), callexprvertex)){

                                // i) Check if called method is instantiated implicitly, e.g. by defining a class.
                                if(auto fcallee_cxxmethoddecl = dyn_cast<CXXMethodDecl>(fcallee)){
                                    if(fcallee_cxxmethoddecl->isCopyAssignmentOperator() ||
                                       fcallee_cxxmethoddecl->isMoveAssignmentOperator() ){
#ifdef MYDEBUG_CFG
                                        llvm::outs() << "\t\t Warning: Skip" << getUniqueFunctionNameAsString(fcallee) << "\n";
#endif
                                        continue;
                                    }
                                }

                                // ii) Handle classes and structs:
                                // Class, structs: here, order does not matter, so that a function can call s.th.
                                //  that is defined later. Thus, we check if fct is inside a RecordDecl and if so,
                                //  we just add the declaration and hopefully will visit the function later...
                                std::vector<const RecordDecl*> record_decl_list =
                                        goUpstairsInASTUntilMatch<RecordDecl, FunctionDecl>(fcallee, Context);
                                if(!record_decl_list.empty()){
#ifdef MYDEBUG_CFG
                                    llvm::outs() << "\t\t Current decl is inside a Record Decl:" << getUniqueFunctionNameAsString(fcallee) << "\n";
#endif
                                    callexprvertex = createNewVertex(0, 0, nullptr, false, fcallee,
                                                                     getUniqueFunctionNameAsString(fcallee), nullptr);

                                } else {

                                    llvm::errs() << "Error: Callee is unknown:"
                                                 << getUniqueFunctionNameAsString(fcallee) << " in "
                                                 << getUniqueFunctionNameAsString(f) << "\n";
                                    return false;

                                }
                            }

                            // Add edge from caller to function start
                            std::pair<Graph::edge_descriptor, bool> e01 =
                                    boost::add_edge(cfgelem, callexprvertex, graph);
                            graph[e01.first].interprocedural = true;
                            graph[cfgelem].calleefunctionname = getUniqueFunctionNameAsString(fcallee);

#ifdef MYDEBUG_CFG
                            llvm::outs() << "\t\t" << "Adding edge between ("
                                         << graph[cfgelem].blockid << "," << graph[cfgelem].functionname << ") and ("
                                         << graph[callexprvertex].blockid << "," << graph[callexprvertex].functionname << ")\n";
#endif

                        }
                    }
                }

                // b. To add new functionality by derived classes.
                // Create special edges, such as declaration edges, ...
                createSpecialEdges(CS, cfgelem, getUniqueFunctionNameAsString(f));
            }
        } // End of CFG Block reverse iteration.
    }
    return true;
}


bool ControlFlowGraphCore::sanity_check(){

    // I. Extract all function names and compare if equals all visited functions
    std::set<std::string> fctnames;
    {
        auto vertices = boost::vertices(graph);
        for (auto it = vertices.first; it != vertices.second; ++it) {
            fctnames.insert(graph[*it].functionname);
        }
    }
    assert(fctnames.size() == visitedfunctions.size());
    return true;
}



Graph::vertex_descriptor ControlFlowGraphCore::getstartingvertex(const Stmt* startStmt){
    if(!startStmt){
        llvm::errs() << "Error: startStmt getvertex is not defined\n";
        throw CFGException();
    }
    if(isa<DeclStmt>(startStmt))
        llvm::errs() << "Warning:" << "You are probably using wrong getvertex method. For DeclStmt, use stmt's decl\n";

    auto vertices = boost::vertices(graph);
    Graph::vertex_descriptor startVertex = 0;
    bool startVertexMatched = false;
    for (auto itv = vertices.first; itv != vertices.second; ++itv) {
        if(graph[*itv].stmt == startStmt){
            startVertex = *itv;
            startVertexMatched = true;
            break;
        }
    }
    if(!startVertexMatched) {
//        llvm::errs() << "Error: Start Vertex not matched in getstartingvertex-stmt\n";
        throw CFGException();
    }
    return startVertex;
}


Graph::vertex_descriptor ControlFlowGraphCore::getstartingvertex(const Decl* startDecl){
    if(!startDecl){
        llvm::errs() << "Error: startStmt getvertex is not defined\n";
        throw CFGException();
    }

    auto vertices = boost::vertices(graph);
    Graph::vertex_descriptor startVertex = 0;
    bool startVertexMatched = false;
    for (auto itv = vertices.first; itv != vertices.second; ++itv) {
        if (graph[*itv].decl == startDecl) {
            startVertex = *itv;
            startVertexMatched = true;
            break;
        }
    }
    if(!startVertexMatched) {
//        llvm::errs() << "Error: Start Vertex not matched in getstartingvertex-decl\n";
        throw CFGException();
    }
    return startVertex;
}


//Graph::vertex_descriptor ControlFlowGraphCore::getstartingvertexViaSourceTextLocationMatch(std::string sourceTextCmp,
//                                                                                           FullSourceLoc fullLocCmp){
//
//    unsigned rowCmp  = fullLocCmp.getSpellingLineNumber();
//
//    auto vertices = boost::vertices(graph);
//    Graph::vertex_descriptor startVertex = 0;
//    bool startVertexMatched = false;
//
//    // Go over all vertices, compare source text and row/column number.
//    for (auto itv = vertices.first; itv != vertices.second; ++itv) {
//
//        if(graph[*itv].stmt && isa<DeclStmt>(graph[*itv].stmt)){
//            FullSourceLoc curFullLoc(graph[*itv].stmt->getLocStart(), sm);
//            std::string curSourceText = getSourceText(*Context, graph[*itv].stmt, false);
//
//            if(sourceTextCmp.find(curSourceText) != std::string::npos
//               && curFullLoc.getSpellingLineNumber() == rowCmp){
//                startVertex = *itv;
//                startVertexMatched = true;
//                break;
//            }
//        }
//
//    }
//    if(!startVertexMatched)
//        throw CFGException();
//    return startVertex;
//}


void ControlFlowGraphCore::consoleoutputOfGraph() {

    // Print the CFG for each function
    for (std::string fctname : visitedfunctions) {
        llvm::outs() << "......... Visiting Function " << fctname << "\n";
        auto vertices = boost::vertices(graph);
        for (auto it = vertices.first; it != vertices.second; ++it) {
            if (graph[*it].functionname == fctname) {
                Graph::out_edge_iterator ei, ei_end;
                for (boost::tie(ei, ei_end) = out_edges(*it, graph); ei != ei_end; ++ei) {
                    Graph::vertex_descriptor tar = boost::target(*ei, graph);
                    Graph::vertex_descriptor src = boost::source(*ei, graph);

                    std::string srctext;
                    if(graph[src].stmt){
                        srctext = graph[src].stmt->getStmtClassName();
                        srctext = srctext + "," + getSourceText(*Context, graph[src].stmt, false);
                    } else if(graph[src].decl){
                        srctext = graph[src].decl->getDeclKindName();
                        srctext = "D/" + srctext + "," + getSourceText(*Context, graph[src].decl, false);
                    }

                    std::string tartext;
                    if(graph[tar].stmt) {
                        tartext = graph[tar].stmt->getStmtClassName();
                        tartext = tartext + "," + getSourceText(*Context, graph[tar].stmt, false);
                        FullSourceLoc fl(graph[tar].stmt->getLocStart(), sm);
                        tartext = tartext + ",(r:" + std::to_string(fl.getSpellingLineNumber())
                                  + ";c:" + std::to_string(fl.getColumnNumber()) + ")";
                    } else if(graph[tar].decl){
                        tartext = graph[tar].decl->getDeclKindName();
                        tartext = "D/" + tartext + "," + getSourceText(*Context, graph[tar].decl, false);
                    }

                    tartext = tartext + ",T:" + std::to_string(graph[tar].isterminatornode);

                    std::cout << "" << src << "[" << srctext << "] --> " << tar << "[" <<  tartext << "]";

                    if (graph[*ei].interprocedural)
                        std::cout << "\t Fct:" << graph[tar].functionname << std::endl;
                    else if(graph[*ei].todeclarationedge)
                        std::cout << "\t <DeclEdge>" << std::endl;
                    else
                        std::cout << ";" << std::endl;
                }

            }
        }
    }
}


std::vector<Graph::vertex_descriptor> ControlFlowGraphCore::findOrCreateBlock(const FunctionDecl *f, CFGBlock *cfgblock,
                                                                              bool isfirstblock) {

    std::vector<Graph::vertex_descriptor> blockvertices = getAllVerticesForBlock(getUniqueFunctionNameAsString(f),
                                                                                 cfgblock->getBlockID());
    if (isfirstblock || blockvertices.empty()) {
        if(isfirstblock)
            assert(blockvertices.size()<=1); // just a small test, can be removed later. todo, actually should be <1 ?

        blockvertices = SaveCFGBlockStatements(f, cfgblock, isfirstblock);

#ifdef MYDEBUG_CFG
        llvm::outs() << "\tcreated new block: " << cfgblock->getBlockID() << "; Length:" << blockvertices.size() << ":" << isfirstblock << "\n";
#endif
    }

    return blockvertices;
}


std::vector<Graph::vertex_descriptor> ControlFlowGraphCore::SaveCFGBlockStatements(const FunctionDecl *f,
                                                                                   CFGBlock *cfgblock, bool isfirstblock){
    std::string fctname = getUniqueFunctionNameAsString(f);
    // I. Create the vertices for all statements in the current CFG Block
    std::vector<Graph::vertex_descriptor> cfgblockvertices;
    unsigned curstmtid = 0;
    for(auto cfgelem : *cfgblock){
        Optional<CFGStmt> CS = cfgelem.getAs<CFGStmt>();
        if (!CS)
            continue;

        Graph::vertex_descriptor predvertex = createNewVertex(cfgblock->getBlockID(),
                                                              curstmtid, CS->getStmt(), false, f,
                                                              fctname, nullptr);
        cfgblockvertices.push_back(predvertex);
        curstmtid++;
    }

    if (cfgblock->getTerminator()){
        Graph::vertex_descriptor predvertex = createNewVertex(cfgblock->getBlockID(), curstmtid,
                                                              cfgblock->getTerminator().getStmt(), true, f,
                                                              fctname, nullptr);
        cfgblockvertices.push_back(predvertex);
        curstmtid++;
    }


    // II. A CFG Block can also be empty: Then, we just save a nullptr stmt. If it is a starting node for a function,
    // we save the parameters as new vertices.
    if(cfgblockvertices.empty()) {

        if (isfirstblock) {

            // pre-step for step B below. We need to look for previous node here, before we create a new one.
            Graph::vertex_descriptor vertexfromdeclarationonly;
            bool haspreviousdeclaration = findStartingVertexForFunction(getUniqueFunctionNameAsString(f),
                                                                        vertexfromdeclarationonly);

            // A. Handle function parameters by adding them as new vertices
            if (!f->parameters().empty()) {
                // Insert the function parameter as new vertices, since they are not part of clang's CFG, as no statements, just
                // declarations -- we add them only, if this is the first block of the function.
                // As the first CFG block from clang is empty, we can simply add the new parameter vertices....
                // If we have no parameters, we add an empty vertex.
                assert(curstmtid == 0);
                for (auto curparmvardecl : f->parameters()) {
                    Graph::vertex_descriptor curparmvertex = createNewVertex(cfgblock->getBlockID(), curstmtid, nullptr,
                                                                             false, f, fctname, curparmvardecl);
                    cfgblockvertices.push_back(curparmvertex);
                    curstmtid++;
                }
            } else {
                Graph::vertex_descriptor predvertex = createNewVertex(cfgblock->getBlockID(),
                                                                      curstmtid, nullptr, false, f,
                                                                      fctname, nullptr);
                cfgblockvertices.push_back(predvertex);
            }

            // B. Handle the case that we can already have a vertex for function (if it had a definition previously)
            // If we had a declaration only for a function, we may already have a vertex for that function
            // in our graph. Of course, this vertex will be empty, since we are parsing a function with definition only.
            // But we need to use this vertex, since there could be some edges to that vertex.
            if (haspreviousdeclaration) {
                copyVertexPropertiesFromTo(cfgblockvertices[0], vertexfromdeclarationonly);
//                remove_vertex(cfgblockvertices[0], graph); // do not use it, due to vecS ?? see docu...
                cleanVertexProperties(cfgblockvertices[0]);
                cfgblockvertices[0] = vertexfromdeclarationonly;
            }

        } else {
            Graph::vertex_descriptor predvertex = createNewVertex(cfgblock->getBlockID(),
                                                                  curstmtid, nullptr, false, f,
                                                                  fctname, nullptr);
            cfgblockvertices.push_back(predvertex);
        }
    }

    // III. Now connect all vertices
    for(unsigned i = 1; i < cfgblockvertices.size(); i++){
        boost::add_edge(cfgblockvertices[i-1], cfgblockvertices[i], graph);
    }

    return cfgblockvertices;
}


Graph::vertex_descriptor ControlFlowGraphCore::createNewVertex(unsigned blockid, unsigned stmtid,
                                                               const Stmt* stmt, bool isterminatornode,
                                                               const FunctionDecl *fdecl, std::string fctname,
                                                               const Decl* decl){

    if(!decl && stmt && isa<DeclStmt>(stmt)){
        // In this way, we directly save the declaration if we save a DeclStmt. Avoids the following problem:
        // If we have a declaration such as float d = 222.98f, d2 = 29.99f, d3 = 30.3f; in one line.
        // Then we have the problem that the CFG will have a DeclStmt for each variable d, d2, d3. But the AST
        // just has a common DeclStmt. By using the Decl, we can find the vertex easier.
        auto stmtdecl = cast<DeclStmt>(stmt);
        decl = stmtdecl->getSingleDecl(); // should/must be a single Decl, since we are in the CFG.
    }

    Graph::vertex_descriptor predvertex = boost::add_vertex(this->graph);
    graph[predvertex].fdecl = fdecl;
    graph[predvertex].functionname = fctname;
    graph[predvertex].blockid = blockid;
    graph[predvertex].stmtid = stmtid;
    graph[predvertex].stmt = stmt;
    graph[predvertex].isterminatornode = isterminatornode;
    graph[predvertex].decl = decl;

    return predvertex;
}

void ControlFlowGraphCore::copyVertexPropertiesFromTo(Graph::vertex_descriptor &from, Graph::vertex_descriptor &to) {
    graph[to].fdecl = graph[from].fdecl;
    graph[to].functionname = graph[from].functionname;
    graph[to].blockid = graph[from].blockid;
    graph[to].stmtid = graph[from].stmtid;
    graph[to].stmt = graph[from].stmt;
    graph[to].isterminatornode = graph[from].isterminatornode;
    graph[to].decl = graph[from].decl;
}

void ControlFlowGraphCore::cleanVertexProperties(Graph::vertex_descriptor &to) {
    graph[to].fdecl = nullptr;
    graph[to].functionname = "cleaned____";
    graph[to].blockid = 0;
    graph[to].stmtid = 0;
    graph[to].stmt = nullptr;
    graph[to].isterminatornode = false;
    graph[to].decl = nullptr;
}


std::vector<Graph::vertex_descriptor> ControlFlowGraphCore::getAllVerticesForBlock(std::string functionname,
                                                                                   unsigned blockid) {

    std::vector<Graph::vertex_descriptor> matches;

    auto vertices = boost::vertices(graph);
    for (auto itv = vertices.first; itv != vertices.second; ++itv) {
        // Compare block id's
        if (graph[*itv].blockid == blockid && graph[*itv].functionname == functionname) {
            matches.push_back(*itv);
        }
    }

    std::sort (matches.begin(), matches.end(), StmtIdCmp(&graph));
    return matches;
}


bool ControlFlowGraphCore::findStartingVertexForFunction(const std::string &functionname,
                                                         Graph::vertex_descriptor &targetvertex){
    unsigned maxblocknumber = 0;
    unsigned minstmtnumber = INT32_MAX;
    bool matched = false;
    auto vertices = boost::vertices(graph);
    for (auto itv = vertices.first; itv != vertices.second; ++itv) {
        if(graph[*itv].functionname == functionname && graph[*itv].blockid >= maxblocknumber
           && graph[*itv].stmtid <= minstmtnumber) {
            maxblocknumber = graph[*itv].blockid;
            minstmtnumber = graph[*itv].stmtid;
            targetvertex = *itv;
            matched = true;
        }
    }
    return matched;
}


bool ControlFlowGraphCore::findEndVertexForFunction(const std::string &functionname,
                                                    Graph::vertex_descriptor &targetvertex){

    bool matched = false;
    auto vertices = boost::vertices(graph);
    for (auto itv = vertices.first; itv != vertices.second; ++itv) {

        if(graph[*itv].functionname == functionname && graph[*itv].blockid == 0) {
            if(!matched){
                targetvertex = *itv;
                matched = true;
            } else {
                // there should be only one vertex in final CFG block
                llvm::errs() << "Error: Final CFG Block has more than one vertex\n";
                return false;
            }
        }
    }
    return matched;
}


void ControlFlowGraphCore::createSpecialEdges(const Stmt *s, Graph::vertex_descriptor &fromvertex, std::string fctname) {
    // you can overwrite me if you extend the core functionality.
}

std::set<std::string> ControlFlowGraphCore::getStringSetOfVisitedFunctions() {
    return visitedfunctions;
}

// Reference A1
//#define DEBUG 0
//int main() {
//    if (!DEBUG) {
//        freopen("in", "r", stdin);
//        freopen("out", "w", stdout);
//    }
//    int t, T = 1;
//    ...
//  This will lead to two paths in CFG where one path actually does not exist...
