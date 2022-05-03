cmake_minimum_required(VERSION 3.19)
project(exp1)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../digital/src/")
#add_executable(exp1 digital/src/a.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../csp/src/")
add_executable(exp1 csp/src/csp_v1.cpp)