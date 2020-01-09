//
// ast_node_bigram, ast_node_types, code_in_ast_leaves, lexical_features in one call.
// saves parsing time to create AST
//

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

#include "Utils.h"

#include "ast_node_bigram.cpp"
#include "ast_node_types.cpp"
#include "code_in_ast_leaves.cpp"
#include "lexical_features.cpp"

using namespace clang;
using namespace clang::tooling;
using namespace clang::driver;
using namespace llvm::cl;

static llvm::cl::OptionCategory FeatureExtractionCategory("Tooling extract-all-features");
static llvm::cl::opt<bool> enablebigramsOpt("ast_node_bigram", desc("enable Bigram Feature Extraction"),
                                            llvm::cl::cat(FeatureExtractionCategory));
static llvm::cl::opt<bool> nodetypesOnlyTypesOpt("ast_node_types", desc("enable Only Types AST Types Feature Extraction"),
                                            llvm::cl::cat(FeatureExtractionCategory));
static llvm::cl::opt<bool> nodetypesAvgDepthOpt("ast_node_types_avg_dep", desc("enable Avg Depth AST Types Feature Extraction"),
                                                 llvm::cl::cat(FeatureExtractionCategory));
static llvm::cl::opt<bool> nodetypesMaxDepthOpt("max_depth_ast_node", desc("enable Max Depth AST Types Feature Extraction"),
                                                 llvm::cl::cat(FeatureExtractionCategory));
static llvm::cl::opt<bool> codeinastleavesOpt("code_in_ast_leaves", desc("enable Code in AST Leaves Feature Extraction"),
                                                llvm::cl::cat(FeatureExtractionCategory));
static llvm::cl::opt<bool> codeinastleavesAvgDepthOpt("code_in_ast_leaves_avg_dep",
                                                      desc("enable Avg Depth Code in AST Leaves Feature Extraction"),
                                                llvm::cl::cat(FeatureExtractionCategory));
static llvm::cl::opt<bool> lexicalfeaturesOpt("lexical_features", desc("enable Lexical Features Feature Extraction"),
                                              llvm::cl::cat(FeatureExtractionCategory));


// ****************************** Classes to set up AST Visiting ******************************** //

/**
 * We start for each feature class such as Bigrams, Code-in-AST-leaves a separate AST Visitor
 * that outputs the features.
 * You have to specify the feature classes that should be extracted via command line arguments.
 * For instance, to start bigram extraction only, call (adapt paths!)
 * ```
 * ./feature_extraction_single file.cpp -ast_node_bigram=True -- -std=c++11
 *      -I/REPLACE_ME_BY_RIGHT_PATH/clang+llvm-5.0.0-linux-x86_64-ubuntu16.04/lib/clang/5.0.0/include/
 * ```
 */
class FindNamedClassConsumer : public clang::ASTConsumer {
public:
    explicit FindNamedClassConsumer(ASTContext *Context, std::string InFile) :
        nodebigrams(GetNodeBigrams(Context, InFile)),
        nodetypes_onlytypes(GetNodeTypes(Context, InFile, false)),
        nodetypes_depth(GetNodeTypes(Context, InFile, true)),
        codeinastleaves(CodeInASTLeaves(Context, InFile, false)),
        codeinastleaves_avgdepth(CodeInASTLeaves(Context, InFile, true)),
        lexicalfeatures(GetLexicalFeatures(Context, InFile))
        {
        }

    virtual void HandleTranslationUnit(clang::ASTContext &Context) {

        // I. Bigrams
        bool enablebigrams = enablebigramsOpt.getValue();
        if(enablebigrams){
            nodebigrams.TraverseDecl(Context.getTranslationUnitDecl());
            llvm::outs() << "ast_node_bigram.dat ::--::";
            printhashmap(nodebigrams.map, nodebigrams.InFile);
        }

        // II. AST Node Types
        if(nodetypesOnlyTypesOpt.getValue()){
            nodetypes_onlytypes.TraverseDecl(Context.getTranslationUnitDecl());
            llvm::outs() << "ast_node_types.dat ::--::";
            printhashmap<int>(nodetypes_onlytypes.map, nodetypes_onlytypes.InFile);
        }
        if(nodetypesAvgDepthOpt.getValue()){
            nodetypes_depth.TraverseDecl(Context.getTranslationUnitDecl());
            llvm::outs() << "ast_node_types_avg_dep.dat ::--::";
            printhashmap<float>(nodetypes_depth.map_avgdepth, nodetypes_depth.InFile);
        }
        if(nodetypesMaxDepthOpt.getValue()){
            nodetypes_depth.TraverseDecl(Context.getTranslationUnitDecl());
            llvm::outs() << "max_depth_ast_node.dat ::--::";
            nodetypes_depth.printmaxdepth();
        }

        // III. Code in AST Leaves
        if(codeinastleavesOpt.getValue()){
            codeinastleaves.TraverseDecl(Context.getTranslationUnitDecl());
            llvm::outs() << "code_in_ast_leaves.dat ::--::";
            printhashmap<int>(codeinastleaves.map, codeinastleaves.map_usage, codeinastleaves.InFile);
        }
        if(codeinastleavesAvgDepthOpt.getValue()){
            codeinastleaves_avgdepth.TraverseDecl(Context.getTranslationUnitDecl());
            llvm::outs() << "code_in_ast_leaves_avg_dep.dat ::--::";
            printhashmap<float>(codeinastleaves_avgdepth.map_avgdepth, codeinastleaves_avgdepth.InFile);
        }

        // IV. Lexical Features
        if(lexicalfeaturesOpt.getValue()){
            lexicalfeatures.TraverseDecl(Context.getTranslationUnitDecl());
            llvm::outs() << "lexical_features.dat ::--::";
            lexicalfeatures.extractlexicalfeatures();
        }


//      Context.getTranslationUnitDecl()->dump();
    }
protected:
    GetNodeBigrams nodebigrams;
    GetNodeTypes nodetypes_onlytypes;
    GetNodeTypes nodetypes_depth;
    CodeInASTLeaves codeinastleaves;
    CodeInASTLeaves codeinastleaves_avgdepth;
    GetLexicalFeatures lexicalfeatures;
};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance &Compiler, llvm::StringRef InFile) {

        std::string s = InFile;
//        llvm::errs() << "** Creating AST consumer for: " << split_path(s)[1] << "\n";

        return std::unique_ptr<clang::ASTConsumer>(
                new FindNamedClassConsumer(&Compiler.getASTContext(), s));
    }
};


int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, FeatureExtractionCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}