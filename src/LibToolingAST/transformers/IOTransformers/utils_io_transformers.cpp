#include "utils_io_transformers.h"


std::vector<const CXXOperatorCallExpr*> get_cxxopcallexprs(const CallExpr* e, SourceManager* sm, const std::string &arrows) {

    // A. Each CXXOperatorCallExpr object corresponds to a >> expression. Get all under current call expr in AST.
    std::vector<const CXXOperatorCallExpr*> cxxops;
    recursiveStmtTVisit<CXXOperatorCallExpr>(e, cxxops);
    // filter out all CXXOpCallExpr's that do not contain '<<':
    for(long i = (long) cxxops.size()-1; i >= 0; i--){
        if(cxxops[i]->getDirectCallee()){
//            llvm::errs() << "found:" << cxxops[i]->getDirectCallee()->getQualifiedNameAsString() << "\n";
            if(cxxops[i]->getDirectCallee()->getQualifiedNameAsString().find("operator" + arrows) == std::string::npos){
//                    llvm::errs() << "erase...\n" << cxxops[i]->getDirectCallee()->getQualifiedNameAsString() << "\n";
                cxxops.erase(cxxops.begin()+i);
            }
        } else {
            llvm::errs() << "CXXOpCallExpr unvalid in list\n";
            throw CodeTransformationException();
        }
    }

    // B. If size<=1, we have actually no >> separator...
    if(cxxops.empty()){
        llvm::errs() << "cin command has empty set of cxx operator call expressions\n";
        throw CodeTransformationException();
    }

    // C. Sort Call Expr's w.r.t to column number; so that first cout expr is first expr.
    struct Local {
        explicit Local(SourceManager* sml) { sm = sml; }
        bool operator () ( const CXXOperatorCallExpr* lhs, const CXXOperatorCallExpr* rhs ){
            FullSourceLoc fullLocLhs_saved(lhs->getArg(1)->getLocStart(), *sm);
            FullSourceLoc fullLocRhs_saved(rhs->getArg(1)->getLocStart(), *sm);

            if(fullLocLhs_saved.getSpellingLineNumber() < fullLocRhs_saved.getSpellingLineNumber())
                return true;
            return fullLocLhs_saved.getSpellingColumnNumber() < fullLocRhs_saved.getSpellingColumnNumber();
        }

        const SourceManager* sm;
    };
    std::sort( cxxops.begin( ), cxxops.end( ), Local(sm));

    // D. Check that each cxxop expr has 2 args.
    for(auto s : cxxops) {
        if (s->getNumArgs() != 2) {
            llvm::errs() << "CxxOpCallExpr has more than 2 arguments; currently not expected\n";
            throw CodeTransformationException();
        }
    }

    return cxxops;
}

bool check_if_streams_are_mixed(const std::vector<const Expr*> &cppexprs, const std::vector<const Expr*> &cppstreamexpr,
                                const std::vector<const CallExpr*> &cexprs){

    return (!cppexprs.empty() || !cppstreamexpr.empty()) && !cexprs.empty();
}