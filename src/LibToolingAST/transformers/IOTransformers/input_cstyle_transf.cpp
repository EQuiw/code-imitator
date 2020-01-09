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
#include "input_transformer.cpp"
#include "../include/SourceTextHelper.h"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1


enum Strategy {scanftocin=1, freopentostdin=2, stdintofreopen=3};
static llvm::cl::OptionCategory MyOptionCategory("Input C-Style to C++-Style Transformer");

static llvm::cl::opt<Strategy> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                           values(clEnumVal(scanftocin, "Scanf to cin"),
                                                  clEnumVal(freopentostdin,
                                                            "freopen to stdin"),
                                                  clEnumVal(stdintofreopen,
                                                            "stdin to freopen")),
                                           cat(MyOptionCategory));


static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
static llvm::cl::opt<bool> AllOpt("all", desc("Rewrite all possible code occurences"),
                                  init(false), cat(MyOptionCategory));


class InputCStyleTransformer : public InputTransformer {
public:

    explicit InputCStyleTransformer(ASTContext &Context, Rewriter &OurRewriter,
                                            PreprocessingInfos *prepinfos) :
            InputTransformer(Context, OurRewriter, prepinfos) {}


    /**
     * Call this function from ASTConsumer after visiting the whole AST.
     * This function allows us to replace c-style input stream commands with their respective c++ counterpart.
     */
    void replacecommand(Strategy strategy, int seed, bool all) {

        // A. Check
        if((!this->cxxstream_inputexpressions.empty()) &&
           (!this->cplusplusInputExpressions.empty() || !this->cstyleInputExpressions.empty())){
            // we also have a problem now. The author mixed cin's and ifstream, so we do not have a unique stdin.
            // freopen is not a stream, thus we ..
            llvm::errs() << "Code 900: no unique stdout. mixed cout's/printfs and ofstream \n";
            return;
        }

        // ** Handling sync_with_stdio. **
        if(!this->syncwithstdio)
            rewrite_syncwithstdio(sync_mode);


        assert(strategy == scanftocin || strategy == freopentostdin || strategy == stdintofreopen);

        // B. Do transformation
        bool successfulRewrite = false;
        if(strategy == scanftocin){
            if(this->cstyleInputExpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            randomlySortVector<const CallExpr*>(this->cstyleInputExpressions, seed);
            for (auto e : this->cstyleInputExpressions) {
                // if transformation was successful and all is false, then return
                successfulRewrite = transformInputStreamCall(e, strategy) || successfulRewrite;
                if(successfulRewrite && !all) return;
            }
        }
        if(strategy == freopentostdin){
            if(this->freopen_inputexpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            randomlySortVector<CallExpr*>(this->freopen_inputexpressions, seed);
            for (auto e : this->freopen_inputexpressions) {
                // if transformation was successful, then return
                if(transformInputStreamCall(e, strategy)) return;
            }
        }

        // We do not need any input commands to insert freopen
        if(strategy==stdintofreopen){
            if(transformStdinToFreopen())
                return;
        }

        if(!successfulRewrite)
            llvm::errs() << "Code 123: No transformations possible\n";
    }

private:


    /**
     * Checks input stream's type and delegates the rewriting to the corresponding method.
     * @param e Call Expr with input stream
     * @param strategy specifies what sub-transformer should be called
     * @return true if successful, else false
     */
    bool transformInputStreamCall(const CallExpr* e, Strategy strategy) {
        auto const srctext = getSourceText(Context, e->getCallee(), false);
        if((strategy==scanftocin) && (srctext=="std::scanf" || srctext=="scanf")){
            return transformScanf(e);
        }
        if((strategy==freopentostdin) && (srctext=="std::freopen" || srctext=="freopen")){
            return transformFreopen(e);
        }

        return false;
    }


    /**
     * Transform a scanf command into a cin command.
     * @param e the respective Call Expr with input stream
     * @return true if transformation was successful
     */
    bool transformScanf(const CallExpr* e) {

        // A. Check if format string in scanf is acceptable
        bool isrewritable = determineIfSimpleScanfCommand(e);
        if(!isrewritable){
            // just for curiosity, we print it...
            llvm::errs() << "Scanf Format String too complex:" << getSourceText(Context, e) << "\n";
            return false;
        }

        std::stringstream sstream;
        sstream << "" << append_std("cin");

        for (unsigned i = 1; i < e->getNumArgs(); i++) {
            sstream << " >> " << getSrcTextForArg(e->getArg(i));
        }
        sstream << ";";
        std::string newcincommand = sstream.str();

        #ifdef MYDEBUG
        llvm::outs() << "New Command:" << newcincommand << "\n";
        #endif

        // Replace the old command by the new cin command
        OurRewriter.ReplaceText(getSourceRangeWithSemicolon(Context, e), newcincommand);

        // Insert header files if not already defined
        insertHeaderAtBeginning("iostream");

        return true;
    }

    bool determineIfSimpleScanfCommand(const CallExpr *e) {

        std::string formatstring = getSourceText(Context, e->getArg(0), false);

        // Regex for simple scanf commands; it just matches with %[length]specifier where length is optional and
        // can be hh, h, l, ll to specify e.g. lld = long long int
        std::string regexplaceholders = "%(hh|h|l|ll|j|z)?[diufegcs]";

        std::regex const rxexpression(regexplaceholders);

        long const match_count(std::distance(
                std::sregex_iterator(formatstring.begin(), formatstring.end(), rxexpression),
                std::sregex_iterator()));

        return (match_count == (e->getNumArgs() - 1));
    }

    /**
     * Get Source Text for Argument.
     * Check if we need to process the source text, i.e. if we passed the address via &, we need to remove &.
     * @param earg an argument from CallExpr
     * @return its source text
     */
    std::string getSrcTextForArg(const Expr* earg) {
        auto srctext = getSourceText(Context, earg, false);

        // Now handle case if & operator is used to pass the address of a variable. We need to remove such an operator
        // If & is used, earg should be an UnaryOperator object.
        if(srctext[0] == '&' && !isa<UnaryOperator>(earg))
            llvm::errs() << "Warning: & is used, but element is not an UnaryOperator:" << srctext << "\n";

        srctext = ReplaceString(srctext, "&", "");

        return srctext;
    }



    /* ********************** Freopen to stdin *********************** */

    /**
     * Transforms freopen with stdin to use stdin directly...
     *  We simply delete freopen, since after deletion, we will simply pipe the input file directly into program.
     * @param e
     * @return
     */
    bool transformFreopen(const CallExpr* e) {

        auto srctext = getSourceText(Context, e);
        if (srctext.find("stdin") != std::string::npos){
            // just small check with stdin
            OurRewriter.RemoveText(getSourceRangeWithSemicolon(Context, e));
            return true;
        }
        return false;
    }

    /* ********************** stdin to Freopen *********************** */

    /**
     * Transforms source code to read input from file via freopen instead of stdin
     * @return true if this transformer was possible and successful
     */
    bool transformStdinToFreopen() {

        if(checkIfInputFileStreamsArePresent())
            return true;

        // B. Insert freopen cmd at the beginning of main fct.
        try{
            const CompoundStmt* firstStmtOfMain =
                    ControlDataFlowGraphQueryHandler::queryBodyOfMainFunction(cfggraph);

            OurRewriter.InsertTextAfter(firstStmtOfMain->getLBracLoc().getLocWithOffset(1),
                "freopen(\"replace-me.in\", \"r\", stdin);\n");

        } catch(CFGException& ex) {
            llvm::errs() << "Could not find first stmt of main fct\n";
            return false;
        }

        return true;
    }


};




/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
            : Visitor(Context, OurRewriter, prepinfos) {
//        cmdoption = static_cast<commandlineoption>(OurCMDOption.getValue());
    }

    void HandleTranslationUnit(ASTContext &Context) override {

        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        Visitor.replacecommand(StrategyOpt.getValue(), SeedOpt.getValue(), AllOpt.getValue());
    }

private:
    InputCStyleTransformer Visitor;
//    commandlineoption cmdoption;
};


int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory
            <MyFrontendActionWithPrep<MyASTConsumer, PreprocessingInfos>>());
}

