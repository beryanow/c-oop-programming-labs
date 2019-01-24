cmake_minimum_required(VERSION 3.7.2)
project(tritset)

set(CMAKE_CXX_STANDARD 14)

add_executable(tritset tritset.cpp tritset.h test.cpp)
add_executable(unittest tritset.h tritset.cpp test.cpp)