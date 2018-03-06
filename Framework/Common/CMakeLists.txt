cmake_minimum_required(VERSION 3.11)
set (CMAKE_C_STAMDARD 11)
set (CMAKE_CXX_STANDARD 11)

add_library(Common
Allocator.cpp
BaseApplication.cpp
GraphicsManager.cpp
main.cpp)
