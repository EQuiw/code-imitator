add_executable(get_lexems_features
        ./lexems_features.cpp
        ../Utilities/Utils.cpp
        ../Utilities/Utils_Features.cpp
        )

TARGET_LINK_LIBRARIES(
        get_lexems_features
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")