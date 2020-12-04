cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers vector/vector_main.cpp vector/vector.hpp input_iterator_tag.hpp base_iterator.hpp)