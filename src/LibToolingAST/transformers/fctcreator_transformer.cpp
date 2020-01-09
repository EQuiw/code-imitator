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
#include "ASTFrontendActionTemplate.inl"
#include "ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "ControlDataFlow/CDFGraphQueryHandler.h"
#include "clang/AST/ParentMap.h"
#include "RenamingGuide.h"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1

enum Strategies {add_function_compound = 1, add_function_compoundcompound=2};
enum ChooseLocationStrategies {arbitrary = 1, deepest = 2};


static llvm::cl::OptionCategory MyOptionCategory("Function Creation Transformer");

// ** These are the command line options **, look at
// https://llvm.org/docs/CommandLine.html#selecting-an-alternative-from-a-set-of-possibilities
static llvm::cl::opt<Strategies> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                          values(clEnumVal(add_function_compound, "Replace Compound by Fct"),
                                                 clEnumVal(add_function_compoundcompound,
                                                           "Replace CompCompound by Fct")),
                                          cat(MyOptionCategory));
static llvm::cl::opt<ChooseLocationStrategies> ChooseLocationStrategyOpt(
        "chooseLocationStrategy", desc("How code block will be selected"), Required,
        values(clEnumVal(arbitrary, "Choose based on seed a random block"),
               clEnumVal(deepest, "Choose the deepest block that is possible")),
        llvm::cl::cat(MyOptionCategory));
static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
//static llvm::cl::opt<int> OurCMDOption4("targetcount", llvm::cl::cat(MyOptionCategory));





typedef std::pair<std::string, QualType> pairstr;

/**
 * We create new functions (inline or normal) to move source text to a new location.
 * In this way, we can modify the AST hierachy and e.g. remove pairs of CompoundStmt's.
 * We do not handle Macro's here.
 */
class FunctionCreatorTransformer : public RecursiveASTVisitor<FunctionCreatorTransformer> {
public:

    ControlFlowGraphWithDataFlow *cfggraph;

    explicit FunctionCreatorTransformer(ASTContext &Context, Rewriter &OurRewriter)
            : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()) {
        cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~FunctionCreatorTransformer(){
        delete cfggraph;
    }
    /* ******************* Collection Methods ******************* */

//    bool VisitNamedDecl(NamedDecl *nd) {
//        auto srcloc = nd->getLocStart();
//        if(sm.isWrittenInMainFile(srcloc)){
//
//            // Save functions that we can rewrite without problems
//            if(auto f = dyn_cast<FunctionDecl>(nd)){
//
////                #ifdef MYDEBUG
////                llvm::outs() << "FctName:" << f->getQualifiedNameAsString()
////                             << "; With Def/Body:" << f->isThisDeclarationADefinition()
////                             << ";" << f->getReturnType().getAsString() << "\t" << std::addressof(*f)<< "\n";
////                #endif
//            }
//        }
//        return true;
//    }

    /**
     * Visit all functions and store them in CFG graph. In addition, saves all function declarations.
     * @param f
     * @return
     */
    bool VisitFunctionDecl(FunctionDecl *f) {
        bool inmainfile = sm.isInMainFile(f->getLocation());
        if (inmainfile) {
            cfggraph->addFunctionDecl(f);
            this->functiondeclarations.push_back(f);
        }
        return true;
    }

    /**
     * Save all CompoundStmt Pairs in AST.
     * @param s
     * @return
     */
    bool VisitCompoundStmt(CompoundStmt *s){
        bool inmainfile = sm.isInMainFile(s->getLocStart());
        if (inmainfile) {

            // I. Save all potential candidates of compound statements that we could move to an own function
            if(!checkIsUsableSingleCompoundStmt(s))
                return true;

            usablesinglecompoundstmts.push_back(s);

            // II. Check if statement is child of a compound stmt, leading to a Compound-Compound Stmt Pair in AST
            std::vector<const CompoundStmt *> compoundlist;
            ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*s);
            goUpstairsInAST<CompoundStmt>(dtn, compoundlist, 1, &Context);

            if (!compoundlist.empty()) {
//                llvm::outs() << "***********\n" << getSourceText(Context, s, false) << "\n***********" << "\n";
                compoundcompoundstmts.push_back(s);
            }
        }
        return true;
    }

    /* ******************* Rewriting Methods ******************* */

    void replacecommand(Strategies strategy, ChooseLocationStrategies chooseLocationStrategy, int seed) {

        assert(strategy==add_function_compound || strategy==add_function_compoundcompound);
        assert(chooseLocationStrategy==arbitrary || chooseLocationStrategy==deepest);

        switch(strategy) {
            case add_function_compound:
                sortCompoundStmts(usablesinglecompoundstmts, chooseLocationStrategy, seed);
                for(auto s : usablesinglecompoundstmts){
                    if(insertnewfunction(s))
                        return;
                }
                break;
            case add_function_compoundcompound:
                sortCompoundStmts(compoundcompoundstmts, chooseLocationStrategy, seed);
                for(auto s : compoundcompoundstmts){
                    if(insertnewfunction(s))
                        return;
                }
        }

        llvm::errs() << "Code 123: No transformations possible\n";
    };


private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    std::vector<CompoundStmt*> compoundcompoundstmts;
    std::vector<CompoundStmt*> usablesinglecompoundstmts;
    std::vector<FunctionDecl*> functiondeclarations;


    /**
     * Checks if compound statement is usable if we want to move a single compound stmt to an own function.
     * So far, we exclude compound statements that are directly below a FunctionDecl.
     * Moreover, we exclude compound statements with a break or continue stmt inside -- In future, we can
     * analyze these code blocks via CFG further and rewrite the blocks as well...
     * Moreover, we exclude blocks that contain a reference to the function A where this code block is in =>
     *  the function A is called recursively. We do so, as we move the code block above before this function A.
     *  As a result, the reference to function A in the new function would be unknown.
     * Moreover, we exclude blocks with gotos and labels that would be across functions due to fct creation.
     * Moreover, we exclude blocks within function templates.
     * @param s compound statement
     * @return true if usable.
     */
    bool checkIsUsableSingleCompoundStmt(CompoundStmt *s) {
        std::vector<const FunctionDecl *> compoundlist;
        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*s);
        goUpstairsInAST<FunctionDecl>(dtn, compoundlist, 1, &Context);
        if(!compoundlist.empty())
            return false;

        std::vector<const ContinueStmt*> continues;
        recursiveStmtTVisit<ContinueStmt>(s, continues);
        if(!continues.empty())
            return false;

        std::vector<const BreakStmt*> breaks;
        recursiveStmtTVisit<BreakStmt>(s, breaks);
        if(!breaks.empty())
            return false;

        if (!checkifcodeblockiscallingupperfunction(s))
            return false;

        if(checkifblockiswithinfunctiontemplatedecl(s))
            return false;

        if(checkifcodeblockhasgotoorlabelsomewhereelse(s))
            return false;

        return true;
    }


    /**
     * Check if code block contains a call reference to function where the code block is currently in.
     *  It means that function was called recursively before, and the code block is doing this.
     * @param s compound stmt = code block.
     * @return true if compound stmt is usable, false if not usable.
     */
    bool checkifcodeblockiscallingupperfunction(CompoundStmt *s){

        // A. Get function where code block is in
        std::vector<const FunctionDecl*> declfcts;
        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*s);

        goUpstairsInAST<FunctionDecl>(dtn, declfcts, -1, &Context);
        if(declfcts.size()!=1){
            llvm::errs() << "Wrong Number of Parent Functions during Fct Check\n";
            return false;
        }

        // B. Now get all CallExpr's in current block and check if they match with function
        std::vector<const CallExpr*> callexprs;
        recursiveStmtTVisit<CallExpr>(s, callexprs);

        for(auto callex : callexprs){
            if(callex->getDirectCallee() != nullptr){
                if(callex->getDirectCallee()->getQualifiedNameAsString() == declfcts[0]->getQualifiedNameAsString()){
#ifdef MYDEBUG
                    llvm::errs() << "Remove current block since it contains a reference to upper fct\n";
                    llvm::errs() << getSourceText(Context, s) << "\n";
#endif
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * Checks if block is within a function template decl.
     *  For instance:
     *      template <typename T1, typename T2, typename T3>
     *      T1 modpow(T1 _a, T2 p, T3 mod) { ... }
     *
     * TODO actually we should check if code block contains template variables, because it is possible
     * that the code block has normal variables...
     * @param s compound stmt
     * @return true if within a template decl.
     */
    bool checkifblockiswithinfunctiontemplatedecl(CompoundStmt *s){
        std::vector<const FunctionTemplateDecl*> declfcts;
        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*s);
        goUpstairsInAST<FunctionTemplateDecl>(dtn, declfcts, -1, &Context);

#ifdef MYDEBUG
        if(!declfcts.empty()) {
            llvm::errs() << "Remove current block since it is within a function template decl.\n";
            llvm::errs() << getSourceText(Context, s) << "\n";
        }
#endif

        return !declfcts.empty();
    }

    /**
     * Check if block contains a goto with a label outside of this block.
     * Background: we cannot have gotos and labels across functions.
     * @param s compound stmt
     * @return true if block is not usable
     */
    bool checkifcodeblockhasgotoorlabelsomewhereelse(CompoundStmt *s){

        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*s);

        // A. check for all gotos in compound stmt if they have a reference to a label outside of this block
        std::vector<const GotoStmt*> gotos;
        recursiveStmtTVisit<GotoStmt>(s, gotos);
        if(!gotos.empty()){
            for(auto g : gotos){
                LabelDecl* ld = g->getLabel();
                ast_type_traits::DynTypedNode ld_dtn = ast_type_traits::DynTypedNode::create(*ld);
                if(!CheckIsChildOf(ld_dtn , dtn, &Context)){
#ifdef MYDEBUG
                    llvm::errs() << "Goto and Label across blocks\n";
#endif
                    return true;
                }
            }
        }

        // TODO B. check for all labels in compound stmt if they are referenced by goto outside of this block

        return false;
    }



    /**
     * Will replace a Compound-Compound Stmt Pair in the AST hierachy by moving the content of the lower Compound
     * Stmt into an own function. For instance, if you write:
     * ```
     * {
     *   int g = 200;
     *   printf("%d\n",g);
     *   }
     * ```
     * Then, we will move the content into an own function.
     *
     * Consider the special case of *return*:
     * A. If author specifies no return stmt in code block,
     *          we simply create a new void function that is called.
     * B. If author specifies a return stmt, we have to break the control flow at the caller location as well.
     *          i) If just return; is used, we need to just break the control flow.
     *          The new function will return a bool for that.
     *          ii) If return Variable; then we need to break the control flow and return the new variable at the caller
     *          location as well. To this end, we will pass this variable as parameter to the new function..
     *
     * @param s the lower Compound Stmt that will be replaced by an own function.
     * @return true if replacement was successful.
     */
    bool insertnewfunction(CompoundStmt *s) {

#ifdef MYDEBUG
        llvm::errs() << "S:" << getSourceText(Context, s) << "\n";
#endif

        std::string newfctname = RenamingGuide::getRandomStringWith(10);
        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*s);

        // I. Find all variables that are defined outside; we need to add them as function parameters
        // for the new function. The parameters are passed by call by reference to make everything easier.

        // Get all DeclRefExpr's within current compound statement
        std::vector<const DeclRefExpr*> declrefexpr;
        recursiveStmtTVisit<DeclRefExpr>(s, declrefexpr);


        // just keep references to variable declarations and if not visited before
        std::set<std::string> svarnames;
        for(long i = declrefexpr.size()-1; i >= 0; i--){

            if(!isa<VarDecl>(declrefexpr[i]->getDecl()))
                declrefexpr.erase(declrefexpr.begin() + i);
            else if(svarnames.find(declrefexpr[i]->getDecl()->getQualifiedNameAsString()) != svarnames.end()){
                declrefexpr.erase(declrefexpr.begin() + i);
            } else {
                svarnames.insert(declrefexpr[i]->getDecl()->getQualifiedNameAsString());
            }
        }

        // Now check if Decl of DeclRefExpr is within the compound statement:
        for(long i = declrefexpr.size()-1; i >= 0; i--){
            ast_type_traits::DynTypedNode d1 = ast_type_traits::DynTypedNode::create(*(declrefexpr[i]->getDecl()));

            if(CheckIsChildOf(d1, dtn, &Context)){
                // remove it since it is not outside, no special treatment necessary
                declrefexpr.erase(declrefexpr.begin() + i);
            }
        }

        // Check if it is a local variable or parameter, if not, we don't need rewrite it.
        // In this way, we actually also solve the problem that cin and cout are treated as variables..
        for(long i = declrefexpr.size()-1; i >= 0; i--){
            if(auto vardec = dyn_cast<VarDecl>(declrefexpr[i]->getFoundDecl())){
                if(!vardec->isLocalVarDeclOrParm()){
                    declrefexpr.erase(declrefexpr.begin() + i);
                }
            }
        }


        // II. Check function position
        std::vector<const FunctionDecl*> declfcts;
        goUpstairsInAST<FunctionDecl>(dtn, declfcts, -1, &Context);

        if(declfcts.size()!=1){
            llvm::errs() << "Wrong Number of Parent Functions during Fct Insertion\n";
            return false;
        }


        // III. Now create the parameter specification for new function
        pairstr returntype = determinereturntype(s);
        std::string calleeretvarname = RenamingGuide::getRandomStringWith(5);

        std::stringstream scallee;
        std::stringstream scaller;

        // Create Interface and Body;  scallee, scaller are saved by call by reference
        createfunctioninterface(scallee, scaller, newfctname, returntype, declrefexpr, calleeretvarname);
        createfunctionbody(scallee, s, returntype, calleeretvarname);
        scallee << "\n\n";


        // IV. Replace finally
        OurRewriter.InsertTextBefore(declfcts[0]->getLocStart(), scallee.str());
        OurRewriter.RemoveText(s->getSourceRange());
        OurRewriter.InsertTextBefore(s->getLocStart(), scaller.str());

        return true;
    }


    /**
     * Return stmt. Determine its type.
     * In addition, Check if code block contains a return statement with or without a variable.
     * @param s
     * @return a pair of strings. The first string contains the type of the new function,
     * the second specifies the type of the variable that was returned in the code block we look at.
     */
    pairstr determinereturntype(const CompoundStmt* s){

        std::vector<const ReturnStmt*> curreturnstmts;
        recursiveStmtTVisit<ReturnStmt>(s, curreturnstmts);
        QualType somequaltype;
        pairstr returntuple("", somequaltype);

        if(curreturnstmts.empty()){
            returntuple.first = "void";
        } else {
            // take the first return statement as reference
            auto retval = curreturnstmts[0]->getRetValue();
            if(retval){
                returntuple.first = "bool";
                returntuple.second = retval->getType();
            } else {
                // Case if author just writes return;
                returntuple.first = "bool";
            }
        }
        return returntuple;
    }


    /**
     * Creates the function declaration (the name, the parameters) and the text for calling the function.
     *
     * If author specified a return stmt in our code block,
     *  we need to stop the control flow at the location where the return stmt was written before.
     *  To this end, we add an if clause at the caller location.
     * @param scallee the text for declaration is saved here. call by reference.
     * @param scaller the text for calling the function is saved here. call by reference.
     * @param newfctname the new function name.
     * @param newfcttype the type of the new function, if void or a specific type.
     * @param declrefexpr a vector of DeclRefExpr's that define the arguments. Should be unique = just one DeclRefExpr
     * per declaration.
     * @param returnvarname the name of the variable at caller side if function is non-void.
     */
    void createfunctioninterface(std::stringstream &scallee, std::stringstream &scaller, const std::string &newfctname,
                                 const pairstr &newfcttype, const std::vector<const DeclRefExpr*> &declrefexpr,
                                 const std::string &returnvarname){

        // I. The start of the function defintion...
        scallee << "inline " << newfcttype.first << " " << newfctname << "(";

        // if caller has to process a return type.
        if(newfcttype.first != "void" && !newfcttype.second.isNull()) {
            scaller << "{\n " << newfcttype.second.getAsString() << " " << returnvarname << ";\n";
            scaller << "if(" << newfctname << "(";
        } else if(newfcttype.first != "void" && newfcttype.second.isNull()) {
            scaller << "{\n if(" << newfctname << "(";
        } else {
            scaller << "" << newfctname << "(";
        }


        // II. Go over all declaration references and add them to the function interface..
        for(unsigned long i = 0; i < declrefexpr.size(); i++){

            auto ddvardecl = cast<VarDecl>(declrefexpr[i]->getFoundDecl());

            // Save type info
//            auto tyloc = ddvardecl->getTypeSourceInfo()->getTypeLoc();
//            std::string vartype2 = getSourceText(Context, ddvardecl->getLocStart(), tyloc.getLocEnd());

            // Save variable name
            std::string varname = ddvardecl->getQualifiedNameAsString();

            // Consider that variable can already be a argument passed by call-by-reference or call-by-pointer.
            // Also consider arrays, these are already passed as pointer.
            std::string vartypeaddition, varcalladdition;
            auto curtype = ddvardecl->getType();

            // It is possible that the type was adjusted, from array to pointer?, e.g. long long dp[18][2][10]
            if(auto curtypeadjusted = dyn_cast<AdjustedType>(curtype)){
                curtype = curtypeadjusted->getOriginalType();
//                llvm::errs() << "Adjusted.." << curtypeadjusted->getAdjustedType().getTypePtr()->getTypeClassName()
//                             << " from " << curtypeadjusted->getOriginalType().getTypePtr()->getTypeClassName() << "\n";
            }
            if(!isa<ReferenceType>(curtype) && !isa<PointerType>(curtype) && !isa<ArrayType>(curtype))
                vartypeaddition = "&";


            // Save type + var name as fct param at caller + callee side
            if(auto curtype_as_arr_type = dyn_cast<ArrayType>(curtype)) {
                auto originaltype = curtype;
                // Here, we have an array such as char s[1][2]:
                // We cannot use getType.getAsAstring, as we would get char [1000] for a char s[1000] var.
                // thus, we need to resolve the inner type of an array, even if it is s[10][20]...

                while(isa<ArrayType>(curtype)){
                    curtype_as_arr_type = cast<ArrayType>(curtype);
                    curtype = curtype_as_arr_type->getElementType();
                }

                // Now replace char [1000] by char varname[1000] in char [1000]:
                std::string vartype = originaltype.getAsString();
                scallee << "" << ReplaceString(vartype, curtype.getAsString(), curtype.getAsString()
                                                                               + " " + varname);
            } else {
                std::string vartype = curtype.getAsString();
                scallee << "" << vartype << vartypeaddition << " " << varname;
            }

            // Now caller side:
            scaller << "" << varname;
            if(i != (declrefexpr.size()-1)){
                scallee << ", ";
                scaller << ", ";
            }
        }

        // II-b. Last but not least, we may need to add the reference to the variable that the code block would return
        if(!newfcttype.second.isNull()){
            std::string vartypeaddition;
            auto curtype = newfcttype.second;
            if(!isa<ReferenceType>(curtype) && !isa<PointerType>(curtype) && !isa<ArrayType>(curtype))
                vartypeaddition = "&";
            if(isa<ArrayType>(curtype)){
                llvm::errs() << "Warning:" << "Array Type as Return Type occurred. Check if everything is correct\n";
            }

            // if empty, it means that no parameters were defined before. We do not need a comma.
            char comma = declrefexpr.empty() ? ' ' : ',';

            // Save type + var name as fct param at caller + callee side
            scallee << comma << curtype.getAsString() << vartypeaddition << " " << returnvarname;
            scaller << comma << returnvarname;
        }


        // III. The end of the new interface
        scallee << ") ";

        if(newfcttype.first != "void" && !newfcttype.second.isNull()) {
            scaller << ")) { return " << returnvarname << "; } }";
        } else if(newfcttype.first != "void" && newfcttype.second.isNull()) {
            scaller << ")) { return; } }";
        } else {
            scaller << ");";
        }

    }

    /**
     * Creates the body of the new function. If not void, and if we have return; stmt's,
     * we need to modify them from
     *      return previous-ret-value;
     * to
     *      returnvarname = previous-ret-value; return 1;
     * @param sstream the body is saved here. Call by reference.
     * @param s the respective Compound Stmt where we get the new body text.
     */
    void createfunctionbody(std::stringstream &sstream, const CompoundStmt *s, const pairstr &newfcttype,
                            const std::string &returnvarname){

        // We get the source text of compound stmt without the right curly brace, as we need to add a final return stmt.
        std::string stext = getSourceText(Context, s->getLBracLoc(),
                                          s->getRBracLoc().getLocWithOffset(-1));


        // Replace all return stmt's by return true to stop the control flow in this new function
        // We also have to consider that we need to save the returned value in the previous-ret-value variable
        std::vector<const ReturnStmt*> curreturnstmts;
        recursiveStmtTVisit<ReturnStmt>(s, curreturnstmts);
        for(auto curret : curreturnstmts){

            std::string srctextret;
            // a. get value of return stmt and save it, do so only if we have a return-value that will be returned..
            if(!newfcttype.second.isNull()) {
                // TODO consider CXX Construct Creation Expr's maybe
//                if (isa<CXXConstructExpr>(curret->getRetValue())) {
//                    srctextret = returnvarname + "(" + getSourceText(Context, curret->getRetValue()) + ");";
//                } else {
                    srctextret = returnvarname + " = " + getSourceText(Context, curret->getRetValue()) + ";";
//                }
            }

            // b. We do not rewrite here directly via OurRewriter, since it would rewrite in the old code block,
            // that we move to the new function later. So replace the return stmt's in the String representation.
            auto returnstring = getSourceText(Context, curret->getLocStart(), curret->getLocEnd());
            stext = ReplaceString(stext, returnstring, srctextret + "return true");
        }

        sstream << "" << stext;
        // At the end of the function, we need a last return stmt as we want to continue with the control flow at the
        // caller side
        if(!curreturnstmts.empty())
            sstream << " return false;";
        sstream << "}";

    }


    /**
     * Sort the array depending on the chosen chooseLocationStrategy option.
     * If arbitrary, we sort the array randomly by using the given seed.
     * If deepest, we sort the array such that the deepest compound stmt is the first element, and then...
     * @param compoundstmts a vector of compound stmt's. -- aiming at the MAX depth feature.
     * @param chooseLocationStrategy either deepest = choose fct based on the deepest caller in AST, any = min calls
     * @param seed -- the seed for sorting arbitrarily.
     */
    void sortCompoundStmts(std::vector<CompoundStmt*> &compoundstmts,
                           const ChooseLocationStrategies chooseLocationStrategy, int seed){

        switch(chooseLocationStrategy) {
            case arbitrary:
                // randomly sort the array
                std::srand ( unsigned ( seed ) );
                std::random_shuffle ( compoundstmts.begin(), compoundstmts.end() );
                break;
            case deepest:
                // sort the array w.r.t. to AST depth
                std::vector<int> astdepth;

                // a. determine the depth for each compound stmt.
                for(auto cmpstmt : compoundstmts) {

                    std::string inFile = sm.getFilename(cmpstmt->getLocStart());
                    int currentdepth = getdepthfornode(Context.getParents(*cmpstmt), &Context, 0, inFile);
                    astdepth.push_back(currentdepth);
                }

                // b. sort, we just use a simple selection sort here for sorting both vectors..
                for(unsigned i = 0; i < compoundstmts.size(); i++){
                    int maxdepth = astdepth[i];
                    int maxdepthindex = i;
                    for(unsigned j = i; j < compoundstmts.size(); j++) {
                        if(astdepth[j] > maxdepth){
                            maxdepth = astdepth[j];
                            maxdepthindex = j;
                        }
                    }
                    auto temp = compoundstmts[maxdepthindex];
                    compoundstmts[maxdepthindex] = compoundstmts[i];
                    astdepth[maxdepthindex] = astdepth[i];
                    compoundstmts[i] = temp;
                    astdepth[i] = maxdepth;
                }

                #ifdef MYDEBUB
                llvm::errs() << "D:" << getSourceText(Context, compoundstmts[0], false)  << "\n\n\n";
                #endif

                break;
        }
    }

};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter) : Visitor(Context, OurRewriter) {
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        Visitor.replacecommand(StrategyOpt.getValue(), ChooseLocationStrategyOpt.getValue(), SeedOpt.getValue());
    }

private:
//    commandlineoption cmdoption;
    FunctionCreatorTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}
