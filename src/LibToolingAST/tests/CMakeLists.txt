include_directories(
        .
)

# exceptions are disabled per default with llvm-config, but for test suite, we need throw statements
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcxx-exceptions")

add_executable(test_get_lexical_features
        catch.hpp
        test_get_lexical_features.cpp
        ../Utilities/Utils.cpp
        )

TARGET_LINK_LIBRARIES(
        test_get_lexical_features
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(test_get_ast_node_types
        catch.hpp
        test_get_ast_node_types.cpp
        ../Utilities/Utils.cpp
        )

TARGET_LINK_LIBRARIES(
        test_get_ast_node_types
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(test_get_ast_node_bigrams
        catch.hpp
        test_get_ast_node_bigram.cpp
        ../Utilities/Utils.cpp
        )

TARGET_LINK_LIBRARIES(
        test_get_ast_node_bigrams
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(test_get_code_in-ast_leaves
        catch.hpp
        test_get_code_in_ast_leaves.cpp
        ../Utilities/Utils.cpp
        ../Utilities/Utils_Features.cpp
        )

TARGET_LINK_LIBRARIES(
        test_get_code_in-ast_leaves
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")