cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers vector/vector_main.cpp vector/vector.hpp test.hpp Iterators/Base_Iterators/Iterator.hpp Iterators/Base_Iterators/Input.hpp Iterators/IteratorTests.cpp Iterators/Base_Iterators/Forward.hpp Iterators/Base_Iterators/Bidirectional.hpp Iterators/Base_Iterators/Random_Access.hpp Iterators/Const_Iterators/Const_Bidirectional.hpp vector/Vector_Iterator.hpp)
include_directories(Iterators/Base_Iterators)
include_directories(Iterators/Const_Iterators)