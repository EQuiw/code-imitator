/**
 * Extract the code in ast leaves feature.
 * In VisitStmt, we really extract the respective source code that a leaf node from the AST has.
 * However, Joern also has more leaves than clang's AST, so we also extract
 *  a. each named declaration (so that we get the name of a variable or function) in VisitDecl
 *  b. each type, so that we get e.g. the type of a variable declaration such as float f = 20.0; then
 *      we get "float".
 *
 * This file has two options that you can get via command-line argument -ast-depth=true or =false.
 * Either you just extract the occurence count of a particular source code in the leaves.
 * Or you extract the respective depth in average.
 *
 * Caution: If you process a node, then call always insertinhashmap and then insertindepthhashmap,
 * because we calculate the average depth incrementally. For this, we need to know how often a
 * particular source code was already seen - the job of insertinhashmap.
 *
 *
 * If ast-depth is false:
 * The output of this class is a json array with the format [ [a,b,c], [a,b,c], ... ]
 * where a is the 'code in ast leaf' - a sort of key.
 * where b is the #occurences.
 * where c is a string that specifies the context of the 'code in ast leaf'. For instance, if it's a VarDecl
 * or a DeclRefExpr or a type. We append each usage by '__<usage>' to the string, so that we get e.g.
 * for 'aVariable' the node ['aVariable', 4, 'Var__DeclRefExpr']. The 'aVariable' was first declared
 * as variable (-> Var) and later used (-> DeclRefExpr).
 *
 * If ast-depth is true:
 * The output of this class is a json array with the format [ [a,b], [a,b], ... ]
 * where a is the 'code in ast leaf' - a sort of key.
 * where b is the average depth.
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
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

#include "Utils.h"
#include "Utils_Features.h"

using namespace clang;
using namespace clang::tooling;
using namespace clang::driver;

// Comment out to omit debugging prints
//#define DEBUG 0


class CodeInASTLeaves : public RecursiveASTVisitor<CodeInASTLeaves>{
public:

    std::string InFile;
    // a hashmap storing node and number of occurences
    std::unordered_map<std::string, int> map;
    // a hashmap storing node and its usage context, e.g. is 'code in AST leaf' a VarDecl, DeclRefExpr, Function?
    std::unordered_map<std::string, std::string> map_usage;
    // a hashmap storing node and its average depth
    std::unordered_map<std::string, float> map_avgdepth;

    explicit CodeInASTLeaves(ASTContext *Context, std::string &InFile, bool get_avg_depth)
            : InFile(InFile), Context(Context),
              sm(Context->getSourceManager()), get_avg_depth(get_avg_depth){
    }

    bool VisitStmt(Stmt *s) {
        // Check whether stmt is in target file
        auto srcloc = s->getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {
//            llvm::outs() << "StmtClass:" << s->getStmtClassName() << "\n";

            const auto& children = s->children();
            // Check whether leaf node
            if(children.begin() == children.end()){

                // 1. Save current leaf node
                insertinhashmap(escapesymbols(stmt2str(s)));
                // 2. Get its depth
                int currentavgdepth = -1;
                if(this->get_avg_depth) {
                    const auto &parents = Context->getParents(*s);
                    currentavgdepth = getdepthfornode(parents, this->Context, 0, InFile);
                    insertindepthhashmap(map, map_avgdepth, escapesymbols(stmt2str(s)), currentavgdepth);
                }

                // 3. Save its usage type
                insertUsageInHashmap(escapesymbols(stmt2str(s)), s->getStmtClassName());

                #ifdef DEBUG
                llvm::outs() << "Stmt:" << s->getStmtClassName();
                llvm::outs() << "\t" << stmt2str(s) << "\t" << currentavgdepth << "\n";
                #endif
            }
        }
        return true;
    }


    bool VisitDecl(Decl *d) {
        bool inmainfile = Context->getSourceManager().isInMainFile(d->getLocation());
        if (inmainfile) {
            if(isa<NamedDecl>(d)){
                NamedDecl *namedd = cast<NamedDecl>(d);

                // 1. Save current "leaf node"
                insertinhashmap(escapesymbols(namedd->getDeclName().getAsString()));
                // 2. Get its depth
                int currentavgdepth = -1;
                if(this->get_avg_depth) {
                    const auto &parents = Context->getParents(*d);
                    currentavgdepth = getdepthfornode(parents, this->Context, 0, InFile);
                    insertindepthhashmap(map, map_avgdepth,
                                         escapesymbols(namedd->getDeclName().getAsString()), currentavgdepth);
                }

                // 3. Save its usage type
                insertUsageInHashmap(escapesymbols(namedd->getDeclName().getAsString()),
                                     namedd->getDeclKindName());

                #ifdef DEBUG
                llvm::outs() << "Decl:\t" << namedd->getDeclName().getAsString() << "(" << namedd->getDeclKindName() << ")"
                        << "\t" << currentavgdepth << "\n";
                #endif
            }
        }
        return true;
    }


    bool VisitTypeLoc(TypeLoc x) {
        auto srcloc = x.getLocStart();
        if (sm.isWrittenInMainFile(srcloc)) {

            // 1. Save current "leaf node"
            insertinhashmap(escapesymbols(x.getType().getAsString()));
            // 2. Get its depth
            int currentavgdepth = -1;
            if(this->get_avg_depth){
                const auto& parents = Context->getParents(x);
                currentavgdepth = getdepthfornode(parents, this->Context, 0, InFile);
                insertindepthhashmap(map, map_avgdepth, escapesymbols(x.getType().getAsString()), currentavgdepth);
            }

            // 3. Save its usage type
            insertUsageInHashmap(escapesymbols(x.getType().getAsString()), "Type");

            #ifdef DEBUG
            llvm::outs() << "Type:\t" << x.getType().getAsString()
                    << "\t" << currentavgdepth << "\n";
            #endif
        }
        return true;
    }

private:
    ASTContext *Context;
    SourceManager &sm;
//    CompilerInstance &ci;
    bool get_avg_depth;


    /**
     * Insert the 'code in ast leaf' into the hashmap.
     * Call this method before you call  insertindepthhashmap.
     * @param str node's source code = code in ast leaf
     */
    void insertinhashmap(const std::string &str){
        if(this->map.find("\"" + str + "\"") != this->map.end()){
            // str is already in
            this->map["\"" + str + "\""] += 1;
        } else {
            this->map["\"" + str + "\""] = 1;
        }
    }

/**
 * Returns the source code for a given statement
 * @param s  the statement
 * @return a string with the source code
 */
    std::string stmt2str(Stmt *s) {
        std::string text = Lexer::getSourceText(CharSourceRange::getTokenRange(s->getSourceRange()),
                                                sm, LangOptions(), 0);
        if (text.size() > 0 && (text.at(text.size()-1) == ',')) //the text can be ""
            return Lexer::getSourceText(CharSourceRange::getCharRange(s->getSourceRange()),
                                        sm, LangOptions(), 0);
        return text;
    }


    /**
     * Insert the Class / Usage Type of current 'code in ast leaf' into the hashmap 'map_usage'.
     * @param key  - the code in ast leaf
     * @param usage - the string representing its usage, e.g. StmtClassName or DeclKindName...
     */
    void insertUsageInHashmap(std::string key, std::string usage) {
        // A. Just small check. Ensure that map also contains this key.
        if(map.find("\"" + key + "\"") == map.end()){
            llvm::errs() << "Error: Storing Usage -- map does not have the #elements for current str" << "\n";
        }

        // B. Insert
        if(this->map_usage.find("\"" + key + "\"") != this->map_usage.end()){
            // str is already in

            if(this->map_usage["\"" + key + "\""].find(usage) == std::string::npos){
                // check that usage is not already in
                this->map_usage["\"" + key + "\""] += ("__" + usage);
            }
        } else {
            this->map_usage["\"" + key + "\""] = usage;
        }
    }


};

/*****************************************************************/

//class FindNamedClassConsumer : public clang::ASTConsumer {
//public:
//    explicit FindNamedClassConsumer(ASTContext *Context, std::string InFile, bool get_avg_depth)
//            : Visitor(Context, InFile, get_avg_depth), get_avg_depth(get_avg_depth) {}
//
//    void HandleTranslationUnit(clang::ASTContext &Context) override {
//        // 1. Traverse through tree and extract features
//        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
//        // 2. Print features to stdout
//        if(!get_avg_depth){
//            printhashmap<int>(Visitor.map, Visitor.map_usage, Visitor.InFile);
//        } else {
//            printhashmap<float>(Visitor.map_avgdepth, Visitor.InFile);
//        }
//    }
//private:
//    CodeInASTLeaves Visitor;
//    bool get_avg_depth;
//};
