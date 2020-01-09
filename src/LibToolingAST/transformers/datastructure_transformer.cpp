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

#include "utils_transform.h"
#include "../Utilities/Utils.h"
#include <string>
#include "ASTFrontendActionWithPrepTemplate.inl"

#include "ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "ControlDataFlow/CDFGraphQueryHandler.h"
#include "include/SourceTextHelper.h"

using namespace clang;
//#define MYDEBUG 1

typedef std::pair<std::string,std::string> StringPair;
typedef std::pair<const ImplicitCastExpr*, bool> EvaluatedImplicitCastExpr;
typedef std::pair<const CXXBoolLiteralExpr*, bool> EvaluatedCXXBoolLiteralExpr;

struct PreprocessingInfos {
    std::vector<std::pair<std::string, SourceLocation>> headerincludes;
};

static llvm::cl::OptionCategory MyOptionCategory("Simple Data Structure Transformer");

static llvm::cl::opt<int> OurCMDOption1("strategy", llvm::cl::cat(MyOptionCategory));
static llvm::cl::opt<int> OurCMDOption2("seed", llvm::cl::cat(MyOptionCategory));


enum Strategy {array_to_vector = 1, chararray_to_string = 2, bool_to_int = 3, float_to_double = 4,
                                    string_to_chararray = 5, tuple_pair = 6,
                                    truefalse_to_one_zero = 7, one_zero_to_truefalse = 8,
                                    int_to_longlong = 9};

/**
 * This transformer deals with equivalent data structures.
 * In general, we transform a variable declaration from type A to type B without changing the behaviour.
 *
 * For instance, we can transform an array into a vector
 * or vice versa. We can also transform int's to float's and cast them before each usage.
 */
class DataStructureTransformer : public RecursiveASTVisitor<DataStructureTransformer> {
public:

    Decl* firstDeclInSrcFile;
    ControlFlowGraphWithDataFlow *cfggraph;

    explicit DataStructureTransformer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
            : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()), prepinfos(prepinfos) {
        cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~DataStructureTransformer(){
        delete cfggraph;
    }

    /* ******************* Collection Methods ******************* */

    /**
     * Store the first occurence of a Decl, so that we can insert a header-include later easily
     * if no #include directives were defined.
     * @param d
     * @return
     */
    bool VisitDecl(Decl* d){
        auto srcloc = d->getLocStart();

        if(sm.isWrittenInMainFile(srcloc) && !firstDeclInSrcFile){
            firstDeclInSrcFile = d;
        }
        return true;
    }

    /**
     * Save all namespaces.
     */
    bool VisitUsingDirectiveDecl(UsingDirectiveDecl *ud){
        auto srcloc = ud->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            #ifdef MYDEBUG
            llvm::outs() << "Namespace:" << ud->getNominatedNamespace()->getQualifiedNameAsString() << "\n";
            #endif
            usedNamespaces.push_back(ud->getNominatedNamespace()->getQualifiedNameAsString());
        }
        return true;
    }

    /**
     * Visit all functions and store them in CFG graph.
     * @param f
     * @return
     */
    bool VisitFunctionDecl(FunctionDecl *f) {
        bool inmainfile = sm.isInMainFile(f->getLocation());
        if (inmainfile) {
            cfggraph->addFunctionDecl(f);
        }
        return true;
    }

    /**
     * Go through all implicitly cast integral type / bool expressions, trying to evaluate them.
     * if we're able to evaluate those expr as boolean conditions, store them and their values
     * in seperate vectors for later replacement
     */

    bool VisitStmt(Stmt *s) {
        auto srcloc = s->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {

            // Catch all  boolean literal expressions and evaluate them,
            // later to be replaced by 1 or 0
            if (auto* const ble = dyn_cast<CXXBoolLiteralExpr>(s)) {
                bool result;
                if (ble->EvaluateAsBooleanCondition(result, Context)) {
                    this->exprsbools.emplace_back(ble, result);
                }


            }

             // Only catch integral / floating type expressions implicitly cast to bools
             // to make sure we're not doing any illegal replacements
             // If we're able to evaluate them, later to replaced by true or false
            if (auto* const icexpr = dyn_cast<ImplicitCastExpr>(s)) {
                if (icexpr->getCastKind() == CK_IntegralToBoolean ||
                    icexpr->getCastKind() == CK_FloatingToBoolean ||
                    icexpr->getCastKind() == CK_FloatingComplexToBoolean ||
                    icexpr->getCastKind() == CK_IntegralComplexToBoolean) {
                    bool result;
                    if (icexpr->EvaluateAsBooleanCondition(result, Context)) {
                        this->exprsimplicitlycastintegrals.emplace_back(icexpr, result);
                    }
                }
            }
        }
            return true;
    }

    /**
    * Saves all VarDecl's that we are able to replace later
    * @param ds DeclStmt
    * @return
    */
    bool VisitDeclStmt(DeclStmt *ds) {
        auto srcloc = ds->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {

            // Iterate over all variable declarations of current declaration statement
            for (DeclStmt::const_decl_iterator db = ds->decl_begin(), de = ds->decl_end(); db != de; ++db) {
                const Decl *vd = *db;
                if (auto vardecl = dyn_cast<VarDecl>(vd)) {

                    // A. Handle SingleDecl
                    if(ds->isSingleDecl()){
                        if (auto vvt = dyn_cast<ArrayType>(vardecl->getType())) {

                            // The current variable is an array.
                            if(vvt->getElementType().getAsString() != "char"){
                                this->declstmtswitharraytype.push_back(ds);
                            } else {
                                // it is a char array, it will be rewritten to a string
                                this->declstmtswithchararray.push_back(ds);
                            }

                            #ifdef MYDEBUG
                            llvm::outs() << "Type:" << vardecl->getType()->getTypeClassName() << "\n";
                            #endif
                        }
                        if (auto vvt = dyn_cast<PointerType>(vardecl->getType())) {

                            // Check if current variable is a pointer to an array.
                            std::vector<const CXXNewExpr*> cxxnewexprs;
                            recursiveStmtTVisit<CXXNewExpr>(ds, cxxnewexprs);

                            if(cxxnewexprs.size() == 1){
                                if(cxxnewexprs[0]->isArray())
                                    this->declstmtswitharraytype.push_back(ds);
                            }
                        }

                        if( vardecl->getType().getCanonicalType().getAsString() == "class std::__cxx11::basic_string<char>") {
                            this->declstmtswithstringtype.push_back(ds);
                        }
                    }

                    // B. Handle MultiDecl
                    if (vardecl->getType()->isBooleanType()){
                        this->declstmtswithbooltype.push_back(ds);
                    }
                    if (vardecl->getTypeSourceInfo()->getType().getAsString() == "float"){
                        this->declstmtswithfloattype.push_back(ds);
                    }
                    if (vardecl->getTypeSourceInfo()->getType().getAsString() == "int"){
                        this->declstmtswithinttype.push_back(ds);
                    }
//                    llvm::errs() << vardecl->getName() << "T:" << vardecl->getTypeSourceInfo()->getType().getAsString() << "\t";
//                    llvm::errs() << "Ty:" << vardecl->getType().getCanonicalType().getAsString() << "\n";
//                    llvm::errs() << "tl:" << vardecl->getTypeSourceInfo()->getTypeLoc().getTypePtr()
//                            ->getCanonicalTypeInternal().getAsString() << "\n";
                }
                break; // We are only interested in the first Decl from a row.
            }
        }

        return true;
    }

    /* ******************* Rewriting Methods ******************* */

    void replacecommand(Strategy strategy, int seed) {

        assert(strategy==array_to_vector || strategy==bool_to_int || strategy==float_to_double ||
               strategy==chararray_to_string || strategy==string_to_chararray ||
               strategy==truefalse_to_one_zero || strategy==one_zero_to_truefalse);

        switch(strategy) {
            case array_to_vector:
                randomlySortVector<const DeclStmt*>(declstmtswitharraytype, seed);
                for(auto s : declstmtswitharraytype){
                    if(transformArrayToVector(s))
                        return;
                }
                break;
            case chararray_to_string:
                randomlySortVector<const DeclStmt*>(declstmtswithchararray, seed);
                for(auto s : declstmtswithchararray){
                    if(transformCharArrayToString(s))
                        return;
                }
                break;
            case bool_to_int:
                randomlySortVector<const DeclStmt*>(declstmtswithbooltype, seed);
                for(auto s : declstmtswithbooltype){
                    if(transformXtoY(s, "int"))
                        return;
                }
                break;
            case float_to_double:
                randomlySortVector<const DeclStmt*>(declstmtswithfloattype, seed);
                for(auto s : declstmtswithfloattype){
                    if(transformXtoY(s, "double"))
                        return;
                }
                break;
            case string_to_chararray:
                randomlySortVector<const DeclStmt*>(declstmtswithstringtype, seed);
                for(auto s : declstmtswithstringtype){
                    if(transformStringToCharArray(s))
                        return;
                }
                break;
            case truefalse_to_one_zero:
                randomlySortVector<EvaluatedCXXBoolLiteralExpr>(exprsbools, seed);
                for(auto s: exprsbools){
                    if(transformTrueFalseToOneZero(s))
                        return;
                }
                break;
            case one_zero_to_truefalse:
                randomlySortVector<EvaluatedImplicitCastExpr>(exprsimplicitlycastintegrals, seed);
                for(auto s : exprsimplicitlycastintegrals){
                    if(transformOneZeroToTrueFalse(s))
                        return;
                }
                break;
            case int_to_longlong:
                randomlySortVector<const DeclStmt*>(declstmtswithfloattype, seed);
                for(auto s : declstmtswithinttype){
                    if(transformXtoY(s, "long"))
                        return;
                }
                break;
        }

        llvm::errs() << "Code 123: No transformations possible\n";
    };


protected:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    PreprocessingInfos* prepinfos;

    // all stmts where we can replace the array type by a vector typ (except char)
    std::vector<const DeclStmt*> declstmtswitharraytype;
    // all stmts with char array
    std::vector<const DeclStmt*> declstmtswithchararray;
    // all stmts with bool type
    std::vector<const DeclStmt*> declstmtswithbooltype;
    // all stmts with float type
    std::vector<const DeclStmt*> declstmtswithfloattype;
    // all stmts with string type
    std::vector<const DeclStmt*> declstmtswithstringtype;
    // all stmts with int type
    std::vector<const DeclStmt*> declstmtswithinttype;

    // all const expressions implicitly cast from integrals to bools with their corresponding values
    std::vector<EvaluatedImplicitCastExpr> exprsimplicitlycastintegrals;
    // all const bool expressions and their corresponding values
    std::vector<EvaluatedCXXBoolLiteralExpr> exprsbools;



    /**
    * The namespaces that are defined by the using command.
    * Necessary to decide if we e.g. use std::cout or simply cout..
    */
    std::vector<std::string> usedNamespaces;



    bool getElemTypeNumelemsArraytype(const DeclStmt *declstmt, std::string &elemtype, std::string &numelems){

        const VarDecl* s = dyn_cast<VarDecl>(declstmt->getSingleDecl());
        const ArrayType* arrtype = dyn_cast<ArrayType>(s->getType());

        // i) Get the type of the array elements
        QualType arrelemtype = arrtype->getElementType();
        elemtype = arrelemtype.getAsString();

        // TODO handle 2D or n-D arrays
//        if(auto bla = dyn_cast<ConstantArrayType>(arrtype)){
//            llvm::errs() << "Con:" << bla->getSize() << "\n";
//            auto sec = bla->getElementType();
//            if(auto secbla = dyn_cast<ConstantArrayType>(sec.getTypePtr())){
//                llvm::errs() << "Con2:" << secbla->getSize() << "\n";
//            }
//        }

        // ii) Get the number of elements in [...]
        auto noelemsplits = split(s->getType().getAsString(), "[\\[\\]]");
        if(noelemsplits.size() != 2){
            //llvm::errs() << s->getType().getAsString() << " was not properly splitted to get [...] content" << "\n";
            return false;
        }
        numelems = noelemsplits[1];

        return true;
    }

    bool getElemTypeNumelemsPointertype(const DeclStmt *declstmt, std::string &elemtype, std::string &numelems){
//        const VarDecl* s = dyn_cast<VarDecl>(declstmt->getSingleDecl());
//        const PointerType* pointype = dyn_cast<PointerType>(s->getType());

        // i) Get the type of the array elements
        std::vector<const CXXNewExpr*> cxxnewexprs;
        recursiveStmtTVisit<CXXNewExpr>(declstmt, cxxnewexprs);
        elemtype = cxxnewexprs[0]->getAllocatedType().getAsString();

        // ii) Get the number of elements in [...]
        numelems = getSourceText(Context, cxxnewexprs[0]->getArraySize(), false);
        return true;
    }

    const CXXDeleteExpr* handleCXXDeleteExpr(const DeclRefExpr *curdeclrefexpr) {
        std::vector<const CXXDeleteExpr*> dslist;
        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*curdeclrefexpr);
        // We try each level above, first only level above, then two levels, then three levels until we find..
        int i = 1;
        while(i < 100 && dslist.empty()){ // 100 is arbitrary and prevents an infinite loop.
            goUpstairsInAST<CXXDeleteExpr>(dtn, dslist, i, &Context);
            i++;
        }

        if(dslist.size() == 1){
            return dslist[0];
        } else {
            return nullptr;
        }
    }


    /**
     * Transforms an array to vector.
     * @param declstmt the declaration whose type will be changed
     * @return true if successful
     */
    bool transformArrayToVector(const DeclStmt *declstmt) {

        const VarDecl* s = dyn_cast<VarDecl>(declstmt->getSingleDecl());

        // * A. We need to rewrite the variable declaration *
        std::string elemtype, numelems;
        const ArrayType* arrtype = dyn_cast<ArrayType>(s->getType());
        const PointerType* pointype = dyn_cast<PointerType>(s->getType());
        if(arrtype != nullptr) {
            if(!getElemTypeNumelemsArraytype(declstmt, elemtype, numelems))
                return false;
        } else if(pointype != nullptr) {
            if(!getElemTypeNumelemsPointertype(declstmt, elemtype, numelems))
                return false;
        } else {
            llvm::errs() << "Chosen Variable for Array Transformation has no Array Type or Pointer Type";
            return false;
        }

        // iii) Get the variable name
        std::string varname = s->getQualifiedNameAsString();

        // iv) Construct the new var. declaration
        std::stringstream sstream;
        sstream << "" << append_std("vector") << "<" << elemtype << "> " << varname << "(" << numelems << ")";

        #ifdef MYDEBUG
        llvm::errs() << "Will Replace:" << getSourceText(Context, s, false) << "\t by:\t" << sstream.str() << "\n";
        #endif

        // v) Replace
        // To this end, we save all rewritings and do it if everything works
        std::vector<std::tuple<SourceRange, std::string, bool>> rewritinglocations;
        rewritinglocations.push_back(std::make_tuple(s->getSourceRange(), sstream.str(), true));


        // * B. We need to get all locations where variable is used and adapt the usage *
        // For each declaration with the matched name, find its occurences in source text via DeclRefExpr;
        // But note that we may find no DeclRef, if variable is never used.

        // First, we go over all DeclRefExpr's and save the possible rewriting.
        // Last, if no errors occured, we rewrite them all. First = SourceRange, Second: new command, Third: true if ReplaceText

        try{
            std::vector<const DeclRefExpr *> declrefexprs =
                    ControlDataFlowGraphQueryHandler::queryAllStmtsForDecl(cfggraph, s);

            for(auto curdeclrefexpr : declrefexprs){

                // Each Decl Ref Expr is below a ArraySubscriptExpr that yields the index information, so go above.
                std::vector<const ArraySubscriptExpr*> dslist =
                        goUpstairsInASTUntilMatch<ArraySubscriptExpr, DeclRefExpr>(curdeclrefexpr, &Context);

                // check that we have not missed the necessary info. May also occur if user e.g. uses *(arr + index). - TODO
                if(dslist.size() != 1){

                    std::vector<const CallExpr*> dslistcallexpr =
                            goUpstairsInASTUntilMatch<CallExpr, DeclRefExpr>(curdeclrefexpr, &Context, 3);

                    // if we have a pointertype, it is possible that the DeclRefExpr is below a CXXDeleteExpr.
                    // We can simply delete the CXXDeleteExpr since we are now working with a vector
                    if(pointype != nullptr){
                        auto cxxdelexpr = handleCXXDeleteExpr(curdeclrefexpr);
                        if(cxxdelexpr != nullptr){
                            // get SourceRange of Delete Expr incl. semicolon!
                            SourceRange sr = getSourceRangeWithSemicolon(Context, cxxdelexpr);
                            rewritinglocations.push_back(std::make_tuple(sr, "", false));
                            continue;
                        }
                        // Return, maybe author used *(arr + index). Then no CXXDelExpr and no ArraySubscriptExpr.
                        return false;
                    } else if (!dslistcallexpr.empty()) {
                        // array is used as argument for function
//                        llvm::errs() << "Var is argument for function (not implemented yet)\n" <<
//                                     dslistcallexpr[0]->getDirectCallee()->getQualifiedNameAsString() << "\n";
                        return false;

                    } else {
                        llvm::errs() << "Could not determine ArraySubscriptExpr for current decl:"
                                     << getSourceText(Context, curdeclrefexpr, false) << "\n";
                        return false;
                    }
                }

                // Now save rewrite
                std::string newdeclref =  "" + varname + "[" + getSourceText(Context, dslist[0]->getIdx(), false) + "]";
                rewritinglocations.push_back(std::make_tuple(dslist[0]->getSourceRange(), newdeclref, true));
            }

        } catch(CFGException &e){
            llvm::errs() << "Note: Could not find a Decl in graph for:"
                         << getSourceText(Context, s, false) << " but everything is fine?! \n";
            return false;
        }

        // Rewrite all
        for(auto &tupl : rewritinglocations){
            if(std::get<2>(tupl)){
                OurRewriter.ReplaceText(std::get<0>(tupl), std::get<1>(tupl));
            } else {
                OurRewriter.RemoveText(std::get<0>(tupl));
            }
        }

        // * C. Finally, add library if necessary *
        insertHeaderAtBeginning("vector");

        return true;
    }


    /**
     * Transforms a variable from type X to Y, e.g. "bool"/"_Bool" to int.
     * We exploit the weak type safety.
     * @param s the declaration whose type will be changed
     * @param newtype the new type as string
     * @return true if successful.
     */
    bool transformXtoY(const DeclStmt *declstmt, std::string newtype) {

        if(newtype=="long")
            return false; // TODO -- add new lib version being capable of that..

        for (DeclStmt::const_decl_iterator db = declstmt->decl_begin(), de = declstmt->decl_end(); db != de; ++db) {
            const VarDecl* s = dyn_cast<VarDecl>(*db);

//            // Find all DeclReferences to VarDecl
//            try{
//                std::vector<const DeclRefExpr *> declrefexprs =
//                        ControlDataFlowGraphQueryHandler::queryAllStmtsForDecl(cfggraph, s);
//
//                for(auto curdeclrefexpr : declrefexprs){
//                    // check usage, e.g. if in C-style input/output, we need to change the format specifier.
//
//                }
//
//            } catch(CFGException &e){
//                llvm::errs() << "Note: Could not find a Decl in graph for:"
//                             << getSourceText(Context, s, false) << " but everything is fine?! \n";
//                return false;
//            }

            auto tloc = s->getTypeSourceInfo()->getTypeLoc();
            OurRewriter.ReplaceText(tloc.getSourceRange(), newtype);
            return true;
        }

        return false;
    }


    /**
     * Transforms a bool literal expression to its corresponding integer literal
     * @param evalexpr a CXXBoolLiteralExpr and its value
     * @return true if successful
     */
    bool transformTrueFalseToOneZero(const EvaluatedCXXBoolLiteralExpr& evalexpr) {
        auto const * expr = std::get<0>(evalexpr);
        assert(expr);
        bool value = std::get<1>(evalexpr);

        // Replace the bool literal expr by either 1 or 0
        OurRewriter.ReplaceText(expr->getSourceRange(), value ? "1" : "0");

        return true;
    }


    bool transformOneZeroToTrueFalse(const EvaluatedImplicitCastExpr& evalexpr) {
        auto const * expr = std::get<0>(evalexpr);
        assert(expr);
        bool value = std::get<1>(evalexpr);

        // Replace the integral literal by either true or false
        // We know this will succeed since we're only calling this for integrals implicitly cast to bools
        OurRewriter.ReplaceText(expr->getSourceRange(), value ? "true" : "false");

        return true;
    }

    /**
     * Transforms a char array such as char str[<length>] to a string if possible
     * If e.g. used in C-based IO such as scanf, we cannot rewrite the char array.
     * If possible, we will also rewrite all equivalent calls such as strlen(str)...
     *
     * Go over all occurences and rewrite API usage. So far, strcpy, strcat are not supported.
     *       i) if strlen, replace by .size()
     *       ii) if in printf, replace by .to_str()
     *       iii) if arraysubscript expr as str[], everything is fine
     *       Otherwise) it is used in a context that we have not considered, yet. No rewriting.
     * @param declstmt the declaration of chosen char array
     * @return true if successful
     */
    bool transformCharArrayToString(const DeclStmt *declstmt) {

        // Get the underyling variable declaration and variable name of current declaration statement.
        const VarDecl* s = dyn_cast<VarDecl>(declstmt->getSingleDecl());
        std::string varname = s->getQualifiedNameAsString();


        // For declaration, find its occurrences in source text via DeclRefExpr;
        // But note that we may find no DeclRef, if variable is never used.
        try {
            std::vector<const DeclRefExpr *> declrefexprs =
                    ControlDataFlowGraphQueryHandler::queryAllStmtsForDecl(cfggraph, s);

            // A. Check that rewriting is safe, i.e. no usage in IO operations such as scanf
            // We collect all possible rewritings and do it only if rewriting is safe = after checking all DeclRefExpr.
            std::vector<std::tuple<SourceRange, std::string>> rewritinglocations;


            for (const auto curdeclrefexpr : declrefexprs) {

                // i. If Decl Ref Expr is below a ArraySubscriptExpr that yields the index information, usage is ok.
                std::vector<const ArraySubscriptExpr*> dslistarr =
                        goUpstairsInASTUntilMatch<ArraySubscriptExpr, DeclRefExpr>(curdeclrefexpr, &Context);
                if (!dslistarr.empty()) // used with [...], so there should be no problem...
                    continue;

                // ii. check if char array is inside some Call Expr = function call, e.g. scanf
                std::vector<const CallExpr*> dslist =
                        goUpstairsInASTUntilMatch<CallExpr, DeclRefExpr>(curdeclrefexpr, &Context);

                // if not empty, decl ref expr is inside some call
                if(!dslist.empty()){
                    if(!checkCharInCallExpr(curdeclrefexpr, dslist[0], varname, rewritinglocations))
                        return false;
                    continue;
                }

                // iii. Case: unknown
                llvm::errs() << "Note: is used in unknown context: (" << varname << ")"
                             << getRowColumn(curdeclrefexpr->getLocStart(), this->sm, false).first << "\n";
                return false;

            }

            // B. Replace declaration
            std::string newdecl = append_std("string") + " " + varname + ";";
            OurRewriter.ReplaceText(getSourceRange(declstmt, sm, Context.getLangOpts()), newdecl);


            // C. Rewrite all locations we have marked for rewriting
            for(auto &tupl : rewritinglocations){
                OurRewriter.ReplaceText(std::get<0>(tupl), std::get<1>(tupl));
            }

            // D. Finally, add library if necessary
            insertHeaderAtBeginning("string");

        } catch(CFGException &e){
            llvm::errs() << "Note: Could not find a Decl in graph for:"
                         << getSourceText(Context, declstmt, false) << " but everything is fine?! \n";
            return false;
        }

        return true;
    }

    /**
     * The declaration reference of char array is inside some call expr = some function call. Check
     * the details and decide if and how we can rewrite the usage. For instance, if strlen(char-array) is written,
     * we can rewrite it to char-array-asstring.size().
     * @param curdeclrefexpr the current DeclRefExpr
     * @param callexpr the detected call expr
     * @param varname the variable name
     * @param rewritinglocations a vector where we collect the rewriting
     * @return true if rewriting is possible..
     */
    bool checkCharInCallExpr(const DeclRefExpr* curdeclrefexpr, const CallExpr* callexpr, std::string &varname,
                               std::vector<std::tuple<SourceRange, std::string>> &rewritinglocations) {

            std::string srctext = getSourceText(Context, callexpr, false);

            // check if it is used in some context where we cannot replace the char array properly
            // Case: scanf
            if(srctext.find("scanf") != std::string::npos)
                return false;

            // Case: cin, is C++ API, so its usage is okay..
            if(srctext.find("cin") != std::string::npos)
                return true;

            // check if char array usage needs some further rewriting, e.g. strlen.
            // Case: strlen
            if(srctext.find("strlen") != std::string::npos){
//                rewritinglocations.push_back(std::make_tuple(getSourceRangeWithSemicolon(Context, callexpr),
//                                                             varname + ".size();"));
                rewritinglocations.push_back(std::make_tuple(getSourceRange(callexpr, sm,
                                                             Context.getLangOpts()),
                                                             varname + ".size()"));
                return true;
            }

            // Case: printf
            if(srctext.find("printf") != std::string::npos){
                rewritinglocations.push_back(std::make_tuple(curdeclrefexpr->getSourceRange(),
                                                             varname + ".c_str()"));
                return true;
            }

            // Case: inside a custom function, then, add Argument to Stack and rewrite it as well TODO

            // Case: unknown
            llvm::errs() << "Note: is used in unknown context: (" << varname << ")" << srctext << "\n";
            return false;
    }

    /* ***************************** String To Char Array ****************************** */
    /**
     * Transform a string into a char array..
     * @param declstmt
     * @return
     */
    bool transformStringToCharArray(const DeclStmt *declstmt) {

        // Get the underyling variable declaration and variable name of current declaration statement.
        const VarDecl *s = dyn_cast<VarDecl>(declstmt->getSingleDecl());
        std::string varname = s->getQualifiedNameAsString();


        // For declaration, find its occurrences in source text via DeclRefExpr;
        // But note that we may find no DeclRef, if variable is never used.
        try {
            std::vector<const DeclRefExpr *> declrefexprs =
                    ControlDataFlowGraphQueryHandler::queryAllStmtsForDecl(cfggraph, s);

            // A. Check that rewriting is safe
            // We collect all possible rewritings and do it only if rewriting is safe = after checking all DeclRefExpr.
            std::vector<std::tuple<SourceRange, std::string>> rewritinglocations;

            for (const auto curdeclrefexpr : declrefexprs) {

                // Two cases possible, since we have a String that is a CXX class
                // A-1) is a CXXOperatorCallExpr such as [] or += ...
                std::vector<const CXXOperatorCallExpr*> dslistOp =
                        goUpstairsInASTUntilMatch<CXXOperatorCallExpr, DeclRefExpr>(curdeclrefexpr, &Context);
                if(!dslistOp.empty()){
                    auto oploc = dslistOp[0]->getOperatorLoc();
                    auto opsrctext = getSourceText(Context, oploc, oploc);
                    // Case: string is accessed via [], which is for char array ok as well
                    if(opsrctext=="]")
                        continue;
                    // Case: string is used for concat. or comparison...
                    if(opsrctext=="+="|| opsrctext=="=="){
                        // actually easy to implement, since we could use strcmp and strcat,
                        // but we would need to rewrite the other variable as well if current string is on right side
                        return false;
                    }
                }

                // A-2) is a CXXMemberCallExpr such as .c_str(), .length(), ...
                std::vector<const CXXMemberCallExpr*> dslistMem =
                        goUpstairsInASTUntilMatch<CXXMemberCallExpr, DeclRefExpr>(curdeclrefexpr, &Context);

                if(!dslistMem.empty()){
                    if(!checkStringInCallExpr(curdeclrefexpr, dslistMem[0], varname, rewritinglocations))
                        return false;
                    continue;
                }

                // A-3) another CallExpr?
                std::vector<const CallExpr*> dslistMem2 =
                        goUpstairsInASTUntilMatch<CallExpr, DeclRefExpr>(curdeclrefexpr, &Context);

                if(!dslistMem2.empty()){
                    if(!checkStringInCallExpr(curdeclrefexpr, dslistMem2[0], varname, rewritinglocations))
                        return false;
                    continue;
                }


                // iii. Case: unknown
                llvm::errs() << "Note: b) is used in unknown context: (" << varname << ")"
                             << getRowColumn(curdeclrefexpr->getLocStart(), this->sm, false).first << "\n";
                return false;
            }

            // B. Replace declaration
            // See paper, we use a hard-coded value of 1000, not completely equivalent to String here. Be careful!
            std::string newdecl = append_std("char") + " " + varname + "[1000];";
            OurRewriter.ReplaceText(getSourceRange(declstmt, sm, Context.getLangOpts()), newdecl);

            // C. Rewrite all locations we have marked for rewriting
            for(auto &tupl : rewritinglocations){
                OurRewriter.ReplaceText(std::get<0>(tupl), std::get<1>(tupl));
            }

            // D. Finally, add library if necessary
            insertHeaderAtBeginning("stdio.h");

        } catch (CFGException &e) {
            llvm::errs() << "Note: Could not find a Decl in graph for:"
                         << getSourceText(Context, declstmt, false) << " but everything is fine?! \n";
            return false;
        }

        return true;
    }

    /**
     * The declaration reference of string is inside some call expr = some function call. Check
     * the details and decide if and how we can rewrite the usage. For instance, if string.size() is written,
     * we can rewrite it to strlen(string-as-chararr)..
     * @param curdeclrefexpr the current DeclRefExpr
     * @param callexpr the detected call expr
     * @param varname the variable name
     * @param rewritinglocations a vector where we collect the rewriting
     * @return true if rewriting is possible..
     */
    bool checkStringInCallExpr(const DeclRefExpr* curdeclrefexpr, const CallExpr* callexpr, std::string &varname,
                             std::vector<std::tuple<SourceRange, std::string>> &rewritinglocations) {

        std::string srctext = getSourceText(Context, callexpr, false);
#ifdef MYDEBUG
        llvm::errs() << "checkStringInCallExpr:" << getSourceText(Context, callexpr) << "\n";
#endif

        // check if it is used in some context where we cannot replace the char array properly
        // Case: getline
        if(srctext.find("getline") != std::string::npos)
            return false;
        if(srctext.find("push_back") != std::string::npos)
            return false;

        // Case: cin, is C++ API that accepts char array, so its usage is okay..
        if(srctext.find("cin") != std::string::npos)
            return true;

        // check if char array usage needs some further rewriting, e.g. strlen.
        // Case: strlen
        if(srctext.find("length") != std::string::npos || srctext.find("size") != std::string::npos){
            rewritinglocations.push_back(std::make_tuple(callexpr->getSourceRange(),
                                                         "strlen(" + varname + ")"));
            return true;
        }

        // Case: cout
        if(srctext.find("c_str()") != std::string::npos){
            rewritinglocations.push_back(std::make_tuple(callexpr->getSourceRange(),
                                                         "*" + varname));
            return true;
        }

        if(srctext.find("cout") != std::string::npos)
            return true;

        // Case: inside some function; if a custom function, then, add Argument to Stack and rewrite it as well TODO
        return false;
    }


    // **** Taken from consoleoutput_transformer ****
    // TODO unify both usages, in consoleoutput and here...
    /**
    * Insert the headerstr---automatically sourrounded by include---before we have the first declaration.
     * @param headerstr
    */
    void insertHeaderAtBeginning(std::string headerstr){

        // header file already defined, nothing to do
        for(auto cs : prepinfos->headerincludes){
            if(cs.first.find(headerstr)!=std::string::npos){
                return;
            }
        }

        // consider only header files that were defined in current src file, get the first in this file
        SourceLocation finalloc;
        bool fromheaderincl = false;
        for(auto cs: prepinfos->headerincludes){
            if (sm.isWrittenInMainFile(cs.second)) {
                finalloc = cs.second;
                fromheaderincl = true;
                break;
            }
        }
        // if no header files were defined, take the first defined declaration where we insert our new include
        if(!fromheaderincl){
            finalloc = firstDeclInSrcFile->getLocStart();
        }

        prepinfos->headerincludes.emplace_back(headerstr, finalloc);
        headerstr = "#include <" + headerstr + ">\n";
        OurRewriter.InsertTextBefore(finalloc, headerstr);
    }


    /**
     * Quite useful helper. If user included the std namespace, this function will just
     * return the input string, otherwise it will add std:: in front of the input string.
     * @param word
     * @return either std::word or word
     */
    std::string append_std(std::string word){
        if(std::find(this->usedNamespaces.begin(),
                     this->usedNamespaces.end(), "std") != this->usedNamespaces.end()) {
            return word;
        } else {
            return "std::"+ word;
        }
    }

};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
            : Visitor(Context, OurRewriter, prepinfos) {
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        auto strategy = static_cast<Strategy>(OurCMDOption1.getValue());
        auto seed = static_cast<int>(OurCMDOption2.getValue());
        Visitor.replacecommand(strategy, seed);
    }

private:
//    commandlineoption cmdoption;
    DataStructureTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory
            <MyFrontendActionWithPrep<MyASTConsumer, PreprocessingInfos>>());
}