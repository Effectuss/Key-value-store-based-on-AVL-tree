include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
)

FetchContent_MakeAvailable(googletest)

target_compile_options(gtest PRIVATE "-w")
target_compile_options(gmock PRIVATE "-w") 

add_executable(
    tests_binary_tree
    ${HEADERS}
    ${CMAKE_SOURCE_DIR}/avl_tree/self_balancing_binary_search_tree.cc
    ${CMAKE_SOURCE_DIR}/tests/tests_self_balancing_binary_search_tree.cc
)

target_link_libraries(tests_binary_tree PUBLIC gtest)

target_include_directories(tests_binary_tree PUBLIC ${CMAKE_SOURCE_DIR}/avl_tree ${CMAKE_SOURCE_DIR}/interface)

target_compile_options(
    tests_binary_tree
    PUBLIC
    -Wall
    -Werror
    -Wextra
    -Wpedantic
    -std=c++17
)