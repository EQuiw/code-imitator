#ifndef CLANG_AST_LIBS
#define CLANG_AST_LIBS
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

#include "clang/AST/AST.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/IR/Constants.h"
#endif

#include <iostream>
#include "../Utilities/Utils.h"

using namespace clang;
using namespace clang::tooling;
using namespace clang::driver;

/**
 * Enum to represent the different choices that you can have with -featuretype
 * 0 - onlytypes just extract the occurence count of each AST node type.
 * 1 - avg_depth extracts its average depth.
 * 2 - max-depth gets the maximum depth over all AST node types.
 */
enum commandlineoption {onlytypes=0, avg_depth=1, max_depth=2};


class GetNodeTypes : public RecursiveASTVisitor<GetNodeTypes>{
public:

    std::string InFile;
    std::unordered_map<std::string, int> map;
    std::unordered_map<std::string, float> map_avgdepth;
    int max_depth;

    explicit GetNodeTypes(ASTContext *Context, std::string InFile, bool get_avg_depth)
            : InFile(InFile), Context(Context),
              sm(Context->getSourceManager()), get_avg_depth(get_avg_depth) {
    }


    bool VisitStmt(Stmt *s) {
        // Check origin of stmt and if in main file: get kind
        auto srcloc = s->getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){
//            llvm::outs() << "StmtClass:" << s->getStmtClassName() << "\n";

            // 1. Save current node
            insertinhashmap(s->getStmtClassName());
            // 2. Get its depth
            int currentavgdepth = -1;
            if(this->get_avg_depth) {
                const auto &parents = Context->getParents(*s);
                currentavgdepth = getdepthfornode(parents, this->Context, 0, InFile);
                insertindepthhashmap(map, map_avgdepth, s->getStmtClassName(), currentavgdepth);
                // Save the maximum depth by the way
                this->max_depth = (currentavgdepth > this->max_depth) ? currentavgdepth : this->max_depth;
            }
        }
        return true;
    }


    bool VisitDecl(Decl *d) {
        bool inmainfile = Context->getSourceManager().isInMainFile(d->getLocation());
        if(inmainfile){

            // 1. Save current node
            insertinhashmap(d->getDeclKindName());
            // 2. Get its depth
            int currentavgdepth = -1;
            if(this->get_avg_depth) {
                const auto &parents = Context->getParents(*d);
                currentavgdepth = getdepthfornode(parents, this->Context, 0, InFile);
                insertindepthhashmap(map, map_avgdepth, d->getDeclKindName(), currentavgdepth);
                // Save the maximum depth by the way
                this->max_depth = (currentavgdepth > this->max_depth) ? currentavgdepth : this->max_depth;
            }
        }
        return true;
    }


    bool VisitTypeLoc(TypeLoc x) {
        auto srcloc = x.getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){
//            llvm::outs() << ">>>Type:" << x.getType().getAsString() << "\n";

            // 1. Save current node
            insertinhashmap("Type");
            // 2. Get its depth
            int currentavgdepth = -1;
            if(this->get_avg_depth) {
                const auto &parents = Context->getParents(x);
                currentavgdepth = getdepthfornode(parents, this->Context, 0, InFile);
                insertindepthhashmap(map, map_avgdepth, "Type", currentavgdepth);
                // Save the maximum depth by the way
                this->max_depth = (currentavgdepth > this->max_depth) ? currentavgdepth : this->max_depth;
            }

        }
        return true;
    }

    void printmaxdepth(){
        llvm::outs() << extract_name(split_path(this->InFile)[1]) << " "
                     << split_path(this->InFile)[1] << " " << this->max_depth << "\n";
    }

private:
    ASTContext *Context;
    SourceManager &sm;
//    CompilerInstance &ci;
    bool get_avg_depth;

    void insertinhashmap(const std::string &str){
        if(map.find("\"" + str + "\"") != map.end()){
            // str is already in
            map["\"" + str + "\""] += 1;
        } else {
            map["\"" + str + "\""] = 1;
        }
    }

};


/*****************************************************************/

//class FindNamedClassConsumer : public clang::ASTConsumer {
//public:
//    explicit FindNamedClassConsumer(ASTContext *Context, std::string InFile, commandlineoption cmdoption)
//            : Visitor(Context, InFile, static_cast<bool>(cmdoption)), cmdoption(cmdoption) {}
//
//    void HandleTranslationUnit(clang::ASTContext &Context) override {
////      Context.getTranslationUnitDecl()->dump();
//
//        // 1. Traverse through tree and extract features
//        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
//
//        // 2. Print features to stdout
//        switch(cmdoption){
//            case onlytypes: printhashmap<int>(Visitor.map, Visitor.InFile); break;
//            case avg_depth: printhashmap<float>(Visitor.map_avgdepth, Visitor.InFile); break;
//            case max_depth: Visitor.printmaxdepth(); break;
//        }
//    }
//protected:
//    GetNodeTypes Visitor;
//    commandlineoption cmdoption;
//};