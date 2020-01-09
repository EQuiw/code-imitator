//
// Utils for Declarations...
//
#ifndef LIBTOOLINGAST_UTILSDECLARATIONS_H
#define LIBTOOLINGAST_UTILSDECLARATIONS_H

#include "clang/AST/AST.h"

#include "Utils.h"
#include "../transformers/include/SourceTextHelper.h"
#include "../transformers/utils_transform.h"

using namespace clang;

struct MultipleDeclInformation {
    const VarDecl* firstDecl = nullptr; // the first Decl in the list of multiple declarations
    bool islastdecl = false;
    // with comma or semi-colon; but if we have int a = 0, int b = 0, int c = 0; and b is the declOfInterest,
    //  then full Range covers range of "int b=0," incl. the right comma, not the left.
    SourceRange fullRange;
    SourceRange declOnlyRange; // only the declaration
};


class UtilsDeclarations {

public:
    explicit UtilsDeclarations(ASTContext &Context);

    /**
     * Check if a name conflict occurs. This method checks the outer scope of Outer Stmt
     * if there is a variable or Declaration-Reference to a variable with the same qualified name as Inner.
     * @param Outer
     * @param Inner
     * @return true if no name conflict; false if name conflict or another error occurs.
     */
    bool check_for_name_conflict(const Stmt* Outer, const VarDecl* Inner);


    MultipleDeclInformation getSourceInformationForMultipleDeclarationStmt(
            std::vector<const VarDecl*> &vardecls, const VarDecl* declOfInterest);


private:
    ASTContext &Context;


    /**
     * Go down - Statements such as recursiveStmtTVisit, BUT do not go further for control statements.
     * @param curstmt
     * @param declrexpr
     */
    void collectAllDeclRefExprsOnCurrentLevel(const clang::Stmt *curstmt,
                                              std::vector<const DeclRefExpr*> &declrexpr);

};


#endif //LIBTOOLINGAST_UTILSDECLARATIONS_H
