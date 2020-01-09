//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER // This tells Catch that we provide a main()
#include "catch.hpp"

#include "../feature_extraction_single/lexical_features.cpp"

static llvm::cl::OptionCategory ToolingSampleCategory("Test-Tooling get lexical features");

// Global pointer to GetLexicalFeatures such that
// TEST_CASE below can access the variables that AST Visitor computed before.
GetLexicalFeatures* gl_Visitor;


TEST_CASE( "Testing lexical features", "[lexical_features]" ) {
    REQUIRE( gl_Visitor->numfuncfilesize == Approx(0.002923977) );
    REQUIRE( gl_Visitor->avgparams == Approx(1.5) );
    REQUIRE( gl_Visitor->stdDevNumParams == Approx(1.5) );
    REQUIRE( gl_Visitor->nestingDepth == 5 );
    REQUIRE( gl_Visitor->avgbranchingfactor == Approx(1.5).epsilon(0.00001) );
}

// We overwrite the class from lexical_features.cpp so that the extraction
// is still the same, but we additionally extract features...
class FindNamedClassConsumerTest : public clang::ASTConsumer {
public:
    explicit FindNamedClassConsumerTest(ASTContext *Context, std::string InFile)
            : lexicalfeatures(GetLexicalFeatures(Context, InFile)) {}

    void HandleTranslationUnit(clang::ASTContext &Context) override {

        lexicalfeatures.TraverseDecl(Context.getTranslationUnitDecl());
        lexicalfeatures.extractlexicalfeatures();

        // Now do additional stuff: the tests :)
        Catch::Session session;
        gl_Visitor = &lexicalfeatures;

        int numFailed = session.run();

        if(numFailed > 0) {
            llvm::errs() << "ERROR TESTS..." << numFailed << " failures" << "\n";
        } else {
            llvm::outs() << "TESTS OK.." << "\n";
        }
    }

protected:
    GetLexicalFeatures lexicalfeatures;

};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {

        std::string s = InFile;
        llvm::errs() << "** Creating AST consumer for: " << split_path(s)[1] << "\n";

        return std::unique_ptr<clang::ASTConsumer>(
                new FindNamedClassConsumerTest(&Compiler.getASTContext(), s));
    }
};

int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, ToolingSampleCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}