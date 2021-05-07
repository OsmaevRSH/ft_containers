#pragma once

#include "Bidirectional_Iterator.hpp"

template<class T>
class Const_Bidirectional_Iterator : Bidirectional_Iterator<T>
{
	public:
		Const_Bidirectional_Iterator() {};
		explicit Const_Bidirectional_Iterator(T *new_ptr);
		Const_Bidirectional_Iterator(const Const_Bidirectional_Iterator<T> &copy);
		Const_Bidirectional_Iterator<T> &operator=(const Const_Bidirectional_Iterator<T> &copy);
		virtual ~Const_Bidirectional_Iterator();

		const T &operator*();
};
template<class T>
Const_Bidirectional_Iterator<T>::Const_Bidirectional_Iterator(T *new_ptr):Bidirectional_Iterator<T>(new_ptr) {}
template<class T>
Const_Bidirectional_Iterator<T>::Const_Bidirectional_Iterator(const Const_Bidirectional_Iterator<T> &copy)
		: Bidirectional_Iterator<T>(copy) {}
template<class T>
Const_Bidirectional_Iterator<T> &Const_Bidirectional_Iterator<T>::operator=(const Const_Bidirectional_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Const_Bidirectional_Iterator<T>::~Const_Bidirectional_Iterator() = default;
template<class T>
const T &Const_Bidirectional_Iterator<T>::operator*() { return *(this->ptr); }
