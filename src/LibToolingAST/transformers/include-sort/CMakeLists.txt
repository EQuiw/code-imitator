set(LLVM_LINK_COMPONENTS support)

add_executable(includesort_transformer
        IncludeSortMain.cpp
        IncludeSort.cpp
        ../utils_transform.cpp
        )

target_link_libraries(includesort_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")
