#include "InterfaceFileRewriter.h"


InterfaceFileRewriter::InterfaceFileRewriter(ASTContext &Context, Rewriter &OurRewriter, ControlFlowGraphWithDataFlow* cfggraph,
                                   bool stdoutmode)
        : Context(Context), OurRewriter(OurRewriter), sm(Context.getSourceManager()), cfggraph(cfggraph){

    if(stdoutmode){
        commonnameproposals = {"fout", "ofs", "out", "outfile", "outstream"};
        streamarrows = "<<";
    } else {
        commonnameproposals = {"fin",  "ifs", "infile", "instream"};
        streamarrows = ">>";
    }

};


bool InterfaceFileRewriter::transformCoutToOfIfstream(std::vector<const Expr*> interface_expressions,
                                                    std::vector<std::string> alldeclarationnames,
                                                    std::vector<UsingDirectiveDecl*> usedNamespaces,
                                                    Decl* firstDeclInSrcFile,
                                                    std::string stream_type
){


    // I. Collect all cout expressions
    std::vector<const DeclRefExpr*> cout_usages;

    for(auto ex : interface_expressions) {

        // I.a Convert and check data type
        const auto e = dyn_cast<CallExpr>(ex);
        if (e == nullptr) {
            llvm::errs() << "transformCoutToIOfstream. unvalid type as input\n";
            return false;
        }

        // I.b Each CXXOperatorCallExpr object corresponds to a << expression. Get all under current call expr in AST.
        std::vector<const CXXOperatorCallExpr *> cxxops;
        try {
            cxxops = get_cxxopcallexprs(e, &sm, streamarrows);
        } catch (CodeTransformationException &ex) {
            return false;
        }

        // I.c collect them all
        auto coutOrCinExpr = cxxops[0]->getArg(0);
        if(const auto c = dyn_cast<DeclRefExpr>(coutOrCinExpr)){
            cout_usages.push_back(c);
        } else {
            llvm::errs() << "Cout/Cin expr is not a DeclRefExpr. Wrong assumption.\n";
            return false;
        }
    }

    // II. Create ofstream/ifstream object and rename all cout/cin to ofstream/ifstream variable

    // II.a Create unique name, try various names and check if they already exist, if so, try it with a random suffix.
    std::string varnameofstream;

    for(const auto &proposal : commonnameproposals){
        if(std::find(alldeclarationnames.begin(), alldeclarationnames.end(), proposal) == alldeclarationnames.end()){
            varnameofstream = proposal;
            break;
        }
    }
    if(varnameofstream.empty()){
        varnameofstream += commonnameproposals[0] + RenamingGuide::getRandomStringWith(5);
    }
    this->newvariablename = varnameofstream;

    // II.b get position, definition should be global
    std::stringstream defintion_oi_fstream;
    defintion_oi_fstream << "" << stream_type << " " << varnameofstream << ";\n";

    if(!usedNamespaces.empty()){
//            auto sl = getCharSourceRange(this->usedNamespaces.back(), sm, Context.getLangOpts());
        auto offs = getOffsetWithSemicolon(Context, usedNamespaces.back());
        SourceLocation sl(Lexer::getLocForEndOfToken(usedNamespaces.back()->getLocEnd(), 0,
                                                     sm, Context.getLangOpts()));
        OurRewriter.InsertTextAfter(sl.getLocWithOffset(offs+1), defintion_oi_fstream.str());

    } else if(firstDeclInSrcFile){
        OurRewriter.InsertTextBefore(firstDeclInSrcFile->getLocStart(), defintion_oi_fstream.str());

    } else {
        // TODO actually we should also try headers...
        llvm::errs() << "Error: Could not find a position for new ofstream defintiion.\n";
        return false;
    }

    // II.c Add the file that will be opened to main
    try{
        const CompoundStmt* firstStmtOfMain =
                ControlDataFlowGraphQueryHandler::queryBodyOfMainFunction(cfggraph);

        OurRewriter.InsertTextAfter(firstStmtOfMain->getLBracLoc().getLocWithOffset(1),
                                    varnameofstream + ".open(\"replace-me.out\");\n");

    } catch(CFGException& ex) {
        llvm::errs() << "Could not find first stmt of main fct\n";
        return false;
    }

    // II.d rewrite all cout occurences.
    for(auto coutexpr : cout_usages)
        OurRewriter.ReplaceText(coutexpr->getSourceRange(), varnameofstream);


    return true;
}
