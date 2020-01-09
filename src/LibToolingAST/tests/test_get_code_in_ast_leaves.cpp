//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER // This tells Catch that we provide a main()
#include "catch.hpp"

#include "../feature_extraction_single/code_in_ast_leaves.cpp"

// Global pointer to GetNodeBigrams such that
// TEST_CASE below can access the variables that AST Visitor computed before.
CodeInASTLeaves* gl_Visitor2;
CodeInASTLeaves* gl_Visitor3;

TEST_CASE( "Testing AST Code in AST Leaves", "[AST Code AST Leaves]" ) {
    REQUIRE( gl_Visitor2->map["\"float\""] == 1);
    REQUIRE( gl_Visitor2->map["\"3333\""] == 1);
    REQUIRE( gl_Visitor2->map["\"printf\""] == 5);
    REQUIRE( gl_Visitor2->map["\"int (int_ int_ int)\""] == 1);
    REQUIRE( gl_Visitor2->map["\"int (void)\""] == 1);
}

TEST_CASE( "Testing AST Code in AST Leaves Avg Dep", "[AST Code AST Leaves Avg Dep]" ) {
    REQUIRE( gl_Visitor3->map_avgdepth["\"float\""] == Approx(5.0));
    REQUIRE( gl_Visitor3->map_avgdepth["\"f\""] == Approx(4.0));
    REQUIRE( gl_Visitor3->map_avgdepth["\"3333\""] == Approx(12.0));
}

static llvm::cl::OptionCategory ToolingSampleCategory("Test-Tooling Code in AST Leaves");



class FindNamedClassConsumerTest : public clang::ASTConsumer {
public:
    explicit FindNamedClassConsumerTest(ASTContext *Context, std::string InFile) :
            codeinastleaves(CodeInASTLeaves(Context, InFile, false)),
            codeinastleaves_avgdepth(CodeInASTLeaves(Context, InFile, true))
            {}

    void HandleTranslationUnit(clang::ASTContext &Context) override {

        codeinastleaves.TraverseDecl(Context.getTranslationUnitDecl());
        codeinastleaves_avgdepth.TraverseDecl(Context.getTranslationUnitDecl());

        // Now do additional stuff: the tests :)
        Catch::Session session;
        gl_Visitor2 = &codeinastleaves;
        gl_Visitor3 = &codeinastleaves_avgdepth;

        int numFailed = session.run();

        if(numFailed > 0) {
            llvm::errs() << "ERROR TESTS..." << numFailed << " failures" << "\n";
        } else {
            llvm::outs() << "TESTS OK.." << "\n";
        }

    }

protected:
    CodeInASTLeaves codeinastleaves;
    CodeInASTLeaves codeinastleaves_avgdepth;
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



