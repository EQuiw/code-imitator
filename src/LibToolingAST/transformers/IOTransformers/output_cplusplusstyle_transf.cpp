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
#include "../../Utilities/Utils.h"
#include "utils_io_transformers.h"
#include "../ASTFrontendActionWithPrepTemplate.inl"
#include "output_transformer.cpp"
#include "StreamRewriters/InterfaceStdinOutRewriter.h"
#include "StreamRewriters/InterfaceFileRewriter.h"
#include "../RenamingGuide.h"
#include "../include/SourceTextHelper.h"
#include <algorithm>

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1


enum Strategy {couttoprintf=1, couttostringstream=2, ofstreamtocout=3, splitcoutintotwo=4,
                    couttoofstream=6}; // couttostring=3,

// ** These are the command line options **
static llvm::cl::OptionCategory MyOptionCategory("Cout Transformer");
static llvm::cl::opt<Strategy> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                           values(clEnumVal(couttoprintf, "Cout to printf"),
                                                  clEnumVal(couttostringstream,
                                                            "Replace cout by stringstream"),
                                                  clEnumVal(ofstreamtocout,
                                                            "Replace ofstream by cout"),
                                                  clEnumVal(couttoofstream,
                                                            "Replace cout by ofstream"),
                                                  clEnumVal(splitcoutintotwo,
                                                            "Split cout into two couts")
                                                  ),
                                           cat(MyOptionCategory));

static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
static llvm::cl::opt<bool> AllOpt("all", desc("Rewrite all possible code occurences"),
                                  init(false), cat(MyOptionCategory));




struct CoutToPrintfException : public std::exception {
    const char * what () const throw () {
        return "Exception during Cout to Printf";
    }
};

struct RewrittenCoutInstance {
    const Expr* expr;
    bool fixed;
    std::string precision;
};

class OuputCPlusPlusStyleTransformer : public OutputTransformer {
public:

    explicit OuputCPlusPlusStyleTransformer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos) :
                                            OutputTransformer(Context, OurRewriter, prepinfos) {}


    /* ******************* Collection Methods ******************* */


    /* ******************* Replacement Methods ******************* */


    /**
     * Call this function from ASTConsumer after visiting the whole AST.
     * This function allows us to replace cout commands with printf commands.
     * Also consider special case with sync_with_stdio:
     * If sync_with_stdio is set to false && and no print and couts are mixed,
     * we need to rewrite all prints into cout or vice versa.
     */
    void replacecommand(Strategy cmdoption, int seed, bool all) {

        assert(cmdoption == couttoprintf || cmdoption == splitcoutintotwo || cmdoption == couttoofstream ||
               cmdoption == couttostringstream || cmdoption == ofstreamtocout);

        // A. Check
        if((!this->cxxstream_outputexpressions.empty()) &&
           (!this->coutexpressions.empty() || !this->printfexpressions.empty())){
            // we also have a problem now. The author mixed cout's and ofstream, so we do not have a unique stdout.
            // freopen is not a stream, thus we d
            llvm::errs() << "Code 900: no unique stdout. mixed cout's/printfs and ofstream \n";
            return;
        }

//        // ** Handling sync_with_stdio. **
        // a. If not all, and we'd rewrite a single cout into printf while sync is false, we get problems
        // b. If all, but not each cout was rewritten while sync is false, we get problems

        // B. Do transformation
        bool successfulRewrite = false;
        if(cmdoption == couttoprintf || cmdoption == splitcoutintotwo || cmdoption == couttostringstream){

            if(!all && !this->syncwithstdio)
                rewrite_syncwithstdio(sync_mode); // Handling sync_with_stdio (case a)

            if(this->coutexpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            randomlySortVector<const Expr*>(this->coutexpressions, seed);

            for(auto e : this->coutexpressions){
                // No default case in switch, since:  if we extended the enum, we could fall into the default case
                bool ret = false;
                switch(cmdoption){
                    case couttoprintf: ret = transformOutputStreamCall(e, couttoprintf); break;
                    case couttostringstream: ret = transformOutputStreamCall(e, couttostringstream); break;
                    case splitcoutintotwo: ret = splitCoutCommand(e); break;
                    case couttoofstream: break; // make compiler happy
                    case ofstreamtocout: break;  // make compiler happy
                }
                successfulRewrite = successfulRewrite || ret;
                if(successfulRewrite && !all)
                    return;
            }

            // Check if we can remove expressions that set cout properties and are not necessary
            // if this expression was the last cout expression that will be transformed to printf
            // if not, we may need to add precision + fixed to rewrites where precision and fixed was present in cout.
            removeallprecisionfixed_if_nocoutanymore();

            if(all && !this->syncwithstdio && !check_if_rewritten_all_couts()) {
                rewrite_syncwithstdio(sync_mode); // Handling sync_with_stdio (case b)
            }

        }

        if(cmdoption == couttoofstream){
            if(this->coutexpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            successfulRewrite = transformCoutToOfstream();
            if(successfulRewrite)
                return;
        }

        if(cmdoption == ofstreamtocout){
            if(this->cxxstream_outputexpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            randomlySortVector<const Expr*>(this->cxxstream_outputexpressions, seed);

            for(auto e : this->cxxstream_outputexpressions){
                successfulRewrite = transformOfStreamCall(e);
                if(successfulRewrite)
                    return;
            }
        }

        if(!successfulRewrite)
            llvm::errs() << "Code 123: No transformations possible\n";
    }



    /**
     * Create two cout commands from a single one by dividing the command in the middle.
     * @param ec
     * @return true if it worked.
     */
    bool splitCoutCommand(const Expr *ec){

        const CallExpr* e = dyn_cast<CallExpr>(ec);
        if(e==nullptr){
            llvm::errs() << "split cout command. unvalid type as input\n";
            return false;
        }

        // First, we need to get all the parts between "<<".
        // Consider semicolon
        SourceLocation End(Lexer::getLocForEndOfToken(e->getLocEnd(), 0, sm, Context.getLangOpts()));
        int offs = getOffsetWithSemicolon(Context, e);
        if(offs==(-1)) {
            llvm::errs() << "split cout command. offset error\n";
            return false;
        }
        std::string srctextcout = getSourceText(Context, e->getLocStart(), End.getLocWithOffset(offs));
        std::vector<std::string> splits = split(srctextcout, "(<<)");

        // We need at least two << operator to divide the cout command, so three splits.
        // If size<=1, we have actually no << separator... e.g. if cout.precision(..) is used.
        if(splits.size()<3)
            return false;
        unsigned long newrowposition = splits.size()/2;
//        llvm::outs() << "rewrite.." << getSourceText(Context, e, false) << "\t -- Size:"
//                     << splits.size() << "Split:" << newrowposition << "\n";

        // Now put all the pieces together..
        std::stringstream firstPart;
        std::stringstream secondPart;

        // Do we need {...}?
        // We deal with << ... << statements, so that we have for each << a node in the AST.
        // Thus, the parent is not a Compound Stmt necessarily, we have to go upwards until we find a CompoundStmt
        // or we find a control structure so that we know we have to add curly braces.
        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*e);
        bool isWithinCompound = isWithinCompoundStmt(Context, dtn);

        if(!isWithinCompound){
            firstPart << "{";
        }

        // Now put the various split tokens into the first and second part respectively:
        for(unsigned long i = 0; i <= newrowposition; i++){
            firstPart << "" << splits[i]; // make clion happy with    << "" <<
            if(i != (newrowposition)){
                // we are at the end;
                firstPart << " << ";
            }
        }
        firstPart << ";\n"; // in secondPart, we reuse the already existing semicolon when we replace the srctext.

        secondPart << "" << append_std("cout");
        for(unsigned long i = newrowposition+1; i < splits.size(); i++){
                secondPart << " << " << splits[i];
        }

        if(!isWithinCompound){
            secondPart << "}";
        }

        // Rewrite and insert text
        OurRewriter.ReplaceText(SourceRange(e->getLocStart(), End.getLocWithOffset(offs)), secondPart.str());
        OurRewriter.InsertTextBefore(e->getLocStart(), firstPart.str());

        return true;
    }


    /**
     * Transforms an expr from ofstream to cout if possible.
     * @param e
     * @return true if transformation was possible, false if no ofstream there or error has occured
     */
    bool transformOfStreamCall(const Expr* e){
        if(auto ecxxconstr = dyn_cast<CXXConstructExpr>(e)) {

            auto cinstring = append_std("cout");
            InterfaceStdinOutRewriter iostreamrewriter(Context, OurRewriter, cfggraph, cinstring);
            bool succ = iostreamrewriter.transformIfStream(ecxxconstr, this->cxxstream_outputexpressions);
            if (succ) {
                insertHeaderAtBeginning("iostream");
            }
            return succ;
        }
        return false;
    }


    bool transformCoutToOfstream(){

        // Check if already other file streams are present
        if (checkIfOutputFileStreamsArePresent())
            return true;

        if(!printfexpressions.empty()){
            llvm::errs() << "Code 124: Empty set\n";
            return true;
        }

        auto stream_type = append_std("ofstream");
        InterfaceFileRewriter iostreamrewriter(Context, OurRewriter, cfggraph, true);
        bool succ = iostreamrewriter.transformCoutToOfIfstream(coutexpressions, alldeclarationnames,
                                            usedNamespaces, firstDeclInSrcFile, stream_type);
        if(!succ)
            return false;

        // III. Insert header files if not already defined
        insertHeaderAtBeginning("fstream");
        return true;
    }


    /**
     * Transforms a cout expr to printf. The method delegates the rewriting to the corresponding sub-method
     * if via printf directly or via stringstream
     * @param e Expr with output stream
     * @return true if successful, else false
     */
    bool transformOutputStreamCall(const Expr* e, Strategy cmdoption) {

        if(auto ecallexpr = dyn_cast<CallExpr>(e)){
            if(getSourceText(Context, ecallexpr, false).find("cout") != std::string::npos){

                // I. First, we need to check if there is a corresponding call via printf/string for current CallExpr,
                // it just may be some setprecision cmd..
                if(determineIfOnlyPrecisionFixedStatement(ecallexpr)) {
                    // As we just rewrite
                    // one expression, return false to trigger that we look at the next Expr.
                    return false;
                }

                // II. we try to convert the cout command into a printf directly
                if(cmdoption == couttoprintf)
                    if(rewriteCoutCommand(ecallexpr))
                        return true;

                // III. we try stringstream and print it via printf
                if(cmdoption == couttostringstream)
                    if(transformCoutToString(ecallexpr))
                        return true;

                return false;
            } else {
                // So far, each call expr must contain cout
                llvm::errs() << "Error: transformOutputStreamCall, but no cout...\n";
            }
        }

        return false;
    }

    // ******************************* Convert Cout To Printf directly ******************************* //

    /**
     * Rewrite the cout command into a printf command.
     * @param e
     * @return true if it worked.
     */
    bool rewriteCoutCommand(const CallExpr *e){

#ifdef MYDEBUG
        llvm::errs() << getSourceText(Context, e, false) << "\n";
#endif

        // A. Each CXXOperatorCallExpr object corresponds to a << expression. Get all under current call expr in AST.
        std::vector<const CXXOperatorCallExpr*> cxxops;
        try{
            cxxops = get_cxxopcallexprs(e, &sm, "<<");
        } catch(CodeTransformationException& ex) {
            return false;
        }

        // B. The output may also depend on some properties defined before.
        // So far, we only consider if precision was changed before.
        // Strategy: For given cout, determine via CFG and previous statements if precision was defined.
        //      This gives an initial precision for all substatements in cout << ... .
        //      Next, we always look if user defined a new precision in the cout << hierachy, so all subsequent
        //      float statements will get a new precision.
        int currentprecision;
        bool isfixed;
        try{
            currentprecision = determinePrecisionForExpr(cxxops[0]->getArg(0));
            isfixed = determineFixedForExpr(cxxops[0]->getArg(0));
        } catch(CFGException& ex) {
            llvm::errs() << "CFG-Error during cout->printf rewrite:" << getSourceText(Context, e, false) << "\n";
            return false;
        }

        // Here, we save the format substrings and args for printf
        std::vector<std::string> formatstr;
        std::vector<std::string> args;

        // we need two flags to check if precision and fixed stmt is inside cout; if so;
        // we need later (if cout commands remain) to add setprecision and fixed after printf to preserve the
        // output of following cout statements.
        auto rewrittencoutinst = std::make_shared<RewrittenCoutInstance>();
        rewrittencoutinst->expr = e;

        // C. We iterate from first to last statement.
        for(auto s : cxxops){
            auto currentstmt = s->getArg(1);
#ifdef MYDEBUG
            llvm::errs() << "\t" << getSourceText(Context, currentstmt) << "\n";
#endif

            // a) check if current statement is 'endl'
            try{
                if(checkiflaststmtisendl(currentstmt)){
                    formatstr.emplace_back("\\n");
                    continue;
                }
            } catch(CoutToPrintfException& ex) {
                return false;
            }

            // b) we need to find out its underlying datatype by using the AST
            if (handleStaticContent(currentstmt, formatstr)) {
                // b.1 Static content: If we have a string,
                // we can directly insert it into printf; Done in handleStaticContent.

            } else if(getSourceText(Context, currentstmt).find(append_std("setprecision"))!=std::string::npos) {
                // b.2.1 A cout property: set precision TODO use clang way instead of string parsing
                currentprecision = extractprecision(getSourceText(Context, currentstmt));
                rewrittencoutinst->precision = getSourceText(Context, currentstmt);

            } else if(getSourceText(Context, currentstmt).find(append_std("fixed"))!=std::string::npos) {
                // b.2.2 A cout property: fixed TODO use clang way instead of string parsing
                isfixed = true;
                rewrittencoutinst->fixed = true;

            } else {
                // b.3 A dynamically created content
                //  Get the final data type for the current split expression

                QualType *f = new QualType(currentstmt->getType().getCanonicalType());

                // Now get the format specifier such as %f for the current type.
                // retrieveformatstring returns a std::pair where the first represents the specifier,
                // the 2nd is a suffix that we may need to add to the printf argument for compatibility.
                StringPair fstr = retrieveformatstring(f, currentprecision, isfixed);
                delete f;
                if (fstr.first.empty()) {
                    // Stop; we have not found a valid specifier for the given datatype
                    return false;
                } else {
                    args.push_back(trim(getSourceText(Context, currentstmt), " ") + fstr.second);
                    formatstr.push_back(fstr.first);
                }
            }

        }

        // D. Create the final printf command.
        std::stringstream printfCmd;
        printfCmd << "\"";
        if (!formatstr.empty()) {
            for (std::string& cs : formatstr) {
                // Ensure each % is escaped by %%
                printfCmd << "" << cs;
            }
        } else {
            return false;
        }
        printfCmd << "\"";

        std::stringstream printfArgs;
        if (!args.empty()) {
            for (std::string& carg : args) {
                printfArgs << ", " << carg;
            }
        }

        // E. Replace cout by printf
        std::string newprintfcommand = "printf(" + printfCmd.str() + printfArgs.str() + ")";
#ifdef MYDEBUG
        llvm::outs() << "New Printf Command:\t" << newprintfcommand << "\n";
#endif
        OurRewriter.ReplaceText(e->getSourceRange(), newprintfcommand);

        // F. Insert header files if not already defined
        insertHeaderAtBeginning("stdio.h");
        // Note that we cannot remove iostream if we do not know if another API may need it. We have to call iwyu later.

        // G. Remark that we have rewritten this cout successfully
        // - necessary for 'removeallprecisionfixed_if_nocoutanymore' fct
        rewritten_coutexpressions.push_back(rewrittencoutinst);

        return true;
    }

    /**
     * Check if current statement is 'endl' / 'std::endl'
     * @param currentstmt
     * @return true if so, false if not, CoutToPrintfException exception if error occurs.
     */
    bool checkiflaststmtisendl(const Expr* currentstmt){
        bool laststmtisendl = false;
        if(getSourceText(Context, currentstmt).find("endl") != std::string::npos){

            std::vector<const DeclRefExpr*> endlrefs;
            recursiveStmtTVisit<DeclRefExpr>(currentstmt, endlrefs);
            for(auto r : endlrefs){
                if(r->getReferencedDeclOfCallee()->getAsFunction()->getQualifiedNameAsString() == "std::endl")
                    laststmtisendl = true;
            }
            if(!laststmtisendl){
                llvm::errs() << "Cout-Endl Error: Expected Endl since in string, but no Decl to it?\n";
                throw CoutToPrintfException();
            }

            return laststmtisendl;
        }
        return laststmtisendl;
    }

    /**
     * Checks if current split is simply a string. It is a static content then, we can directly copy it into printf
     * without any further arguments for printf.
     * @param curstr the current expr
     * @param formatstr the format string vector. Call by Reference.
     * @return true if static content, false if not and we need to continue with current split.
     */
    bool handleStaticContent(const Expr* curstr, std::vector<std::string> &formatstr){

//        auto rettype = new QualType(curstr->getType().getCanonicalType());
        // Why not simply checking for type == string? Because "constant-string" and char-array have same type later.


        // To find out if it is only a string or char element, we look in AST under current expression.
        // If we only find a CharacterLiteral or StringLiteral, it is probably a fixed string.
        // To ensure that we do not misinterpret calls such as 'foo("string")', we check if source text of curstr
        // is equal to Literal
        std::vector<const CharacterLiteral*> chlits;
        recursiveStmtTVisit<CharacterLiteral>(curstr, chlits);
        std::vector<const StringLiteral*> slits;
        recursiveStmtTVisit<StringLiteral>(curstr, slits);

        // At least one of them needs to have an entry
        if(chlits.size() != 1 && slits.size() != 1)
            return false;
        // Avoid case that both have entries
        if(!chlits.empty() and !slits.empty())
            return false;

        // Check that source text of literal == source text of expression; otherwise, Literal is somewhere inside..
        if(!chlits.empty() && getSourceText(Context, chlits[0]) != getSourceText(Context, curstr))
            return false;
        if(!slits.empty() && getSourceText(Context, slits[0]) != getSourceText(Context, curstr))
            return false;


        std::string content = getSourceText(Context, curstr);
        // So we have a static content, we have to remove whitespaces, inverted commas and escape single % chars.
        if (trim(content, " ").front() == '"' &&
            trim(content, " ").back() == '"') {
            formatstr.push_back(ReplaceString(trim(trim(content, " "), "\""), "%", "%%"));
            return true;
        } else if (trim(content, " ").front() == '\'' &&
                   trim(content, " ").back() == '\'') {
            formatstr.push_back(ReplaceString(trim(trim(content, " "), "\'"), "%", "%%"));
            return true;
        } else {
            llvm::errs() << "Error handleStaticContent: expected string, but no valid content\n";
            return false;
        }
    }



    int determinePrecisionForExpr(const Expr *e) {

        // A. Define all strings where precision information could be present
        std::vector<std::string> targetsrctexts = {"cout.precision", append_std("setprecision")};
        // B. Now do a BFS search; if error, we will get an exception, if match, we get a pointer, if no match: nullptr
//        const Stmt *targetstmt = cfggraph->QueryGetStmtForSourceText(e, targetsrctexts);
        const Stmt *targetstmt = ControlDataFlowGraphQueryHandler::QueryGetStmtForSourceText(
                cfggraph, &Context, e, targetsrctexts);

        if (targetstmt) {
            // C.1 Match! Now parse source text and look out for precision stmt's.
            // If multiple precision stmts are found, use the last one,
            // e.g. if user writes cout << setprecision(2) << ... << setprecision(8);
            std::vector<std::string> splits = split(getSourceText(Context, targetstmt, false), "(<<)");

            // Go backwards through all splits and try to find the match string from above... take the first one..
            for (unsigned long i = splits.size(); i-- > 0;) {
                for (std::string &cs : targetsrctexts) {
                    if (splits[i].find(cs) != std::string::npos) {
                        return extractprecision(splits[i]);
                    }
                }
            }
            llvm::errs() << "Error during precision extraction; we found a precision stmt, but could not extract info.;"
                         << getSourceText(Context, targetstmt, false) << "\n";
            throw CFGException();

        } else {
            // C.2 No match, use default precision
            return -1;
        }
    }


    /**
     * Determine fixed property. Make sure you pass the first arg of first CXXOperatorCallExpr,
     * otherwise we will look for fixed commands in current cout command not before...
     * @param e
     * @return
     */
    bool determineFixedForExpr(const Expr *e) {

        // A. Define all strings where precision information could be present
        std::vector<std::string> targetsrctexts = {append_std("fixed")};
        // B. Now do a BFS search; if error, we will get an exception, if match, we get a pointer, if no match: nullptr
        const Stmt *targetstmt = ControlDataFlowGraphQueryHandler::QueryGetStmtForSourceText(
                cfggraph, &Context, e, targetsrctexts);

        if(e == targetstmt){
            llvm::errs() << "Determine fixed cmd error:" << (e == targetstmt) << "\n";
            throw CFGException();
        }

        return targetstmt != nullptr;
    }

    int extractprecision(const std::string si){
        // ignore clang-tidy, si must be copied.
        // extract the precision information
        std::string iliteral = si.substr(si.find('(') + 1,
                                         si.find(')') - si.find('(') - 1);
        if (!iliteral.empty()) {
            int a = std::stoi(iliteral);
            return a;
        } else {
            llvm::errs() << "Error during precision extraction for:"
                         << si << "\n";
            throw CFGException();
        }
    }


    /**
     * Returns true if cout << setprecision(2); or cout << std::fixed; or cout << setprecision(2) << fixed; only..
     * It does not find the code if author uses cout.precision(5); to this end, check for CXXMemberCallExprs...
     * @param e
     * @return
     */
    bool determineIfOnlyPrecisionFixedStatement(const CallExpr *e){

        std::vector<std::string> splits = split(getSourceText(Context, e, false), "(<<)");

        unsigned startingdepth = 0;
        if(splits.back().find("endl") != std::string::npos){
            // endl is the last part, so we do not have a part that we need to understand
            startingdepth = 1;
        }

        if(startingdepth == (splits.size()-startingdepth)){
            return false;
            // we have just a cout << endl; command.
        }

        for(unsigned i = 1; i < (splits.size()-startingdepth); i++){
            if(splits[i].find(append_std("setprecision"))==std::string::npos &&
                    splits[i].find(append_std("fixed"))==std::string::npos) {
                // Not a "set precision" or "fixed" cmd, so that a cout command that we need to consider for rewrit.
                return false;
            }
        }
        return true;
    }


    bool check_if_rewritten_all_couts() {

        // check if all (remaining) couts were rewritten
        for(auto e : coutexpressions){
            if(auto ecallexpr = dyn_cast<CallExpr>(e)){

                // if only precision-fixed cmd, then ignore it...
                if(determineIfOnlyPrecisionFixedStatement(ecallexpr)){
                    continue;
                }
                // check if cout is in vector of rewritten instances
                bool isinrewritten = false;
                for(auto& re : rewritten_coutexpressions){
                    if(re->expr == e) {
                        isinrewritten = true;
                        break;
                    }
                }
                if(!isinrewritten){
                    // we have one cout that was not rewritten.
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * If no cout commands are present anymore (since we have rewritten all), we can remove
     * the setprecision and fixed only commands...
     */
    void removeallprecisionfixed_if_nocoutanymore() {

        // check if all (remaining) couts were rewritten
        if(!check_if_rewritten_all_couts()){
            reset_cout_properties();
            return;
        }

        // ok, each cout was rewritten into a printf. Let's remove all precision and fixed commands.
        // type: cout << setprecision << fixed << ...
        std::vector<const CallExpr*> RemovableCoutExprs;
        for(auto e : coutexpressions) {
            if (auto ecallexpr = dyn_cast<CallExpr>(e)) {
                // if only precision-fixed cmd, then ignore it...
                if (determineIfOnlyPrecisionFixedStatement(ecallexpr)) {
                    RemovableCoutExprs.push_back(ecallexpr);
                }
            }
        }
        // type: cout.precision
        for(auto e : cxxmember_outputexpressions){
            if (determineIfOnlyPrecisionFixedStatement(e)) {
                RemovableCoutExprs.push_back(e);
            }
        }

        for(auto e : RemovableCoutExprs){
            OurRewriter.RemoveText(getSourceRangeWithSemicolon(Context, e));
        }

    }

    /**
     * We will add a precision or fixed statement after printf rewrite if precision or fixed
     * was inside the previous cout command. This is because other cout commands are still there
     * and may be affected by removing the setprecision << fixed    statement..
     */
    void reset_cout_properties() {

        for(auto& re : rewritten_coutexpressions){
            std::stringstream st;
            st << "" << append_std("cout");
            if(!re->precision.empty()){
                st << "<<" << re->precision;
            }
            if(re->fixed){
                st << "<<" << "fixed";
            }
            st << ";\n";
            if(!re->precision.empty() || re->fixed){
                OurRewriter.InsertTextBefore(re->expr->getLocStart(), st.str());
            }
        }
    }


    // ******************************* Convert Cout To Stringstream ******************************* //

    /**
     * Rewrite the cout command into a stringstream command which is displayed via printf then.
     * cout << some output << endl;
     *      becomes
     * stringstream s;
     * s << some output << endl;
     * printf("%s", s.str().c_str());
     * @param e
     * @return true if it worked.
     */
    bool transformCoutToString(const CallExpr *e){

        // Actually we can reuse most of the expressions that cout uses, however,
        // we need to set the precision and fixed parameters that are not automatically taken from cout..
        std::vector<const CXXOperatorCallExpr*> cxxops;
        recursiveStmtTVisit<CXXOperatorCallExpr>(e, cxxops);
        std::reverse(cxxops.begin(), cxxops.end());

        // If size<=1, we have actually no << separator... e.g. if cout.precision(..) is used.
        if(cxxops.empty()){
            llvm::errs() << "cout command has empty set of cxx operator call expressions\n";
            return false;
        }

        // A. Determine precision before the current cout command via CFG
        // (see rewriteCoutCommand for more details)...
        int currentprecision;
        bool isfixed;
        try{
            currentprecision = determinePrecisionForExpr(cxxops[0]->getArg(0));
            isfixed = determineFixedForExpr(cxxops[0]->getArg(0));
        } catch(CFGException& ex) {
            llvm::errs() << "Error during cout command:" << getSourceText(Context, e, false) << "\n";
            return false;
        }


        // B. Now simply replace cout via stringstream, and add precision and fixed if necessary ...
        auto srcrange = getSourceRangeWithSemicolon(Context, e);

        // B-1: Define stringstream variable
        std::string stringstreamvarname = RenamingGuide::getRandomStringWith(4);
        std::string stringstreamdef = append_std("stringstream") + " " + stringstreamvarname + ";";
//        OurRewriter.InsertTextBefore(e->getLocStart(), stringstreamdef);

        // B-2: get precision and fixed prefix and append it to previous cout cmd
        auto fullcoutcmd = getSourceText(Context, srcrange.getBegin(), srcrange.getEnd());
        std::stringstream newcoutcmd;
        newcoutcmd << "" << stringstreamvarname;
        if(currentprecision != -1)
            newcoutcmd << " << " << append_std("setprecision(" + std::to_string(currentprecision) + ")");
        if(isfixed)
            newcoutcmd << " << " << append_std("fixed");

        if(fullcoutcmd.find("std::cout") != std::string::npos){
            fullcoutcmd = ReplaceString(fullcoutcmd, "std::cout", newcoutcmd.str());
        } else {
            fullcoutcmd = ReplaceString(fullcoutcmd, "cout", newcoutcmd.str());
        }

        // B-3: append new printf cmd for printing
        std::string printfcmd = "printf(\"%s\"," + stringstreamvarname + ".str().c_str());";

        // B-4: concat. all parts and rewrite, check if inside a compound stmt ==> if not, add curly braces { ... }
        // couts are only used in functions. If the parent is not a compound statement, it must be a control statement.
        std::stringstream finaltextbefore;
        const auto Parents = Context.getParents(*e);
        const auto CS = Parents[0].get<CompoundStmt>();
        if (!CS) {
            printfcmd += "}";
            finaltextbefore << "{";
        }
        finaltextbefore << "" << stringstreamdef << "\n" << fullcoutcmd << "\n";

        // Important. If we replace text over multiple lines, the order of rewritings is important..
        // If we replace current cout row by multiple lines, the internal row mapping is not correct and
        // we will also replace some following lines of code..
        OurRewriter.ReplaceText(srcrange, printfcmd);
        OurRewriter.InsertTextBefore(srcrange.getBegin(), finaltextbefore.str());

#ifdef MYDEBUG
        llvm::errs() << "New stringstream cmd:" << finaltextbefore.str() << "\n";
#endif

        // G. Insert header files if not already defined
        insertHeaderAtBeginning("stdio.h");
        insertHeaderAtBeginning("iomanip");
        insertHeaderAtBeginning("sstream");

        // H. Check if we can remove expressions that have set cout properties and are not necessary
        // if this expression was the last cout expression that will be transformed to printf
        // here not necessary, and we also do not use rewritten_coutexpressions, since we need all prec./fixed stmts.
//        removePrecisionFixedStatement(e);

        return true;
    }



private:
    /**
     * Vector to save all rewritten cout occurences
     */
    std::vector<std::shared_ptr<RewrittenCoutInstance>> rewritten_coutexpressions;


};



/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
            : Visitor(Context, OurRewriter, prepinfos) {
    }

    void HandleTranslationUnit(ASTContext &Context) override {

        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        Visitor.replacecommand(StrategyOpt.getValue(), SeedOpt.getValue(), AllOpt.getValue());
    }

private:
    OuputCPlusPlusStyleTransformer Visitor;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory
            <MyFrontendActionWithPrep<MyASTConsumer, PreprocessingInfos>>());
}
