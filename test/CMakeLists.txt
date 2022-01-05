cmake_minimum_required(VERSION 3.10)
project(Google_tests)

add_subdirectory(lib)

include(GoogleTest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run
        BoardTest.cpp
        NodeTest.cpp
        TreeTest.cpp
        RuleTest.cpp
        Util.cpp
        ${ai-reversi_SOURCE_DIR}/src/board.c
        ${ai-reversi_SOURCE_DIR}/src/node.c
        ${ai-reversi_SOURCE_DIR}/src/rule.c
        ${ai-reversi_SOURCE_DIR}/src/tree.c
        ${ai-reversi_SOURCE_DIR}/src/com.c
        )

target_link_libraries(Google_Tests_run gtest gmock gtest_main)
target_include_directories(Google_Tests_run PUBLIC ${ai-reversi_SOURCE_DIR}/include)

gtest_discover_tests(Google_Tests_run)
