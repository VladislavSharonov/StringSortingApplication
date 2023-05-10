cmake_minimum_required(VERSION 3.24)
project(StringLib)

set(CMAKE_CXX_STANDARD 11)

add_library(StringLib STATIC stringlib.h stringlib.cpp)
