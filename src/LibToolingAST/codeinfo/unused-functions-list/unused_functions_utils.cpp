#include "unused_functions_utils.h"



std::vector<const FunctionDecl*> get_unused_functions_approximative(std::vector<const FunctionDecl*> fctdecls,
                                                      ASTContext &Context,
                                               ControlFlowGraphWithDataFlow *cfggraph) {

    std::vector<const FunctionDecl*> unused_fctdecls;

    for(const FunctionDecl* f : fctdecls){
        try{
            if(f->isMain())
                continue;
            if(isa<CXXConstructorDecl>(f))
                continue;
            if(f->isOverloadedOperator())
                continue;

            std::vector<const CallExpr *> callexprs =
                    ControlDataFlowGraphQueryHandler::queryAllCallExprsToFunction(cfggraph, f);
            // Simple Case
            if(callexprs.empty()){
                unused_fctdecls.push_back(f);
            } else {
                // Spot if function is called recursively, but not from outside
                bool unused = true;
                for(auto c : callexprs){
                    if(!is_call_expr_reference_to_itself(c, f, Context)){
                        unused = false;
                    }
                }

                if (unused)
                    unused_fctdecls.push_back(f);
            }

        } catch(CFGException &e){
            llvm::errs() << "Error with CFG: Could not list fct-name\n";
        }
    }

    return unused_fctdecls;
}


    bool is_call_expr_reference_to_itself(const CallExpr *c, const FunctionDecl* f, ASTContext &Context){

        // A. Get function where code block is in
        std::vector<const FunctionDecl*> declfcts;
        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*c);

        goUpstairsInAST<FunctionDecl>(dtn, declfcts, -1, &Context);
        if(declfcts.size()!=1){
            llvm::errs() << "Wrong Number of Parent Functions during Fct Check\n";
            return false;
        }

        // B. Now check if they match with function
        return getUniqueFunctionNameAsString(declfcts[0]) == getUniqueFunctionNameAsString(f);
    }


//  TODO function pointers are not considered so far.
std::vector<std::pair<const FunctionDecl *, unsigned>> get_unused_functions(std::vector<const FunctionDecl*> fctdecls,
                                                                    ASTContext &Context,
                                                                    ControlFlowGraphWithDataFlow *cfggraph,
                                                                    bool consider_overloaded) {

    std::vector<std::pair<const FunctionDecl *, unsigned>> unused_fctdecls;

    // get main:
    const FunctionDecl* maindecl = nullptr;
    for(const FunctionDecl* f : fctdecls) {
        if(f->isMain())
            maindecl = f;
    }
    if(maindecl == nullptr) {
        llvm::errs() << "Could not find main in get_unused_functions" << "\n";
        throw CodeTransformationException();
    }

    for(const FunctionDecl* f : fctdecls) {
//        llvm::errs() << getUniqueFunctionNameAsString(f) << "\n";
        bool isneeded = false;

        try {
            if (f->isMain())
                continue;
            if (isa<CXXConstructorDecl>(f))
                continue;
            if (f->isOverloadedOperator() && !consider_overloaded)
                continue;
            if (f->isOverloadedOperator() && isa<CXXMethodDecl>(f)) {
                // we do not continue if f is overloaded and part of a struct/class.
                // Problem, e.g., if we overload a compare operator, then it is hard to find out
                // if another class uses this overloaded method...
                continue;
            }


            std::vector<const CallExpr *> callexprs =
                    ControlDataFlowGraphQueryHandler::queryAllCallExprsToFunction(cfggraph, f);
            unsigned incoming_edges = 0;

            // Simple Case
            if(callexprs.empty()) {
                isneeded = false;
            } else {
                // determine the number of incoming edges.. exclude edges from the function itself
                for(auto c : callexprs){
                    if(!is_call_expr_reference_to_itself(c, f, Context)){
                        incoming_edges++;
                    }
                }

                // Overall Strategy: Path to constructor/main?
                // Search Strategy:
                // a. if within a record, then we search a path to constructor. If a path exists, this method is needed.
                // b. if within a record, and no path to constructor. Check for path to main.
                // c. if not within a record, check for path to main.
                //  Alternative Overall Strategy: we could go over each function, check if incoming edges,
                //      if no, mark fct., iterate again over all fcts, check if incoming edges except marked fcts, and so on...

                std::vector<const FunctionDecl *> querypoints;

                if (auto md = dyn_cast<CXXMethodDecl>(f)) {

                    const RecordDecl *rd = md->getParent();
                    if (auto cxxrd = dyn_cast<CXXRecordDecl>(rd)) {
                        for (clang::CXXRecordDecl::ctor_iterator it = cxxrd->ctor_begin();
                             it != cxxrd->ctor_end(); ++it) {
                            const CXXConstructorDecl *ra = (*it);
//                            llvm::errs() << "->" << getUniqueFunctionNameAsString(ra)
//                                         << ":" << ra->isDefaultConstructor()
//                                    << ":" << ra->isCopyOrMoveConstructor()
//                                    << ":" << ra->isConvertingConstructor(true)
//                                    << ":" << ra->isInheritingConstructor()
//                                    << ":" << ra->isSpecializationCopyingObject()
//                                    << ":" << ra->isMoveConstructor()
//                                    << ":" << ra->isExplicitSpecified() << ra->isExplicit()
//                                    << "\n";

                            // we will get multiple (implicit) constructors, such as copy, move constructors.
                            // they were not part of the CFG, as not written by user. Thus we check if they are
                            // in the set of functions.
                            for(const FunctionDecl* fx : fctdecls) {
                                if(fx == ra)
                                    querypoints.push_back(ra);
                            }
                        }
                    } else {
                        llvm::errs() << "Unused Fcts: No CXXRecordDecl for CXXMethodDecl\n";
                        throw CodeTransformationException(); //
                    }

                    // a.
                    for (auto qr : querypoints) {
                        bool response = ControlDataFlowGraphQueryHandler::isthereapathtofct(cfggraph, &Context, f, qr);
                        if (response) {
                            isneeded = true;
                            break;
                        }
                    }

                    // b.
                    if (!isneeded) {
                        isneeded = ControlDataFlowGraphQueryHandler::isthereapathtofct(cfggraph, &Context, f, maindecl);
                    }

                } else {
                    // c.
                    isneeded = ControlDataFlowGraphQueryHandler::isthereapathtofct(cfggraph, &Context, f, maindecl);
                }
            }

            // if not used, add it to vector of unused fcts.
            if(!isneeded){
                unused_fctdecls.emplace_back(f, incoming_edges);
            }

        } catch(CFGException &e){
            llvm::errs() << "Error with CFG: Could not list fct-name in get-unused-fcts\n";
            throw CodeTransformationException(); //
        }

    }

//    for(const FunctionDecl* f : unused_fctdecls) {
//        llvm::errs() << "Unused:->" << f->getNameAsString() << "\n";
//    }

    return unused_fctdecls;
}