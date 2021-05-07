#pragma once

#include "Reverse_Random_Access_Iterator.hpp"

template<class T>
class Const_Reverse_Random_Access_Iterator : Reverse_Random_Access_Iterator<T>
{
	public:
		Const_Reverse_Random_Access_Iterator() {};
		explicit Const_Reverse_Random_Access_Iterator(T *new_ptr);
		Const_Reverse_Random_Access_Iterator(const Const_Reverse_Random_Access_Iterator<T> &copy);
		Const_Reverse_Random_Access_Iterator<T> &operator=(const Const_Reverse_Random_Access_Iterator<T> &copy);
		virtual ~Const_Reverse_Random_Access_Iterator();

		const T &operator*();
		const T &operator[](size_t n);
};
template<class T>
Const_Reverse_Random_Access_Iterator<T>::Const_Reverse_Random_Access_Iterator(T *new_ptr):Reverse_Random_Access_Iterator<T>(new_ptr) {}
template<class T>
Const_Reverse_Random_Access_Iterator<T>::Const_Reverse_Random_Access_Iterator(const Const_Reverse_Random_Access_Iterator<T> &copy)
		: Reverse_Random_Access_Iterator<T>(copy) {}
template<class T>
Const_Reverse_Random_Access_Iterator<T> &Const_Reverse_Random_Access_Iterator<T>::operator=(const Const_Reverse_Random_Access_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Const_Reverse_Random_Access_Iterator<T>::~Const_Reverse_Random_Access_Iterator() {}
template<class T>
const T &Const_Reverse_Random_Access_Iterator<T>::operator*() { return *(this->ptr); }
template<class T>
const T &Const_Reverse_Random_Access_Iterator<T>::operator[](size_t n)
{
	return *(this->ptr + n);
}
