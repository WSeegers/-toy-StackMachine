cmake_minimum_required (VERSION 3.0)


project(StackMachine)
set (CMAKE_CXX_STANDARD 20)
enable_testing()

add_subdirectory(Core)

add_executable(vm main.cpp)
target_link_libraries(vm PRIVATE Core)
target_link_libraries(vm PRIVATE Lexer)
