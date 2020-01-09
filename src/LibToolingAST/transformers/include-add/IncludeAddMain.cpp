#include "IncludeAdd.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace clang::tooling;
using namespace llvm::cl;

OptionCategory MyToolCategory("include-add options");
list<std::string> AngledHeaderFiles(
    "angled_headers", ZeroOrMore,
    desc("The name of the files for which to add an angled include directive."),
    value_desc("header files"), cat(MyToolCategory));
list<std::string> QuotedHeaderFiles(
    "quoted_headers", ZeroOrMore,
    desc("The name of the files for which to add an quoted include directive."),
    value_desc("header files"), cat(MyToolCategory));

int main(int argc, const char *argv[]) {
  CommonOptionsParser optionsParser(argc, argv, MyToolCategory);
  ClangTool tool(optionsParser.getCompilations(),
                 optionsParser.getSourcePathList());

  return tool.run(newFrontendActionFactory<IncludeAddAction>().get());
}
