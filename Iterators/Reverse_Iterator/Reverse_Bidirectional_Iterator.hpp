#pragma once

#include "Reverse_Forward_Iterator.hpp"

template<class T>

class Reverse_Bidirectional_Iterator : public Reverse_Forward_Iterator<T>
{
	public:
		Reverse_Bidirectional_Iterator() {};
		Reverse_Bidirectional_Iterator(T *new_ptr);
		Reverse_Bidirectional_Iterator(const Reverse_Bidirectional_Iterator<T> &copy);
		Reverse_Bidirectional_Iterator<T> &operator=(const Reverse_Bidirectional_Iterator<T> &copy);
		virtual ~Reverse_Bidirectional_Iterator();

		Reverse_Bidirectional_Iterator<T> &operator--();
		Reverse_Bidirectional_Iterator<T> operator--(int);
};
template<class T>
Reverse_Bidirectional_Iterator<T>::Reverse_Bidirectional_Iterator(T *new_ptr):Reverse_Forward_Iterator<T>(new_ptr) {}
template<class T>
Reverse_Bidirectional_Iterator<T>::Reverse_Bidirectional_Iterator(const Reverse_Bidirectional_Iterator<T> &copy) : Reverse_Forward_Iterator<T>(copy) {}
template<class T>
Reverse_Bidirectional_Iterator<T> &Reverse_Bidirectional_Iterator<T>::operator=(const Reverse_Bidirectional_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Reverse_Bidirectional_Iterator<T>::~Reverse_Bidirectional_Iterator(){}
template<class T>
Reverse_Bidirectional_Iterator<T> &Reverse_Bidirectional_Iterator<T>::operator--()
{
	++ptr;
	return *this;
}
template<class T>
Reverse_Bidirectional_Iterator<T> Reverse_Bidirectional_Iterator<T>::operator--(int)
{
	Reverse_Bidirectional_Iterator<T> copy(*this);
	++ptr;
	return copy;
}


