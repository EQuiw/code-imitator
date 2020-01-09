//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER // This tells Catch that we provide a main()
#include "catch.hpp"

#include "../feature_extraction_single/ast_node_types.cpp"

// Global pointer to GetNodeTypes such that
// TEST_CASE below can access the variables that AST Visitor computed before.
GetNodeTypes* gl_Visitor;


TEST_CASE( "Testing AST Node Types", "[AST Node Types]" ) {
    REQUIRE( gl_Visitor->map["\"FloatingLiteral\""] == 1);
    REQUIRE( gl_Visitor->map["\"IfStmt\""] == 3);
    REQUIRE( gl_Visitor->map["\"Function\""] == 2);
    REQUIRE( gl_Visitor->map["\"ForStmt\""] == 1);
    REQUIRE( gl_Visitor->map["\"BinaryOperator\""] == 8);
    REQUIRE( gl_Visitor->map["\"ReturnStmt\""] == 2);
    REQUIRE( gl_Visitor->map["\"Typedef\""] == 1);

    REQUIRE( gl_Visitor->map_avgdepth["\"ReturnStmt\""] == Approx(3.0));
    REQUIRE( gl_Visitor->map_avgdepth["\"ForStmt\""] == Approx(3.0));
    REQUIRE( gl_Visitor->map_avgdepth["\"ParmVarDecl\""] == Approx(0));
    REQUIRE( gl_Visitor->map_avgdepth["\"CompoundStmt\""] == Approx(6));

    REQUIRE( gl_Visitor->max_depth == 12);
}

static llvm::cl::OptionCategory ToolingSampleCategory("Test-Tooling AST NODE Types Extraction");



class FindNamedClassConsumerTest : public clang::ASTConsumer {
public:
    explicit FindNamedClassConsumerTest(ASTContext *Context, std::string InFile)
            : nodetypes(GetNodeTypes(Context, InFile, true)) {}
    // Let's run the test only once, with param = 1 (True), so that avg is also counted.
    // Max is counted anyway in this case.

    void HandleTranslationUnit(clang::ASTContext &Context) override {

        nodetypes.TraverseDecl(Context.getTranslationUnitDecl());

        // Now do additional stuff: the tests :)
        Catch::Session session;
        gl_Visitor = &nodetypes;

        int numFailed = session.run();

        if(numFailed > 0) {
            llvm::errs() << "ERROR TESTS..." << numFailed << " failures" << "\n";
        } else {
            llvm::outs() << "TESTS OK.." << "\n";
        }

    }

protected:
    GetNodeTypes nodetypes;

};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {

        std::string s = InFile;
        llvm::errs() << "** Creating AST consumer for: " << split_path(s)[1];

        return std::unique_ptr<clang::ASTConsumer>(
                new FindNamedClassConsumerTest(&Compiler.getASTContext(), s));
    }
};


int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, ToolingSampleCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}

