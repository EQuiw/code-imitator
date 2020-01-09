//
// Contains a Decl-Ref-Mapping.
// Note that the CFG also contains such a Decl-Ref-Mapping, but as the CFG is only built for functions/methods,
// it will not contain mappings for global variables...
//
// Consider (*only for local variables*)
// A Decl Stmt may contain multiple VarDecl's.
// A Var Decl may be referenced by multiple DeclRefExpr's.
// Thus, we have two hashmaps.
//
// For global variables, we can only rely on the second hashmap with DeclRefExpr's and have to check for same
// SourceLocation to find grouped VarDecl's. http://lists.llvm.org/pipermail/cfe-dev/2017-April/053497.html
//

#ifndef LIBTOOLINGAST_DECLREFMAPPING_H
#define LIBTOOLINGAST_DECLREFMAPPING_H

#ifndef CLANG_LIBS
#define CLANG_LIBS
#include "llvm/Support/CommandLine.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#endif

#include "../../utils_transform.h"
#include "../../../Utilities/Utils.h"
#include <utility>
#include <tuple>

/**
 * Declaration Reference Mapping.
 * Note that we save a mapping from SourceLocation/DeclStmt to VarDecl's and
 *                   a mapping from VarDecl to all DeclRefExprs.
 */
class DeclRefMapping {

public:
    explicit DeclRefMapping(ASTContext *Context);

    /**
     * Insert a DeclRefExpr to DeclRefMapping.
     * This is necessary to get a mapping from a Decl to all its usages (DeclRefExprs).
     * @param d
     * @return true if everything works
     */
    bool insert_declref(const DeclRefExpr* d);

    /**
     * Insert a VarDecl to DeclRefMapping.
     * This is necessary to get a mapping from a SourceLocation to all VarDecl's.
     * E.g. we could have int a,b,c; <-- Multiple VarDecl's at one line/DeclStmt.
     * In local scope, this SourceLocation can be used instead of a DeclStmt that includes multiple VarDecl's.
     * In global scope, however, we can only find multiple VarDecl's
     * if we look which VarDecl's have the same SourceLocation Start.
     * @param d
     * @return true if everything works
     */
    bool insert_vardecl(const VarDecl* d);

    /**
     * Insert a DeclStmt to DeclRefMapping.
     * This is necessary to get a mapping from a DeclStmt to all its VarDecl's and vice versa.
     * In clang, we can easily get all VarDecl's to a DeclStmt, but the other way round is harder.
     * Be careful, only local variables have a DeclStmt as parent node.
     * @param ds DeclStmt.
     * @return true if everything works.
     */
    bool insert_declstmt(const DeclStmt* ds);

    /**
     * Get all DeclRefExprs for a given VarDecl.
     */
    std::vector<const DeclRefExpr*> getVarDeclToDeclRefExprs(const VarDecl* ddecl);

    /**
     * Get DeclStmt for a given VarDecl.
     */
    const DeclStmt* getVarDeclToDeclStmt(const VarDecl* vd);

    /**
     * Get VarDecls for a given DeclStmt.
     * Sorting order should be guaranteed w.r.t to appearence in declaration list.
     */
    std::vector<const VarDecl*> getDeclStmtToVarDecls(const DeclStmt* ds);

    /**
     * Get all VarDecl's for a given SourceLocation.
     * Guaranteed that VarDecls are sorted w.r.t to row and column.
     */
    std::vector<const VarDecl*> getSourceLocationToVarDecls(SourceLocation sl);

    /**
     * Get all VarDecl's for a given SourceLocation == pair of its row and column.
     * Guaranteed that VarDecls are sorted w.r.t to row and column.
     */
    std::vector<const VarDecl*> getSourceLocationToVarDecls(std::pair<unsigned,unsigned> slkey);

private:
//    ASTContext *Context;
    SourceManager &sm;

    std::map<const VarDecl*, std::vector<const DeclRefExpr*> > declrefmap;
    std::map<const DeclStmt*, std::vector<const VarDecl*> > declstmttovardecls;
    std::map<std::pair<unsigned,unsigned>, std::vector<const VarDecl*> > sourcelocationtovardecls;

};


#endif //LIBTOOLINGAST_DECLREFMAPPING_H
