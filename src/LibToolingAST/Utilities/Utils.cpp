#include <llvm/Support/raw_ostream.h>
#include "Utils.h"


std::vector<std::string> split_path(const std::string &path) {
    // split path
    std::size_t dirpos = path.find_last_of("/");
    // +1 is necessary so that directory contains the last '/', and not file
    // get directory
    std::string dir = path.substr(0, dirpos+1);
    // get file
    std::string file = path.substr(dirpos+1, path.length());

    std::vector<std::string> data;
    data.push_back(dir);
    data.push_back(file);
    return data;
}


std::string extract_name(const std::string &uid) {

    // split uid
    std::size_t pos = uid.find_last_of(".");
    // get file name
    std::string file = uid.substr(0, pos);
    // get file ending
    std::string fileending = uid.substr(pos, uid.length());

    // split file name, +1 because '_' should not be in the file name
    // get the 2nd occurence of '_' because a user name could contain this letter as well.
    std::size_t pos2 = file.find("_");
    std::string usertemp = file.substr(pos2+1, file.length());
    std::size_t pos3 = usertemp.find("_");
    std::string userfinal = usertemp.substr(pos3+1, usertemp.length());

    // return everything
    return userfinal;
}

int getdepthfornode(const clang::ASTContext::DynTypedNodeList &parents,
                    clang::ASTContext *Context, int currentdepth, std::string &curfile) {

        // A. Check whether empty parent, means we stop the walk and return the depth
        if ( parents.empty() ) {
            return currentdepth;
        } else {
            // B. If multiple parents, iterate over each one of them and take the maximum depth afterwards
//            if(parents.size()>1)
//                llvm::errs() << "Parent size=" << parents.size() << " in " << curfile << "\n";

            int temporarydepthmax = currentdepth;
            int temporarydepth;
            for(auto par : parents){
                const auto *ST = par.get<clang::Stmt>();
                const auto *DC = par.get<clang::Decl>();
                const auto *TL = par.get<clang::Type>();
                const auto *TLloc = par.get<clang::TypeLoc>();
//                const auto *NN = par.get<clang::NestedNameSpecifier>();
//                const auto *NNloc = par.get<clang::NestedNameSpecifierLoc>();

                if (ST||DC||TL||TLloc) {
                    temporarydepth = getdepthfornode(Context->getParents(par), Context, ++currentdepth, curfile);
                    if(temporarydepth > temporarydepthmax){
                        temporarydepthmax = temporarydepth;
                    }
                }
            }
            currentdepth = temporarydepthmax;
        }
        return currentdepth;
}


void insertindepthhashmap(std::unordered_map<std::string, int> &map,
                          std::unordered_map<std::string, float> &map_avgdepth,
                          const std::string &str, const int currentdepth){
    // "Incremental averaging", so let's ensure that we also have the number of terms so far
    // Fortunately, map exactly stores this piece of information.
    if(map.find("\"" + str + "\"") == map.end()){
        // just small check. Ensure that map also contains this key.
        llvm::errs() << "Error: Avg Depth -- map does not have the #elements for current str" << "\n";
    }

    // Now update if necessary
    if(map_avgdepth.find("\"" + str + "\"") != map_avgdepth.end()){
        // str is already in, get #params that have been calculated so far.
        // If you are not familiar with incremental average, look at
        // 'https://math.stackexchange.com/questions/106700/incremental-averageing'.
        int n = map["\"" + str + "\""];
        // we add the (n+1)th number..
        map_avgdepth["\"" + str + "\""] = ((n-1)*map_avgdepth["\"" + str + "\""]
                                                 + currentdepth)/(n);
    } else {
        if(map["\"" + str + "\""] != 1)
            llvm::errs() << "Error: insertindepthhasmap else branch" << "\n";

        map_avgdepth["\"" + str + "\""] = currentdepth;
    }
}


bool CheckIsChildOf(clang::ast_type_traits::DynTypedNode currentchild,
                     clang::ast_type_traits::DynTypedNode parent, clang::ASTContext *Context){

    if(currentchild == parent)
        return true;

    for(auto par : Context->getParents(currentchild)){
        if(CheckIsChildOf(par, parent, Context))
            return true;
    }

    return false;
}


bool checkifcontrolstmt(const clang::Stmt *s){
    return (clang::isa<clang::IfStmt>(s) || clang::isa<clang::ForStmt>(s) || clang::isa<clang::WhileStmt>(s)
            || clang::isa<clang::DoStmt>(s) ||
            clang::isa<clang::SwitchStmt>(s) || clang::isa<clang::CXXTryStmt>(s) ||
            clang::isa<clang::CXXForRangeStmt>(s) || clang::isa<clang::CapturedStmt>(s));
}



bool isWithinCompoundStmt(clang::ASTContext &Context, clang::ast_type_traits::DynTypedNode dtn){

    auto parents = Context.getParents(dtn);
    for(auto par : parents) {
        auto parentpointer = par.get<clang::Stmt>();
        if (clang::isa<clang::CompoundStmt>(parentpointer))
            return true;

        if (checkifcontrolstmt(parentpointer))
            return false;

        return (isWithinCompoundStmt(Context, par));
    }
    return false;
}