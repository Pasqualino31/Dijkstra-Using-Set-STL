cmake_minimum_required(VERSION 3.9)
project(Dijkstra_master)

set(CMAKE_CXX_STANDARD 11)

add_executable(Dijkstra_master
        main.cpp Graph.h Graph.cpp)
set(QMAKE_CXXFLAGS "-std=c++11" -Wall -Werror -pedantic )