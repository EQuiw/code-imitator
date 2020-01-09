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

#include "io_transformer.cpp"
#include "../utils_transform.h"
#include "../ControlDataFlow/ControlFlowGraphWithDataFlow.h"
#include "../ControlDataFlow/CDFGraphQueryHandler.h"

using namespace clang;
//#define MYDEBUG 1


class OutputTransformer : public IOTransformer {
public:

    // Here, we set what streams are considered to be checked if streams are mixed due to sync_with_stdio.
    sync_with_stdio_channels sync_mode = sync_ouput_only;

    explicit OutputTransformer(ASTContext &Context, Rewriter &OurRewriter, PreprocessingInfos *prepinfos)
            : IOTransformer(Context, OurRewriter, prepinfos) {}

    /* ******************* Replacement Methods ******************* */

protected:

    // Regex for simple printf commands; it just matches with e.g. %d or %f, or lld, llu, lu, ld
    std::string regexplaceholders = "(%[diufeEgGcs])|%lld|%lu|%ld|%llu|(%\\.[0-9]*f)";

    /**
     * Go over all strings in input vector and check if they have inverted commas at the beginning and at the end,
     * if not, insert some. If we just have a string with only ", then remove it.
     * @param inputvec a vector of strings where we check the inverted commas' presence
     */
    void wrapinvertedcommas(std::vector<std::string> &inputvec){

        for(unsigned long i = 0; i < inputvec.size(); i++){
            if(inputvec[i].empty())
                continue; // nothing to do here

            // Go over all splits and check if they need inverted commas at the beginning and at the end
            if(inputvec[i] == "\""){
                // If current split consists only of a single ", then remove it, since we would not print it
                inputvec[i] = "";
            } else {
                // Current split may need inverted commas, check..
                if(inputvec[i].front() != '"'){
                    inputvec[i] = "\"" + inputvec[i];
                }
                if(inputvec[i].back() != '"'){
                    inputvec[i].append("\"");
                }
            }
        }
    }

    /**
     * Computes the necessary prefix based on the respective placeholder in printf.
     * For example:
     *      Take printf("Hello: %e", d); where d is float
     *      Then we need to print cout << "Hello: " << scientific << setprecision(6) << d;
     *      Thus, we store the prefix: "scientific << setprecision(6)".
     * @param plholdersvec vector of placeholders
     * @return vector of prefix for each placeholder, CodeTransformationException if an error occurs
     */
    std::vector<std::string> getPrecisionPrefix(std::vector<std::string> &plholdersvec){
//        *      TODO Actually, if user specifies multiple printf commands with the same precision,
//        *      we could set the precision once at the beginning... requires some more analysis...
        std::vector<std::string> prefixlist;

        std::string floatprecisionregex = "(%\\.[0-9][0-9]*f)";
        std::string floatsplitregex = "\\.|f";

        std::string curmode = ""; // we only need to add fixed if fixed changed to scientific or vice versa
        int currentprecision = -1; // we only need to add setprecision if precision changed..


        for(std::string &plholder : plholdersvec){
            std::string currentprefix;

            // Check if we have s.th. like "%.10f"
            auto floatmatches = getMatches(plholder, floatprecisionregex);
            if(!floatmatches.empty()){

                if(floatmatches.size() != 1) {
                    llvm::errs() << "Warning: Format string has != 1 matches for %.Xf.\n";
                    throw CodeTransformationException();
                }
                auto splits = split(floatmatches[0], floatsplitregex);
                if(splits.size() != 2) {
                    llvm::errs() << "Error: Splits != 2.; size:" << splits.size() << "for:" << floatmatches[0] << "\n";
                    throw CodeTransformationException();
                } else {
                    if(curmode != "fixed") {
                        currentprefix += append_std("fixed");
                        curmode = "fixed";
                    }
                    if(std::stoi(splits[1]) != currentprecision){
                        currentprecision = std::stoi(splits[1]);
                        currentprefix += " << " + append_std("setprecision("+ splits[1] +") << ");
                    }
                }
            } else if(plholder=="%f") {
                // Check if only %f, %e, %E,
                // printf's default precision is 6.. that's why we use setprecision(6) in the default case %f
                if(curmode != "fixed"){
                    currentprefix += append_std("fixed") + " << ";
                    curmode = "fixed";
                }
                if(currentprecision != 6){
                    currentprecision = 6;
                    currentprefix += append_std("setprecision(6)") + " << ";
                }

            } else if(plholder=="%e" || plholder=="%E"){
                if(curmode != "scientific"){
                    currentprefix += append_std("scientific") + " << ";
                    curmode = "scientific";
                }
                if(currentprecision != 6){
                    currentprecision = 6;
                    currentprefix += append_std("setprecision(6)") + " << ";
                }
            }
            prefixlist.push_back(currentprefix);
        }

        if(prefixlist.size() != plholdersvec.size()){
            llvm::errs() << "placeholders and prefix list mismatch\n";
            throw CodeTransformationException();
        }

        return prefixlist;
    }


    /**
     * Retrieves the printf format string for a given type.
     * Currently, we support builtin-types and std::strings as well as char (array's)
     * If we have a floating-point value, we use the precision and isfixed variables.
     * We do nothing if not fixed, as cout also counts the number of leading digits, what we cannot do with printf?!.
     * Example: float d = 222.987654321f; float dd = 22334.12484; yields 223.988 and 22334.1 (always 6 digits).
     * @param qt the qualified type
     * @return a std::pair of two strings (for convenience, I use a typedef here). The first
     * is the % specifier, the second is a suffix that we may need to add to use the type in printf.
     * For instance, consider that we have to use .c_str() for std::strings in printf.
     */
    StringPair retrieveformatstring(QualType *qt, int precision, bool isfixed){

        StringPair formatstring;
        if(qt->getTypePtr()->isBuiltinType()) {
            // Switch+Strings in C++ not directly possible
            if (qt->getAsString() == "int")
                formatstring.first = "%d";
            if (isfixed && (qt->getAsString() == "float" || qt->getAsString() == "double")) {
                if (precision != -1) {
                    formatstring.first = "%." + std::to_string(precision) + "f";
                } else {
                    formatstring.first = "%.6f";
                }
            }
            if (qt->getAsString() == "unsigned int")
                formatstring.first = "%u";
            if (qt->getAsString() == "long")
                formatstring.first = "%ld";
            if (qt->getAsString() == "unsigned long")
                formatstring.first = "%lu";
            if (qt->getAsString() == "long long")
                formatstring.first = "%lld";
            if (qt->getAsString() == "unsigned long long")
                formatstring.first = "%llu";
            if(qt->getTypePtr()->isCharType())
                formatstring.first = "%c";
        } else if(qt->getAsString() == "const class std::__cxx11::basic_string<char>") {
            formatstring.first = "%s";
            formatstring.second = ".c_str()";
        } else if(qt->getAsString() == "const char *") {
            formatstring.first = "%s";
        }

//        llvm::outs() << "Found:" << qt->getAsString() << "becomes:" << formatstring.first << "\n";

        return formatstring;
    }




};
