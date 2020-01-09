# Enable Exceptions
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcxx-exceptions")

add_executable(unused_functions_transformer
        unused_functions_transformer.cpp
        ../utils_transform.cpp
        ../../Utilities/Utils.cpp
        ../lib/SourceTextHelper.cpp
        ../ControlDataFlow/ControlFlowGraphCore.cpp
        ../ControlDataFlow/CDFGraphQueryHandler.cpp
        ../ControlDataFlow/DFSVisitor.cpp
        ../ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../../codeinfo/unused-functions-list/unused_functions_utils.cpp)
TARGET_LINK_LIBRARIES(
        unused_functions_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(unused_declarations_transformer
        unused_declarations_transformer.cpp
        ../utils_transform.cpp
        ../../Utilities/Utils.cpp
        ../../Utilities/Utils2.cpp
        ../lib/SourceTextHelper.cpp
        ../ControlDataFlow/DeclRefMapping/DeclRefMapping.cpp
        ../../Utilities/Utils_Declarations.cpp
        )
TARGET_LINK_LIBRARIES(
        unused_declarations_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(unused_typedefs_transformer
        unused_typedefs_transformer.cpp
        ../lib/SourceTextHelper.cpp
        ../ControlDataFlow/DeclRefMapping/DeclRefMapping.cpp
        ../utils_transform.cpp
        ../../Utilities/Utils.cpp
        ../../Utilities/Utils2.cpp
        ../../Utilities/Utils_Declarations.cpp
        )

target_link_libraries(unused_typedefs_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(unused_records_transformer
        unused_records_transformer.cpp
        ../lib/SourceTextHelper.cpp
        ../ControlDataFlow/DeclRefMapping/DeclRefMapping.cpp
        ../utils_transform.cpp
        ../../Utilities/Utils.cpp
        ../../Utilities/Utils2.cpp
        ../../Utilities/Utils_Declarations.cpp
        )

target_link_libraries(unused_records_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")