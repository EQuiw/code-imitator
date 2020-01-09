#include "Utils2.h"

bool check_if_vardecl_ispartof_recorddecl(const VarDecl * dx, SourceManager& sm){
    // Resolve Elaborated Type.

    auto trr = dx->getType();
    auto tr = trr->getAs<clang::ElaboratedType>();

    if(tr != nullptr){
        auto etnt = tr->getNamedType().getTypePtr();
        while(isa<ElaboratedType>(etnt)){
            if(auto te = dyn_cast<ElaboratedType>(etnt)) // to do - remove unnecessary dyn_cast + if.
                etnt = te->getNamedType().getTypePtr();
        }

        const RecordType* record_type = etnt->getAs<clang::RecordType>();
        if (record_type != nullptr) {
//            llvm::errs() << dx->getNameAsString() << ":" << record_type->getDecl()->getNameAsString() << "\n";

            auto dx_start = getRowColumn(dx->getLocStart(), sm, false);
            auto record_def_start = getRowColumn(record_type->getDecl()->getDefinition()->getLocStart(), sm, false);

            // now check if both declaration/defs. have the same row and col as start
            return dx_start.first == record_def_start.first && dx_start.second == record_def_start.second;

        } else {
            return false;
        }
    }
    return false;
}


void resolve_inner_types(QualType ctype, std::vector<QualType> &includes){

    if(auto tvt = dyn_cast<TemplateSpecializationType>(ctype)) {
        // Is a TemplateSpecializationType such as priority_queue<S> where S may be a class or struct.

        for(unsigned i = 0; i < tvt->getNumArgs(); i++){
            auto argtype = tvt->getArg(i).getAsType();

            // todo following if-check is necessary for cases with:
            //       auto groups = array<Group, 3>{{{R, 'R'}, {Y, 'Y'}, {B, 'B'}}};
            if(argtype.getAsString().empty()){
                llvm::errs() << "Warning: argtype in resolve inner types is empty string\n";
            } else{
                resolve_inner_types(argtype, includes);
            }
        }

    } else if(auto et = dyn_cast<ElaboratedType>(ctype) ){
        // Is an ElaboratedType, such as std::priority_queue<S>; we need to unpack it.
        auto etnt = et->getNamedType();
        resolve_inner_types(etnt, includes);
    } else {
        // is unpacked.
        includes.push_back(ctype);
    }
}