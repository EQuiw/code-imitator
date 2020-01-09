#include "DeclRefMapping.h"



DeclRefMapping::DeclRefMapping(ASTContext *Context) : sm(Context->getSourceManager()) {};


bool DeclRefMapping::insert_declref(const DeclRefExpr* d) {

    // get Decl to DeclRefExpr
    if(auto ddecl = dyn_cast<VarDecl>(d->getDecl())){
//        auto slkey = getkeySourceLocation(ddecl->getLocStart());

        if(declrefmap.find(ddecl) != declrefmap.end()){
            // d is already in
            declrefmap[ddecl].push_back(d);
//            sourcelocationtovardecls[slkey].push_back(ddecl);
        } else {
//            std::vector<const DeclRefExpr*> dvec;
//            dvec.push_back(d);
//            declrefmap[ddecl] = dvec;
            declrefmap[ddecl] = std::vector<const DeclRefExpr*> {d};
//            sourcelocationtovardecls[slkey] = std::vector<const VarDecl*> {ddecl};
        }

        return true;
    } else {
        return false;
    }

}

bool DeclRefMapping::insert_vardecl(const VarDecl* d){
    auto slkey = getRowColumn(d->getLocStart(), sm, false);

    if(sourcelocationtovardecls.find(slkey) != sourcelocationtovardecls.end()){
        // sl is already in
        sourcelocationtovardecls[slkey].push_back(d);
    } else {
        sourcelocationtovardecls[slkey] = std::vector<const VarDecl*> {d};
    }
    return true;
}


std::vector<const DeclRefExpr*> DeclRefMapping::getVarDeclToDeclRefExprs(const VarDecl* ddecl){

    if(declrefmap.find(ddecl) != declrefmap.end()){
        // d is already in
        return declrefmap[ddecl];
    } else {
        std::vector<const DeclRefExpr*> dvec;
        return dvec;
    }

}


bool DeclRefMapping::insert_declstmt(const DeclStmt* ds) {

    if(declstmttovardecls.find(ds) == declstmttovardecls.end()) {
        declstmttovardecls[ds] = std::vector<const VarDecl*> {};
    }

    // Iterate over all variable declarations of current declaration statement
    for (DeclStmt::const_decl_iterator db = ds->decl_begin(), de = ds->decl_end(); db != de; ++db) {
        const Decl *vd = *db;
        if (auto vardecl = dyn_cast<VarDecl>(vd)) {
            declstmttovardecls[ds].push_back(vardecl);
        }
    }

    return true;
}

const DeclStmt* DeclRefMapping::getVarDeclToDeclStmt(const VarDecl* vd){

    // Iterate over DeclStmt to VarDecl Hashmap and find key

    for(std::map<const DeclStmt*, std::vector<const VarDecl*>>::iterator iter = declstmttovardecls.begin();
        iter != declstmttovardecls.end(); ++iter)
    {
        const DeclStmt* k =  iter->first;
        auto v = iter->second;

        for(auto e : v){
            if (e==vd){
                return k;
            }
        }

    }

    return nullptr;
}

std::vector<const VarDecl*> DeclRefMapping::getDeclStmtToVarDecls(const DeclStmt* ds){
    if(declstmttovardecls.find(ds) != declstmttovardecls.end()){
        // d is already in
        return declstmttovardecls[ds];
    } else {
        return std::vector<const VarDecl*>{};
    }
}


std::vector<const VarDecl*> DeclRefMapping::getSourceLocationToVarDecls(SourceLocation sl){
    auto slkey = getRowColumn(sl, sm, false);
    return getSourceLocationToVarDecls(slkey);
}

std::vector<const VarDecl*> DeclRefMapping::getSourceLocationToVarDecls(std::pair<unsigned,unsigned> slkey){

    if(sourcelocationtovardecls.find(slkey) != sourcelocationtovardecls.end()){
        // sl is already in
        auto slarr = sourcelocationtovardecls[slkey];

        // Sort w.r.t to row, column
        struct Local {
            explicit Local(SourceManager* sml) { sm = sml; }
            bool operator () ( const VarDecl* lhs, const VarDecl* rhs ){
                FullSourceLoc fullLocLhs_saved(lhs->getLocEnd(), *sm);
                FullSourceLoc fullLocRhs_saved(rhs->getLocEnd(), *sm);

                if(fullLocLhs_saved.getSpellingLineNumber() == fullLocRhs_saved.getSpellingLineNumber())
                    return fullLocLhs_saved.getSpellingColumnNumber() < fullLocRhs_saved.getSpellingColumnNumber();

                return fullLocLhs_saved.getSpellingLineNumber() < fullLocRhs_saved.getSpellingLineNumber();
            }

            const SourceManager* sm;
        };
        std::sort( slarr.begin( ), slarr.end( ), Local(&sm));
        return slarr;
    } else {
        return std::vector<const VarDecl*>{};
    }
}
