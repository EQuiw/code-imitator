set(LLVM_LINK_COMPONENTS support)

add_executable(includeadd_transformer
        IncludeAddMain.cpp
        IncludeAdd.cpp
        )

target_link_libraries(includeadd_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")
