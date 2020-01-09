#include "code_in_ast_leaves.cpp"

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling code in AST leaves Extraction");
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static llvm::cl::extrahelp MoreHelp("\nThis particular sample extracts code in ast leaves and respective average depth");
static llvm::cl::opt<bool> OurAvgDepthOption("avg-depth", llvm::cl::cat(ToolingSampleCategory));


class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {

        std::string s = InFile;
//        llvm::errs() << "** Creating AST consumer for: " << split_path(s)[1];

        bool get_avg_depth = OurAvgDepthOption.getValue();
//        llvm::errs() << " with avg-depth option: " << get_avg_depth << "** \n";

        return std::unique_ptr<clang::ASTConsumer>(
                new FindNamedClassConsumer(&Compiler.getASTContext(), s, get_avg_depth));
    }
};


int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, ToolingSampleCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}
