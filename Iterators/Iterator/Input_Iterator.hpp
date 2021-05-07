#pragma once

#include <iostream>

template<class T>
class Input_Iterator
{
	private:
		Input_Iterator() {};
	protected:
		T *ptr;
	public:
		Input_Iterator(const Input_Iterator<T> &copy);
		Input_Iterator<T> &operator=(const Input_Iterator<T> &copy);
		virtual ~Input_Iterator();

		bool operator==(const Input_Iterator<T> &iterator);
		bool operator!=(const Input_Iterator<T> &iterator);
		Input_Iterator<T> &operator++();
		Input_Iterator<T> operator++(int);
		virtual T &operator*();
		T *operator->();

};

template<class T>
Input_Iterator<T>::Input_Iterator(const Input_Iterator<T> &copy) : ptr(copy.ptr) {}
template<class T>
Input_Iterator<T> &Input_Iterator<T>::operator=(const Input_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Input_Iterator<T>::~Input_Iterator() {}
template<class T>
bool Input_Iterator<T>::operator==(const Input_Iterator<T> &iterator) { return this->ptr == iterator.ptr; }
template<class T>
bool Input_Iterator<T>::operator!=(const Input_Iterator<T> &iterator) { return this->ptr != iterator.ptr; }
template<class T>
Input_Iterator<T> &Input_Iterator<T>::operator++()
{
	++ptr;
	return *this;
}
template<class T>
Input_Iterator<T> Input_Iterator<T>::operator++(int)
{
	Input_Iterator<T> copy(*this);
	++ptr;
	return copy;
}
template<class T>
T &Input_Iterator<T>::operator*() { return *(this->ptr); }
template<class T>
T *Input_Iterator<T>::operator->() { return this->ptr; }