#include "IncludeAdd.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include <sstream>

using namespace std;
using namespace clang;

// extern opt<std::string> HeaderFile;
extern llvm::cl::list<std::string> AngledHeaderFiles;
extern llvm::cl::list<std::string> QuotedHeaderFiles;

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

  // Remember all includes and the corresponding source location.
  Includes->push_back(pair<StringRef, SourceLocation>(FileName, HashLoc));
}

void IncludeAddAction::ExecuteAction() {
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

  vector<string> FilteredAngledHeaderFiles;
  for (auto &HeaderFile : AngledHeaderFiles) {
    bool isIncluded = false;
    for (auto Inc = Includes.rbegin(); Inc != Includes.rend(); ++Inc) {
      // Don't add an already included header file
      if (HeaderFile == Inc->first.str()) {
        isIncluded = true;
      }
      Loc = Inc->second;
    }
    if (!isIncluded)
      FilteredAngledHeaderFiles.push_back(HeaderFile);
  }

  vector<string> FilteredQuotedHeaderFiles;
  for (auto &HeaderFile : QuotedHeaderFiles) {
    bool isIncluded = false;
    for (auto Inc = Includes.rbegin(); Inc != Includes.rend(); ++Inc) {
      // Don't add an already included header file
      if (HeaderFile == Inc->first.str()) {
        isIncluded = true;
      }
      Loc = Inc->second;
    }
    if (!isIncluded)
      FilteredQuotedHeaderFiles.push_back(HeaderFile);
  }

  if (FilteredAngledHeaderFiles.empty() && FilteredQuotedHeaderFiles.empty()) {
    llvm::errs() << "Code 123: No transformations possible\n";
    return;
  }

  // Create the code for the new include directive and use the rewriter to add
  // it.
  stringstream sstream;
  for (auto &Target : FilteredAngledHeaderFiles)
    sstream << "#include"
            << " "
            << "<" << Target << ">"
            << "\n";
  for (auto &Target : FilteredQuotedHeaderFiles)
    sstream << "#include"
            << " "
            << "\"" << Target << "\""
            << "\n";

  // add empty line after the added include if it is the only include in the
  // source file.
  if (Includes.empty())
    sstream << "\n";

  // Rewrite file and write modified file to stdout
  Rewrite.InsertTextBefore(Loc, sstream.str());
  Rewrite.getEditBuffer(FID).write(llvm::outs());
}
