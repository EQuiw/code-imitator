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
//#include "../ASTFrontendActionTemplate.inl"
#include "../ASTFrontendActionWithPrepTemplate.inl"
#include "typedef_collector.cpp"
#include "../include/SourceTextHelper.h"

using namespace clang;
using namespace llvm::cl;
//#define MYDEBUG 1
//#define OVERWRITE 1



// ** These are the command line options **
static llvm::cl::OptionCategory MyOptionCategory("Typedef with Side Info Transformer");


//static llvm::cl::opt<int> SeedOpt("seed", desc("PRNG seed"), init(0), cat(MyOptionCategory));
llvm::cl::list<std::string> TypedefTypesOpt(
        "typedefs", ZeroOrMore,
        desc("The typedef(s) that will be included.."),
        value_desc("typedefs"), cat(MyOptionCategory));



struct PreprocessingInfos {
    std::vector<std::pair<std::string, SourceLocation>> headerincludes;
};

class TypeDefSideInfoTransformer : public TypeDefCollector {
public:


    explicit TypeDefSideInfoTransformer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos) :
            TypeDefCollector(Context, OurRewriter), prepinfos(prepinfos) {}

    /* ******************* Replacement Methods ******************* */



/**
 * Add the typedef w.r.t to given input typedefs.
 * This function will only output 'Code 124 Empty Set', if no of the given typedefs can be included,
 * since all are already present. Code 123 is not used, as we expect to include a given typedef,
 * if it is not present already.
 * The important param TypedefTypesOpt is passed globally..
 */
    void addtypedef() {

        // we try to add 1 or more typedefs, to this end, we also try to find the type in source code,
        // if its there, we replace it directly...
        // TODO we could also combine this step with datastructure transformer to get a suitable type

        // used to check if some of the passed typedefs have the same name.
        std::set<std::string> namesofincludedtypedefs;

        std::vector<std::pair<SourceRange, std::string>> todos;
        std::vector<std::string> todos2;

        bool insertedatleastonce = false;
        for (auto &typedefinclude : TypedefTypesOpt) {
#ifdef MYDEBUG
            llvm::outs() << "typedef to include:" << typedefinclude << "\n";
#endif

            // I. Parse Input, I expect the format as given from DeclNamesList.cpp
            //  If no headers are given, we have only 4 splits to consider...
            auto splits = split(typedefinclude, "##");
            if(splits.size() != 4 && splits.size() != 5){
                llvm::errs() << "Wrong input:" << typedefinclude << ";" << splits.size() << "\n";
                return;
            }

            auto typedeftype = splits[0];
            auto typedefunqtype = splits[1];
            // It could be that typedef was defined in a namespace before, in future work, we could also move
            // the namespace to current author, but as a first try, we just ignore the namespace. That's why
            // we have two typedef names.
            auto typedefname_qualified = remove_last_whitespace(splits[2]);
            auto typedefname_plain = remove_last_whitespace(splits[3]);
            bool withheaderincludes = splits.size() == 5;

#ifdef MYDEBUG
            llvm::outs() << "New typedef:" << typedeftype << "\t" << typedefunqtype << "\t" << typedefname_plain << "\n";
#endif

            // II.a Check if we already included a typedef with the same name (in the list of passed args)
            while(namesofincludedtypedefs.find(typedefname_plain) != namesofincludedtypedefs.end()){
                typedefname_plain += "_";
                typedefname_qualified += "_";
            }

            // II.b Check if we already have a typedef/typealias with the same name
            bool continuefortypedef = true;
            for(auto t : typedefnamedeclarations){
                auto curtypedefname = t->getNameAsString();
                if(curtypedefname == typedefname_plain) {
                    // if there is a typedef with the same name, we do nothing...
                    continuefortypedef = false;
                    break;
                }
            }
            if(!continuefortypedef)
                continue;

            // III. same type, but with another name, then let's rename the existing typedef
            continuefortypedef = true;
            for(auto t : typedefdeclarations){
                auto curtypedefunqtype = t->getUnderlyingType().getAsString();
                if(curtypedefunqtype == typedefunqtype){

                    // a. rewrite name of current typedef
                    auto curnewtypedef = "typedef " + typedefunqtype + " " + typedefname_plain + "";
                    todos.emplace_back(t->getSourceRange(), curnewtypedef);

                    //llvm::errs() << getSourceText(Context, t->getSourceRange().getBegin(), t->getSourceRange().getEnd()) << "\n";
                    // b. rewrite all occurences
                    auto curname = t->getQualifiedNameAsString();
                    replaceAllTypedefTypesWith(curname, typedefname_plain);
                    continuefortypedef = false;
                    insertedatleastonce = true;
                    namesofincludedtypedefs.insert(typedefname_plain);
                    break;
                }
            }
            if(!continuefortypedef)
                continue;

            // IV. Insert new typedef
            // a. check if underlying type requires some headers,
            //  if we cannot say this for sure, we cannot include typedef.
            if(withheaderincludes){
                try {
                    auto headers = tokenize_input_from_DeclNamesList(splits[4], true);
                    for(auto &s2 : headers)
                        insertHeaderAtBeginningOfSourceFile(s2, &(prepinfos->headerincludes),
                                                            first_decl, sm, OurRewriter);
                } catch (const CodeTransformationException& e){
                    return;
                }
            }


            // b. create new typedef
            // b-1 Check for namespace std
            // std necessary, but no std given <- only here s.th. to do
            // no std necessary, but std given
            // std necessary, std given
            // no std necessary, no std given
            bool std_necessary = !namespace_defined("std", usedNamespaces);
            bool std_given = typedefunqtype.find("std::") != std::string::npos;
            if(std_necessary && !std_given && withheaderincludes){

                try {
                    auto headers = tokenize_input_from_DeclNamesList(splits[4], false);
                    for(auto &s2 : headers){
                        // We simply replace the type that we got from DeclNamesList by std:: version,
                        //  todo, we may directly create the std version in DeclNamesList by deeper analyzing the type.
                        typedefunqtype = ReplaceString(typedefunqtype, s2, "std::"+s2);
                    }
                } catch (const CodeTransformationException& e){
                    return;
                }
            }

            std::string completetypedef;
            completetypedef.append("typedef ").append(typedefunqtype).append(" ").append(typedefname_plain).append(";\n");
            //if(!getLocationWithoutDependencies(completetypedef))
            //    return;
            todos2.push_back(completetypedef);

            // V. Find out if source code has the type of new typedef, not as typedef yet.
            // Note that we may not replace each occurence, as the list typelocsfortypedef in
            //  fct replaceAllNecessaryTypesWithNewTypedef does not contain all typedeflocs.
            // This is not so severe, since the code still remains valid.
            replaceAllNecessaryTypesWithNewTypedef(typedefunqtype, typedefname_plain);
            insertedatleastonce = true;
            namesofincludedtypedefs.insert(typedefname_plain);
        }

        // We have to rename all things first, and then we can insert something,
        // otherwise if we insert s.th. before, and then rename, we may work at the wrong line
        for(auto &td : todos)
            OurRewriter.ReplaceText(td.first, td.second);

        for(auto &td : todos2)
            if(!getLocationWithoutDependencies(td))
                return;



        if(!insertedatleastonce)
            llvm::errs() << "Code 123: No transformations possible\n";

    }

private:
    PreprocessingInfos* prepinfos;


    /**
     * Split the output from DeclNamesList, the third one with a list of
     * (header-names; type-names),(header-names; type-names),(header-names; type-names),
     * to a list with all header-names or all type-names
     * @param input_str the input string from DeclNamesList with header- and type-names
     * @param firstelement if true, it will return header-names, if false, type-names.
     * @return list of names, throws Exception if an error occurs.
     */
    std::vector<std::string> tokenize_input_from_DeclNamesList(const std::string &input_str, bool firstelement) {

        int index;
        std::string trimsymbol;
        if (firstelement) {
            index = 0;
            trimsymbol = "(";
        } else {
            index = 1;
            trimsymbol = ")";
        }

        auto necessaryincludes = split(input_str, ",");
        std::vector<std::string> outputs;
        for (auto &s : necessaryincludes) {
            // Split (header-name;type-name)
            auto s_splits = split(s, ";");
            if (s_splits.size() < 2) {
                llvm::errs() << "Header Includes, Wrong Format?:" << s <<"\n";
                throw CodeTransformationException();
            }

            auto s1 = s_splits[index];
            auto s2 = trim(s1, trimsymbol);
            outputs.push_back(s2);
        }
        return outputs;
    }

};


/* ****************** ************** **************** */

class MyASTConsumer : public ASTConsumer {
public:

    explicit MyASTConsumer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
            : Visitor(Context, OurRewriter, prepinfos) {}

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());

        Visitor.addtypedef();
    }

private:
    TypeDefSideInfoTransformer Visitor;
};


int main(int argc, const char **argv) {
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv, MyOptionCategory);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(&*clang::tooling::newFrontendActionFactory
            <MyFrontendActionWithPrep<MyASTConsumer, PreprocessingInfos>>());
}

