#pragma once

#include "Reverse_Bidirectional_Iterator.hpp"

template<class T>
class Const_Reverse_Bidirectional_Iterator : Reverse_Bidirectional_Iterator<T>
{
	public:
		Const_Reverse_Bidirectional_Iterator() {};
		Const_Reverse_Bidirectional_Iterator(T *new_ptr);
		Const_Reverse_Bidirectional_Iterator(const Const_Reverse_Bidirectional_Iterator<T> &copy);
		Const_Reverse_Bidirectional_Iterator<T> &operator=(const Const_Reverse_Bidirectional_Iterator<T> &copy);
		virtual ~Const_Reverse_Bidirectional_Iterator();

		const T &operator*();
};
template<class T>
Const_Reverse_Bidirectional_Iterator<T>::Const_Reverse_Bidirectional_Iterator(T *new_ptr):Reverse_Bidirectional_Iterator<T>(new_ptr) {}
template<class T>
Const_Reverse_Bidirectional_Iterator<T>::Const_Reverse_Bidirectional_Iterator(const Const_Reverse_Bidirectional_Iterator<T> &copy)
		: Reverse_Bidirectional_Iterator<T>(copy) {}
template<class T>
Const_Reverse_Bidirectional_Iterator<T> &Const_Reverse_Bidirectional_Iterator<T>::operator=(const Const_Reverse_Bidirectional_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Const_Reverse_Bidirectional_Iterator<T>::~Const_Reverse_Bidirectional_Iterator() {}
template<class T>
const T &Const_Reverse_Bidirectional_Iterator<T>::operator*() { return *(this->ptr); }
