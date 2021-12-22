set(CMAKE_C_STANDARD 99)

add_executable(ai-reversi main.c board.c com.c node.c rule.c tree.c)

target_include_directories(ai-reversi PRIVATE ${PROJECT_SOURCE_DIR}/include)

