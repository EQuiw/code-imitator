# Enable Exceptions
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcxx-exceptions")

add_executable(ifostream_preprocessor
        ifostream_preprocessor.cpp
        ../ControlDataFlow/ControlFlowGraphCore.cpp
        ../ControlDataFlow/CDFGraphQueryHandler.cpp
        ../ControlDataFlow/DFSVisitor.cpp
        ../ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../utils_transform.cpp
        ../lib/SourceTextHelper.cpp
        )
TARGET_LINK_LIBRARIES(
        ifostream_preprocessor
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")

add_executable(output_cplusplusstyle_transformer
        io_transformer.cpp
        output_cplusplusstyle_transf.cpp
        output_transformer.cpp
        StreamRewriters/InterfaceStdinOutRewriter.cpp
        StreamRewriters/InterfaceFileRewriter.cpp
        ../ControlDataFlow/ControlFlowGraphCore.cpp
        ../ControlDataFlow/CDFGraphQueryHandler.cpp
        ../ControlDataFlow/DFSVisitor.cpp
        ../ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../../Utilities/Utils.cpp
        ../utils_transform.cpp
        utils_io_transformers.cpp
        ../RenamingGuide.cpp
        ../lib/SourceTextHelper.cpp
        )
TARGET_LINK_LIBRARIES(
        output_cplusplusstyle_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(output_cstyle_transformer
        io_transformer.cpp
        output_cstyle_transf.cpp
        output_transformer.cpp
        ../ControlDataFlow/ControlFlowGraphCore.cpp
        ../ControlDataFlow/CDFGraphQueryHandler.cpp
        ../ControlDataFlow/DFSVisitor.cpp
        ../ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../utils_transform.cpp
        utils_io_transformers.cpp
        ../../Utilities/Utils.cpp
        ../RenamingGuide.cpp
        ../lib/SourceTextHelper.cpp
        )
TARGET_LINK_LIBRARIES(
        output_cstyle_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(input_cstyle_transformer
        io_transformer.cpp
        input_cstyle_transf.cpp
        input_transformer.cpp
        ../ControlDataFlow/ControlFlowGraphCore.cpp
        ../ControlDataFlow/CDFGraphQueryHandler.cpp
        ../ControlDataFlow/DFSVisitor.cpp
        ../ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../utils_transform.cpp
        ../lib/SourceTextHelper.cpp
        utils_io_transformers.cpp
        )
TARGET_LINK_LIBRARIES(
        input_cstyle_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(input_cplusplusstyle_transformer
        io_transformer.cpp
        input_cplusplusstyle_transf.cpp
        input_transformer.cpp
        StreamRewriters/InterfaceStdinOutRewriter.cpp
        StreamRewriters/InterfaceFileRewriter.cpp
        ../ControlDataFlow/ControlFlowGraphCore.cpp
        ../ControlDataFlow/CDFGraphQueryHandler.cpp
        ../ControlDataFlow/DFSVisitor.cpp
        ../ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../utils_transform.cpp
        utils_io_transformers.cpp
        ../lib/SourceTextHelper.cpp
        ../RenamingGuide.cpp
        )
TARGET_LINK_LIBRARIES(
        input_cplusplusstyle_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(sync_with_stdio_transformer
        sync_with_stdio_transformer.cpp
        io_transformer.cpp
        ../ControlDataFlow/ControlFlowGraphCore.cpp
        ../ControlDataFlow/CDFGraphQueryHandler.cpp
        ../ControlDataFlow/DFSVisitor.cpp
        ../ControlDataFlow/ControlFlowGraphWithDataFlow.cpp
        ../utils_transform.cpp
        utils_io_transformers.cpp
        ../lib/SourceTextHelper.cpp
        )
TARGET_LINK_LIBRARIES(
        sync_with_stdio_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")