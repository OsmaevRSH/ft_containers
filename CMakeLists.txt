cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(
        ft_containers
        Test/tests.cpp
        Container/vector.hpp
        Container/list.hpp
        Test/test_color.hpp
        Container/stack.hpp
        Container/queue.hpp
        Container/map.hpp)


include_directories(./)
include_directories(vector)
include_directories(Iterator)
include_directories(Container)