cmake_minimum_required(VERSION 2.8)

project(MLStone)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g")

add_executable(MLStone main.cpp card.cpp)
