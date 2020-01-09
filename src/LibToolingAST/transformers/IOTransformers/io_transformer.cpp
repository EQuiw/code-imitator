//
// The input / output collector that collects information that are relevant for both
//      input- and output transformers.
//

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
#include "utils_io_transformers.h"
#include "../ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../ControlDataFlow/CDFGraphQueryHandler.h"

using namespace clang;
//#define MYDEBUG 1


typedef std::pair<std::string,std::string> StringPair;

struct PreprocessingInfos {
    std::vector<std::pair<std::string, SourceLocation>> headerincludes;
};

enum sync_with_stdio_channels {sync_ouput_only=1, sync_input_only=2, sync_both_output_input=3};


class IOTransformer : public RecursiveASTVisitor<IOTransformer> {

public:

    ControlFlowGraphWithDataFlow *cfggraph;
    Decl * firstDeclInSrcFile = nullptr;

    explicit IOTransformer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
        : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()), prepinfos(prepinfos) {
            cfggraph = new ControlFlowGraphWithDataFlow(&Context);
    }

    ~IOTransformer(){
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

        if(sm.isWrittenInMainFile(srcloc)){
            if(auto *nd = dyn_cast<NamedDecl>(d)){
                if(!firstDeclInSrcFile){
                    firstDeclInSrcFile = d;
                }

                this->alldeclarationnames.push_back(nd->getNameAsString());
            }
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
            usedNamespaces.push_back(ud);
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

    bool VisitCallExpr(CallExpr *e){
        if(!VisitOutputCallExpr(e))
            return false;
        return VisitInputCallExpr(e);
    }

    /**
     * Save all printf or cout expressions.
     * In addition, we check if sync_with_stdio is set to false. If so, we cannot simply rewrite print and cout cmds,
     * since the order would be different. Remind we should check later that only couts or only printf's are used.
     * If they are mixed, and sync_with_stdio is false, we cannot do this transformation.
     * If not, and sync_with_stdio is set to false, we need to rewrite all prints into cout or vice versa.
     */
    bool VisitOutputCallExpr(CallExpr *e){

        auto srcloc = e->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            auto const srctext = getSourceText(Context, e->getCallee(), false);

            bool cond1 = srctext == "std::printf" || srctext == "printf";
            bool cond2 = (srctext == "std::freopen" || srctext == "freopen") &&
                         (getSourceText(Context, e).find("stdout") != std::string::npos);
            bool cond3 = (srctext == "fopen" || srctext == "std::fopen")
                         && e->getNumArgs() == 2
                         && trim(getSourceText(Context, e->getArg(1)), " ") == "\"w\""; // !Do not use SourceTextStable
            // if we use source text stable here, we will get ) as well, because for Expressions, it has an offset of 1.

            if(cond1) {
                // Replacing printf by cout. Check later if we can directly rewrite the command
                // or if we have to use asprintf to avoid more problems.
                this->printfexpressions.push_back(e);

#ifdef MYDEBUG
                llvm::outs() << "\n\nCallee:" << e->getCallee()->getStmtClassName() << "\t";
                llvm::outs() << "#Args:" << e->getNumArgs() << "\n";
                llvm::outs() << "Callee:" << getSourceText(Context, e->getCallee(), false) << "\t";
                llvm::outs() << ";Callee:" << getSourceText(Context, e, false) << "\n";
#endif

            } else if(cond2){
                // Or Replacing freopen by direct stdout.
                this->freopen_outputexpressions.push_back(e);
            } else if(cond3){
                // Or adding fopen (so far, we do not replace or add it, just used for checks)
                this->fopen_outputexpressions.push_back(e);

            } else if(getSourceText(Context, e).find("cout") != std::string::npos && e->getNumArgs() == 2) {
                // Replacing cout by printf: Consider that for each <<, a new CallExpr is created.
                // For instance, "cout << "test:" << i << std::endl;" leads to 3 CallExpr's such that
                // each CallExpr appends a new part of the whole command. The first visited CallExpr
                // should be the one highest Stmt in the hierachy, so that we do not need the subsequent CallExpr's.
                // Look at an ast-dump and you know what I mean. Now, each CallExpr has two arguments.
                // The first argument contains a part of the command, the 2nd argument the new part at the end.

                // The column and line number are usable to identify the whole cout command uniquely.
                // even across the multiple 'Call Expressions' for the same cout << ... << endl command.
                FullSourceLoc fullLoc(e->getLocStart(), sm);
                unsigned first  = fullLoc.getSpellingLineNumber();
                unsigned second  = fullLoc.getSpellingColumnNumber();
                // check if we already have the command,
                // we just store the first occurence while visiting the AST = the whole cout cmd.
                for(auto savede : this->coutexpressions){
                    FullSourceLoc fullLoc_saved(savede->getLocStart(), sm);
                    unsigned first_saved  = fullLoc_saved.getSpellingLineNumber();
                    unsigned second_saved  = fullLoc_saved.getSpellingColumnNumber();
                    if(first_saved == first && second_saved == second){
                        return true;
                    }
                }

                // check that we really deal with a cout-expression. The author Djok uses stream object with name cout.
                // to this end, we collect all DeclRefExpr's, one of them should be cout... and then we check its class.
                auto passexpr = false;
                if(auto cxxopcallexpr = dyn_cast<CXXOperatorCallExpr>(e)){
                    std::vector<const DeclRefExpr*> declrefexpr;
                    recursiveStmtTVisit<DeclRefExpr>(cxxopcallexpr, declrefexpr);
                    for (auto d : declrefexpr){
                        if (getSourceText(Context, d).find("cout") != std::string::npos &&
                            d->getType().getAsString() == "std::ostream") {
                            passexpr = true;
                            break;
                        }
                    }
                }
                if (!passexpr)
                    return true;

#ifdef MYDEBUG
                llvm::outs() << "Location Col-Row:" << getSourceText(Context, e->getArg(0), false) << "\t $$ \t"
                    << getSourceText(Context, e->getArg(1), false) << "\t; L:"
                             << first << ";C:" << second << "\n";
#endif

                this->coutexpressions.push_back(e);
            } else if(srctext.find("sync_with_stdio") != std::string::npos) {

                if(e->getNumArgs() != 1){
                    llvm::errs() << "Sync_with_stdio-getNumArgs != 1\n";
                    return false;
                }

                // If the argument is a const expression, evaluate it and store its value
                if(!e->getArg(0)->EvaluateAsBooleanCondition(this->syncwithstdio, Context)) {
                    // Evaluation failed, go the safe route and assume its false
                    this->syncwithstdio = false;
                }

                this->syncwithstdioexpr = e;
            }

        }

        return true;
    }


    /**
 * Save all input stream expressions.
 * In addition, we check if sync_with_stdio is set to false. If so, we cannot mix c-style and c++-style
 * input streams. You can easily try it by reading an input file with scanf and cin afterwards in a loop.
 * scanf and cin would read the same line. If sync_with_stdio is true, cin would read the next line...
 * If false, we need to rewrite all expressions.
 */
    bool VisitInputCallExpr(CallExpr *e){

        auto srcloc = e->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {

            auto const srctext = getSourceText(Context, e->getCallee(), false);

            bool cond1 = srctext=="std::scanf" || srctext=="scanf";
            bool cond2 = (srctext=="std::freopen" || srctext=="freopen") &
                         (getSourceText(Context, e).find("stdin") != std::string::npos);
            bool cond3 = (srctext == "fopen" || srctext == "std::fopen")
                         && e->getNumArgs() == 2
                         && trim(getSourceText(Context, e->getArg(1)), " ") == "\"r\""; // !Do not use SourceTextStable
            // if we use source text stable here, we will get ) as well, because for Expressions, it has an offset of 1.

            if(cond1) {
                // Replacing scanf.
                this->cstyleInputExpressions.push_back(e);

#ifdef MYDEBUG
                llvm::outs() << "\n\nCallee:" << e->getCallee()->getStmtClassName() << "\t";
                llvm::outs() << "#Args:" << e->getNumArgs() << "\n";
                llvm::outs() << "Callee:" << getSourceText(Context, e->getCallee(), false) << "\t";
                llvm::outs() << ";Callee:" << getSourceText(Context, e, false) << "\n";
#endif
            } else if(cond2){
                // Or Replacing freopen by direct stdin.
                this->freopen_inputexpressions.push_back(e);

            } else if(cond3) {
                // Or adding fopen (so far, we do not replace or add it, just used for checks)
                this->fopen_inputexpressions.push_back(e);
            } else if(getSourceText(Context, e).find("cin") != std::string::npos
                      && e->getNumArgs() == 2) {
                // Replacing cin: Consider that for each >>, a new CallExpr is created.
                // Look at consoleoutput_transformer.cpp's VisitCallExpr for more information...

                // The column and line number are usable to identify the whole cin command uniquely.
                // even across the multiple 'Call Expressions' for the same cin >> ... command.
                FullSourceLoc fullLoc(e->getLocStart(), sm);
                unsigned first  = fullLoc.getSpellingLineNumber();
                unsigned second  = fullLoc.getSpellingColumnNumber();
                // check if we already have the command,
                // we just store the first occurence while visiting the AST = the whole cin cmd.
                for(auto savede : this->cplusplusInputExpressions){
                    FullSourceLoc fullLoc_saved(savede->getLocStart(), sm);
                    unsigned first_saved  = fullLoc_saved.getSpellingLineNumber();
                    unsigned second_saved  = fullLoc_saved.getSpellingColumnNumber();
                    if(first_saved == first && second_saved == second){
                        return true;
                    }
                }

                // TODO check that we really deal with a cin-expression. The author Djok uses stream object with name cin.
                // to this end, we collect all DeclRefExpr's, one of them should be cin... and then we check its class.
                auto passexpr = false;
                if(auto cxxopcallexpr = dyn_cast<CXXOperatorCallExpr>(e)){
                    std::vector<const DeclRefExpr*> declrefexpr;
                    recursiveStmtTVisit<DeclRefExpr>(cxxopcallexpr, declrefexpr);
                    for (auto d : declrefexpr){
                        if (getSourceText(Context, d).find("cin") != std::string::npos &&
                            d->getType().getAsString() == "std::istream") {
                            passexpr = true;
                            break;
                        }
                    }
                }
                if (!passexpr)
                    return true;

#ifdef MYDEBUG
                llvm::outs() << "Location Col-Row:" << getSourceText(Context, e->getArg(0), false) << "\t $$ \t"
                    << getSourceText(Context, e->getArg(1), false) << "\t; L:"
                             << first << ";C:" << second << "\n";
#endif

                this->cplusplusInputExpressions.push_back(e);

            }
//            else if(srctext.find("sync_with_stdio") != std::string::npos) {
//
//                assert(e->getNumArgs() == 1);
//
//                // If the argument is a const expression, evaluate it and store its value
//                if(!e->getArg(0)->EvaluateAsBooleanCondition(this->syncwithstdio, Context)) {
//                    // Evaluation failed, go the safe route and assume its false
//                    this->syncwithstdio = false;
//                }
//
//                this->syncwithstdioexpr = e;
//            }

            // Save further input c-style expressions...
            if(e->getDirectCallee() && e->getDirectCallee()->getNameAsString() == "getchar"){
                further_cstyle_callexpressions.push_back(e);
            }

        }

        return true;
    }




    /**
     * Save all output stream expressions. ofstream is a CXXConstructExpr in AST.
     * ofstream is used from fstream library; it writes to a file instead of writing the output to stdout..
     *
     * In addition, save all input stream expressions. ifstream is a CXXConstructExpr in AST.
     * ifstream is used from fstream library; it opens a file instead of processing the piped input directly.
     * However, we consider later that we can only rewrite ifstream to cin if we have one ifstream and no other
     * input way, otherwise we would mix various input streams. In this case, we would need to use
     * another API for replacement that we leave for future work..
     * @param e
     * @return
     */
    bool VisitCXXConstructExpr(CXXConstructExpr* e) {

        auto srcloc = e->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {

            if(e->getType().getCanonicalType().getAsString().find("ofstream") != std::string::npos){
#ifdef MYDEBUG
                llvm::outs() << "CXXConstructExpr:" << getSourceText(Context, e) << "\n";
                    llvm::outs() << "-->" << e->getType().getCanonicalType().getAsString() << "\n";
#endif
                this->cxxstream_outputexpressions.push_back(e);
            }
            if(e->getType().getCanonicalType().getAsString().find("ifstream") != std::string::npos){
#ifdef MYDEBUG
                llvm::outs() << "CXXConstructExpr:" << getSourceText(Context, e) << "\n";
                    llvm::outs() << "-->" << e->getType().getCanonicalType().getAsString() << "\n";
#endif
                this->cxxstream_inputexpressions.push_back(e);
            }
        }
        return true;
    }

    /**
     * Collect all cout.precision(.) commands.
     * @param e
     * @return
     */
    bool VisitCXXMemberCallExpr(CXXMemberCallExpr* e){
        auto srcloc = e->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            if(e->getCallee()){
                if(getSourceText(Context, e->getCallee()).find("cout.precision") != std::string::npos){
                    this->cxxmember_outputexpressions.push_back(e);
                }
            }
        }
        return true;
    }


protected:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;
    PreprocessingInfos* prepinfos;

    /**
     * The namespaces that are defined by the using command.
     * Necessary to decide if we e.g. use std::cout or simply cout when replacing printf
     */
    std::vector<UsingDirectiveDecl*> usedNamespaces;

    /**
     * Vector to save all printf occurences
     */
    std::vector<const CallExpr*> printfexpressions;
    /**
     * Vector to save all freopen occurences
    */
    std::vector<CallExpr*> freopen_outputexpressions;
    /**
     * Vector to save all cout occurences
     */
    std::vector<const Expr*> coutexpressions;
    /**
     * Vector to save all cxx-stream occurences
    */
    std::vector<const Expr*> cxxstream_outputexpressions;

    /**
     * Vector to save all fopen occurences
     */
    std::vector<const Expr*> fopen_outputexpressions;

    /**
     * Vector to save all cxx-member occurences
    */
    std::vector<const CXXMemberCallExpr*> cxxmember_outputexpressions;

    /**
     * Vector to save all named declarations (used to check for name conflicts, e.g.)
     */
    std::vector<std::string> alldeclarationnames;

    /**
     * A flag that indicates if user specified that sync_with_stdio should be true or false.
     */
    bool syncwithstdio = true;
    const CallExpr* syncwithstdioexpr = nullptr;


    /**
     * Vector to save all c-style input occurences
     */
    std::vector<const CallExpr*> cstyleInputExpressions;
    /**
     * Vector to save all freopen occurences
    */
    std::vector<CallExpr*> freopen_inputexpressions;
    /**
     * Vector to save all c++-style input occurences. We specify the upper class Expr, since
     * we will save CallExpr and CXXConstructExpr.
     */
    std::vector<const Expr*> cplusplusInputExpressions;

    /**
     * Vector to save all fopen occurences
     */
    std::vector<const Expr*> fopen_inputexpressions;

    /**
     * Vector to save all cxx-stream occurences
    */
    std::vector<const Expr*> cxxstream_inputexpressions;

    /**
     * Vector to save further c-style call expressions
     */
    std::vector<const CallExpr*> further_cstyle_callexpressions;


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

        if(namespace_defined("std", this->usedNamespaces)){
            return word;
        } else {
            return "std::"+ word;
        }
    }


    /**
     * Checks if a file stream is present, such as ofstream, freopen, and fopen.
     * If so, returns true.
     */
    bool checkIfOutputFileStreamsArePresent() {

        if (!this->cxxstream_outputexpressions.empty()) {
//            llvm::errs() << "Output stream already used (ofstream)" << "\n";
            llvm::errs() << "Code 124: Empty set\n";
            return true;
        }

        if (!this->freopen_outputexpressions.empty()) {
//            llvm::errs() << "Output stream already used (freopen)" << "\n";
            llvm::errs() << "Code 124: Empty set\n";
            return true;
        }

        if (!this->fopen_outputexpressions.empty()) {
//            llvm::errs() << "Output stream already used (Fopen)" << "\n";
            llvm::errs() << "Code 124: Empty set\n";
            return true;
        }


        return false;
    }


    /**
     * Checks if a file stream is present, such as ifstream, freopen, and fopen.
     * If so, returns true.
     */
    bool checkIfInputFileStreamsArePresent() {
        if (!this->cxxstream_inputexpressions.empty()) {
            llvm::errs() << "Code 124: Empty set\n";
            return true;
        }

        if (!this->freopen_inputexpressions.empty()) {
            llvm::errs() << "Code 124: Empty set\n";
            return true;
        }

        if (!this->fopen_inputexpressions.empty()) {
            llvm::errs() << "Code 124: Empty set\n";
            return true;
        }

        return false;
    }


    /**
     * If sync_with_stdio exists, remove it. If streams are mixed and option is false, we cannot remove it.
     * If sync_with_stdio is not there, add it (with option: true if streams are mixed, false if not)
     */
    void rewrite_syncwithstdio(sync_with_stdio_channels sync_mode) {
        if(!this->syncwithstdioexpr){
            // Add sync, only if not defined already
            // find main start point
            try{
                const CompoundStmt* firstStmtOfMain =
                        ControlDataFlowGraphQueryHandler::queryBodyOfMainFunction(cfggraph);

                bool aremixed = check_if_c_and_cplusplus_is_mixed(sync_mode);

                std::string st = aremixed ? "true" : "false";

                OurRewriter.InsertTextAfter(firstStmtOfMain->getLBracLoc().getLocWithOffset(1),
                                            append_std("ios::sync_with_stdio("+ st +")") + ";\n");
                insertHeaderAtBeginning("iostream");
                return;
            } catch(CFGException& ex) {
                llvm::errs() << "Change:sync_with_stdio -- Could not find first stmt of main fct\n";
                return;
            }
        } else {
            // Remove sync, if not mixed.
            if(!this->syncwithstdio && check_if_c_and_cplusplus_is_mixed(sync_mode)){
                llvm::errs() << "Code 988: Sync-With-Stdio---No transformations possible\n";
                return;
            } else {
                // we simply remove ios::sync_with_stdio, we need to pass the syncexpr expression as stmt to source text
                // so that we get the end of the token, either ; or , -- both is possible, e.g.
                // std::ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); is a valid row..
                const Stmt* syncasstmt = this->syncwithstdioexpr;
                OurRewriter.RemoveText(getSourceRange(syncasstmt, sm, Context.getLangOpts()));
                return;
            }
        }
    }


    /**
     * Check if C and C++ are mixed on the output or input-only domain.
     * For example, check if printf or couts are mixed.
     * @return true if mixed.
     */
    bool check_if_c_and_cplusplus_is_mixed(sync_with_stdio_channels sync_mode) {

        bool aremixed_o = false;
        bool aremixed_i = false;

        if (sync_mode == sync_ouput_only || sync_mode == sync_both_output_input) {
            aremixed_o = check_if_streams_are_mixed(this->coutexpressions,
                                                         this->cxxstream_outputexpressions, this->printfexpressions);
        }
        if (sync_mode == sync_input_only || sync_mode == sync_both_output_input) {
            aremixed_i = check_if_streams_are_mixed(this->cplusplusInputExpressions,
                                                         this->cxxstream_inputexpressions,
                                                         this->cstyleInputExpressions);

            // Check if other C-style APIs are used..
            aremixed_i = aremixed_i || check_if_streams_are_mixed(this->cplusplusInputExpressions,
                                       this->cxxstream_inputexpressions,
                                       this->further_cstyle_callexpressions);
        }
        return aremixed_o || aremixed_i;
    }


};

