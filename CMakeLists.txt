cmake_minimum_required (VERSION 3.0)


project(StackMachine)
set (CMAKE_CXX_STANDARD 20)
add_compile_options(-Wextra -Werror -Wall)

enable_testing()

add_subdirectory(Core)

add_executable(avm main.cpp)
target_link_libraries(avm PRIVATE Core)
target_link_libraries(avm PRIVATE Lexer)
