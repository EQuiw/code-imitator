#include <set>
#include <sstream>
#ifndef CLANG_LIBS
#define CLANG_LIBS
#include "llvm/Support/CommandLine.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#endif


#include "../utils_transform.h"
#include "../ASTFrontendActionTemplate.inl"
//#include "../ASTFrontendActionWithPrepTemplate.inl"
#include "../include/SourceTextHelper.h"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1
//#define OVERWRITE 1



// ** These are the command line options **
static llvm::cl::OptionCategory MyOptionCategory("Global Const Include Transformer");


//static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
llvm::cl::list<std::string> GlobalConstsOpt(
        "global_const", ZeroOrMore,
        desc("The global const includes that will be included.."),
        value_desc("global consts"), cat(MyOptionCategory));


//struct PreprocessingInfos {
//    std::vector<std::pair<std::string, SourceLocation>> headerincludes;
//};

class GlobalConstTransformer : public RecursiveASTVisitor<GlobalConstTransformer> {
public:

    explicit GlobalConstTransformer(ASTContext &Context, Rewriter &OurRewriter) :
            Context(Context),
            OurRewriter(OurRewriter),
            sm(Context.getSourceManager()) {}

    /**
    * Save all namespaces.
    */
    bool VisitUsingDirectiveDecl(UsingDirectiveDecl *ud) {
        if (sm.isWrittenInMainFile(ud->getLocStart())) {
            usedNamespaces.push_back(ud);
        }
        return true;
    }

    /**
    * Saves the first visited declaration, so that we know where we can insert global consts if necessary.
    * Moreover, it saves the names of all declarations so that if we create a new global const later, we can
    * easily check for name conflicts.
    * @param d
    * @return
    */
    bool VisitDecl(Decl *d) {
        if (sm.isWrittenInMainFile(d->getLocStart())) {
            // Save the name
            if (auto *nd = dyn_cast<NamedDecl>(d)) {
                this->alldeclarationnames.push_back(nd->getNameAsString());
                // Save the first visited declaration
                if (!this->first_decl)
                    this->first_decl = d;
            } else {
//               llvm::outs() << "No NamedDecl:" << d->getDeclKindName() << "\n";
            }
        }
        return true;
    }

    /**
     * Add global const(s)...
     */
    void addglobalconsts() {

        bool insertedatleastonce = false;
        for(auto &gcinclude : GlobalConstsOpt) {

            // I. Parse Input, I expect the format as given from DeclNamesList.cpp
            auto splits = split(gcinclude, "##");
            if(splits.size() != 2){
                llvm::errs() << "Wrong input:" << gcinclude << ";" << splits.size() << "\n";
                return;
            }

            auto globalconstname = splits[0];
            auto fullglobalconstdefinition = splits[1];

            // II. Check for name conflicts
            if(std::find(alldeclarationnames.begin(), alldeclarationnames.end(), globalconstname)
                != alldeclarationnames.end()){
                continue;
            }

            // III. Insert
            if(!usedNamespaces.empty()){
                auto offs = getOffsetWithSemicolon(Context, this->usedNamespaces.back());
                SourceLocation End(Lexer::getLocForEndOfToken(this->usedNamespaces.back()->getLocEnd(), 0,
                                                              sm, Context.getLangOpts()));
                OurRewriter.InsertTextAfter(End.getLocWithOffset(offs+1), fullglobalconstdefinition);
            } else if(this->first_decl) {
                OurRewriter.InsertTextBefore(this->first_decl->getLocStart(), fullglobalconstdefinition);
            } else {
                llvm::errs() << "No position found for new global const!\n";
                return;
            }


            insertedatleastonce = true;
        }

        if(!insertedatleastonce)
            llvm::errs() << "Code 123: No transformations possible\n";

    }


private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

//    PreprocessingInfos* prepinfos;
    Decl *first_decl = nullptr;
    std::vector<std::string> alldeclarationnames;
    std::vector<UsingDirectiveDecl*> usedNamespaces;

};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter)
            : Visitor(Context, OurRewriter) {}

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        Visitor.addglobalconsts();
    }

private:
    GlobalConstTransformer Visitor;
};


int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>());
}

