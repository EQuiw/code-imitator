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

#include "../utils_transform.h"
#include "../ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../ControlDataFlow/CDFGraphQueryHandler.h"
#include "../ASTFrontendActionTemplate.inl"

using namespace clang;
//#define MYDEBUG 1

static llvm::cl::OptionCategory MyOptionCategory("Input/Output Stream Path Preprocessor/Transformer");
static llvm::cl::opt<std::string> OurCMDOption1("inputstreampath", llvm::cl::cat(MyOptionCategory));
static llvm::cl::opt<std::string> OurCMDOption2("outputstreampath", llvm::cl::cat(MyOptionCategory));


/**
 * A preprocessor-transformer to rewrite the hard-coded *input / output* stream path,
 * so that we can call a compiled program with the correct file.
 * Sometimes, we have e.g.
 *      ifstream input;
 *      input.open("/custom/path/of/author/to/input.in");
 * In this case, we can compile, but not run the program. This transformer accepts
 * a new input and output path and rewrites the paths for further evasion...
 *
 * Important: This transformer is not a transformer for the evasion attack, it just
 * makes it possible to obtain the program output and compare it with the original output before
 * the evasion attack.
 * It is only necessary for this reason, that's why I call it preprocessor ;)
 */
class IfOStreamPreprocessorTransformer : public RecursiveASTVisitor<IfOStreamPreprocessorTransformer> {
public:

    ControlFlowGraphWithDataFlow *cfggraph;

    explicit IfOStreamPreprocessorTransformer(ASTContext &Context, Rewriter &OurRewriter)
            : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()) {
        cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~IfOStreamPreprocessorTransformer(){
        delete cfggraph;
    }

    /* ******************* Collection Methods ******************* */

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

//    bool VisitVarDecl(VarDecl *d){
//        bool inmainfile = sm.isInMainFile(d->getLocation());
//        if (inmainfile) {
//            llvm::errs() << "d:" << d->getQualifiedNameAsString() << ":" << d->isLocalVarDeclOrParm() << "\n";
//            if (!d->isLocalVarDeclOrParm()){
//                llvm::errs() << "->" << d->getType().getTypePtr()->getCanonicalTypeInternal().getAsString() << "\n";
//            }
//        }
//        return true;
//    }

    /**
     * Save input and ouput stream expression. ifstream, ofstream is a CXXConstructExpr in AST.
     * From fstream library; it opens a file / writes to a file
     * instead of processing the piped input/output directly.
     * However, if an author has two input files during the contest, we exclude the author, since
     * only one input file was possible. Take a closer look to find out what is going on...
     * @param e
     * @return
     */
    bool VisitCXXConstructExpr(CXXConstructExpr* e) {

        auto srcloc = e->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {

            try{
                if(is_globally_used(e))
                    this->globalcxxconstructexprs.push_back(e);
            } catch(CodeTransformationException& ex){
                return false;
            }

            // Case A. Input
            if (!visitCXXConstructExprHelper(e, "ifstream", inputexpr))
                return false;
            // Case B. Output
            if (!visitCXXConstructExprHelper(e, "ofstream", outputexpr))
                return false;
        }
        return true;
    }

    /**
     * Small helper script to check if ifstream / ofstream occurs in code and to save the pointer.
     * @param e a cxx construct expr
     * @param cmpstring string to check the type
     * @param target where we save the reference; the pointer is passed by call by reference..
     * @return false if something goes wrong, i.e. multiple inputs or outputs are defined..
     */
    bool visitCXXConstructExprHelper(CXXConstructExpr* e, std::string cmpstring, const Expr* &target) {

        if(e->getType().getCanonicalType().getAsString().find(cmpstring) != std::string::npos){
#ifdef MYDEBUG
            llvm::outs() << "CXXConstructExpr:" << getSourceText(Context, e) << "\n";
            llvm::outs() << "-->" << e->getType().getCanonicalType().getAsString() << "\n";
#endif
            if(target == nullptr){
                target = e;
            } else {
                llvm::errs() << "Error: Multiple ifstream or freopen commands found.\n";
                return false;
            }
        }
        return true;
    }

    bool VisitCallExpr(CallExpr* e){
        auto srcloc = e->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {

            // I. First, check if function is freopen, and freopen must have 3 arguments
            if (!e->getDirectCallee())
            {
#ifdef MYDEBUG
                llvm::errs() << "Not able to resolve current call expr:" << e->getStmtClassName() << "\n";
#endif
                return true;
            }

            auto fctname = e->getDirectCallee()->getQualifiedNameAsString();

            if(fctname == "freopen"){
                handle_freopen(e);
            } else if(fctname == "fopen"){
                handle_fopen(e);
            } else{
                return true;
            }

        }
        return true;
    }

    /**
     * Handles fopen. Includes some checks if we can understand this freopen command.
     * @param e
     * @return true/false, false if severe errors occured.
     */
    bool handle_fopen(CallExpr* e) {

        if(e->getNumArgs() != 2){
            llvm::errs() << "FOPEN cmd detected, but number of args != 2\n";
            return false;
        }
        std::string arg1 = trim(getSourceText(Context, e->getArg(1)), " ");
//        auto srct = getSourceText(Context, e);

        if(arg1 == "\"r\""){
            if(inputexpr==nullptr){
                this->inputexpr = e;
            } else {
                llvm::errs() << "Error: Multiple ifstream/freopen/fopen commands found.\n";
                return false;
            }
        } else if(arg1 == "\"w\""){
            if(outputexpr==nullptr){
                this->outputexpr = e;
            } else {
                llvm::errs() << "Error: Multiple ifstream/freopen/fopen commands found.\n";
                return false;
            }
        } else {
            llvm::errs() << "unknown 2nd arg in fopen. Submit bug report.\n";
            return false;
        }

        return true;
    }

    /**
     * Handles freopen. Includes some checks if we can understand this freopen command.
     * @param e
     * @return true/false, false if severe errors occured.
     */
    bool handle_freopen(CallExpr* e) {

        if(e->getNumArgs() != 3){
            llvm::errs() << "freopen cmd detected, but number of args != 3\n";
            return false;
        }

//            auto arg0 = getSourceText(Context, e->getArg(0));
        auto arg2 = getSourceText(Context, e->getArg(2));
        auto srct = getSourceText(Context, e);
//        llvm::errs() << "Handle:" << srct << "\n";

        // I. Case A. Input
        // old cmd: if(srct.find("freopen") != std::string::npos & srct.find("stdin") != std::string::npos)
        if(arg2.find("stdin") != std::string::npos){
            if(inputexpr==nullptr){
                this->inputexpr = e;
            } else {
                llvm::errs() << "Error: Multiple ifstream or freopen commands found.\n";
                return false;
            }
        }
        // II. Case B. Output
        if(arg2.find("stdout")!=std::string::npos){
            if(outputexpr==nullptr){
                this->outputexpr = e;
            } else {
                llvm::errs() << "Error: Multiple ifstream or freopen commands found.\n";
                return false;
            }
        }

        if(inputexpr==nullptr && outputexpr==nullptr)
            llvm::errs() << "freopen fct detected, but no stdin and stdout found! Check file and preprocessor\n"
                         << srct << "\n";

//        llvm::errs() << "->" << (inputexpr != nullptr) << ";" << (outputexpr != nullptr) << "\n";

        return true;

    }




    /* ******************* Replacement Methods ******************* */

    void replacecommand(std::string inputstreampath, std::string outputstreampath) {
        bool inputrewrite = rewriteStreamPath(inputexpr, inputstreampath);
        bool outputrewrite = rewriteStreamPath(outputexpr, outputstreampath);
        // we need to pass some status via stderr, since we use stdout just for returning the source code..
        llvm::errs() << "Replace:"<<inputrewrite<<":"<<outputrewrite<<":\n";
    }

private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    // Save all CXX Construct Expr's that are in global context, necessary to check if expr is called at all.
    std::vector<const CXXConstructExpr*> globalcxxconstructexprs;

    const Expr* inputexpr = nullptr;
    const Expr* outputexpr = nullptr;

    /**
     * Check if s lies under a FunctionDecl. If not, it is used globally.
     * @param s
     * @return true if globally, if not under a FunctionDecl (includes RecordDecl, CXXRecordDecl).
     */
    bool is_globally_used(const Stmt* s) {

        std::vector<const FunctionDecl*> dslist =
                goUpstairsInASTUntilMatch<FunctionDecl, Stmt>(s, &Context);
        if(dslist.size() > 1){
            llvm::errs() << "Error: Match multiple FunctionDecl???:" << getSourceTextStable(s, Context) << "\n";
            throw CodeTransformationException();
        } else if (dslist.empty()){
            // now we know that expression is not under a current function, so it must be global.
            return true;
        }
        return false;
    }

    /**
     * Check if CFG path from expr to main fct exists or if variable is in some global context
     * or if within a constructor that is created globally.
     *
     * If so, we have to change the path from freopen
     * and we do not need to call the script with ./program < input; just ./program is sufficient.
     * TODO actually, we should also check if some input IO commands are between freopen and main?
     * @param e
     * @return
     */
    bool check_if_expression_iscalled(const Expr* e){

        // A. check if in global context
        try{
            if(is_globally_used(e))
                return true;
        } catch(CodeTransformationException& ex){
            return false;
        }


        // B. object-oriented check, check if expr is within a constructor for an object
        // and object is created globally...
        // E.g.: struct __s { ... } S; then S is created, and its constructor is called.
        std::vector<const CXXConstructorDecl*> clist =
                goUpstairsInASTUntilMatch<CXXConstructorDecl, Expr>(e, &Context);
        if(!clist.empty()){
            std::vector<const CXXRecordDecl*> record =
                    goUpstairsInASTUntilMatch<CXXRecordDecl, Expr>(e, &Context);
            if(record.size()==1){
                // find Declarations to this struct/class
                auto matchtype = record[0]->getTypeForDecl()->getCanonicalTypeInternal().getAsString();

                // if somewhere obj is created at global scope, then return true
                for(auto r : globalcxxconstructexprs){
                    if(r->getType().getCanonicalType().getAsString() == matchtype){
//                        llvm::errs() << "match for" << matchtype << "\n";
                        return true;
                    }
                }
            } else {
                llvm::errs() << "No/Multiple CXXRecord found, although constructor...\n";
                return false;
            }
        }


        // C. check if path to main
        try{
            return ControlDataFlowGraphQueryHandler::isthereapathtomain(cfggraph, &Context, e);
        } catch(CFGException& ex) {
            llvm::errs() << "Check-if-expression-is-called: Could not find first stmt of main fct\t" <<
                "tried:" << getSourceTextStable(e, Context) << "\n";
            return false;
        }

    }

    /**
     * We rewrite the given path where IO stream is reading from or writing to.
     * @param e the construct expr where IO stream is defined or the freopen command where IO path is defined
     * @param newpath the new path that we want to have
     * @return true if no errors, false if errors or no expr is defined..
     */
    bool rewriteStreamPath(const Expr* e, std::string &newpath) {
        if (e == nullptr)
            return false;

        // check if expr is actually called
        if(!check_if_expression_iscalled(e)) {
#ifdef MYDEBUG
            llvm::errs() << "remove expr as not used:" << getSourceTextStable(e, Context) << "\n";
#endif
            return false;
        }

        // we need to add inverted commas to path string, as it is removed when parsing the cmd line input here
        newpath = "\"" + newpath + "\"";

        if (auto ecxx = dyn_cast<CXXConstructExpr>(e))
            return rewriteCXXPath(ecxx, newpath);
        if (auto efreop = dyn_cast<CallExpr>(e))
            return rewriteFreopenFopenPath(efreop, newpath);

        llvm::errs() << "Error: Unvalid input expr for rewriteStreamPath \n";
        return false;
    }


    /**
     * Rewrite if or of stream object...
     * This method is similiar to input_cplusplusstyle_transf' transformIfStream necessarily.
     * @param e the construct expr where IO stream is defined
     * @param newpath the new path of file
     * @return true if no errors
     */
    bool rewriteCXXPath(const CXXConstructExpr* e, std::string &newpath){

        // Our plan is quite easy. We check for the current expression if we find a StringLiteral
        // in the AST under the expression. If so, we rewrite it, otherwise we will find the path in
        // a DeclRefExpr inside 'open'.
        if(e->getNumArgs() > 0){
            std::vector<const StringLiteral*> refs;
            recursiveStmtTVisit<StringLiteral>(e, refs);
            if(!refs.empty()){
                OurRewriter.ReplaceText(refs[0]->getSourceRange(), newpath);
            }
        }

        // Go over all references to stream expression and check for '.open' command
        // i) We need the parent of current node, the var decl.
        std::vector<const VarDecl*> dslist =
                goUpstairsInASTUntilMatch<VarDecl, CXXConstructExpr>(e, &Context);

        if(dslist.size() != 1){
            llvm::errs() << "Error: Not exactly one VarDecl to CXXConstructExpr:" << getSourceText(Context, e) << "\n";
            return false;
        }
        auto vardecl = dslist[0];

        // ii) over all occurences...
        try {
            std::vector<const DeclRefExpr *> declrefexprs =
                    ControlDataFlowGraphQueryHandler::queryAllStmtsForDecl(cfggraph, vardecl);

            for(auto curdeclrefexpr : declrefexprs){

                    // we need to get the upper call expr in AST from current DeclRefExpr..
                    std::vector<const CXXMemberCallExpr*> dslistref =
                            goUpstairsInASTUntilMatch<CXXMemberCallExpr, DeclRefExpr>(curdeclrefexpr, &Context);

                    if(!dslistref.empty()){
                        std::string membercall = dslistref[0]->getMethodDecl()->getQualifiedNameAsString();
                        // check if member method 'open' is used
                        if(membercall.find("open") != std::string::npos){
                           // get the StringLiteral below and replace it
                            std::vector<const StringLiteral*> refs;
                            recursiveStmtTVisit<StringLiteral>(dslistref[0], refs);
                            if(!refs.empty()){
                                OurRewriter.ReplaceText(refs[0]->getSourceRange(), newpath);
                            }
                        }
                    }
            }

        } catch(CFGException &e){
            llvm::errs() << "Note: Could not find a Decl in graph for:"
                         << getSourceText(Context, vardecl) << " but everything is fine?! \n";
            return false;
        }

        return true;
    }

    /**
     * Replaces the first argument in freopen / fopen (the path) with new path
     * @param e CallExpr
     * @param newpath the new path
     * @return true or false if no error / error
     */
    bool rewriteFreopenFopenPath(const CallExpr* e, std::string &newpath){

        auto fctname = e->getDirectCallee()->getQualifiedNameAsString();

        if((fctname == "freopen" && e->getNumArgs() == 3) ||
                (fctname == "fopen" && e->getNumArgs() == 2)){
            OurRewriter.ReplaceText(e->getArg(0)->getSourceRange(), newpath);
        } else{
            llvm::errs() << "Error: rewriteFreopenFopenPath with n-args:" << e->getNumArgs() << "\n";
        }

        return true;
    }

};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter) : Visitor(Context, OurRewriter) {
        inputstreampath = static_cast<std::string>(OurCMDOption1.getValue());
        outputstreampath = static_cast<std::string>(OurCMDOption2.getValue());
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        Visitor.replacecommand(inputstreampath, outputstreampath);
    }

private:
    std::string inputstreampath;
    std::string outputstreampath;
    IfOStreamPreprocessorTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}