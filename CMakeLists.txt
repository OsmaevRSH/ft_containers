cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(
        ft_containers
        vector/Test/vector_main.cpp
        vector/Container/vector.hpp
        vector/Iterator/Iterator.hpp)


include_directories(./)
include_directories(vector)
include_directories(vector/Iterator)
include_directories(vector/Container)