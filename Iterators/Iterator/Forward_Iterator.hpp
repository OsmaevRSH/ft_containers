#pragma once

#include "Input_Iterator.hpp"

template<class T>
class Forward_Iterator : public Input_Iterator<T>
{
	public:
		Forward_Iterator() {};
		explicit Forward_Iterator(T *new_ptr);
		Forward_Iterator(const Forward_Iterator<T> &copy);
		Forward_Iterator<T> &operator=(const Forward_Iterator<T> &copy);
		virtual ~Forward_Iterator();
};
template<class T>
Forward_Iterator<T>::Forward_Iterator(T *new_ptr) { this->ptr = new_ptr; }
template<class T>
Forward_Iterator<T>::Forward_Iterator(const Forward_Iterator<T> &copy) : Input_Iterator<T>(copy) {}
template<class T>
Forward_Iterator<T> &Forward_Iterator<T>::operator=(const Forward_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Forward_Iterator<T>::~Forward_Iterator() {}

