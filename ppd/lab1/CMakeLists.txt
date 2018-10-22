cmake_minimum_required(VERSION 3.12)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab1 main.cpp Account.h Account.cpp Bank.h Bank.cpp Transaction.h Transaction.cpp utils.h utils.cpp)