cmake_minimum_required(VERSION 3.25)
project(CppBacktest)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppBacktest main.cpp sharpe_long_only.h sharpe_long_only.cpp)

file(COPY IGE.csv DESTINATION ${CMAKE_BINARY_DIR})