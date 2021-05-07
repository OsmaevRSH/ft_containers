cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers
        vector/vector_main.cpp
        vector/vector.hpp
        test.hpp
        Iterators/Iterator/Input_Iterator.hpp Iterators/Const_Iterator/Const_Input_Iterator.hpp Iterators/Reverse_Iterator/Reverse_Input_Iterator.hpp Iterators/Const_Reverse_Iterator/Const_Reverse_Input_Iterator.hpp Iterators/Iterator/Forward_Iterator.hpp Iterators/Const_Iterator/Const_Forward_Iterator.hpp Iterators/Reverse_Iterator/Reverse_Forward_Iterator.hpp Iterators/Const_Reverse_Iterator/Const_Reverse_Forward_Iterator.hpp Iterators/Iterator/Bidirectional_Iterator.hpp Iterators/Const_Iterator/Const_Bidirectional_Iterator.hpp Iterators/Reverse_Iterator/Reverse_Bidirectional_Iterator.hpp Iterators/Const_Reverse_Iterator/Const_Reverse_Bidirectional_Iterator.hpp Iterators/Iterator/Random_Access_Iterator.hpp Iterators/Const_Iterator/Const_Random_Access_Iterator.hpp Iterators/Reverse_Iterator/Reverse_Random_Access_Iterator.hpp Iterators/Const_Reverse_Iterator/Const_Reverse_Random_Access_Iterator.hpp vector/vector_iterator.hpp)

include_directories(vector)
include_directories(Iterators/Iterator)
include_directories(Iterators/Const_Iterator)
include_directories(Iterators/Reverse_Iterator)
include_directories(Iterators/Const_Reverse_Iterator)