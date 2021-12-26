project(Google_tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run
        BoardTest.cpp
        NodeTest.cpp
        TreeTest.cpp
        RuleTest.cpp
        ../src/board.c
        ../src/node.c
        ../src/rule.c
        ../src/tree.c
        )

target_link_libraries(Google_Tests_run gtest gmock gtest_main)
target_include_directories(Google_Tests_run PUBLIC ${CMAKE_SOURCE_DIR}/include)