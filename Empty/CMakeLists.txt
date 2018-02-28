cmake_minimum_required(VERSION 3.11)
set (CMAKE_C_STAMDARD 11)
set (CMAKE_CXX_STANDARD 11)

add_executable(Empty EmptyApplication.cpp )
target_link_libraries(Empty Common)