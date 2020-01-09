cmake_minimum_required(VERSION 3.9)

# read/set user specific paths
#MESSAGE(STATUS ${MY_CLANG_ROOT_DIR})
if (NOT DEFINED MY_CLANG_ROOT_DIR)
    MESSAGE(FATAL_ERROR "Clang root directory not set (use -DMY_CLANG_ROOT_DIR)")
endif ()
set(MY_CLANG_BIN_DIR "${MY_CLANG_ROOT_DIR}/bin")

#MESSAGE(STATUS ${MY_BOOST_ROOT_DIR})
if (NOT DEFINED MY_BOOST_ROOT_DIR)
    MESSAGE(FATAL_ERROR "Boost root directory not set (use -DMY_BOOST_ROOT_DIR)")
endif ()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DMYDEBUG=1)
endif ()

# compilers must be set before you use project()!
set(CMAKE_C_COMPILER ${MY_CLANG_BIN_DIR}/clang)
set(CMAKE_CXX_COMPILER ${MY_CLANG_BIN_DIR}/clang++)

# use llvm-config to obtain necessary compiler flags, etc.
set(LLVM_CONFIG ${MY_CLANG_BIN_DIR}/llvm-config)

project(LibToolingAST)

set(CMAKE_CXX_STANDARD 11)

execute_process(COMMAND ${LLVM_CONFIG} --cxxflags
        OUTPUT_VARIABLE MY_CXX_FLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${LLVM_CONFIG} --libs
        OUTPUT_VARIABLE MY_LLVM_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${LLVM_CONFIG} --system-libs
        OUTPUT_VARIABLE MY_SYSTEM_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${LLVM_CONFIG} --ldflags
        OUTPUT_VARIABLE MY_LD_FLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE)

# some libraries are not (yet) used
set(PROJECT_LINK_LIBS
        clangAST
        clangASTMatchers
        clangAnalysis
        clangBasic
        clangDriver
        clangEdit
        clangFrontend
        #clangFrontendTool
        clangLex
        clangParse
        clangSema
        #clangEdit
        clangRewrite
        #clangRewriteFrontend
        #clangStaticAnalyzerFrontend
        #clangStaticAnalyzerCheckers
        #clangStaticAnalyzerCore
        clangSerialization
        clangToolingCore
        clangTooling
        clangFormat #
        )

include_directories(
        feature_extraction
        Utilities
        ${MY_CLANG_ROOT_DIR}/include
        ${MY_CLANG_ROOT_DIR}/lib/clang/5.0.0/include/
        ${MY_BOOST_ROOT_DIR}
)

link_directories(${MY_LD_FLAGS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_CXX_FLAGS}")

# ** Our tools **
# All the tools we need to extract the authorship identification features
add_subdirectory(feature_extraction)
# All the tools we need to extract the authorship identification features, fork of feature_extraction.
# All feature classes are now extracted by a single call.
add_subdirectory(feature_extraction_single)
# All the tools we need to modify the authorship features
add_subdirectory(transformers)
# Tests to check validity of feature_extraction tools
add_subdirectory(tests)
# Tools used to collect information from source files
add_subdirectory(codeinfo)


