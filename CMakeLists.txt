cmake_minimum_required(VERSION 3.21)
project(ai-reversi C)

add_executable(ai-reversi)

set(CMAKE_C_FLAGS "-Wall")

target_include_directories(ai-reversi PRIVATE include)
target_sources(ai-reversi PRIVATE
        src/main.c
        src/rule.c
        src/board.c
        src/tree.c
        src/node.c
        src/com.c
        src/com_rand.c
        src/evaluator.c
        src/history.c
        src/human.c
        src/measure.c)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/lib/CMakeLists.txt")
    enable_testing()
    add_subdirectory(test)
endif()