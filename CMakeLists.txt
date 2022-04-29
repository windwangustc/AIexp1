cmake_minimum_required(VERSION 3.19)
project(exp1)

set(CMAKE_CXX_STANDARD 14)

add_executable(exp1 digital/src/digital.cpp digital/src/digital.h)
#add_executable(exp1 csp/src/csp.cpp)