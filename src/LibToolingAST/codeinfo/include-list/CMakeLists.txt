set(LLVM_LINK_COMPONENTS support)

add_executable(include-list
        IncludeList.cpp)

target_link_libraries(include-list
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}")
