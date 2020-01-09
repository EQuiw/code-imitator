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
#include "../ASTFrontendActionWithPrepTemplate.inl"
#include "input_transformer.cpp"
#include "StreamRewriters/InterfaceStdinOutRewriter.h"
#include "../include/SourceTextHelper.h"
#include "StreamRewriters/InterfaceFileRewriter.h"


using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1

typedef std::pair<std::string,std::string> StringPair;


enum Strategy {ifstreamtocin=1, cintoscanf=2, cintoifstream=3};

static llvm::cl::OptionCategory MyOptionCategory("Input C++-Style to C-Style Transformer");

static llvm::cl::opt<Strategy> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                           values(clEnumVal(ifstreamtocin, "ifstream to cin"),
                                                  clEnumVal(cintoifstream, "cin to ifstream"),
                                                  clEnumVal(cintoscanf, "Cin to scanf")),
                                           cat(MyOptionCategory));


static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
static llvm::cl::opt<bool> AllOpt("all", desc("Rewrite all possible code occurences"),
                                  init(false), cat(MyOptionCategory));


class InputCPlusPlusStyleTransformer : public InputTransformer {
public:

    explicit InputCPlusPlusStyleTransformer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos) :
            InputTransformer(Context, OurRewriter, prepinfos) {}


    /* ******************* Collection Methods ******************* */

    /* ******************* Replacement Methods ******************* */

    /**
     * Call this function from ASTConsumer after visiting the whole AST.
     * This function allows us to replace c++ style input stream commands with their c-style counterpart.
     * Also consider special case with sync_with_stdio:
     * If sync_with_stdio is set to false,
     * we need to rewrite all input streams to their c-style counterpart.
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

        assert(strategy == ifstreamtocin || strategy == cintoscanf || strategy == cintoifstream);
        // B. Do transformation
        bool successfulRewrite = false;

        if(strategy == ifstreamtocin){
            if(this->cxxstream_inputexpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            randomlySortVector<const Expr*>(this->cxxstream_inputexpressions, seed);
            for(auto e : this->cxxstream_inputexpressions){
                if(transformInputStreamCall(e, strategy)) return;
            }

        } else if(strategy == cintoifstream) {
            if(this->cplusplusInputExpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            successfulRewrite = transformCinToIfstream();
            if(successfulRewrite)
                return;

        } else if (strategy == cintoscanf) {
            if(this->cplusplusInputExpressions.empty()){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            randomlySortVector<const Expr*>(this->cplusplusInputExpressions, seed);
            for(auto e : this->cplusplusInputExpressions){
                successfulRewrite = transformInputStreamCall(e, strategy) || successfulRewrite;
                if(successfulRewrite && !all) return;
            }
        }

        if(!successfulRewrite)
            llvm::errs() << "Code 123: No transformations possible\n";
    }

private:

    /**
     * Checks input stream's type and delegates the rewriting to the corresponding method.
     * @param e Expr with input stream
     * @param strategy specifies what sub-transformer should be called
     * @return true if successful, else false
     */
    bool transformInputStreamCall(const Expr* e, Strategy strategy) {

        if(strategy == ifstreamtocin){
            if(auto ecxxconstr = dyn_cast<CXXConstructExpr>(e)) {

                auto cinstring = append_std("cin");
                InterfaceStdinOutRewriter iostreamrewriter(Context, OurRewriter, cfggraph, cinstring);
                bool succ = iostreamrewriter.transformIfStream(ecxxconstr, this->cxxstream_inputexpressions);
                if (succ) {
                    insertHeaderAtBeginning("iostream");
                }
                return succ;
            }
            return false;
        } else if(strategy == cintoscanf){
            if(auto ecallexpr = dyn_cast<CallExpr>(e)){
                if(getSourceText(Context, ecallexpr, false).find("cin") != std::string::npos)
                    return transformCinToScanf(ecallexpr);
                llvm::errs() << "Error: transformInputStreamCall, but no cin...\n";
            }
            return false;
        }
        return false;
    }

    bool transformCinToIfstream() {
        // Check if already other file streams are present
        if (checkIfInputFileStreamsArePresent())
            return true;

        if(!cstyleInputExpressions.empty()){
            llvm::errs() << "Code 124: Empty set\n";
            return true;
        }

        auto stream_type = append_std("ifstream");
        InterfaceFileRewriter iostreamrewriter(Context, OurRewriter, cfggraph, false);
        bool succ = iostreamrewriter.transformCoutToOfIfstream(cplusplusInputExpressions, alldeclarationnames,
                                                               usedNamespaces, firstDeclInSrcFile, stream_type);
        if(!succ)
            return false;

        // So far, if someone uses getchar(), we use inputstream.get() although it may not be equivalent.
        //  TODO check if we have problems and exclude if necessary
        for(auto ex : further_cstyle_callexpressions){
            if(ex->getDirectCallee() && ex->getDirectCallee()->getNameAsString() == "getchar"){
//                llvm::errs() << "Code 124: Empty set\n";
//                return true;
                OurRewriter.ReplaceText(ex->getSourceRange(), iostreamrewriter.newvariablename + ".get()");
            }
        }

        // III. Insert header files if not already defined
        insertHeaderAtBeginning("fstream");
        return true;
    }


    // ************************ CIN TO SCANF ************************** //
    /**
     * Transforms a cin command into a scanf command if the underlying types are also supported by scanf,
     * i.e. must be supported by C, so int or long long would be ok, but strings not..
     * @param e the current expression with cin call
     * @return true if no error, false if no rewriting is possible due to error
     */
    bool transformCinToScanf(const CallExpr* e) {
        #ifdef MYDEBUG
        llvm::errs() << "\t" << getSourceTextStable(e, Context) << "\n";
        #endif

        // A. Each CXXOperatorCallExpr object corresponds to a >> expression. Get all under current call expr in AST.
        std::vector<const CXXOperatorCallExpr*> cxxops;
        try{
            cxxops = get_cxxopcallexprs(e, &sm, ">>");
        } catch(CodeTransformationException& ex) {
            return false;
        }

        // B. Now, for each part, we need to find out its underlying datatype by using the AST

        // B-1) We again collect everything and if everything is ok, we do the rewriting.
        std::vector<std::string> scanfarguments; // the arguments
        std::stringstream formatstring; // the format string
        formatstring << "scanf(\"";

        // B-2) Now go through each split and find the respective DeclRefExpr; we ignore the first cin cmd..
        for(auto cs : cxxops) {
            auto currentstmt = cs->getArg(1);

            std::string src;
            QualType matchType;

            if(isa<ArraySubscriptExpr>(currentstmt) || isa<DeclRefExpr>(currentstmt)) {
                // we have an expression like cin >> a[i];
                // Get type; canonical to go through possible typedef's
                matchType = currentstmt->getType().getTypePtr()->getCanonicalTypeInternal();
                src = getSourceTextStable(currentstmt, Context);
            } else if(isa<UnaryOperator>(currentstmt) || isa<ImplicitCastExpr>(currentstmt)) {
                // try to find DeclRefExpr in AST
                std::vector<const DeclRefExpr*> declrefs;
                recursiveStmtTVisit<DeclRefExpr>(currentstmt, declrefs);
                if(declrefs.size()!=1){
                    llvm::errs() << "No DeclRef for Unary or ImplicitCastExpr\n";
                    return false;
                }
                src = getSourceTextStable(declrefs[0], Context);
                matchType = declrefs[0]->getType().getTypePtr()->getCanonicalTypeInternal();

            } else if(isa<CXXOperatorCallExpr>(currentstmt) || isa<MemberExpr>(currentstmt)) {
                // expression is itself a CXXOperatorCallExpr (but not >> or <<),
                //  like cin >> a[i] where a is a vector<int> e.g.
                // MemberExpr, e.g. as part of tuple, if cin >> a.first ..
                // TODO
                return false;
            } else {
                llvm::errs() << "Error: No DeclRefExpr's or ArraySubscriptExpr detected.. for cin rewriting;\t"
                                << "Class:" << currentstmt->getStmtClassName() << "\n";

                return false;
            }

#ifdef MYDEBUG
            llvm::errs() << getSourceTextStable(currentstmt, Context) << "\tType:" << matchType.getAsString() << "\n";
#endif

            // Now decide if we can parse the underlying type in scanf -- C needs to understand this type;
            // as a first heuristic, we check if it is a built-in type or array / pointer..
            StringPair formatstr = retrieveformatstring(&matchType);

            if(formatstr.first.empty())
                return false;

            // we can rewrite, so save it...
            formatstring << "" << formatstr.first << " ";
            scanfarguments.push_back(formatstr.second + src);
        }

        // C. now create final scanf command and rewrite
        formatstring << "\"";
        for(auto s : scanfarguments)
            formatstring << "," << s;
        formatstring << ")";

#ifdef MYDEBUG
      llvm::errs() << "The new scanf cmd will be:\t" << formatstring.str() << "\n";
#endif

        OurRewriter.ReplaceText(getSourceRange(e, sm, Context.getLangOpts()), formatstring.str());

        // D. check if we need to add stdio library
        insertHeaderAtBeginning("stdio.h");

        return true;
    }


    /**
     * Retrieves the format string for a given type.
     * Similar to consoleoutput_transformer's retrieveformatstring. We may merge these two methods in future.
     * Currently, we support builtin-types as well as char (array's)
     * @param qt the qualified type
     * @return the % specifier
     */
    StringPair retrieveformatstring(QualType *qt){

        StringPair formatstring;
        if(qt->getTypePtr()->isBuiltinType()) {
            // Switch+Strings in C++ not directly possible
            if (qt->getAsString() == "int")
                formatstring.first = "%d";
            if (qt->getAsString() == "float")
                formatstring.first = "%f";
            if (qt->getAsString() == "double")
                formatstring.first = "%lf";
            if (qt->getAsString() == "unsigned int")
                formatstring.first = "%u";
            if (qt->getAsString() == "long")
                formatstring.first = "%ld";
            if (qt->getAsString() == "unsigned long")
                formatstring.first = "%lu";
            if (qt->getAsString() == "long long")
                formatstring.first = "%lld";
            if (qt->getAsString() == "unsigned long long")
                formatstring.first = "%llu";
            if(qt->getTypePtr()->isCharType())
                formatstring.first = "%c";
            formatstring.second = "&";
        } else if(auto qtpointee = dyn_cast<PointerType>(*qt)){
            // if we have a pointer, recursively deduce its pointed type if we have a supported array...
            QualType qtpointeetype = qtpointee->getPointeeType().getTypePtr()->getCanonicalTypeInternal();
            retrieveformatstring_helper(qtpointeetype, formatstring);
        } else if(auto qtarray = dyn_cast<ArrayType>(*qt)){
            QualType qtarraytype = qtarray->getElementType().getTypePtr()->getCanonicalTypeInternal();
            retrieveformatstring_helper(qtarraytype, formatstring);
        }

#ifdef MYDEBUG
        llvm::errs() << "Found:" << qt->getAsString() << " becomes:" << formatstring.first << "\n";
#endif

        return formatstring;
    }

    /**
     * Short helper function for retrieveformatstring function.
     * @param qtype
     * @param formatstring
     */
    void retrieveformatstring_helper(QualType qtype, StringPair &formatstring) {
        auto retvalue = retrieveformatstring(&qtype);
        if(retvalue.first == "%c"){
            formatstring.first = "%s";
        } else if(!retvalue.first.empty()){
            formatstring.first = retvalue.first;
        }
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
    InputCPlusPlusStyleTransformer Visitor;
//    commandlineoption cmdoption;
};

int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory
            <MyFrontendActionWithPrep<MyASTConsumer, PreprocessingInfos>>());
}
