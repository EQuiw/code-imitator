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
//#include "ASTFrontendActionTemplate.inl"
#include "../ASTFrontendActionWithPrepTemplate.inl"
#include "output_transformer.cpp"
#include "../RenamingGuide.h"
#include "../../Utilities/Utils.h"
#include "../include/SourceTextHelper.h"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1


enum Strategy {printftocout=1, printftoasprintf=2, freopentostdout=3, stdouttofreopen=4};

// ** These are the command line options **
static llvm::cl::OptionCategory MyOptionCategory("Printf Transformer");
static llvm::cl::opt<Strategy> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                             values(clEnumVal(printftocout, "Printf to cout"),
                                                    clEnumVal(printftoasprintf,
                                                              "Printf to asprintf"),
                                                    clEnumVal(freopentostdout,
                                                              "Remove freopen"),
                                                    clEnumVal(stdouttofreopen,
                                                              "Add freopen")),
                                             cat(MyOptionCategory));

static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
static llvm::cl::opt<bool> AllOpt("all", desc("Rewrite all possible code occurences"),
                                  init(false), cat(MyOptionCategory));


class OutputCStyleTransformer : public OutputTransformer {
public:

    explicit OutputCStyleTransformer(ASTContext &Context, Rewriter &OurRewriter,
                                            PreprocessingInfos *prepinfos) :
            OutputTransformer(Context, OurRewriter, prepinfos) {}


    /**
     * Call this function from ASTConsumer after visiting the whole AST.
     * This function allows us to replace printf commands with cout commands.
     */
    void replacecommand(Strategy strategy, int seed, bool all) {

        assert(strategy == printftocout || strategy == printftoasprintf
               || strategy == freopentostdout || strategy == stdouttofreopen);

        // A. Check
        if((!this->cxxstream_outputexpressions.empty()) &&
           (!this->coutexpressions.empty() || !this->printfexpressions.empty())){
            // we also have a problem now. The author mixed cout's and ofstream, so we do not have a unique stdout.
            llvm::errs() << "Code 900: no unique stdout. mixed cout's/printfs and ofstream \n";
            return;
        }

        // ** Handling sync_with_stdio. **
        if(!this->syncwithstdio)
            rewrite_syncwithstdio(sync_mode);


        // B. Do transformation
        bool successfulRewrite = false;

        if (strategy == printftocout || strategy == printftoasprintf) {
            // B-1 We rewrite printf to cout or printf to asprintf

            if(this->printfexpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            randomlySortVector<const CallExpr*>(this->printfexpressions, seed);

            for (auto e : this->printfexpressions) {

                if (strategy == printftocout){
                    if (determineIfSimplePrintfCommand(e)) {
                        // TODO Handle also .5f directives --. Do not forget to consider setprecision...
                        bool ret = rewriteSimplePrintfCommand(e);
                        successfulRewrite = successfulRewrite || ret;
                    }
                } else if(strategy == printftoasprintf){
                    bool ret = replacevia_asprintf(e);
                    successfulRewrite = successfulRewrite || ret;
                }
                if(successfulRewrite && !all) {
                    return;
                }
            }



        } else if (strategy == freopentostdout) {
            // B-2 We rewrite freopen to stdout
            if(this->freopen_outputexpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            randomlySortVector<CallExpr*>(this->freopen_outputexpressions, seed);

            for (auto e : this->freopen_outputexpressions) {

                if(rewriteIfFreopen(e))
                    return;
            }
        } else {
            // B-3 we insert freopen
            // strategy == stdouttofreopen
            if(transformStdoutToFreopen())
                return;
        }

        if(!successfulRewrite)
            llvm::errs() << "Code 123: No transformations possible\n";
    }

    /**
     * Check if the current printf expression has a simple structure with only %d or %f
     * placeholders, no more complex commands.
     * A good source for more information is http://www.cplusplus.com/reference/cstdio/printf/
     * @param e current call expression
     * @return true if we have a relatively simple printf command
     */
    bool determineIfSimplePrintfCommand(const CallExpr *e) {

        std::string formatstring = getSourceText(Context, e->getArg(0), false);

        // We rewrite simple printf commands directly.
        // If the number of args matches with the number from the regex,
        // we have a relative simple printf command that we replace here:
        std::regex const rxexpression(regexplaceholders);

        long const match_count(std::distance(
                std::sregex_iterator(formatstring.begin(), formatstring.end(), rxexpression),
                std::sregex_iterator()));

        return (match_count == (e->getNumArgs() - 1));
    }


    /**
     * Replaces a relatively simple printf command with a cout command
     * @param e current call expression
     */
    bool rewriteSimplePrintfCommand(const CallExpr *e) {

        // A. Definitions
        // Get the first printf argument = the format string with all the placeholders..
        std::string formatstring = getSourceText(Context, e->getArg(0), false);

        // B. Get all the substrings between the placeholders
        std::vector<std::string> splits = split(formatstring, regexplaceholders);
        // Assure that each string has inverted commas at the begin. and at the end
        wrapinvertedcommas(splits);
        // Assure the number of splits equals the number of arguments
        if(splits.size() != e->getNumArgs()){
            llvm::errs() << "Splits != Num Args\n";
            return false;
        }

        // C. get the placeholders
        std::vector<std::string> plholders = getMatches(formatstring, regexplaceholders);
        if((splits.size()-1) != plholders.size()){
            llvm::errs() << splits.size() << ";" << plholders.size() << "Splits-1 != plholders.size()\n";
            return false;
        }

        // D. Now get the correct precision for each substring depending on the respective placeholder
        std::vector<std::string> prefixforeachplholder;
        try{
            prefixforeachplholder = getPrecisionPrefix(plholders);
        } catch(CodeTransformationException& ex) {
            llvm::errs() << "Precision-Prefix-Error during printf->cout rewrite:\n";
            return false;
        }

        // D. Construct the new cout command
        std::stringstream sstream;

        // Keep in mind: add std only if user has included the std namespace via "using namespace std"
        sstream << "" << append_std("cout");
        // Now build the rest
        if (!splits[0].empty())
            sstream << " << " << splits[0];
        for (unsigned i = 1; i < e->getNumArgs(); i++) {
            sstream << " << " << prefixforeachplholder[i - 1] << getSrcTextForArg(e->getArg(i));
            if (!splits[i].empty()) {
                // a split could be empty if e.g. printf("bla %i",1) occurs:
                sstream << " << " << splits[i];
            }
        }
        std::string newcoutcommand = sstream.str();

        // Addition: If special character %% occurs, it means that we print a single % -- printf specific...
        newcoutcommand = ReplaceString(newcoutcommand, "%%", "%");

        #ifdef MYDEBUG
        llvm::outs() << "New Command:" << newcoutcommand << "\n";
        #endif

        // D. Replace the old printf command by the new cout command
        OurRewriter.ReplaceText(e->getSourceRange(), newcoutcommand);

        // E. Insert header files if not already defined
        insertHeaderAtBeginning("iostream");
        insertHeaderAtBeginning("iomanip");
//        llvm::outs() << "Prep:!!!: " << prepinfos->headerincludes[0].first << "\n";

        return true;
    }

    /**
     * Get Source Text for Argument.
     * Check if we can shorten the call, e.g. if we have argum.c_str(), then we could directly pass argum.
     * Moreover, check if expression has an overloaded operator << or >> (bit-shifts).
     * @param e the Expr.
     * @return the string that we can insert to printf.
     */
    std::string getSrcTextForArg(const Expr* earg) {
        auto srctext = getSourceText(Context, earg, false);

        // If c_str is inside, we can remove it and directly pass the call.
        if (srctext.find("c_str()") != std::string::npos){
            if(!isa<CXXMemberCallExpr>(earg)) // short check
                llvm::errs() << "Warning: Replace c_str, but is not a CXXMemberCallExpr:" << srctext << "\n";
            srctext = ReplaceString(srctext, ".c_str()", "");
        }
        // << / >> overloading: We can have the case such as printf("%d", a >> 2); this would lead to
        // unvalid code: cout << a >> 2. Thus, add parenthesis...
        if(auto binop = dyn_cast<BinaryOperator>(earg)){
            if(binop->isShiftOp()){
                srctext = "(" + srctext + ")";
            }
        }
        // Cmd such as 'res ? ans : "IMPOSSIBLE"' e.g.:
        if(auto condop = dyn_cast<ConditionalOperator>(earg)){
            srctext = "(" + srctext + ")";
        }

        return srctext;
    }

    /**
     * Replaces a printf command with a cout command that is based on an intermediate asprintf.
     * In this way, we do not have to handle all the different format options from printf.
     * TODO in future, we may handle more format options from printf directly to be more stealthy.
     *
     * Example: We have printf("Value:%.5f\n", d);
     * It becomes
     *      char *temp; asprintf(&temp, "Value:%.5f\n", d);
     *      std::cout << "asprintf:" << temp;
     *      free(temp);
     *
     * @param e current call expression
     */
    bool replacevia_asprintf(const CallExpr *e) {

        // A. Definitions
        // Get the first printf argument = the format string with all the placeholders..
        std::string formatstring = getSourceText(Context, e->getArg(0), false);

        std::string tempvarname = RenamingGuide::getRandomStringWith(4);
        std::string asprintfstr = "char* " + tempvarname + ";\n";
        asprintfstr += "asprintf(&" + tempvarname + ", " + formatstring;
        for (unsigned i = 1; i < e->getNumArgs(); i++) {
            asprintfstr += ", " + getSourceText(Context, e->getArg(i), false);
        }
        asprintfstr += ");\n";

        asprintfstr += "std::cout << " + tempvarname + ";\n";
        asprintfstr += "free(" + tempvarname + ");\n";

        // As we replace a cmd by a multi-line cmd, we need to consider if we need to add curly braces
        ast_type_traits::DynTypedNode dtn = ast_type_traits::DynTypedNode::create(*e);
        bool isWithinCompound = isWithinCompoundStmt(Context, dtn);
        if(!isWithinCompound){
            asprintfstr = "{" + asprintfstr + "}";
        }

        OurRewriter.ReplaceText(getSourceRangeWithSemicolon(Context, e), asprintfstr);

        // Insert header files if not already defined
        insertHeaderAtBeginning("iostream");
        insertHeaderAtBeginning("iomanip");

        return true;
    }


    /**
     * Rewrite freopen to use stdout directly
     * @param e
     * @return true if rewriting was successfull, false if there is not freopen cmd or rewriting failed.
     */
    bool rewriteIfFreopen(CallExpr* e){
        if(getSourceText(Context, e->getCallee())=="freopen"){
            auto srctext = getSourceText(Context, e);
            if (srctext.find("stdout") != std::string::npos){
                // just small check with stdin
                OurRewriter.RemoveText(getSourceRangeWithSemicolon(Context, e));
                return true;
            }
        }
        return false;
    }


    /* ********************** stdout to Freopen *********************** */

    /**
     * Transforms source code to write output into a file via freopen instead of writing to stdout
     * @return true if this transformer was possible and successful (or if empty set).
     */
    bool transformStdoutToFreopen() {

        // A. Check that no other output file is already used for output stream
        if(checkIfOutputFileStreamsArePresent())
            return true;

        // B. Insert freopen cmd at the beginning of main fct.
        try{
            const CompoundStmt* firstStmtOfMain =
                    ControlDataFlowGraphQueryHandler::queryBodyOfMainFunction(cfggraph);

            OurRewriter.InsertTextAfter(firstStmtOfMain->getLBracLoc().getLocWithOffset(1),
                                        "freopen(\"replace-me.out\", \"w\", stdout);\n");

        } catch(CFGException& ex) {
            llvm::errs() << "Could not find first stmt of main fct\n";
            return false;
        }

        return true;
    }


private:

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
    OutputCStyleTransformer Visitor;
};


int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory
            <MyFrontendActionWithPrep<MyASTConsumer, PreprocessingInfos>>());
}

