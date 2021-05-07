#pragma once

#include "Random_Access_Iterator.hpp"

template<class T>
class Const_Random_Access_Iterator : Random_Access_Iterator<T>
{
	public:
		Const_Random_Access_Iterator() {};
		Const_Random_Access_Iterator(T *new_ptr);
		Const_Random_Access_Iterator(const Const_Random_Access_Iterator<T> &copy);
		Const_Random_Access_Iterator<T> &operator=(const Const_Random_Access_Iterator<T> &copy);
		virtual ~Const_Random_Access_Iterator();

		const T &operator*();
		const T &operator[](size_type n);
};
template<class T>
Const_Random_Access_Iterator<T>::Const_Random_Access_Iterator(T *new_ptr):Random_Access_Iterator<T>(new_ptr) {}
template<class T>
Const_Random_Access_Iterator<T>::Const_Random_Access_Iterator(const Const_Random_Access_Iterator<T> &copy)
		: Random_Access_Iterator<T>(copy) {}
template<class T>
Const_Random_Access_Iterator<T> &Const_Random_Access_Iterator<T>::operator=(const Const_Random_Access_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Const_Random_Access_Iterator<T>::~Const_Random_Access_Iterator() {}
template<class T>
const T &Const_Random_Access_Iterator<T>::operator*() { return *(this->ptr); }
template<class T>
const T &Const_Random_Access_Iterator<T>::operator[](size_type n)
{
	return *(this->ptr + n);
}
