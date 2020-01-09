#include "ast_node_types.cpp"

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling AST NODE Types Extraction");
static llvm::cl::opt<int> OurCMDOption("featuretype", llvm::cl::cat(ToolingSampleCategory));

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {

        std::string s = InFile;
//        llvm::errs() << "** Creating AST consumer for: " << split_path(s)[1];

        commandlineoption cmdoption = static_cast<commandlineoption>(OurCMDOption.getValue());
//        llvm::errs() << " with avg-depth option: " << cmdoption << "** \n";

        return std::unique_ptr<clang::ASTConsumer>(
                new FindNamedClassConsumer(&Compiler.getASTContext(), s, cmdoption));
    }
};


int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, ToolingSampleCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}





