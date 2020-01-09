#include "Utils_Features.h"

/**
     * Removes all characters so that code in ast leaf does not lead to problems with a json parser.
     * Based on https://github.com/nlohmann/json.
     * @param s  a string where we'd like to remove problematic characters
     * @return  a string without characters that could cause problems
    */
std::string escapesymbols(const std::string &s) {

    std::ostringstream o;
    for (auto c = s.cbegin(); c != s.cend(); c++) {
        switch (*c) {
            case '"':  o << "\\\""; break;
            case '\\': o << "\\\\"; break;
            case '\b': o << "\\b"; break;
            case '\f': o << "\\f"; break;
            case '\n': o << "\\n"; break;
            case '\r': o << "\\r"; break;
            case '\t': o << "\\t"; break;
            case ',':  o << "_"; break;
            default:
                if ('\x00' <= *c && *c <= '\x1f') {
                    o << "\\u"
                      << std::hex << std::setw(4) << std::setfill('0') << (int)*c;
                } else {
                    o << *c;
                }
        }
    }
    return o.str();
}