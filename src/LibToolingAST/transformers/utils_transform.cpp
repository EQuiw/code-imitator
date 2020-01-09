//
// Useful functions for common operations while transforming code.
// Look at utils_transform.h for documentation.
//

#include "utils_transform.h"


std::string getSourceText(ASTContext &Context, const Stmt *S, bool checkforsemicolon) {
    SourceLocation Start(S->getLocStart()), _End(S->getLocEnd());
    return __getSourceTextInternal(Context, Start, _End, checkforsemicolon);
}

std::string getSourceText(ASTContext &Context, const Decl *D, bool checkforsemicolon) {
    SourceLocation Start(D->getLocStart()), _End(D->getLocEnd());
    return __getSourceTextInternal(Context, Start, _End, checkforsemicolon);
}

std::string getSourceText(ASTContext &Context, const TypeLoc T, bool checkforsemicolon) {
    SourceLocation Start(T.getLocStart()), _End(T.getLocEnd());
    return __getSourceTextInternal(Context, Start, _End, checkforsemicolon);
}

std::string getSourceText(ASTContext &Context, SourceLocation Start, SourceLocation _End) {
    return __getSourceTextInternal(Context, Start, _End, false);
}


std::string __getSourceTextInternal(ASTContext &Context, SourceLocation Start, SourceLocation _End, bool checkforsemicolon) {
    SourceManager &SM = Context.getSourceManager();

//    Consider special case with Macros
//    https://stackoverflow.com/questions/24062989/clang-fails-replacing-a-statement-if-it-contains-a-macro
    if( Start.isMacroID() )
        Start = SM.getFileLoc(Start);

    if (_End.isMacroID())
        _End = SM.getFileLoc(_End);

    SourceLocation End(Lexer::getLocForEndOfToken(_End, 0, SM, Context.getLangOpts()));

    unsigned int offs = 0;
    if(checkforsemicolon)
        offs = Lexer::MeasureTokenLength(_End, SM, Context.getLangOpts());

    // Some debugging info before sending the exception
    if(SM.getCharacterData(End.getLocWithOffset(offs)) - SM.getCharacterData(Start) < 0)
        llvm::errs() << "getSourceText with negative char range. Caused by Macro? \n";

    return std::string(SM.getCharacterData(Start),
                       SM.getCharacterData(End.getLocWithOffset(offs)) - SM.getCharacterData(Start));
}




int getOffsetWithSemicolon(ASTContext &Context, const Stmt *s) {
    SourceManager &SM = Context.getSourceManager();

    SourceLocation End(Lexer::getLocForEndOfToken(s->getLocEnd(), 0, SM, Context.getLangOpts()));
    unsigned int offs = Lexer::MeasureTokenLength(s->getLocEnd(), SM, Context.getLangOpts());

    // Now try increasing offsets as long as the last char is ;
    for(unsigned of = 0; of <= offs; of++){
        std::string t = getSourceText(Context, s->getLocStart(), End.getLocWithOffset(of));
        if(t.back() == ';')
            return of;
    }

    llvm::errs() << "No semicolon found in getOffsetWithSemicolon for:" << getSourceText(Context, s, false) << "\n";
    return -1;
}

int getOffsetWithSemicolon(ASTContext &Context, const Decl *d) {
    SourceManager &SM = Context.getSourceManager();

    SourceLocation End(Lexer::getLocForEndOfToken(d->getLocEnd(), 0, SM, Context.getLangOpts()));
    unsigned int offs = Lexer::MeasureTokenLength(d->getLocEnd(), SM, Context.getLangOpts());

    // Now try increasing offsets as long as the last char is ;
    for(unsigned of = 0; of <= (offs); of++){
        std::string t = getSourceText(Context, d->getLocStart(), End.getLocWithOffset(of));
        if(t.back() == ';')
            return of;
    }

    llvm::errs() << "No semicolon found in getOffsetWithSemicolon for:" << getSourceText(Context, d, false) << "\n";
    return -1;
}

SourceRange getSourceRangeWithSemicolon(ASTContext &Context, const Stmt *s) {
    SourceManager &SM = Context.getSourceManager();
    SourceLocation End(Lexer::getLocForEndOfToken(s->getLocEnd(), 0, SM, Context.getLangOpts()));
    int offs = getOffsetWithSemicolon(Context, s);

    SourceRange sr(s->getLocStart(), End.getLocWithOffset(offs));
    return sr;
}

SourceRange getSourceRangeWithSemicolon(ASTContext &Context, const Decl *s) {
    SourceManager &SM = Context.getSourceManager();
    SourceLocation End(Lexer::getLocForEndOfToken(s->getLocEnd(), 0, SM, Context.getLangOpts()));
    int offs = getOffsetWithSemicolon(Context, s);

    SourceRange sr(s->getLocStart(), End.getLocWithOffset(offs));
    return sr;
}

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

std::string trim(const std::string& str, std::string trimcharacter)
{
    const auto strBegin = str.find_first_not_of(trimcharacter);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(trimcharacter);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string remove_last_whitespace(std::string s){
    s.resize(s.find_last_not_of(" ")+1);
    return s;
}


std::vector<std::string> split(const std::string& input, const std::string& regex) {
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
    return {first, last};
}


std::vector<std::string> getMatches(std::string input, const std::string &regex){
    // Show matches
    std::regex simpleplholder(regex);
    std::smatch res;
    std::vector<std::string> output;

    while (std::regex_search(input, res, simpleplholder)) {
//            llvm::outs() << "Match:" << res[0] << "\n";
        output.push_back(res[0].str());
        input = res.suffix();
    }
    return output;
}


std::string getUniqueFunctionNameAsString(const FunctionDecl* f) {
    std::stringstream sstream;
    sstream << "" << f->getQualifiedNameAsString();
    for(auto farg : f->parameters()){
        sstream << "_" << ReplaceString(farg->getType().getAsString(), " ", "") << "_" << farg->getQualifiedNameAsString();
    }
    return sstream.str();
}

std::pair<unsigned, unsigned> getRowColumn(SourceLocation sl, SourceManager &sm, bool verbose) {
    FullSourceLoc fullLoc(sl, sm);
    std::pair<unsigned, unsigned> returnval;
    returnval.first = fullLoc.getSpellingLineNumber();
    returnval.second = fullLoc.getColumnNumber();
    if(verbose)
        llvm::outs() << "(r:" << returnval.first << ",c:" << returnval.second << ")\n";
    return returnval;
}

bool getParentOfWholeCommandLine(ast_type_traits::DynTypedNode dtn,
                                 ast_type_traits::DynTypedNode &targetdtn,
                                 const unsigned targetrow,
                                 ASTContext &Context,
                                 SourceManager &sm){
    FullSourceLoc fullLoc(dtn.getSourceRange().getBegin(), sm);
    if(fullLoc.getSpellingLineNumber() < targetrow)
        return true;

    for(auto par : Context.getParents(dtn)){
        if(getParentOfWholeCommandLine(par, dtn, targetrow, Context, sm)){
            targetdtn = dtn;
            return true;
        }
    }
    return false;
}



void insertHeaderAtBeginningOfSourceFile(std::string headerstr,
                             std::vector<std::pair<std::string, SourceLocation>>* headerincludes,
                             Decl* firstDeclInSrcFile,
                             SourceManager &sm,
                             Rewriter &OurRewriter
){

    // header file already defined, nothing to do
    for(auto cs : *headerincludes){
        if(cs.first.find(headerstr)!=std::string::npos){
            return;
        }
    }

    // consider only header files that were defined in current src file, get the first in this file
    SourceLocation finalloc;
    bool fromheaderincl = false;
    for(auto cs: *headerincludes){
        if (sm.isWrittenInMainFile(cs.second)) {
            finalloc = cs.second;
            fromheaderincl = true;
            break;
        }
    }
    // if no header files were defined, take the first defined declaration where we insert our new include
    if(!fromheaderincl){
        finalloc = firstDeclInSrcFile->getLocStart();
    }

    (*headerincludes).emplace_back(headerstr, finalloc);
    headerstr = "#include <" + headerstr + ">\n";
    OurRewriter.InsertTextBefore(finalloc, headerstr);
}


bool namespace_defined(std::string targetns, std::vector<UsingDirectiveDecl*> namespaces){
    for(auto ud : namespaces){
        if(ud->getNominatedNamespace()->getQualifiedNameAsString() == targetns)
            return true;
    }
    return false;
}