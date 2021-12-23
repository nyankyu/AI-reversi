project(Google_tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run
        BoardTest.cpp
        NodeTest.cpp
        ../src/board.c
        ../src/node.c)

target_link_libraries(Google_Tests_run gtest gtest_main)
target_include_directories(Google_Tests_run PUBLIC ${CMAKE_SOURCE_DIR}/include)