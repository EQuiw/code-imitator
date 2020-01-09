add_executable(feature_extraction_single
        extract_all_features.cpp
        ../Utilities/Utils.cpp
        ../Utilities/Utils_Features.cpp
        )

TARGET_LINK_LIBRARIES(
        feature_extraction_single
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")