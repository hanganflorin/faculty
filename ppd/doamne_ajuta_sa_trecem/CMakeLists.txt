cmake_minimum_required(VERSION 3.12)
project(doamne_ajuta_sa_trecem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(doamne_ajuta_sa_trecem sum.cpp)