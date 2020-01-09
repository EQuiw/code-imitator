#include <algorithm>
#include "RenamingGuide.h"
#include <ctime>




std::string RenamingGuide::getRandomStringWith(int length) {
    // Adapted fct from stackoverflow

    srand( unsigned ( time(0)) );
    auto randchar = []() -> char
    {
        const char charset[] =
//                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}