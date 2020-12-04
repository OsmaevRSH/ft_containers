cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers vector/vector_main.cpp vector/vector.hpp iterator/base_iterator.hpp iterator/forward_iterator.hpp iterator/bidirectional_iterator.hpp iterator/random_access_iterator.hpp)