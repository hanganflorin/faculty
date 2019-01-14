cmake_minimum_required(VERSION 3.12)
project(15_puzzle)

set(CMAKE_CXX_STANDARD 14)

add_executable(15_puzzle main.cpp Board.cpp State.cpp sequential.cpp TSPriorityQueue.cpp PriorityQueue.cpp parallel.cpp)