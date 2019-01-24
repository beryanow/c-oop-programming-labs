cmake_minimum_required (VERSION 3.7.2)
project (drawer)

set(CMAKE_CXX_STANDARD 14)
add_executable(drawer main.cpp drawer_functions.cpp drawer_header.h)
add_executable(unittest test.cpp drawer_functions.cpp)