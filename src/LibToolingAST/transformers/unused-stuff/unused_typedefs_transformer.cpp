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

//#include "clang/AST/ASTConsumer.h"
//#include "clang/AST/AST.h"
//#include "clang/Frontend/ASTConsumers.h"
//#include "clang/Frontend/FrontendActions.h"
//#include "llvm/IR/Constants.h"


#include "../utils_transform.h"
#include "../../Utilities/Utils2.h"
#include "../include/SourceTextHelper.h"
#include "Utils_Declarations.h"
#include "../ControlDataFlow/DeclRefMapping/DeclRefMapping.h"
#include <unordered_map>

#include "../typedef-transform/typedef_collector.cpp"

using namespace clang;
using namespace llvm::cl;


static llvm::cl::OptionCategory MyOptionCategory("Remove all unused typedefs");
/* ****************** ************** **************** */




/**
 * Remove unused typedefs.
 * TODO -- template + typedefs are not handled or supported.
 * Some IDEs may show an error below for typedef_map, but the code should work.
 */
class UnusedTypedefsTransformer : public TypeDefCollector  {
public:

    explicit UnusedTypedefsTransformer(ASTContext &Context, Rewriter &OurRewriter)
            : TypeDefCollector(Context, OurRewriter), sm(Context.getSourceManager()) {
    }

    /* ****************** Collect Further Stuff **************** */

    /**
     * Get a map with key: typedef decl and value: a list where this typedef is used by other typedefs!
     * @return
     */
    std::unordered_map<TypedefNameDecl*, std::vector<TypedefNameDecl*>> get_collection(){
        // stores for each typedef decl a list where this typedef is used.
        std::unordered_map<TypedefNameDecl*, std::vector<TypedefNameDecl*>> typedef_map;

        for(auto tl : typedefnamedeclarations){
            std::vector<TypedefNameDecl*> typedef_vec;

            for(auto td : typedefnamedeclarations){
                if(tl != td){
                    std::vector<QualType> resolvs;
                    resolve_inner_types(td->getUnderlyingType(), resolvs);
                    for(auto s : resolvs) {
                        if (s.getAsString() == tl->getQualifiedNameAsString()) {
                            // td is used inside of tl
                            typedef_vec.push_back(td);
                        }
                    }
                }
            }

            typedef_map[tl] = typedef_vec;
        }

        return typedef_map;
    }

    /**
     * Get a map with key: typedef decl and value: a list where this typedef is used in source code (except typedefs).
     * @return
    */
    std::unordered_map<TypedefNameDecl*, std::vector<TypeLoc>> get_collection_codelocs(){
        std::unordered_map<TypedefNameDecl*, std::vector<TypeLoc>> typedef_map;

        // todo: we use the quick hack to compare rows, since we need a better way to get the decl for a typeloc.
        std::vector<unsigned> rows_withtypedefs;
        for(auto td : typedefnamedeclarations)
            rows_withtypedefs.push_back(getRowColumn(td->getLocStart(), sm, false).first);

        // iterate over each typedef-decl. and each typedef usage location.
        for(auto td : typedefnamedeclarations){
            for(auto tl : typelocswithtypedef){

                // check if same typedef at code location and check if code location is not a typedef.
                if(tl.getType().getAsString() == td->getQualifiedNameAsString()){
                  if(std::find(rows_withtypedefs.begin(), rows_withtypedefs.end(),
                               getRowColumn(tl.getLocStart(), sm, false).first) == rows_withtypedefs.end()){
                      typedef_map[td].push_back(tl);
                  }
                }
            }
        }

        return typedef_map;
    }

    /**
     * Now filter out unused typdefs recursively.
     * For instance,
     * typedef long long ll;
     * typedef std::vector<ll> vll;
     * may be used. Then if ll is used by vll, but vll is not used, so that vll and ll can be removed.
     * @param typedef_map
     * @param typedef_map_codeloc
     * @return a list of unused typedef declarations.
     */
    std::vector<TypedefNameDecl*> filter_out_unused_typedefs_recursively(
            std::unordered_map<TypedefNameDecl*, std::vector<TypedefNameDecl*>> &typedef_map,
            std::unordered_map<TypedefNameDecl*, std::vector<TypeLoc>> &typedef_map_codeloc){

        std::vector<TypedefNameDecl*> unused_typedefs;

        bool some_deleted;
        do {
            some_deleted = false;

            std::vector<TypedefNameDecl*> toerase;
            for (auto &tl_elem : typedef_map){ // clang may issue here a warning, but it works.
                TypedefNameDecl* tl = tl_elem.first;
                std::vector<TypedefNameDecl*> tl_vec = tl_elem.second;

                if (tl_vec.empty() && typedef_map_codeloc[tl].empty()){
                    // typedef has no usage, so we can delete it safely
                    unused_typedefs.push_back(tl);
                    some_deleted = true;
#ifdef MYDEBUG
                    llvm::errs() << "Detected unused typedef: " << tl->getQualifiedNameAsString() << "\n";
#endif

                    for (auto &tl_elem_inner : typedef_map){
                        if(tl_elem != tl_elem_inner){

                            std::vector<TypedefNameDecl*>* tl_vec_inner = &(tl_elem_inner.second);
                            (*tl_vec_inner).erase( remove((*tl_vec_inner).begin(), (*tl_vec_inner).end(), tl) , (*tl_vec_inner).end() );
                        }
                    }
                    toerase.push_back(tl);
                }
            }
            for(auto tl : toerase)
                typedef_map.erase(tl);

        } while (some_deleted);

        return unused_typedefs;
    }


    /* ****************** Remove Stuff **************** */

    void remove_unused_code() {

        // We iterate over typealiasdecl to find out if we have a template typedef, which we do not consider, yet.
        for(auto t : typealiasdeclarations){
            if(t->getDescribedAliasTemplate()){
                llvm::errs() << "Code 123: No transformations possible\n";
                return;
            }
        }

        // A. Collect unused typedefs by checking if type is used in source code
        auto typedef_codelocs = get_collection_codelocs();
        auto typedef_map = get_collection();
        auto unused_typedefs = filter_out_unused_typedefs_recursively(typedef_map, typedef_codelocs);

        if(unused_typedefs.empty()){
            llvm::errs() << "Code 124: Empty set\n";
            return;
        }

        // B. Remove them
        for(auto td : unused_typedefs)
            OurRewriter.RemoveText(getCharSourceRange(td, sm, Context.getLangOpts()));
    }

private:
//    ASTContext &Context;
    SourceManager &sm;
//    Rewriter &OurRewriter;

};

/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter) : Visitor(Context, OurRewriter) {
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        Visitor.remove_unused_code();
    }

private:
    UnusedTypedefsTransformer Visitor;
};


class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) override {

        OurRewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());

//        std::string s = InFile;
//        llvm::errs() << "** Creating AST consumer for: " << split_path(s)[1] << "\n";

        return std::unique_ptr<clang::ASTConsumer>(
                new MyASTConsumer(Compiler.getASTContext(), OurRewriter));
    }

    void EndSourceFileAction() override {
        // I. Now emit the rewritten buffer to stdout:
        {
            OurRewriter.getEditBuffer(OurRewriter.getSourceMgr().getMainFileID()).write(llvm::outs());
//            llvm::outs() << "\n";
        }
    }

private:
    Rewriter OurRewriter;
};


int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, MyOptionCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}