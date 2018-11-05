cmake_minimum_required(VERSION 3.12)
project(lab2)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(lab2 main.cpp Matrix.h Matrix.cpp utils.h utils.cpp)