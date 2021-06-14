cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(
        ft_containers
        Test/vector_main.cpp
        Container/vector.hpp
        Iterator/Vector_Iterator.hpp
        Container/list.hpp
        Test/test.cpp)


include_directories(./)
include_directories(vector)
include_directories(Iterator)
include_directories(Container)