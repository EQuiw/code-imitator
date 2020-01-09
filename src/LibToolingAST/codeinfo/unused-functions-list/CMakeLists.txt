# Enable Exceptions
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcxx-exceptions")

add_executable(unused-functions-list
        ../../transformers/ControlDataFlow/ControlFlowGraphCore.cpp
        ../../transformers/ControlDataFlow/CDFGraphQueryHandler.cpp
        ../../transformers/ControlDataFlow/DFSVisitor.cpp
        ../../transformers/ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../../transformers/utils_transform.cpp
        ../../transformers/lib/SourceTextHelper.cpp
        ListUnusedFunctions.cpp
        unused_functions_utils.cpp)

target_link_libraries(unused-functions-list
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")
