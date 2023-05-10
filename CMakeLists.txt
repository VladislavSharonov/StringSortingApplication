cmake_minimum_required(VERSION 3.24)
project(StringSortingApplication)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(StringLib)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} StringLib)
target_include_directories(${PROJECT_NAME} PRIVATE StringLib)
