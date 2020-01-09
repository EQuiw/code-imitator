#include "IncludeSort.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace clang::tooling;
using namespace llvm::cl;

OptionCategory MyToolCategory("include-sort options");
opt<std::string> SortIncludes("sort-includes",
                              Required,
                              desc("list the includes that should be sorted, separated by ##"),
                              value_desc("include list"),
                              cat(MyToolCategory));


int main(int argc, const char *argv[]) {
    CommonOptionsParser optionsParser(argc, argv, MyToolCategory);
    ClangTool tool(optionsParser.getCompilations(),
                   optionsParser.getSourcePathList());
    return tool.run(newFrontendActionFactory<IncludeSortAction>().get());
}
