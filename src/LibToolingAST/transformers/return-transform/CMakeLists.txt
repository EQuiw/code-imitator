set(LLVM_LINK_COMPONENTS support)

#add_clang_executable(return-transform
#        ReturnStatementTransform.cpp
#        ReplaceLiteral.cpp
#        )
add_executable(return_transformer
        ReturnStatementTransform.cpp
        ../lib/SourceTextHelper.cpp
        ReplaceLiteral.cpp
        AddReturn.cpp
        )
target_include_directories(return_transformer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

target_link_libraries(return_transformer
        -Wl,--start-group "${PROJECT_LINK_LIBS}" -Wl,--end-group
        "${MY_LLVM_LIBS} ${MY_SYSTEM_LIBS}"
#        authorshipEvasion
        )
#install(TARGETS return-transform
#        RUNTIME DESTINATION bin)


#include_directories(
#        ${CMAKE_CURRENT_SOURCE_DIR}/../include
#        ${MY_CLANG_ROOT_DIR}/include
#        ${MY_CLANG_ROOT_DIR}/lib/clang/5.0.0/include/
#)
