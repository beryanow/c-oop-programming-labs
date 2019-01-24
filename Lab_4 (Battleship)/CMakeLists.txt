cmake_minimum_required(VERSION 3.7.2)
project(lab_4_battle)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab_4_battle main.cpp battle_functions.cpp battle_header.h)
add_executable(unittest test.cpp battle_header.h battle_functions.cpp)