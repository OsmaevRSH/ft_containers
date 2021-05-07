#pragma once

#include "Reverse_Bidirectional_Iterator.hpp"

template<class T>
class Reverse_Random_Access_Iterator : public Reverse_Bidirectional_Iterator<T>
{
	public:
		Reverse_Random_Access_Iterator() {};
		explicit Reverse_Random_Access_Iterator(T *new_ptr);
		Reverse_Random_Access_Iterator(const Reverse_Random_Access_Iterator<T> &copy);
		Reverse_Random_Access_Iterator<T> &operator=(const Reverse_Random_Access_Iterator<T> &copy);
		virtual ~Reverse_Random_Access_Iterator();

		bool operator<(const Reverse_Random_Access_Iterator<T> &iterator);
		bool operator>(const Reverse_Random_Access_Iterator<T> &iterator);
		bool operator<=(const Reverse_Random_Access_Iterator<T> &iterator);
		bool operator>=(const Reverse_Random_Access_Iterator<T> &iterator);
		Reverse_Random_Access_Iterator<T> operator+(size_t n);
		friend Reverse_Random_Access_Iterator<T> operator+(size_t n, Reverse_Random_Access_Iterator<T> &rhs);
		Reverse_Random_Access_Iterator<T> operator-(size_t n);
		Reverse_Random_Access_Iterator<T> operator-(Reverse_Random_Access_Iterator<T> &rhs);
		Reverse_Random_Access_Iterator<T> &operator+=(size_t n);
		Reverse_Random_Access_Iterator<T> &operator-=(size_t n);
		virtual T &operator[](size_t n);
};
template<class T>
Reverse_Random_Access_Iterator<T>::Reverse_Random_Access_Iterator(T *new_ptr):Reverse_Bidirectional_Iterator<T>(new_ptr) {}
template<class T>
Reverse_Random_Access_Iterator<T>::Reverse_Random_Access_Iterator(const Reverse_Random_Access_Iterator<T> &copy) : Reverse_Bidirectional_Iterator<T>(copy) {}
template<class T>
Reverse_Random_Access_Iterator<T> &Reverse_Random_Access_Iterator<T>::operator=(const Reverse_Random_Access_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Reverse_Random_Access_Iterator<T>::~Reverse_Random_Access_Iterator() {}
template<class T>
bool Reverse_Random_Access_Iterator<T>::operator<(const Reverse_Random_Access_Iterator<T> &iterator)
{
	return this->ptr >iterator.ptr;
}
template<class T>
bool Reverse_Random_Access_Iterator<T>::operator>(const Reverse_Random_Access_Iterator<T> &iterator)
{
	return this->ptr < iterator.ptr;
}
template<class T>
bool Reverse_Random_Access_Iterator<T>::operator<=(const Reverse_Random_Access_Iterator<T> &iterator)
{
	return this->ptr >= iterator.ptr;
}
template<class T>
bool Reverse_Random_Access_Iterator<T>::operator>=(const Reverse_Random_Access_Iterator<T> &iterator)
{
	return this->ptr <= iterator.ptr;
}
template<class T>
Reverse_Random_Access_Iterator<T> Reverse_Random_Access_Iterator<T>::operator+(size_t n)
{
	Reverse_Random_Access_Iterator<T> tmp(*this);
	tmp.ptr -= n;
	return tmp;
}
template<class T>
Reverse_Random_Access_Iterator<T> operator+(size_t n, Reverse_Random_Access_Iterator<T> &rhs)
{
	Reverse_Random_Access_Iterator<T> tmp(rhs);
	tmp.ptr -= n;
	return tmp;
}
template<class T>
Reverse_Random_Access_Iterator<T> Reverse_Random_Access_Iterator<T>::operator-(size_t n)
{
	Reverse_Random_Access_Iterator<T> tmp(*this);
	tmp.ptr += n;
	return tmp;
}
template<class T>
Reverse_Random_Access_Iterator<T> Reverse_Random_Access_Iterator<T>::operator-(Reverse_Random_Access_Iterator<T> &rhs)
{
	Reverse_Random_Access_Iterator<T> tmp(*this);
	tmp.ptr += rhs.ptr;
	return tmp;
}
template<class T>
Reverse_Random_Access_Iterator<T> &Reverse_Random_Access_Iterator<T>::operator+=(size_t n)
{
	this->ptr -= n;
	return *this;
}
template<class T>
Reverse_Random_Access_Iterator<T> &Reverse_Random_Access_Iterator<T>::operator-=(size_t n)
{
	this->ptr += n;
	return *this;
}
template<class T>
T &Reverse_Random_Access_Iterator<T>::operator[](size_t n)
{
	return *(this->ptr - n);
}
