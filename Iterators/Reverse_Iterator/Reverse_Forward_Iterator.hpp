#pragma once

#include "Reverse_Input_Iterator.hpp"

template<class T>
class Reverse_Forward_Iterator : public Reverse_Input_Iterator<T>
{
	public:
		Reverse_Forward_Iterator() {};
		Reverse_Forward_Iterator(T *new_ptr);
		Reverse_Forward_Iterator(const Reverse_Forward_Iterator<T> &copy);
		Reverse_Forward_Iterator<T> &operator=(const Reverse_Forward_Iterator<T> &copy);
		virtual ~Reverse_Forward_Iterator();
};
template<class T>
Reverse_Forward_Iterator<T>::Reverse_Forward_Iterator(T *new_ptr) { this->ptr = new_ptr; }
template<class T>
Reverse_Forward_Iterator<T>::Reverse_Forward_Iterator(const Reverse_Forward_Iterator<T> &copy) : Reverse_Input_Iterator<T>(copy) {}
template<class T>
Reverse_Forward_Iterator<T> &Reverse_Forward_Iterator<T>::operator=(const Reverse_Forward_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Reverse_Forward_Iterator<T>::~Reverse_Forward_Iterator() {}
