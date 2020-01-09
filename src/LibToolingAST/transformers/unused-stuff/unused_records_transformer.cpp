//
// Removes unused records (structs, classes).
//

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


static llvm::cl::OptionCategory MyOptionCategory("Remove all unused records");
/* ****************** ************** **************** */




/**
 * Remove unused records.
 */
class UnusedRecordsTransformer : public RecursiveASTVisitor<UnusedRecordsTransformer> {
public:

    explicit UnusedRecordsTransformer(ASTContext &Context, Rewriter &OurRewriter) : Context(Context),
                                                                                    OurRewriter(OurRewriter),
                                                                                    sm(Context.getSourceManager()) {
    }

    /* ****************** Collect Further Stuff **************** */

    bool VisitRecordDecl(RecordDecl *d){
        auto srcloc = d->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            record_decls.push_back(d);
        }
        return true;
    }

    bool VisitTypeLoc(TypeLoc x) {
        auto srcloc = x.getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
            type_locs.push_back(x);
        }
        return true;
    }

    /* ****************** Remove Stuff **************** */

    void remove_unused_code() {

        // A. Identify what Record Decls are not used.
        std::vector<const RecordDecl*> recorddecls_toremove;

        for(auto recdecl : record_decls){
            bool isused = false;

            for(auto typloc : type_locs){
                // is this a reference to a record decl?

                std::vector<QualType> incl_types;
                // we need to resolve an elaborated type if e.g. var. a is directly defined with struct def., struct A {} a;
                resolve_inner_types(typloc.getType(), incl_types);
                for(auto r : incl_types){

                    // Maybe it is a pointer to a struct, so resolve it before
                    while (auto rp = dyn_cast<PointerType>(r)){
                        r = r->getPointeeType();
                        if(isa<RecordType>(r)){  // rp->getPointeeCXXRecordDecl()
                            break;
                        }
                    }

                    // now check if record type
                    if(auto rt = dyn_cast<RecordType>(r)){
                        if(rt->getDecl()->getDefinition()->getQualifiedNameAsString()
                           == recdecl->getQualifiedNameAsString()){
                           // Match. Current var decl has recdecl as type.
                            isused = true;
                            break;
                        }
                    }
                }
            }

            // Mark to remove
            if(!isused)
                recorddecls_toremove.push_back(recdecl);
        }

        if(recorddecls_toremove.empty()){
            llvm::errs() << "Code 124: Empty set\n";
            return;
        }

        // B. Remove all of them
        for(auto recdecl : recorddecls_toremove){
            OurRewriter.RemoveText(getCharSourceRange(recdecl, sm, Context.getLangOpts()));

            // Actually, we need to iterate over all member functions that have only a declaration within the record,
            // and their definition is outside.
            
        }

    }

private:
    ASTContext &Context;
    Rewriter &OurRewriter;
    SourceManager &sm;

    std::vector<const RecordDecl*> record_decls;
    std::vector<TypeLoc> type_locs;

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
    UnusedRecordsTransformer Visitor;
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