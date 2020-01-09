#include "InterfaceStdinOutRewriter.h"

InterfaceStdinOutRewriter::InterfaceStdinOutRewriter(ASTContext &Context, Rewriter &OurRewriter, ControlFlowGraphWithDataFlow* cfggraph,
                                   std::string &cinorcout)
            : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()), cfggraph(cfggraph),
              cinorcout(cinorcout) {
    if (cinorcout.find("cin") != std::string::npos)
        streamarrows = ">>";
    if (cinorcout.find("cout") != std::string::npos)
        streamarrows = "<<";
};


bool InterfaceStdinOutRewriter::transformIfStream(const CXXConstructExpr* e, std::vector<const Expr*> inputexpr) {

#ifdef MYDEBUG
    llvm::errs() << "IfStream:" << getSourceText(Context, e) << "\t" << inputexpr.size() << "\n";
#endif

    // A. Check that we have only one input stream type, otherwise we cannot change it to cin,
    // as there is already some piped input or other opened files..
    if (inputexpr.size() != 1)
        return false;

    // B. Collect all references in source code
    // We first collect all possible rewritings and if everything is ok, we do the rewriting.
    std::vector<std::tuple<SourceRange, std::string>> rewritinglocations;

    // B-1 We need the parent of current node, the var decl.
    std::vector<const VarDecl*> dslist =
            goUpstairsInASTUntilMatch<VarDecl, CXXConstructExpr>(e, &Context);

    if(dslist.size() != 1){
        llvm::errs() << "Error: Not exactly one VarDecl to CXXConstructExpr:" << getSourceText(Context, e) << "\n";
        return false;
    }
    auto vardecl = dslist[0];


    // B-2 Find the references via CFG and determine the necessary rewriting
    try {
        std::vector<const DeclRefExpr *> declrefexprs =
                ControlDataFlowGraphQueryHandler::queryAllStmtsForDecl(cfggraph, vardecl);

        for(auto curdeclrefexpr : declrefexprs){

            try{
                std::tuple<SourceRange, std::string> rewriting = getRewritingForCXXConstructExprRef(curdeclrefexpr);
                rewritinglocations.push_back(rewriting);
            } catch(CodeTransformationException &ce){
                llvm::errs() << "Error: CXXConstructExprRef no rewriting possible for DeclRef at"
                             << getRowColumn(curdeclrefexpr->getLocStart(), sm).first << "\n";
                return false;
            }

        }

    } catch(CFGException &e){
        llvm::errs() << "Note: Could not find a Decl in graph for:"
                     << getSourceText(Context, vardecl) << " but everything is fine?! \n";
        return false;
    }

    // C. Now rewrite
    // C-1 Remove initial declaration
    OurRewriter.RemoveText(getSourceRangeWithSemicolon(Context, vardecl));
    // C-2 Remove all occurences
    for(auto &rewr : rewritinglocations){
        if(std::get<1>(rewr).empty()){
            // empty string means we delete code from source range
            OurRewriter.RemoveText(std::get<0>(rewr));
        } else {
            OurRewriter.ReplaceText(std::get<0>(rewr), std::get<1>(rewr));
        }
    }

    // D. remove fstream library if no other ofstreams are used.. TODO


    return true;
}


std::tuple<SourceRange, std::string> InterfaceStdinOutRewriter::getRewritingForCXXConstructExprRef(const DeclRefExpr* curdeclrefexpr){

    // Case A. CXXMemberCallExpr: from clang docu "Represents a call to a member function".
    {
        std::vector<const CXXMemberCallExpr*> dslist =
                goUpstairsInASTUntilMatch<CXXMemberCallExpr, DeclRefExpr>(curdeclrefexpr, &Context);

        if(!dslist.empty()){
            std::string membercall = dslist[0]->getMethodDecl()->getQualifiedNameAsString();
            // Case A-1, A-2: open or close
            if(membercall.find("open") != std::string::npos ||
               membercall.find("close") != std::string::npos){
                return std::make_tuple(getSourceRangeWithSemicolon(Context, dslist[0]), "");
            }

        }
    }

    // Case B. CXXOperatorCallExpr: from clang docu "A call to an overloaded operator written
    // using operator syntax." For instance, '>>' is such an operator.
    {
        std::vector<const CXXOperatorCallExpr*> dslist =
                goUpstairsInASTUntilMatch<CXXOperatorCallExpr, DeclRefExpr>(curdeclrefexpr, &Context);
        if(!dslist.empty()){
            std::string opcall = getSourceText(Context, dslist[0]->getOperatorLoc(),
                                               dslist[0]->getOperatorLoc().getLocWithOffset(0));
            if(opcall == this->streamarrows){
                return std::make_tuple(curdeclrefexpr->getSourceRange(), this->cinorcout);
            }
        }
    }

    // Case C. Not considered, yet: throw exception
    throw CodeTransformationException();

};



