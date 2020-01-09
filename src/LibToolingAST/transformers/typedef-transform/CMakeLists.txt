# Enable Exceptions
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcxx-exceptions")

add_executable(typedef_transformer
        typedef_transformer.cpp
        typedef_collector.cpp
        ../utils_transform.cpp
        ../../Utilities/Utils.cpp
        )
TARGET_LINK_LIBRARIES(
        typedef_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")


add_executable(typedef_sideinfo_transformer
        typedef_sideinfo_transformer.cpp
        typedef_collector.cpp
        ../utils_transform.cpp
        ../../Utilities/Utils.cpp
        ../lib/SourceTextHelper.cpp
        )
TARGET_LINK_LIBRARIES(
        typedef_sideinfo_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")