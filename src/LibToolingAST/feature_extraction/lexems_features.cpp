//
// Extracts lexems (part of lexical features), can serve as replacement for word unigrams
// Count on console: clang -Xclang -dump-tokens -fsyntax-only   FILE.CPP   2>&1 | grep "FILE.CPP" | wc -l
//                  --> (replace FILE.CPP)
//  In addition, we also add includes.
//

#include <sstream>
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/Support/CommandLine.h"

#include "Utils.h"
#include "Utils_Features.h"

using namespace llvm::cl;
using namespace clang;
using namespace clang::tooling;


static OptionCategory MyToolCategory("extract lexems");
const bool coloured = true; // similar to coloured bloom filters, if true, token's kind is appended

//#define MYDEBUG 0

/**
 * Class that lists the includes in addition to the lexem tokens
 */
class IncludePrinter : public PPCallbacks {

public:
    std::vector<std::string> &includes;

    explicit IncludePrinter(const CompilerInstance &CI, std::vector<std::string> &includes) :
            includes(includes), CI(CI) {}

    void InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok,
                            StringRef FileName, bool IsAngled,
                            CharSourceRange FilenameRange, const FileEntry *File,
                            StringRef SearchPath, StringRef RelativePath,
                            const Module *Imported) override {
        const auto &SM = CI.getSourceManager();

        if (!SM.isInMainFile(HashLoc)) {
            return;
        }

        std::stringstream strs;
        if(coloured)
            strs << "header__";

        if (IsAngled) {
            strs << "<" << FileName.str() << ">";
            includes.push_back(strs.str());
        } else {
            strs  << "\"" << FileName.str() << "\"";
            includes.push_back(strs.str());
        }

    }

private:
    const CompilerInstance &CI;
};


/**
 * Class that a) lists all lexems and b) also includes all header includes.
 */
class IncludeListAction : public PreprocessOnlyAction {

    std::unordered_map<std::string, int> map;
    std::string InFile;

    void ExecuteAction() override {
        const auto &CI = getCompilerInstance();
        const auto &SM = CI.getSourceManager();

        // we pass the includes vector to Printer, so that we can access it later..
        std::vector<std::string> includes;

        std::unique_ptr<IncludePrinter> Printer(new IncludePrinter(CI, includes));
        CI.getPreprocessor().addPPCallbacks(std::move(Printer));

        CI.getPreprocessor().EnterMainSourceFile();
        CI.getDiagnosticClient().BeginSourceFile(CI.getLangOpts(),
                                                 &CI.getPreprocessor());
        Token tok;
        do {
            CI.getPreprocessor().Lex(tok);
            if( CI.getDiagnostics().hasErrorOccurred())
                break;

            // mimic output from void Preprocessor::DumpToken with DumpFlags = True
//            CI.getPreprocessor().DumpToken(tok, true);

            if(tok.isNot(clang::tok::eof) && SM.isInMainFile(tok.getLocation())) {
                std::stringstream ss;
                if(coloured)
                    ss << tok::getTokenName(tok.getKind()) << "__";
                ss << CI.getPreprocessor().getSpelling(tok);
#ifdef MYDEBUG
                llvm::outs() << ss.str() << "\n";
#endif
                insertinhashmap(escapesymbols(ss.str()));
            }

        } while ( tok.isNot(clang::tok::eof));
        CI.getDiagnosticClient().EndSourceFile();
        InFile = SM.getFilename(tok.getLocation());

        for(const auto &s : includes){
            insertinhashmap(escapesymbols(s));
        }

        // call to parent..
        PreprocessOnlyAction::ExecuteAction();
    }

    void EndSourceFileAction() override {
        printhashmap<int>(map, InFile);
#ifdef MYDEBUG
        int stats = 0;
        for(auto const &ent1: map){
            stats += ent1.second;
        }
        llvm::outs() << "Number of tokens:" << stats << "\n";
#endif
    }


    void insertinhashmap(const std::string &str){
        if(map.find("\"" + str + "\"") != map.end()){
            // str is already in
            map["\"" + str + "\""] += 1;
        } else {
            map["\"" + str + "\""] = 1;
        }
    }

};

int main(int argc, const char *argv[]) {
    CommonOptionsParser optionsParser(argc, argv, MyToolCategory);
    ClangTool tool(optionsParser.getCompilations(),
                   optionsParser.getSourcePathList());

    return tool.run(newFrontendActionFactory<IncludeListAction>().get());
}