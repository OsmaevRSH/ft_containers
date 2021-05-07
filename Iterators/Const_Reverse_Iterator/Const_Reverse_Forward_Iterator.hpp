#pragma once

#include "Reverse_Forward_Iterator.hpp"

template<class T>
class Const_Reverse_Forward_Iterator : public Reverse_Forward_Iterator<T>
{
	public:
		Const_Reverse_Forward_Iterator() {};
		explicit Const_Reverse_Forward_Iterator(T *new_ptr);
		Const_Reverse_Forward_Iterator(const Const_Reverse_Forward_Iterator<T> &copy);
		Const_Reverse_Forward_Iterator<T> &operator=(const Const_Reverse_Forward_Iterator<T> &copy);
		virtual ~Const_Reverse_Forward_Iterator();

		const T &operator*();
};
template<class T>
Const_Reverse_Forward_Iterator<T>::Const_Reverse_Forward_Iterator(T *new_ptr) { this->ptr = new_ptr; }
template<class T>
Const_Reverse_Forward_Iterator<T>::Const_Reverse_Forward_Iterator(const Const_Reverse_Forward_Iterator<T> &copy)
		: Reverse_Forward_Iterator<T>(copy) {}
template<class T>
Const_Reverse_Forward_Iterator<T> &Const_Reverse_Forward_Iterator<T>::operator=(const Const_Reverse_Forward_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Const_Reverse_Forward_Iterator<T>::~Const_Reverse_Forward_Iterator() {}
template<class T>
const T &Const_Reverse_Forward_Iterator<T>::operator*() { return *(this->ptr); }

