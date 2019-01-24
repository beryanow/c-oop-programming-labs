cmake_minimum_required(VERSION 3.7.2)
project(final_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled1 main.cpp supplement.cpp functions.h)
add_executable(unittest supplement.cpp test.cpp)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
