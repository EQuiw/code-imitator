#include <set>
#include <sstream>

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


#include "../../Utilities/Utils.h"
#include "../utils_transform.h"
#include "../ASTFrontendActionTemplate.inl"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1
//#define OVERWRITE 1


/**
 * TODO TypeAliasDecl (typedef using C++11 style via: using LL = long long;) is so far not included
 *
 * TypeDef Parent Class that collects information about typedefs.
 * Can be used by various further typedef transformers for their transformations.
 */
class TypeDefCollector : public RecursiveASTVisitor<TypeDefCollector> {
public:

    // Types that we exclude from add_typedef, since it is not plausible to replace them.
    std::vector<std::string> excl_types_typedef = {"int", "_Bool", "char"};

    explicit TypeDefCollector(ASTContext &Context, Rewriter &OurRewriter) : Context(Context),
                                                                              OurRewriter(OurRewriter),
                                                                              sm(Context.getSourceManager()) {}

    /* ******************* Collection Methods ******************* */

    /**
     * Visits a typedef declaration and stores it in a list.
     * @param td
     * @return
     */
    bool VisitTypedefDecl(TypedefDecl *td) {
        auto srcloc = td->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            // Check if td is in main file

            this->typedefdeclarations.push_back(td);

#ifdef MYDEBUG
            llvm::outs() << "Typedef name:\t" << td->getQualifiedNameAsString() << "\n";
            llvm::outs() << "Typedef inner type:\t" << td->getUnderlyingType().getAsString() << "\n";
            QualType child_withoutsugar = td->getUnderlyingType().getDesugaredType(Context);
            llvm::outs() << "Typedef desugared:\t" << child_withoutsugar.getAsString() << "\n";
#endif
        }

        return true;
    }

    /** Saves a type alias declaration.
     * "Represents the declaration of a typedef-name via a C++11 alias-declaration" (Clang-doc.)
     * @param ta
     * @return
     */
    bool VisitTypeAliasDecl(TypeAliasDecl *ta){
        auto srcloc = ta->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            this->typealiasdeclarations.push_back(ta);
        }
        return true;
    }

    /**
     * Collects typedef name declarations (the parent class for typedefdecl and typealiasdecl).
     */
    bool VisitTypedefNameDecl(TypedefNameDecl *tnd){
        auto srcloc = tnd->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            this->typedefnamedeclarations.push_back(tnd);
        }
        return true;
    }

    /**
     * Saves all type locations that are typedef types and can be replaced by desugared type.
     * Used to remove typedefs later.
     * @param tl TypeLoc
     * @return
     */
    bool VisitTypeLoc(TypeLoc tl){
        auto srcloc = tl.getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){
//            llvm::outs() << ">>>Type:" << tl.getType().getAsString() << "; \n";

            // If type of variable is a typedef, we add it for replacement:
            if(const TypedefType *vdtype = dyn_cast<TypedefType>(tl.getType())){
                this->typelocswithtypedef.push_back(tl);
            }
        }
        return true;
    }

    /**
     * Save all namespaces.
     */
    bool VisitUsingDirectiveDecl(UsingDirectiveDecl *ud) {
        auto srcloc = ud->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
#ifdef MYDEBUG
            llvm::outs() << "Namespace:" << ud->getNominatedNamespace()->getQualifiedNameAsString() << "\n";
#endif
            usedNamespaces.push_back(ud);
        }
        return true;
    }


    /**
    * Saves all type locations where a new variable is defined.
    * Used to add typedefs later.
     * TODO we ignore global variables, when we just parse DeclStmt's.
    * @param ds DeclStmt
    * @return
    */
    bool VisitDeclStmt(DeclStmt *ds) {
        auto srcloc = ds->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {

            // Iterate over all variable declarations of current declaration statement
            for (DeclStmt::const_decl_iterator db = ds->decl_begin(), de = ds->decl_end(); db != de; ++db) {
                const Decl *vd = *db;
                if(auto vardecl = dyn_cast<VarDecl>(vd)){

                    // Check that type is not a typedef already
                    if(!isa<TypedefType>(vardecl->getType())){

#ifdef MYDEBUG
                        auto tl = vardecl->getTypeSourceInfo()->getTypeLoc();
                        llvm::outs() << "Possible Type for Replacement:"
                                     << getSourceText(Context, tl, false) << ";"
                                     << tl.getType().getUnqualifiedType().getAsString() << "; \t";
                        llvm::outs() << vardecl->getType()->getTypeClassName() << "/\t";
                        llvm::outs() << vardecl->getType().getTypePtr()->isPlaceholderType() << "/\t";
                        llvm::outs() << vardecl->getType().getTypePtr()->isOverloadableType() << "/\n";
                        // check how we can check for TypeWithKeyword...
#endif

                        // A. Auto Type
                        if(isa<AutoType>(vardecl->getType()))
                            break;

                        // B. Templates
                        // we need to exclude templates such as typename map <T, T1> or vector<T>
                        if(vardecl->getType().getTypePtr()->isOverloadableType()){
//                            llvm::outs() << "Skip:" << vardecl->getType().getAsString() << "\n";
                            break;
                        }

                        // C. If we have an array, it gets more complicated... so far we skip it..
                        if(auto vvt = dyn_cast<ArrayType>(vardecl->getType()))
                            break;

                        // D. Exclude too simple types
                        if (std::find(excl_types_typedef.begin(), excl_types_typedef.end(),
                                      vardecl->getType().getAsString()) != excl_types_typedef.end())
                            break;


                        this->typelocsfortypedef.push_back(vardecl->getTypeSourceInfo()->getTypeLoc());

                        // A DeclStmt may have multiple var declarations such as int a,b = 0; we jut want to have one.
                        break;
                    }

                }
            }
        }
        return true;
    }


    /**
     * Saves the first visited declaration, so that we know where we can insert typedef's if necessary.
     * Moreover, it saves the names of all declarations so that if we create a new typedef later, we can
     * easily check for name conflicts.
     * @param d
     * @return
     */
    bool VisitDecl(Decl *d) {
        auto srcloc = d->getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){
            // Save the name
            if(auto *nd = dyn_cast<NamedDecl>(d)){
                this->alldeclarationnames.push_back(nd->getQualifiedNameAsString());
                // Save the first visited declaration
                if(!this->first_decl)
                    this->first_decl = d;
            } else {
//               llvm::outs() << "No NamedDecl:" << d->getDeclKindName() << "\n";
            }
        }
        return true;
    }



protected:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    TypedefDecl *typedefdecltorewrite = nullptr;
    std::vector<TypedefDecl*> typedefdeclarations;
    std::vector<TypeAliasDecl*> typealiasdeclarations;
    std::vector<TypedefNameDecl*> typedefnamedeclarations;

    std::vector<TypeLoc> typelocswithtypedef;
//    std::set<SourceLocation> visitedLocs; TODO check if must be here, or sufficient in method below..

    std::vector<TypeLoc> typelocsfortypedef;
    Decl *first_decl = nullptr;
    std::vector<std::string> alldeclarationnames;
    std::vector<UsingDirectiveDecl*> usedNamespaces;




    /**
     * Resolves the inner type for a more complex type such as std::pair<...,...>
     * @param ctype a pointer to the type that we want to resolve.
     * @param collecteddecls all finally resolved declarations are saved here.
     */
    void check_type(const Type* ctype, std::vector<const Decl*> &collecteddecls){

        if(!ctype)
            return;

        if(auto tvt = dyn_cast<TemplateSpecializationType>(ctype)) {
            // Is a TemplateSpecializationType such as priority_queue<S> where S may be a class or struct.

            for(unsigned i = 0; i < tvt->getNumArgs(); i++){
                auto argtype = tvt->getArg(i).getAsType();
                check_type(argtype.getTypePtr(), collecteddecls);
            }

        } else if(auto et = dyn_cast<ElaboratedType>(ctype) ){
            // Is an ElaboratedType, such as std::priority_queue<S>; we need to unpack it.
            auto etnt = et->getNamedType();
            check_type(etnt.getTypePtr(), collecteddecls);

        } else {
            // now check if inner type is a typedef, class, struct

#ifdef MYDEBUG
            llvm::outs() << "ResolvedType--->:" << ctype->getTypeClassName() << "\n";
#endif

            const RecordType* record_type = ctype->getAs<clang::RecordType>();
            if (record_type != nullptr) {
                const RecordDecl *type_decl = record_type->getDecl();
                if(type_decl!=nullptr && sm.isWrittenInMainFile(type_decl->getLocStart())){
                    collecteddecls.push_back(type_decl);
                }
            }
            const TypedefType* typedef_type = ctype->getAs<clang::TypedefType>();
            if(typedef_type != nullptr){
                const TypedefNameDecl *type_decl = typedef_type->getDecl();
                if(type_decl!=nullptr && sm.isWrittenInMainFile(type_decl->getLocStart())){
                    collecteddecls.push_back(type_decl);
                }
            }
        }

    }



    /**
    * Returns the typedef that we can safely change. For this, it processes all typedef's and checks
    * if dependencies are there.
    * Example: typedef long long ll; \n typedef std::pair<ll,ll> pll; <-- pll should be replaced first.
    * It implements the strategy to remove typedefs that are not used in other typedefs.
    * @return nullptr if no typedef was found, otherwise the typedef that we can replace safely.
    */
    TypedefDecl *retrievetypedefdecl_resolvedependencies() {

        TypedefDecl *returnpar = nullptr;
        int indexmatch = 0;
        for (TypedefDecl *curpar : this->typedefdeclarations) {
//            QualType utype = curpar.first->getUnderlyingType();
            // Use only a typedef if it does not contain any other typedef's
            bool noothertypedefinsideofcurpar = true;
            for (TypedefDecl *curpar2 : this->typedefdeclarations) {
                if (curpar != curpar2) {
//                    llvm::outs() << curpar2->getUnderlyingType().getAsString() << ","
//                                 << curpar->getQualifiedNameAsString() << "\n";
                    if (curpar2->getUnderlyingType().getAsString().find(curpar->getQualifiedNameAsString())
                        != std::string::npos) {
                        // curpar is in curpar2 -- found
                        noothertypedefinsideofcurpar = false;
                    }
                }
            }
            if (noothertypedefinsideofcurpar) {
                // Save element for returning
                returnpar = curpar;
                // Remove element from vector
                this->typedefdeclarations.erase(this->typedefdeclarations.begin() + indexmatch);
                break;
//                llvm::outs() << curpar.second << ": is safe to rewrite\n";
            }
            indexmatch++;
        }

        return returnpar;
    }

    /**
     * Returns the first typedef that was found during the AST traversal.
     * @return
     */
    TypedefDecl *retrievetypedefdecl_toptobottom() {
        if(this->typedefdeclarations.empty()){
            return nullptr;
        }
        return this->typedefdeclarations.front();
    }

    /**
     * Returns the last typedef that was found during the AST traversal.
     * @return
     */
    TypedefDecl *retrievetypedefdecl_bottomtotop() {
        if(this->typedefdeclarations.empty()){
            return nullptr;
        }
        return this->typedefdeclarations.back();
    }

    /**
     * Computes a possible new typedef name for the type that we want to replace.
     * It extracts the first x letters from current type, if the name already exists as typedef name,
     * it checks for x+1 letters.
     * @param curtypetoinsert the full type
     * @param x number of letters to extract from each splitted word
     * @return a possible typedefname...
     */
    std::string findnewtypedefname(const std::string &curtypetoinsert, unsigned long x){
        std::string typedefname = "td_";

        // A. Extract the first x letters from each word in curtypetoinsert
        std::istringstream iss(curtypetoinsert);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>{}};
        for(const auto &cs : tokens){
            typedefname += cs.substr(0, x);
        }

        // B. Replace special characters like & or *
        // If last character would be such a special character, insert empty space, because
        // e.g. int *l would become i_l otherwise at each type replacement in source code.
        std::replace_if(typedefname.end()-1, typedefname.end(), ::isdigit, ' ');
        std::replace_if(typedefname.end()-1, typedefname.end(), ::ispunct, ' ');
        std::replace_if(typedefname.begin(), typedefname.end(), ::isdigit, '_');
        std::replace_if(typedefname.begin(), typedefname.end(), ::ispunct, '_');
//        llvm::outs() << "typedef name:\"" << typedefname <<"\"\n";


        // C. Check if declaration with this name already exists, if so, increase x
        // Check also for declname + empty space, since we may have an empty space due to previous step B.
        for(auto declname : this->alldeclarationnames){
            if(declname == typedefname || declname+" " == typedefname){
//                llvm::outs() << "Increasing x for \"" << typedefname <<"\"\n";
                return findnewtypedefname(curtypetoinsert, ++x);
            }
        }

        return typedefname;
    }


    /**
     *  The thing is to find the location where we can put the new typedef.
     *  We seek to find the highest possible row that is below a possible inner type.
     *  For instance, we may want to replace priority_queue<S> where S is a struct defined somewhere above.
     *  We need the type S, so that we can only put the typedef declaration below S.
     *  If we replace a simple type such as std::vector<int>, we can put it to the other typedef's.
     * @param chosentypeloc the typeloc that we want to replace
     * @param completetypedef the new typedef declaration
     * @param typetoinsert the type's string that we want to replace
     * @return true if no error. false if error.
     */
    bool getLocationForNewTypedef(const TypeLoc &chosentypeloc, const std::string &completetypedef,
                                  const std::string &typetoinsert) {

        std::vector<const Decl*> collecteddecls;
        check_type(chosentypeloc.getTypePtr(), collecteddecls);

        if(collecteddecls.empty()){
            // if no inner dependencies, put it above to other typedef's or above the first declaration
            return getLocationWithoutDependencies(completetypedef);

        } else {
            // inner dependencies, we need to check where we can actually put the new typedef.

            // put it below the highest possible row
            unsigned highest_row = 0;
            const Decl* cdecl = nullptr;
            for(auto dec : collecteddecls){
                FullSourceLoc locEnd(dec->getLocEnd(), sm);
                if(locEnd.getSpellingLineNumber() > highest_row) {
                    highest_row = locEnd.getSpellingLineNumber();
                    cdecl = dec;
                }
            }
            // some checks
            if(cdecl == nullptr){
                llvm::errs() << "Error: There are inner decls, but sth. was wrong for typedef;" << typetoinsert << "\n";
                return false;
            }
            // we want to add the new typedef after the declaration, so get its end after its semicolon.
            auto offs = getOffsetWithSemicolon(Context, cdecl);
            if(offs==(-1)){
                llvm::errs() << "Error: There are inner decls, but error during offset calc.;" << typetoinsert << "\n";
                return false;
            }

            // add the new typedef.
            SourceLocation End(Lexer::getLocForEndOfToken(cdecl->getLocEnd(), 0, sm, Context.getLangOpts()));
            OurRewriter.InsertTextAfterToken(End.getLocWithOffset(offs), completetypedef);
        }

        return true;
    }


    /**
     * Get a suitable location for a typedef command, if no complex dependencies are there for the typedef cmd.
     * TODO implements only a very basic namespace understanding, needs to cover more cases.
     * @param completetypedef
     * @return
     */
    bool getLocationWithoutDependencies(const std::string &completetypedef) {

        // check if all namespaces are above typedefs, then it is safe to include new typedef in front of all
        //  other typedefs, if they exist. Otherwise, we should include new typedef under namespace.
        bool putnewtypes_undernamespace = true;
        if(!this->usedNamespaces.empty() && !this->typedefdeclarations.empty()){
            unsigned namesp_row = 0;
            for(auto u : usedNamespaces){
                unsigned row = getRowColumn(u->getLocStart(), sm).first;
                if(row > namesp_row)
                    namesp_row = row;
            }
            unsigned typedecl_row = 65000;
            for(auto t : typedefdeclarations){
                unsigned row = getRowColumn(t->getLocStart(), sm).first;
                if(row < typedecl_row)
                    typedecl_row = row;
            }
            if(namesp_row < typedecl_row)
                putnewtypes_undernamespace = false;
        }


        if( (!this->usedNamespaces.empty() && !this->typedefdeclarations.empty() && putnewtypes_undernamespace)
                || (!this->usedNamespaces.empty() && this->typedefdeclarations.empty()) ){

            // Namespace should actually have priority, since typedef may depend on namespace, e.g. std.
            //  although we may get a list of typdefs, namespace and then typedefs again...
            auto offs = getOffsetWithSemicolon(Context, this->usedNamespaces.back());
            SourceLocation End(Lexer::getLocForEndOfToken(this->usedNamespaces.back()->getLocEnd(), 0,
                                                          sm, Context.getLangOpts()));
            OurRewriter.InsertTextAfter(End.getLocWithOffset(offs+1), completetypedef);

        } else if(!this->typedefdeclarations.empty()){
            TypedefDecl *tdd = this->typedefdeclarations.front();
            OurRewriter.InsertTextAfter(tdd->getLocStart(), completetypedef);

        } else if(this->first_decl){
            OurRewriter.InsertTextBefore(this->first_decl->getLocStart(), completetypedef);

        } else {
            llvm::errs() << "Error: Could not find a position for new typedef\n";
            return false;
        }

        return true;
    }


    bool replaceAllTypedefTypesWith(std::string &typetomatch, std::string &newtype) {
        // Replace it in all occurrences
        // Now we replace the current type if it belongs to the typedef that we want to replace
        std::set<SourceLocation> visitedLocs;
        for(TypeLoc tl : this->typelocswithtypedef){
            const TypedefType *vdtype = cast<TypedefType>(tl.getType());

            // Check that we have the right typedef
            if(typetomatch ==
               vdtype->getDecl()->getQualifiedNameAsString()) {

                // Rewrite type without typedef
                // Problem: We may visit a typeloc multiple times, if e.g. a variable was declared via int a,b = 2;
                // Solution: We memorize what locations were already visited.
                SourceRange targetloc = tl.getSourceRange();
                const bool is_in = visitedLocs.find(targetloc.getBegin()) != visitedLocs.end();
                if(!is_in){
//                        llvm::outs() << "New Location:" << targetloc.getBegin().printToString(sm) << "\n";

                    // In addition, we need to check if used as CXXFunctionalCastExpr, e.g. const ll m = ll(200);
                    // The term ll(200) is a CXXFunctionalCastExpr....;
                    // Function Style Cast requires that target type is a single word, thus check if white spaces are..
                    std::vector<const CXXFunctionalCastExpr*> dslist;
                    ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(tl);
                    goUpstairsInAST<CXXFunctionalCastExpr>(dtn, dslist, 1, &Context);

                    auto currenttype = newtype;
                    if(!dslist.empty()){
                        auto sps = split(newtype, "\\s+");
                        if(sps.size() > 1){
                            currenttype = "(" + newtype + ")";
                        }
                    }

                    // Now rewrite text with new type
                    OurRewriter.ReplaceText(targetloc, currenttype); // .getDesugaredType(Context)
                    visitedLocs.insert(targetloc.getBegin());
                } else {
//                        llvm::outs() << "Already visited:" << targetloc.getBegin().printToString(sm) << "\n";
                }
            }
        }

        return true;
    }


    bool replaceAllNecessaryTypesWithNewTypedef(std::string &typetoinsert, std::string &newtypedefname){

        for(TypeLoc tl : this->typelocsfortypedef){
            if( tl.getType().getUnqualifiedType().getAsString() == typetoinsert ){

#ifdef MYDEBUG
                llvm::outs() << "Replaced:" << tl.getType().getUnqualifiedType().getAsString()
                             << ";" << isa<ParenType>(tl.getType())
                             << ";" << getSourceText(Context, tl, false) << "\n";
#endif
                // Note: getType().getString returns the type incl. qualifier such as const,
                // but TypeLoc' location just contains the type without qualifier...

                // Moreover, if user writes s.th. like int(i) = 0; then typeloc fills complete int(i)
                // thus, we need to check what we rewrite... we cannot simply replace typeloc string by new typedef string
                auto typelocsrctext = getSourceText(Context, tl);
                std::string curentnewtypedefname = newtypedefname;
                const std::string r = "[()]";
                auto splits = split(typelocsrctext, r);

                if (splits.size() == 2){
                    curentnewtypedefname += "(" + splits[1] + ")";
                } else if(splits.size() > 2){
                    llvm::errs() << "typedef, type with () found, could not tokenize..\n";
                    return false;
                }

                OurRewriter.ReplaceText(tl.getSourceRange(), curentnewtypedefname);
            }
        }
        return true;
    }



};

