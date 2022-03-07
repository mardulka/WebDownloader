cmake_minimum_required(VERSION 3.16)
include(CMakePrintHelpers)
project(PA2)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)


add_executable(PR03 practice/03/test.cpp)
add_executable(PR04 practice/04/test.cpp)

add_executable(HW01 homework/01/test.cpp)
