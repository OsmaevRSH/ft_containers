#pragma once

#include "Forward_Iterator.hpp"

template<class T>

class Bidirectional_Iterator : public Forward_Iterator<T>
{
	public:
		Bidirectional_Iterator() {};
		explicit Bidirectional_Iterator(T *new_ptr);
		Bidirectional_Iterator(const Bidirectional_Iterator<T> &copy);
		Bidirectional_Iterator<T> &operator=(const Bidirectional_Iterator<T> &copy);
		virtual ~Bidirectional_Iterator();

		Bidirectional_Iterator<T> &operator--();
		Bidirectional_Iterator<T> operator--(int);
};
template<class T>
Bidirectional_Iterator<T>::Bidirectional_Iterator(T *new_ptr):Forward_Iterator<T>(new_ptr) {}
template<class T>
Bidirectional_Iterator<T>::Bidirectional_Iterator(const Bidirectional_Iterator<T> &copy) : Forward_Iterator<T>(copy) {}
template<class T>
Bidirectional_Iterator<T> &Bidirectional_Iterator<T>::operator=(const Bidirectional_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Bidirectional_Iterator<T>::~Bidirectional_Iterator(){}
template<class T>
Bidirectional_Iterator<T> &Bidirectional_Iterator<T>::operator--()
{
	--(this->ptr);
	return *this;
}
template<class T>
Bidirectional_Iterator<T> Bidirectional_Iterator<T>::operator--(int)
{
	Bidirectional_Iterator<T> copy(*this);
	--(this->ptr);
	return copy;
}


