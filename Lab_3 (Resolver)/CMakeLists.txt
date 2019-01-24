cmake_minimum_required(VERSION 3.7.2)
project(resolver)

set(CMAKE_CXX_STANDARD 11)

add_executable(resolver main.cpp supplement.cpp resolver_overall.h resolver.cpp)
add_executable(unittest resolver.cpp supplement.cpp test.cpp)