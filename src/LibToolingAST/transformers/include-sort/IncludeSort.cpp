#include <clang/Tooling/Refactoring.h>
#include "IncludeSort.h"


/// Preprocessor callback that is called each time an include is encountered.
///
/// Collects all includes of a file.
void IncludeCollector::InclusionDirective(
        SourceLocation HashLoc, const Token &IncludeTok, StringRef FileName,
        bool IsAngled, CharSourceRange FilenameRange, const FileEntry *File,
        StringRef SearchPath, StringRef RelativePath, const Module *Imported) {

    const auto &SM = CI.getSourceManager();

    // Skip all includes not contained in the main file, i.e., includes found in
    // included header files.
    if (!SM.isInMainFile(HashLoc)) {
        return;
    }

    // Check filename. Includes added via `-include` pass the `isInMainFile` check
    // but have filename "<built-in>". We have to skip those includes because they
    // are part of the source code.
    if (HashLoc.isFileID()) {
        string fname(SM.getPresumedLoc(HashLoc).getFilename());
        if (fname == "<built-in>") {
            return;
        }
    }

    // get full source range from first # char to end of include directive
    SourceRange fullincludeloc = SourceRange(HashLoc, FilenameRange.getAsRange().getEnd());
    // Remember all includes and the corresponding source location.
    Includes->push_back(tuple<StringRef, SourceRange, bool>(FileName, fullincludeloc, IsAngled));
}


void IncludeSortAction::ExecuteAction() {
    const auto &CI = getCompilerInstance();
    auto &SM = CI.getSourceManager();
    const auto FID = SM.getMainFileID();

    // rewriter used to add an include
    Rewriter Rewrite(SM, CI.getLangOpts());

    // register our callback for include directives
    unique_ptr<IncludeCollector> IncAdd(new IncludeCollector(CI, &Includes));
    CI.getPreprocessor().addPPCallbacks(move(IncAdd));

    PreprocessOnlyAction::ExecuteAction();

    // Iterate over all include directives that were found in the provided source
    // file. Iterate in reverse order such that the location of the first include
    // is used as an anchor to add the new include directive (we add the new
    // incude just before the first include in the file).
    //
    // Do not add a new include directive for a file that is already included.
    SourceLocation Loc;
    Loc = CI.getSourceManager().getLocForStartOfFile(FID);

    // Tokenize input SortIncludeList by splitting at ##
    std::vector<std::string> todo_list;
    todo_list = split(SortIncludes, "##");

    // First, we collect all locations that we will remove, and not remove
    std::vector<std::tuple<llvm::StringRef, SourceRange, bool>> moved_includes_neworder;
    for(auto &incl : todo_list) {
        for (auto Inc : Includes) {
            if( (std::get<0>(Inc)).str() == incl){
                moved_includes_neworder.emplace_back(Inc);
            }
        }
    }

    if(moved_includes_neworder.empty()){
        llvm::errs() << "Code 124: Empty set\n";
        return;
    }

    std::vector<std::tuple<llvm::StringRef, SourceRange, bool>> moved_includes_oldorder;
    std::stack<std::tuple<llvm::StringRef, SourceRange, bool>> unMoved_includes;
    for (auto Inc : Includes) {
        if(std::find(todo_list.begin(), todo_list.end(), std::get<0>(Inc).str()) != todo_list.end()){
            moved_includes_oldorder.push_back(Inc);
        } else {
            unMoved_includes.push(Inc);
        }
    }

    // Now we iterate over each location where we want to move an include, and check if we can use
    // an un-moved include so that we have no empty rows between includes

    for(auto &incl : moved_includes_oldorder){
        auto row_toreplace = getRowColumn(std::get<1>(incl).getBegin(), SM).first;
        unsigned int row_replace = 0;
        if (!unMoved_includes.empty())
            row_replace = getRowColumn(std::get<1>(unMoved_includes.top()).getBegin(), SM).first;

        if(!unMoved_includes.empty() && row_replace > row_toreplace){
            Rewrite.ReplaceText(std::get<1>(incl), std::get<1>(unMoved_includes.top()));
            Rewrite.RemoveText(std::get<1>(unMoved_includes.top()));
            unMoved_includes.pop();
        } else {
            Rewrite.RemoveText(std::get<1>(incl));
        }
    }


    // II. Add removed includes at the beginning in the new order
    stringstream sstream;
    for (auto target : moved_includes_neworder){
        sstream << "#include" << " ";
        bool isangle = std::get<2>(target);
        if(isangle){
            sstream << "<" << std::get<0>(target).str() << ">";
        } else {
            sstream << "\"" << std::get<0>(target).str() << "\"";
        }
        sstream << "\n";
    }
    Rewrite.InsertTextBefore(Loc, sstream.str());

    // write modified code to stdout
    Rewrite.getEditBuffer(FID).write(llvm::outs());
}