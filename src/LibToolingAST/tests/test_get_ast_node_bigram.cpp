//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER // This tells Catch that we provide a main()
#include "catch.hpp"

#include "../feature_extraction_single/ast_node_bigram.cpp"

// Global pointer to GetNodeBigrams such that
// TEST_CASE below can access the variables that AST Visitor computed before.
GetNodeBigrams* gl_Visitor;


TEST_CASE( "Testing AST Node Bigrams", "[AST Node Bigrams]" ) {
    REQUIRE( gl_Visitor->map["[\"IfStmt\", \"BinaryOperator\"]"] == 3);
    REQUIRE( gl_Visitor->map["[\"Function\", \"CompoundStmt\"]"] == 2);
    REQUIRE( gl_Visitor->map["[\"ReturnStmt\", \"IntegerLiteral\"]"] == 1);
    REQUIRE( gl_Visitor->map["[\"ReturnStmt\", \"ParenExpr\"]"] == 1);
    REQUIRE( gl_Visitor->map["[\"DeclStmt\", \"Var\"]"] == 5);
    REQUIRE( gl_Visitor->map["[\"ImplicitCastExpr\", \"StringLiteral\"]"] == 5);
}

static llvm::cl::OptionCategory ToolingSampleCategory("Test-Tooling AST NODE Bigrams Extraction");



class FindNamedClassConsumerTest : public clang::ASTConsumer {
public:
    explicit FindNamedClassConsumerTest(ASTContext *Context, std::string InFile)
            : nodebigrams(GetNodeBigrams(Context, InFile)) {}

    void HandleTranslationUnit(clang::ASTContext &Context) override {

        nodebigrams.TraverseDecl(Context.getTranslationUnitDecl());

        // Now do additional stuff: the tests :)
        Catch::Session session;
        gl_Visitor = &nodebigrams;

        int numFailed = session.run();

        if(numFailed > 0) {
            llvm::errs() << "ERROR TESTS..." << numFailed << " failures" << "\n";
        } else {
            llvm::outs() << "TESTS OK.." << "\n";
        }

    }

protected:
    GetNodeBigrams nodebigrams;

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

