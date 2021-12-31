cmake_minimum_required(VERSION 3.21)
project(ai-reversi C)

add_executable(ai-reversi)

set(CMAKE_C_FLAGS "-Wall -O3")

target_include_directories(ai-reversi PUBLIC include)
target_sources(ai-reversi PUBLIC
        src/main.c
        src/rule.c
        src/board.c
        src/tree.c
        src/node.c
        src/com.c)

if (EXISTS "${CMAKE_SOURCE_DIR}/test/lib/CMakeLists.txt")
    enable_testing()
    add_subdirectory(test)
endif()