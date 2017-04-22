cmake_minimum_required(VERSION 2.8.4)
project(data_structure)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/usr/local/Cellar/boost/1.57.0/include/boost")

set(SOURCE_FILES linear_list.c linear_list/linear_list.c linear_list/linear_list.h)
add_executable(data_structure ${SOURCE_FILES})