cmake_minimum_required(VERSION 3.20.2)
project(daily)
set(CMAKE_CXX_STANDARD 20 -O2)

add_compile_definitions(LOCAL)
add_executable(daily tmp.cpp)
