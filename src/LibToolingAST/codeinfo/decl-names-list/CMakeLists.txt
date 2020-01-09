# Enable Exceptions
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcxx-exceptions")

add_executable(decl-names-list
        ../../transformers/utils_transform.cpp
        ../../Utilities/Utils.cpp
        ../../transformers/lib/SourceTextHelper.cpp
        ../../transformers/ControlDataFlow/DeclRefMapping/DeclRefMapping.cpp
        ../../Utilities/Utils_Declarations.cpp
        DeclNamesList.cpp
        )

target_link_libraries(decl-names-list
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")
