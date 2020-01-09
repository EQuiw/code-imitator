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
#include "typedef_collector.cpp"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1
//#define OVERWRITE 1


enum Strategy {replacetypedef=1, addtypedefs=2};
enum Selection {resolvedependencies=1, bottomtotop=2, toptobottom=3, selectrandomly=4, selectlongestchar=5};


// ** These are the command line options **
static llvm::cl::OptionCategory MyOptionCategory("Typedef Transformer");
static llvm::cl::opt<Strategy> StrategyOpt("strategy", desc("Transformation strategy"), Required,
                                           values(clEnumVal(replacetypedef, "replace typedef"),
                                                  clEnumVal(addtypedefs, "add typedef")
                                                  ),
                                           cat(MyOptionCategory));
static llvm::cl::opt<Selection> SelectionOpt("selection", desc("Selection strategy; not each is relevant for each strategy"),
                                         Required,
                                           values(clEnumVal(resolvedependencies, "replace typedef"),
                                                  clEnumVal(bottomtotop, "replace typedef"),
                                                  clEnumVal(toptobottom, "replace typedef"),
                                                  clEnumVal(selectrandomly, "add typedef"),
                                                  clEnumVal(selectlongestchar, "add typedef")
                                           ),
                                           cat(MyOptionCategory));

static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));





class TypeDefTransformer : public TypeDefCollector {
public:

    explicit TypeDefTransformer(ASTContext &Context, Rewriter &OurRewriter) :
            TypeDefCollector(Context, OurRewriter) {}

    /* ******************* Replacement Methods ******************* */
    // "Code 123" as status is not needed in both replacement methods,
    // as we expect to include / remove a given typedef,
    //    if we found a suitable typeloc / typedef.

    /**
     * Finally replace typedef w.r.t. to chosen strategy to select a certain typedef.
     *
     */
    void replacetypedefs(Selection cselection) {
        // I. Get the typedef that should be replaced
        if(!this->typedefdecltorewrite){

            TypedefDecl *res = nullptr;
            assert(cselection == resolvedependencies || cselection == bottomtotop || cselection == toptobottom);
            switch(cselection) {
                case resolvedependencies: res = retrievetypedefdecl_resolvedependencies(); break;
                case bottomtotop: res = retrievetypedefdecl_bottomtotop(); break;
                case toptobottom: res = retrievetypedefdecl_toptobottom(); break;
                default: return;
            }

            if(!res){
                llvm::errs() << "Code 124: Empty set\n";
                return;
            }
            // II.a Save typedef
            this->typedefdecltorewrite = res;
            #ifdef MYDEBUG
            llvm::outs() << "Rewrite.." << typedefdecltorewrite->getQualifiedNameAsString() << "\n";
            #endif

            // II.b Remove typedef declaration in source text that has been selected..
            SourceLocation _End = this->typedefdecltorewrite->getLocEnd();
            SourceLocation End = Lexer::getLocForEndOfToken(_End, 0, sm, Context.getLangOpts());
            OurRewriter.RemoveText(SourceRange(this->typedefdecltorewrite->getLocStart(),
                                               End.getLocWithOffset(1))); //offset 1 fixes missing ;
        }

        // II. Replace it in all occurrences
        auto typetomatch = this->typedefdecltorewrite->getQualifiedNameAsString();
        auto newtype = typedefdecltorewrite->getUnderlyingType().getAsString();
        replaceAllTypedefTypesWith(typetomatch, newtype);
    }




    void addnewtypedef(Selection cselection, int seed) {

        if(this->typelocsfortypedef.empty()){
            llvm::errs() << "Code 124: Empty set\n";
            return;
        }

        // I. Get the type that will be replaced by typedef
        // Note: getType().getString returns the type incl. qualifier such as const,
        // but TypeLoc' location just contains the type without qualifier... that's why we just UnqualifiedType...
        std::string typetoinsert;
        TypeLoc chosentypeloc;

        assert(cselection == selectrandomly || cselection == selectlongestchar);
        if(cselection == selectrandomly){
            // Choose type randomly
            randomlySortVector<TypeLoc>(typelocsfortypedef, seed);
            chosentypeloc = *(typelocsfortypedef.begin());
//            typetoinsert = getSourceText(Context, chosentypeloc);
            typetoinsert = chosentypeloc.getType().getUnqualifiedType().getAsString();

        } else if(cselection == selectlongestchar) {
            // add the type with the longest char range
            for (TypeLoc tl : this->typelocsfortypedef) {
//                std::string curtype = getSourceText(Context, tl, false);
                std::string curtype = tl.getType().getUnqualifiedType().getAsString();
                if (curtype.size() > typetoinsert.size()) {
                    typetoinsert = curtype;
                    chosentypeloc = tl;
                }
            }

        } else {
            llvm::errs() << "Wrong typedef selection\n";
            return;
        }


        // II. Find an appropriate typedef name. We simply take the first x letters of each word in type;
        // thus e.g. x=1 and "unsigned int" becomes "ui"; We increase x if a typedef already exists with this name.
        std::string newtypedefname = findnewtypedefname(typetoinsert, 1);
        if(newtypedefname.empty()){
            llvm::errs() << "Error: Could not determine a new name for typedef;" << typetoinsert << "\n";
            return;
        }
        #ifdef MYDEBUG
        llvm::outs() << "Max length:" << typetoinsert.size() << " from: "
                     << typetoinsert << " with new name: " << newtypedefname <<"\n";
        #endif

        // III. Insert new typedef
        std::string completetypedef = "typedef " + typetoinsert + " " + remove_last_whitespace(newtypedefname) +";\n";
        if(!getLocationForNewTypedef(chosentypeloc, completetypedef, typetoinsert))
            return;


        // IV. Replace all necessary types with new typedef
        replaceAllNecessaryTypesWithNewTypedef(typetoinsert, newtypedefname);

    }

private:


};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter)
            : Visitor(Context, OurRewriter) {
        cmdoption = StrategyOpt.getValue();
        cselection = SelectionOpt.getValue();
        seed = SeedOpt.getValue();
    }

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        // Now decide if new typedef's should be added or an existing typedef should be replaced.
        if(cmdoption == addtypedefs){
            Visitor.addnewtypedef(cselection, seed);
        } else if(cmdoption == replacetypedef){
            Visitor.replacetypedefs(cselection);
        } else {
            llvm::errs() << "Wrong cmdoption\n";
        }
    }

private:
    TypeDefTransformer Visitor;
    Strategy cmdoption;
    Selection cselection;
    int seed;
};


int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(clang::tooling::newFrontendActionFactory<MyFrontendAction<MyASTConsumer>>().get());
}