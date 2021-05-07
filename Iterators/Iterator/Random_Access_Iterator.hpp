#pragma once

#include "Bidirectional_Iterator.hpp"

template<class T>
class Random_Access_Iterator : public Bidirectional_Iterator<T>
{
	public:
		Random_Access_Iterator() {};
		Random_Access_Iterator(T *new_ptr);
		Random_Access_Iterator(const Random_Access_Iterator<T> &copy);
		Random_Access_Iterator<T> &operator=(const Random_Access_Iterator<T> &copy);
		virtual ~Random_Access_Iterator();

		bool operator<(const Random_Access_Iterator<T> &iterator);
		bool operator>(const Random_Access_Iterator<T> &iterator);
		bool operator<=(const Random_Access_Iterator<T> &iterator);
		bool operator>=(const Random_Access_Iterator<T> &iterator);
		Random_Access_Iterator<T> operator+(size_type n);
		Random_Access_Iterator<T> operator+(size_type n, Random_Access_Iterator<T> &rhs);
		Random_Access_Iterator<T> operator-(size_type n);
		Random_Access_Iterator<T> operator-(Random_Access_Iterator<T> &rhs);
		Random_Access_Iterator<T> &operator+=(size_type n);
		Random_Access_Iterator<T> &operator-=(size_type n);
		virtual T &operator[](size_type n);
};
template<class T>
Random_Access_Iterator<T>::Random_Access_Iterator(T *new_ptr):Bidirectional_Iterator<T>(new_ptr) {}
template<class T>
Random_Access_Iterator<T>::Random_Access_Iterator(const Random_Access_Iterator<T> &copy) : Bidirectional_Iterator<T>(copy) {}
template<class T>
Random_Access_Iterator<T> &Random_Access_Iterator<T>::operator=(const Random_Access_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Random_Access_Iterator<T>::~Random_Access_Iterator() {}
template<class T>
bool Random_Access_Iterator<T>::operator<(const Random_Access_Iterator<T> &iterator)
{
	return this->ptr < iterator.ptr;
}
template<class T>
bool Random_Access_Iterator<T>::operator>(const Random_Access_Iterator<T> &iterator)
{
	return this->ptr > iterator.ptr;
}
template<class T>
bool Random_Access_Iterator<T>::operator<=(const Random_Access_Iterator<T> &iterator)
{
	return this->ptr <= iterator.ptr;
}
template<class T>
bool Random_Access_Iterator<T>::operator>=(const Random_Access_Iterator<T> &iterator)
{
	return this->ptr >= iterator.ptr;
}
template<class T>
Random_Access_Iterator<T> Random_Access_Iterator<T>::operator+(size_type n)
{
	Random_Access_Iterator<T> tmp(*this);
	tmp.ptr += n;
	return tmp;
}
template<class T>
Random_Access_Iterator<T> Random_Access_Iterator<T>::operator+(size_type n, Random_Access_Iterator<T> &rhs)
{
	Random_Access_Iterator<T> tmp(rhs);
	tmp.ptr += n;
	return tmp;
}
template<class T>
Random_Access_Iterator<T> Random_Access_Iterator<T>::operator-(size_type n)
{
	Random_Access_Iterator<T> tmp(*this);
	tmp.ptr -= n;
	return tmp;
}
template<class T>
Random_Access_Iterator<T> Random_Access_Iterator<T>::operator-(Random_Access_Iterator<T> &rhs)
{
	Random_Access_Iterator<T> tmp(*this);
	tmp.ptr -= rhs.ptr;
	return tmp;
}
template<class T>
Random_Access_Iterator<T> &Random_Access_Iterator<T>::operator+=(size_type n)
{
	this->ptr += n;
	return *this;
}
template<class T>
Random_Access_Iterator<T> &Random_Access_Iterator<T>::operator-=(size_type n)
{
	this->ptr -= n;
	return *this;
}
template<class T>
T &Random_Access_Iterator<T>::operator[](size_type n)
{
	return *(this->ptr + n);
}
