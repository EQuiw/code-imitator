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

#include "../../transformers/ASTFrontendActionTemplate.inl"
#include "../../transformers/utils_transform.h"
#include "../../transformers/include/SourceTextHelper.h"
#include "../../Utilities/Utils_Declarations.h"
#include "../../transformers/ControlDataFlow/DeclRefMapping/DeclRefMapping.h"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1

typedef std::pair<std::string, std::string> strpair;

enum Listing {typedefs=1, fctnames=2, varnames=3, all_typedefs=4, all_varnames=5, all_decl_names=6, global_consts=7};
static llvm::cl::OptionCategory MyOptionCategory("List Declaration Names");
static llvm::cl::opt<Listing> ListingOpt("listing", desc("Transformation strategy"), Required,
                                           values(clEnumVal(typedefs, "list typedef names that are usable by typedef transformer"),
                                                  clEnumVal(fctnames,
                                                            "List fct names"),
                                                  clEnumVal(varnames,
                                                            "List var names that are usable by name transformer"),
                                                  clEnumVal(all_typedefs,
                                                            "List all typedefs, even if not usable"),
                                                  clEnumVal(all_varnames,
                                                            "List all var names, even if not usable"),
                                                  clEnumVal(all_decl_names,
                                                            "List all declaration names (includes vars, typedefs, fcts, ...)"),
                                                  clEnumVal(global_consts,
                                                            "List all global consts that are usable by global_const transformer")
                                           ),
                                           cat(MyOptionCategory));



/**
 * A preprocessor to list all decl names.
 * //
 * // List various types of declaration names.
 * // a. Typedefs
 * // b. Function Names (we exclude the main fct in listing).
 * // c. Var Names
 * //
 */
class DeclNamesList : public RecursiveASTVisitor<DeclNamesList> {
public:

    DeclRefMapping *DeclRefMap;

    explicit DeclNamesList(ASTContext &Context)
            : Context(Context), sm(Context.getSourceManager()) {
        DeclRefMap = new DeclRefMapping(&Context);
    }

    ~DeclNamesList(){
        delete DeclRefMap;
    }

    /* ******************* Collection Methods ******************* */

    /**
     * Visit Named Declarations, equivalent method to variablename_transformer.
     * @param nd
     * @return
     */
    bool VisitNamedDecl(NamedDecl *nd) {
        auto srcloc = nd->getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){
            // Save all named declarations, e.g. to check for name conflicts
            this->alldeclarationnames.push_back(nd->getNameAsString());

            // Save variables that we can rewrite without problems
            if(auto d = dyn_cast<VarDecl>(nd)){
                DeclRefMap->insert_vardecl(d);
                this->all_variable_declarations.push_back(nd);
#ifdef MYDEBUG
                llvm::outs() << "VarName:" << d->getQualifiedNameAsString() << ";" << d->getIdentifier()->getName()
                             << ";\t Local Var?:"
                             << d->isLocalVarDecl() << ";" << d->isLocalVarDeclOrParm() << ";"
                             << d->hasExternalStorage() << "\n";
                llvm::outs() << "Type:" << d->getType().getCanonicalType().getAsString() << "\n";
#endif

                if (!d->hasExternalStorage()
                    && d->getType().getCanonicalType().getAsString().find("const") == std::string::npos) {
                    // We do not rewrite extern variables
                    // and const variables (these are directly replaced in AST, no DeclRefExpr's).
                    this->variable_declarations.push_back(nd);
                }

                // Save global consts TODO use hasGlobalStorage
                if(!d->hasExternalStorage() && !d->isLocalVarDeclOrParm() && d->getType().isConstQualified()){
                    all_global_const_declarations.push_back(d);
                }


            }
            // Save functions that we can rewrite without problems
            if(auto f = dyn_cast<FunctionDecl>(nd)){
                this->function_declarations.push_back(f);
#ifdef MYDEBUG
                llvm::outs() << "FctName:" << f->getQualifiedNameAsString()
                             << "; With Def/Body:" << f->isThisDeclarationADefinition() << "\n";
#endif
            }
        }
        return true;
    }

    /**
     * Visits a typedef declaration and stores it in a list. Equivalent to typedef_transformer's method.
     * @param td
     * @return
     */
    bool VisitTypedefDecl(TypedefDecl *td) {
        auto srcloc = td->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            // Check if td is in main file

            this->typedef_declarations.push_back(td);

#ifdef MYDEBUG
            llvm::outs() << "Typedef name:\t" << td->getQualifiedNameAsString() << "\n";
            llvm::outs() << "Typedef inner type:\t" << td->getUnderlyingType().getAsString() << "\n";
            QualType child_withoutsugar = td->getUnderlyingType().getDesugaredType(Context);
            llvm::outs() << "Typedef desugared:\t" << child_withoutsugar.getAsString() << "\n";
#endif
        }

        return true;
    }

    // Some overwrites for DeclRefMapping
    bool VisitDeclStmt(DeclStmt *DS) {
        if(sm.isWrittenInMainFile(DS->getLocStart())){
            DeclRefMap->insert_declstmt(DS);
        }
        return true;
    }

    // Some overwrites for DeclRefMapping
    bool VisitDeclRefExpr(DeclRefExpr *DS) {
        if(sm.isWrittenInMainFile(DS->getLocStart())){
            DeclRefMap->insert_declref(DS);
        }
        return true;
    }




    /* ******************* Listing Methods ******************* */

    void list_decl_names(Listing listing) {

        switch(listing){
            case all_decl_names:
                for(auto &nd : alldeclarationnames){
                    llvm::outs() << nd << "\n";
                }
                break;
            case varnames:
                for(auto nd : variable_declarations){
                    llvm::outs() << nd->getNameAsString() << "\n";
                }
                break;
            case all_varnames:
                for(auto nd : all_variable_declarations){
                    llvm::outs() << nd->getNameAsString() << "\n";
                }
                break;
            case fctnames:
                for(auto f : function_declarations){
                    if (!f->isMain())
                        llvm::outs() << f->getNameAsString() << "\n";
                }
                break;
            case typedefs:
                for(auto td : typedef_declarations){
                    std::vector<strpair> includes;
                    auto typedeftype = td->getUnderlyingType().getAsString();
                    auto typedefunqtype = td->getUnderlyingType().getUnqualifiedType().getAsString();
                    bool isprimitive = isTriviallyCopyable(td->getUnderlyingType().getTypePtr(), includes, Context);
                    if(isprimitive){
                        llvm::outs() << typedeftype << "##" << typedefunqtype << "##" <<
                                     td->getQualifiedNameAsString() << "##";
                        llvm::outs() << td->getNameAsString() << "##";
                        for(auto &s : includes)
                            llvm::outs() << "(" << s.first << ";" << s.second << ")" << ",";
                        llvm::outs() << "\n";
                    }
                }
                break;
            case all_typedefs:
                for (auto td : typedef_declarations) {
                    std::vector<strpair> includes;
                    auto typedeftype = td->getUnderlyingType().getAsString();
                    auto typedefunqtype = td->getUnderlyingType().getUnqualifiedType().getAsString();
                    isTriviallyCopyable(td->getUnderlyingType().getTypePtr(), includes, Context);

                    llvm::outs() << typedeftype << "##" << typedefunqtype << "##" <<
                                 td->getQualifiedNameAsString() << "##";
                    llvm::outs() << td->getNameAsString() << "##";
                    for (auto &s : includes)
                        llvm::outs() << "(" << s.first << ";" << s.second << ")" << ",";
                    llvm::outs() << "\n";

                }
                break;

            case global_consts:
                for(auto d : all_global_const_declarations){

                    // Show only global consts that have a simple built-in type and that are not init. with a function.
                    // We check the function call (e.g. const int A = acos(-1)) by getEvaluatedValue...
                    if(d->getType()->isBuiltinType() && !isa<TypedefType>(d->getType())
                            && (d->isInitICE() || (d->getEvaluatedValue() == nullptr))) {
                        // TODO we will also have problems if variable is defined with another const variable, e.g.
                        //  const int MAX = 100; const int N = MAX;

                        handle_global_const_output(d);
                    }

                }

        }

    }



    /**
     * Recursively check if inner types of a pair, set or e.g. vector< ...> are built-in types.
     * If we have vector<long long>, inner type is built-in.
     * If we have vector<LL> where LL is typedef, then inner type is not built-in.
     */
    bool are_inner_types_builtin_types(const Type* ctype, std::vector<strpair> &includes) {

        if(!ctype)
            return false;

        if(auto tvt = dyn_cast<TemplateSpecializationType>(ctype)) {
            // Is a TemplateSpecializationType such as priority_queue<S> where S may be a class or struct.

            // Check if outer type is usable, and if so, add the necessary library to includes vector
            if(!whitelistofoutertypes(tvt, includes)){
                return false;
            }

            for(unsigned i = 0; i < tvt->getNumArgs(); i++){
                auto argtype = tvt->getArg(i).getAsType();
                if(!are_inner_types_builtin_types(argtype.getTypePtr(), includes))
                    return false;
            }

        } else if(auto et = dyn_cast<ElaboratedType>(ctype) ){
            // Is an ElaboratedType, such as std::priority_queue<S>; we need to unpack it.
            auto etnt = et->getNamedType();
            if(!are_inner_types_builtin_types(etnt.getTypePtr(), includes))
                return false;
        } else {
            if(!isa<BuiltinType>(*ctype))
                return false;
        }

        return true;
    }


    /**
     * White list check if outer type (e.g. 'vector' in vector<...>) is s.th. we can handle.
     * @param tvt
     * @param includes we will save the necessary header for type and the compact type name in includes
     * that is passed by reference.
     * @return true if type is ok, false if not.
     */
    bool whitelistofoutertypes(const TemplateSpecializationType* tvt, std::vector<strpair> &includes){

        // inner and outer definition, we are here only interested in the 'outer' definition of e.g. std::vector<int>
        PrintingPolicy pp(Context.getLangOpts());

        std::string type_str;
        llvm::raw_string_ostream rso(type_str);
        tvt->getTemplateName().print(rso,  pp);
        std::string curtype = rso.str();
//        llvm::errs() << "->" << curtype << "//" << tvt->getAliasedType().getAsString() << "\n";

        if(curtype == "vector"){
            includes.emplace_back("vector", curtype);
        }
        else if(curtype == "map"){
            includes.emplace_back("map", curtype);
        }
        else if(curtype == "set"){
            includes.emplace_back("set", curtype);
        }
        else if(curtype == "pair"){
            includes.emplace_back("utility", curtype);
        }
        else if(curtype == "tuple") {
            includes.emplace_back("tuple", curtype);
        }
        else if(curtype == "list"){
                includes.emplace_back("list", curtype);
        } else {
            return false;
        }

        return true;
    }



    bool isTriviallyCopyable(const Type* t, std::vector<strpair> &includes, const ASTContext &Context) {

        // a. if built-in type such as int, double, ...
        if(isa<BuiltinType>(*t))
                return true;

        // b. check if vector/map/set/... and inner type trivial
        return are_inner_types_builtin_types(t, includes);
    }


    /**
     * Output of the global const variable if usable by global-const transformer.
     * It also checks if we have multiple declarations by using the DeclRefMap.
     * @param d
     */
    void handle_global_const_output(const VarDecl* d) {

        // Now we need to check if we have a list of declarations in global scope (remind that
        //  we do not have an upper DeclStmt in global scope, we use DeclRefMap as a remedy)
        std::vector<const VarDecl*> vardecls = DeclRefMap->getSourceLocationToVarDecls(d->getLocStart());
        if(vardecls.size() == 1){
            std::string srctext = getSourceTextStable(d, Context);
            // if someone writes const int INF = \n sizeof(int)...
            srctext = ReplaceString(ReplaceString(srctext, "\n", " "), "\r", " ");
            llvm::outs() << d->getNameAsString() << "##" << srctext << "\n";
        } else {
            try {
                UtilsDeclarations utilsDeclarations(Context);
                MultipleDeclInformation mdi = utilsDeclarations.
                        getSourceInformationForMultipleDeclarationStmt(vardecls, d);


                auto srctype = getSourceTextStable(Context, mdi.firstDecl->getLocStart(),
                                                   mdi.firstDecl->getTypeSourceInfo()->getTypeLoc().getLocEnd());
                auto srctext = getSourceTextStable(Context, mdi.declOnlyRange.getBegin(), mdi.declOnlyRange.getEnd());

                srctext = ReplaceString(ReplaceString(srctext, "\n", " "), "\r", " ");
                llvm::outs() << d->getNameAsString() << "##" << srctype + " " + srctext << ";\n";

            } catch(CodeTransformationException& e) {
                return;
            }
        }
    }



private:
    ASTContext &Context;
    SourceManager &sm;

    // All declaration names that were visited during the AST traversal,
    // also includes declarations that we won't rewrite.
    std::vector<std::string> alldeclarationnames;

    std::vector<const NamedDecl*> variable_declarations;
    std::vector<const NamedDecl*> all_variable_declarations;
    std::vector<const VarDecl*> all_global_const_declarations;

    std::vector<const FunctionDecl*> function_declarations;

    std::vector<const TypedefDecl*> typedef_declarations;


};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context) : Visitor(Context) {
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        Visitor.list_decl_names(ListingOpt.getValue());
    }

private:
    DeclNamesList Visitor;
};


class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {

//        std::string s = InFile;
//        llvm::errs() << "** Creating AST consumer for: " << split_path(s)[1] << "\n";

        return std::unique_ptr<clang::ASTConsumer>(
                new MyASTConsumer(Compiler.getASTContext()));
    }
};


int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, MyOptionCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}

