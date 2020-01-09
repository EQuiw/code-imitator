#include "Utils_Declarations.h"


UtilsDeclarations::UtilsDeclarations(ASTContext &Context)  : Context(Context) {};

bool UtilsDeclarations::check_for_name_conflict(const Stmt* Outer, const VarDecl* Inner) {

    // A. Find upper CompoundStmt to Outer Stmt
    auto upperlevel = goUpstairsInASTUntilMatch<CompoundStmt, Stmt>(Outer, &Context);
    if(upperlevel.size() != 1){
        llvm::errs() << "Failure to find unique Compound Stmt\n";
        return false;
    }

    // B. Check if there is a variable declaration with same name
    const auto CS = upperlevel[0];
    for (CompoundStmt::const_body_iterator I = CS->body_begin(), EI = CS->body_end();
         I != EI; ++I) {

        // DeclStmt's
        auto *DS = dyn_cast<DeclStmt>(*I);
        if(DS) {
            for (DeclStmt::decl_iterator J = DS->decl_begin(); J != DS->decl_end(); ++J) {
                NamedDecl *ND = dyn_cast<NamedDecl>(*J);
                if (isa<UsingDirectiveDecl>(*J))
                    continue;

                if (ND && ND->getQualifiedNameAsString() == Inner->getQualifiedNameAsString()) {
//                        llvm::errs() << "Name Clash\n";
                    return false;
                }

            }
        }
    }

    // C. Check if there are DeclRefExprs with same name
    std::vector<const DeclRefExpr*> declrefexprs;
    collectAllDeclRefExprsOnCurrentLevel(CS, declrefexprs);
    if(!declrefexprs.empty()){
        for(auto DR : declrefexprs){
            if (DR->getDecl() && DR->getDecl()->getQualifiedNameAsString()
                                 == Inner->getQualifiedNameAsString()) {
//                    llvm::errs() << "Name Clash Type II\n";
                return false;
            }
        }
    }

    return true;
}


void UtilsDeclarations::collectAllDeclRefExprsOnCurrentLevel(const clang::Stmt *curstmt,
                                          std::vector<const DeclRefExpr*> &declrexpr) {

    if (auto dec = dyn_cast<DeclRefExpr>(curstmt)) {
        declrexpr.push_back(dec);
    }

    const auto &children = curstmt->children();
    for (const clang::Stmt *child : children) {
        if (child) {
            if(!checkifcontrolstmt(child) && !isa<CompoundStmt>(child)){
                collectAllDeclRefExprsOnCurrentLevel(child, declrexpr);
            }
        }
    }
}


MultipleDeclInformation UtilsDeclarations::getSourceInformationForMultipleDeclarationStmt(
        std::vector<const VarDecl*> &vardecls, const VarDecl* declOfInterest) {

    MultipleDeclInformation mdi;

    if(vardecls.size() == 1){
        // the full range covers the last token such as , or ; as well
        mdi.fullRange = getSourceRange(declOfInterest, Context.getSourceManager(), Context.getLangOpts());
        auto SRend = getCharSourceRange(declOfInterest, Context.getSourceManager(), Context.getLangOpts()).
                getEnd().getLocWithOffset(-1); // remove ;

        // without semi-colon
        mdi.declOnlyRange = SourceRange(declOfInterest->getLocStart(), SRend);
    } else {
        // if we have s.th. like int aaa, bbbb, c; and we want to remove b, then we need the SourceRange
        //  from the start of bbbb until , (including comma or semi-colon)

        SourceLocation end = getCharSourceRange(declOfInterest, Context.getSourceManager(),
                                                Context.getLangOpts()).getEnd();
        SourceLocation startwithouttype = declOfInterest->getLocation();
        SourceRange SR;
        const VarDecl* firstND = nullptr;
        const VarDecl *prevND = nullptr;
        for (auto ND : vardecls) {
            if(firstND == nullptr)
                firstND = ND;
            if(ND == declOfInterest) {
                break;
            } else {
                prevND = ND;
            }
        }
        if(!firstND){
            // we do not check if prevND, since if Outer is first Decl, prevND will be nullptr,
            // but this is okay, since it cannot be the last VarDecl with ";" at the end, since len(vardecls)>1
            llvm::errs() << "Unvalid first Declaration\n";
            throw CodeTransformationException();
        }

        if(getSourceTextStable(Context, startwithouttype, end).back() == ';'){
            // if Decl is the last Decl in the list of declarations, we need to close it correctly with ;
            // to this end, we need the start of previous vardecl.
            if(!prevND){
                llvm::errs() << "Unvalid previous Declaration\n";
                throw CodeTransformationException();
            }
            SourceLocation end_prev = getCharSourceRange(prevND, Context.getSourceManager(),
                                                         Context.getLangOpts()).getEnd();
            SR = SourceRange(end_prev, end.getLocWithOffset(-1)); // do not remove ;
            mdi.islastdecl = true;
        } else {
            SR = SourceRange(startwithouttype, end);
        }

        mdi.firstDecl = firstND;
        mdi.fullRange = SR;
        mdi.declOnlyRange = SourceRange(startwithouttype, end.getLocWithOffset(-1));
    }

    return mdi;
}

