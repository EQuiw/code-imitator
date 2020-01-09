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

class GetNodeBigrams : public RecursiveASTVisitor<GetNodeBigrams> {
public:

    std::string InFile;
    std::unordered_map<std::string, int> map;

    explicit GetNodeBigrams(ASTContext *Context, std::string InFile)
            :  InFile(InFile), Context(Context), sm(Context->getSourceManager()) {
    }


    bool VisitStmt(Stmt *s) {
        // Check origin of stmt and if in main file: get its kind and the parent's kind
        auto srcloc = s->getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){
//            llvm::outs() << "StmtClass:" << s->getStmtClassName() << "\n";

            const auto& parents = Context->getParents(*s);

            // Include this node together with its parent into hashmap as bigram
            return createbigramwithparent(s->getStmtClassName(), parents);
        }
        return true;
    }


    bool VisitDecl(Decl *d) {
        bool inmainfile = Context->getSourceManager().isInMainFile(d->getLocation());
        if(inmainfile){
//            llvm::outs() << "DeclClass:" << d->getDeclKindName() << "\n";
//            insertinhashmap(d->getDeclKindName());

            const auto& parents = Context->getParents(*d);

            // Include this node together with its parent into hashmap as bigram
            return createbigramwithparent(d->getDeclKindName(), parents);

        }
        return true;
    }


    bool VisitTypeLoc(TypeLoc x) {
        auto srcloc = x.getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){
//            llvm::outs() << ">>>Type:" << x.getType().getAsString() << "\n";
            const auto& parents = Context->getParents(x);

            // Include this node together with its parent into hashmap as bigram
            return createbigramwithparent("Type", parents);
        }
        return true;
    }

private:
    ASTContext *Context;
    SourceManager &sm;
//    CompilerInstance &ci;

    /**
     * This function is a helper function to deal with bigrams, since
     * the following code is relevant for Stmt, Decl and TypeLoc's.
     * So, first it checks how many parent nodes are there.
     * If too many, we stop, since we have not considered this case, yet.
     * If no parent is there, we continue, but do not extract this node as bigram.
     * Otherwise, we check the type of the parent node and save the bigram in the hashmap,
     * and everyone is happy.
     * @param child - the child node's node type
     * @param parents   - the parent
     * @return true if everything is fine, false if something bad happened.
     */
    bool createbigramwithparent(const std::string &child,
                                const ASTContext::DynTypedNodeList &parents){

        // A. Check whether empty parent
        if ( parents.empty() ) {
//            llvm::errs() << "No parent found.. \n";
            return true;
        } else {
            // B. Parent:'NodeT' can be one of Decl, Stmt, Type, TypeLoc,
            // NestedNameSpecifier or NestedNameSpecifierLoc.
            for(auto par : parents){
                const auto *ST = par.get<Stmt>();
                const auto *DC = par.get<Decl>();
                const auto *TL = par.get<Type>();
                const auto *TLloc = par.get<TypeLoc>();
                const auto *NN = par.get<NestedNameSpecifier>();
                const auto *NNloc = par.get<NestedNameSpecifierLoc>();

                // B.i: Check if its a statement
                std::string bigram;
                if (ST) {
                    bigram = createbigram(ST->getStmtClassName(), child);
                }
                // B.ii: Check if its a declaration
                else if (DC) {
                    bigram = createbigram(DC->getDeclKindName(), child);
                }
                // B.iii: Check if its a type
                else if (TL || TLloc) {
                    bigram = createbigram("Type", child);
                }
                // B.iv: Check if its a nested name ..
                else if (NN || NNloc) {
//                    bigram = createbigram("NestedName", child);
//                    llvm::errs() << "NestedName occured...look deeper into it,"<< child << " file:" <<
//                    InFile << "\n";
                } else{
                    llvm::errs() << "Bigram unknown parent class, "<< child << " file:" << InFile << "\n";
                    return false;
                }
                if(!bigram.empty())
                    insertinhashmap(bigram);
            }

            return true;
        }
    }

    /**
     * Creates a bigram from two given strings
     * @param a 1st string
     * @param b 2nd string
     * @return "[ string1, string 2]"
     */
    std::string createbigram(const std::string &a, const std::string &b) {
        return std::string("[\"") +
               a +
               std::string("\", \"") +
               b +
               std::string("\"]");
    }

    /**
     * Insert the string into the hashmap.
     * @param str the element to be inserted.
     */
    void insertinhashmap(const std::string &str){
        if(map.find(str) != map.end()){
            // str is already in
            map[str] += 1;
        } else {
            map[str] = 1;
        }
    }
};


/*****************************************************************/

//class FindNamedClassConsumer : public clang::ASTConsumer {
//public:
//    explicit FindNamedClassConsumer(ASTContext *Context, std::string InFile)
//            : Visitor(Context, InFile) {}
//
//    virtual void HandleTranslationUnit(clang::ASTContext &Context) {
//        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
//        printhashmap(Visitor.map, Visitor.InFile);
////      Context.getTranslationUnitDecl()->dump();
//    }
//protected:
//    GetNodeBigrams Visitor;
//};