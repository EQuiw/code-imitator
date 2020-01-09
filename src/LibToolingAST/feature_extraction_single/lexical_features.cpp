/**
 * This file implements the features that are not extracted correctly in the Java implementation.
 * We focus on the lexical features, in particular:
 *  - numFunctions
 *  - branchingFactor
 *  - nestingDepth
 * Moreover, we extract the following features where we feel more comfortable to do that with the AST:
 *  - avgParams
 *  - stdDevNumParams
 *
 *
 */

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
#include <fstream>
#include <numeric>

#include "../Utilities/Utils.h"

using namespace clang;
using namespace clang::tooling;
using namespace clang::driver;

//#define DEBUG 0

class GetLexicalFeatures : public RecursiveASTVisitor<GetLexicalFeatures>{
public:

    std::string InFile;

    /** Final output features **/
    double numfuncfilesize;
    double avgparams;
    double stdDevNumParams;
    unsigned int nestingDepth = 0;
    double avgbranchingfactor;


    explicit GetLexicalFeatures(ASTContext *Context, std::string &InFile)
            :  InFile(InFile), Context(Context), sm(Context->getSourceManager()) {

        // Get file length in characters
        std::ifstream file(InFile.c_str(), std::ifstream::in | std::ifstream::binary);

        if(!file.is_open())
        {
            llvm::errs() << "**Cannot open file" << InFile << "\n";
        }

        file.seekg(0, std::ios::end);
        this->fileSize = file.tellg();
        file.close();

    }

    bool VisitStmt(Stmt *s) {
        // Check origin of stmt and if in main file
        auto srcloc = s->getLocStart();
        if(sm.isWrittenInMainFile(srcloc)){

            // A. Stmt Branching Factor.
            getbranchingfactor(s);

            // B. Stmt Nesting Depth.
            const auto& children = s->children();
            unsigned int currentnestingdepth = 0;
            if(children.begin() == children.end()){
                // is a leaf node, go to parent to calculate nesting depth
//                llvm::outs() << "#####" << s->getStmtClassName() << "\n";
                currentnestingdepth = findnestingdepth(currentnestingdepth,
                                                       Context->getParents(*s));
            }
            // Update if depth of current leaf node is bigger than the currently known
            if(currentnestingdepth > this->nestingDepth){
                this->nestingDepth = currentnestingdepth;
            }

        }
        return true;
    }

    bool VisitFunctionDecl(FunctionDecl *f) {
        // Class methods and functions are counted.
        bool inmainfile = Context->getSourceManager().isInMainFile(f->getLocation());
        if(inmainfile) {
            // Only function definitions (with bodies), not declarations.
            if (f->hasBody()) {
                // A) Feature numFunctions
                this->numFunctions++;

                // B) Get function params
                this->numberParams.push_back(f->getNumParams());
            }
        }
        return true;
    }

    /**
     * Extract & print the relevant lexical features...
     */
    void extractlexicalfeatures(){
        // Some Debug Info's
#ifdef DEBUG
        llvm::errs() << "[fileSize:" << fileSize << "]" << "\n";
        llvm::errs() << "[#params:" << numberParams.size() << "]" << "\n";
        llvm::errs() << "[#fcts:" << numFunctions << "]" << "\n";
        llvm::errs() << "[#branchingfactor size:" << branchingfactor.size() << "]" << "\n";
#endif

        llvm::outs() << extract_name(split_path(InFile)[1]) << " "
                     << split_path(InFile)[1] << " [";

        // A. NumFunctions/length
        this->numfuncfilesize = this->numFunctions/(double) this->fileSize;
        llvm::outs() << "[\"NumFunctions/length\", \"" << numfuncfilesize << "\"]" << ", ";


        // B. Average parameters among all functions
        this->avgparams = 1.0 * std::accumulate(this->numberParams.begin(), this->numberParams.end(), 0UL)
                           / this->numberParams.size();
        llvm::outs() << "[\"avgParams\", \"" << avgparams << "\"]" << ", ";


        // C. Std of the number of parameters among all functions
        // The following code is really just to get the std of the vector!
        std::vector<double> diff(this->numberParams.size());
        double avgparamsbadhack = this->avgparams; // since following command has so namespace problems.
        std::transform(this->numberParams.begin(), this->numberParams.end(), diff.begin(), [avgparamsbadhack](double x) { return x - avgparamsbadhack; });
        double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
        this->stdDevNumParams = std::sqrt(sq_sum / this->numberParams.size());
        llvm::outs() << "[\"stdDevNumParams\", \"" << stdDevNumParams << "\"]" << ", ";


        // D. nestingDepth
        llvm::outs() << "[\"nestingdepth\", \"" << this->nestingDepth << "\"]" << ", ";


        // E. branchingFactor
        this->avgbranchingfactor = 1.0 * std::accumulate(this->branchingfactor.begin(),
                                                          this->branchingfactor.end(), 0UL)
                                    / this->branchingfactor.size();
        llvm::outs() << "[\"avgbranchingfactor\", \"" << avgbranchingfactor << "\"]";

        llvm::outs() << "] \n";
    }

private:
    ASTContext *Context;
    SourceManager &sm;
//    CompilerInstance &ci;

    unsigned int numFunctions = 0;
    long fileSize;
    std::vector<int> numberParams;
    std::vector<int> branchingfactor;



    bool checkifcompoundcompoundpair(const Stmt *s){
        if (isa<CompoundStmt>(s)) {
            auto parents = Context->getParents(*s);
            if (parents.size() > 0) {
                const auto *ST = parents[0].get<Stmt>();
                if (ST && isa<CompoundStmt>(ST)) {
                       return true;
                }
            }
        }
        return false;
    }

    /**
     * Checks whether decl is a code block stmt.
     * @param d Decl.
     * @return true if it so.
     */
    bool checkifcontrolstmtorloop(const Decl* d){
        return (isa<FunctionDecl>(d) || isa<NamespaceDecl>(d) || isa<CXXRecordDecl>(d)
                || isa<CXXMethodDecl>(d));
    }

    /**
     * Get branching factor of current statement. It will be saved in class variable branchingfactor.
     * @param s the current Stmt
     */
    void getbranchingfactor(Stmt *s){
        const auto& children = s->children();

        // Case 1. Current stmt is a compound stmt, then count all control and compound stmt's
        // under this stmt. If nothing found, there are no { ctrl stmt } under this stmt, so count 0
        int currentbranchingfactor = 0;
        if(isa<CompoundStmt>(s)){
            // Case 1-a) Go over all children now. Control or compound stmt?
            for(Stmt *child : children){
                if(child && (checkifcontrolstmt(child) || isa<CompoundStmt>(child))) {
                    currentbranchingfactor++;
                }
            }
//            llvm::errs() << "Stmt-a:" << s->getStmtClassName()
//                         << ":" << currentbranchingfactor << "\n";
        }

        // Case 2. Current stmt is single stmt without {...}. Check that no compound stmt is
        // under this stmt, if so, it will get a branching factor of 1. Otherwise, we will visit
        // the compound stmt later and work with it under Case 1.
        if(checkifcontrolstmt(s)){
            bool iscasetwo = true;
            // Case 2-a) Check if we find a compound stmt under it..
            for(Stmt *child : children){
                if(child && isa<CompoundStmt>(child)) {
                    iscasetwo = false;
                    break;
                }
            }
            // Case 2-b) If not, count branching factor of 1
            if(iscasetwo){
                currentbranchingfactor = 1;
            }
//            llvm::errs() << "Stmt-b:" << s->getStmtClassName()
//                         << ":" << currentbranchingfactor << "\n";
        }

        if(currentbranchingfactor > 0)
            this->branchingfactor.push_back(currentbranchingfactor);
    }


    /**
     * Go towards the parent node and determine the depth recursively.
     * @param nestingdepth the current nesting depth
     * @param parents the parent from the node that called this method
     * @return the updated nesting depth..
     */
    unsigned int findnestingdepth(unsigned int nestingdepth,
                                  const ASTContext::DynTypedNodeList &parents){

        // A. Check whether empty parent or too many parents for our application
        if ( parents.empty() ) {
//            llvm::errs() << "No parent found.. \n";
            return nestingdepth;
        } else {
            // B. Okay, everthing is fine, let's get the parents.
            // The parent can be a stmt or decl, so consider what we get..
            unsigned int temporarydepthmax = nestingdepth;
            unsigned int temporarydepth = 0;
            for(auto par : parents) {

                // B.i: Check if its a statement
                const auto *ST = par.get<Stmt>();
                if (ST) {
                    if (checkifcontrolstmt(ST) || checkifcompoundcompoundpair(ST)) {
                        // increment depth if control statement
                        nestingdepth++;
//                    llvm::outs() << ">" << ST->getStmtClassName() << ";" << nestingdepth
//                           << "\t" << checkifcontrolstmt(ST) << ";"<<  checkifcompoundcompoundpair(ST) << "\n";
                    }
                    // go to parent..
                    temporarydepth = findnestingdepth(nestingdepth, Context->getParents(*ST));
                }
                // B.ii: Check if its a declaration
                const auto *DC = par.get<Decl>();
                if (DC) {
                    if (checkifcontrolstmtorloop(DC)) {
                        // increment depth if control statement
                        nestingdepth++;
//                    llvm::outs() << ">" << DC->getDeclKindName() << ";" << nestingdepth << "\n";
                    }
                    temporarydepth = findnestingdepth(nestingdepth, Context->getParents(*DC));
                }
                // B.iii: Check if its a type, typeloc, nestednamespecifier, nestnamespecifierloc
//            const auto *TL = parents[0].get<Type>();
//            const auto *TLloc = parents[0].get<TypeLoc>();
//            const auto *NN = parents[0].get<NestedNameSpecifier>();
//            const auto *NNloc = parents[0].get<NestedNameSpecifierLoc>();
//            if (TL || TLloc || NN || NNloc) {
//                llvm::errs() << "Not considered Parent-Type yet! " << "\n";
//            }
                if(temporarydepth > temporarydepthmax)
                    temporarydepthmax = temporarydepth;
            }
            nestingdepth = temporarydepthmax;
        }
        return nestingdepth;
    }
};


/*****************************************************************/

//class FindNamedClassConsumer : public clang::ASTConsumer {
//public:
//    explicit FindNamedClassConsumer(ASTContext *Context, std::string InFile)
//            : Visitor(Context, InFile) {}
//
//    void HandleTranslationUnit(clang::ASTContext &Context) override {
//        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
//        Visitor.extractlexicalfeatures();
////      Context.getTranslationUnitDecl()->dump();
//    }
//protected:
//    GetLexicalFeatures Visitor;
//};