cmake_minimum_required(VERSION 3.28.3)
project(comparer_builder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(inc)

add_executable(comparer_builder src/main.cpp)