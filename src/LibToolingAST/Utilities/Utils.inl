/**
 * This function prints a hashmap of [string, T] in the format such that we can read it in Python.
 * T can be an arbitrary type, e.g. int or float.
 * @param map
 * @param InFile
 */
template <typename T>
void printhashmap(const std::unordered_map<std::string, T> &map, const std::string &InFile){
    // First, print the user name and the current file
    llvm::outs() << extract_name(split_path(InFile)[1]) << " "
                 << split_path(InFile)[1] << " [";

    // Go over all elements; we use firstelem
    // so that we do not set a comma when printing the first element:
    bool firstelem = true;
    for(auto const &ent1: map){
        //ent1.first is the key, ent1.second is its value
        if(firstelem){
            llvm::outs() << "[" << ent1.first << ", " << ent1.second << "]" << "";
            firstelem = false;
        } else {
            llvm::outs() << ", [" << ent1.first << ", " << ent1.second << "]" << "";
        }

    }

    // Print last ] to close list of all types
    llvm::outs() << "] \n";
}

/**
 * This function prints two hashmaps of [string, T] and [string,string] in the format such that
 * we can read it in Python. T can be an arbitrary type, e.g. int or float.
 * @param map
 * @param map2
 * @param InFile
 */
template <typename T>
void printhashmap(const std::unordered_map<std::string, T> &map,
                        std::unordered_map<std::string, std::string> &map2,
                        const std::string &InFile){
    // First, print the user name and the current file
    llvm::outs() << extract_name(split_path(InFile)[1]) << " "
                 << split_path(InFile)[1] << " [";

    // Go over all elements; we use firstelem
    // so that we do not set a comma when printing the first element:
    bool firstelem = true;
    for(auto const &ent1: map){
        std::string ent2 = map2[ent1.first];

        //ent1.first is the key, ent1.second is its value
        if(firstelem){
            llvm::outs() << "[" << ent1.first << ", " << ent1.second << ", " << "\"" + ent2 + "\"" << "]" << "";
            firstelem = false;
        } else {
            llvm::outs() << ", [" << ent1.first << ", " << ent1.second << ", " << "\"" + ent2 + "\"" << "]" << "";
        }
    }

    // Print last ] to close list of all types
    llvm::outs() << "] \n";
}

/**
 * Go down - Statements.
 *
 * Function traverses the AST from the start stmt recursively and saves all matching S stmt's in vector
 * by call by reference. It is focused on Statements, since we can only get Stmt's as children.
 * @tparam S template for a particular stmt class, e.g. DeclStmt.
 * @param curstmt the start stmt
 * @param declrexpr a vector that will be filled with all matching statements
 */
template <typename S>
void recursiveStmtTVisit(const clang::Stmt *curstmt, std::vector<const S*> &declrexpr) {
    if (const S* dec = clang::dyn_cast<S>(curstmt)) {
        declrexpr.push_back(dec);
    }

    const auto &children = curstmt->children();
    for (const clang::Stmt *child : children) {
        if (child) {
            recursiveStmtTVisit<S>(child, declrexpr);
        }
    }
}

/**
 * Go upwards - Statements, Declarations, Types...
 *
 * Function traverses the AST from the start node recursively above and saves all matching S NodeType's in vector;
 * by call by reference. We can have any node type (stmt, type, decl), if we go above in the AST.
 *
 * For instance, for a certain DeclRefExpr, we want to get DeclStmt one level above.
 * Write:
 * `std::vector<const DeclStmt*> dslist;
 *  ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*vardeclr);
 *  goUpstairsInAST<DeclStmt>(dtn, dslist, 1, Context);
 * `
 * You will find all found DeclStmt's in the vector dslist.
 *
 * @tparam N template for a particular Node Type, e.g. Stmt, DeclStmt, Decl.
 * @param curnode the start DynTypedNode.
 * @param matchednodes a vector that will be filled with all matching NodeTypes
 * @param height set the wanted levels that we want to go above in the AST,
 * if -1, then we go so far we can in the AST and maybe far beyond...
 * @param Context the AST context
 */
template <typename N>
void goUpstairsInAST(clang::ast_type_traits::DynTypedNode curnode, std::vector<const N*> &matchednodes, int height,
                         clang::ASTContext *Context) {

    if(height==0)
        return;

    if(height!=-1)
        height--;
    auto parents = Context->getParents(curnode);
    for(auto par : parents){
        const N* parentpointer = par.get<N>();
        if(parentpointer){
            matchednodes.push_back(parentpointer);
        }
        goUpstairsInAST<N>(par, matchednodes, height, Context);
    }
}

/**
 * A wrapper around goUpstairsInAST. It will call goUpstairsInAST with an increasing height each time until
 * some node(s) with class N is/are found.
 * @tparam N template for a particular Node Type, e.g. Stmt, DeclStmt, Decl.
 * @tparam M the class of inputnode
 * @param inputnode Stmt, DeclStmt, Decl, ...
 * @param maxheight the max height where goUpstarsInAST will be called. Can be arbitrary,
 * just used to prevent an infinite loop.
 * @param Context the AST Context
 * @return a list with found elements.
 */
template <typename N, typename M>
std::vector<const N*> goUpstairsInASTUntilMatch(const M* inputnode, clang::ASTContext *Context, int maxheight = 25) {
    std::vector<const N*> dslist;
    clang::ast_type_traits::DynTypedNode dtnarr = clang::ast_type_traits::DynTypedNode::create(*inputnode);
    // We try each level above, first only level above, then two levels, then three levels until we find..
    int j = 1;
    while(j < maxheight && dslist.empty()){
        goUpstairsInAST<N>(dtnarr, dslist, j, Context);
        j++;
    }
    return dslist;
}