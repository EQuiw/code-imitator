# Enable Exceptions
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcxx-exceptions")

add_executable(declname_transformer
        declname_transformer.cpp
        ../ControlDataFlow/ControlFlowGraphCore.cpp
        ../ControlDataFlow/CDFGraphQueryHandler.cpp
        ../ControlDataFlow/DFSVisitor.cpp
        ../ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../utils_transform.cpp
        ../lib/SourceTextHelper.cpp
        ../RenamingGuide.cpp
        )
TARGET_LINK_LIBRARIES(
        declname_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(global_const_transformer
        global_const_transformer.cpp
        ../utils_transform.cpp
        ../../Utilities/Utils.cpp
        ../lib/SourceTextHelper.cpp
        )
TARGET_LINK_LIBRARIES(
        global_const_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")