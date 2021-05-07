#pragma once

#include "Forward_Iterator.hpp"

template<class T>
class Const_Forward_Iterator : Forward_Iterator<T>
{
	public:
		Const_Forward_Iterator() {};
		Const_Forward_Iterator(T *new_ptr);
		Const_Forward_Iterator(const Const_Forward_Iterator<T> &copy);
		Const_Forward_Iterator<T> &operator=(const Const_Forward_Iterator<T> &copy);
		virtual ~Const_Forward_Iterator();

		const T &operator*();
};
template<class T>
Const_Forward_Iterator<T>::Const_Forward_Iterator(T *new_ptr) : Forward_Iterator<T>(new_ptr) {}
template<class T>
Const_Forward_Iterator<T>::Const_Forward_Iterator(const Const_Forward_Iterator<T> &copy) : Forward_Iterator<T>(copy) {}
template<class T>
Const_Forward_Iterator<T> &Const_Forward_Iterator<T>::operator=(const Const_Forward_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Const_Forward_Iterator<T>::~Const_Forward_Iterator() {}
template<class T>
const T &Const_Forward_Iterator<T>::operator*() { return *(this->ptr); }
