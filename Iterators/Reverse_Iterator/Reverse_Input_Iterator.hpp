#pragma once

#include <iostream>

template<class T>
class Reverse_Input_Iterator
{
	private:
		Reverse_Input_Iterator() {};
	protected:
		T *ptr;
	public:
		Reverse_Input_Iterator(const Reverse_Input_Iterator<T> &copy);
		Reverse_Input_Iterator<T> &operator=(const Reverse_Input_Iterator<T> &copy);
		virtual ~Reverse_Input_Iterator();

		bool operator==(const Reverse_Input_Iterator<T> &iterator);
		bool operator!=(const Reverse_Input_Iterator<T> &iterator);
		Reverse_Input_Iterator<T> &operator++();
		Reverse_Input_Iterator<T> operator++(int);
		virtual T &operator*();
		T *operator->();

};

template<class T>
Reverse_Input_Iterator<T>::Reverse_Input_Iterator(const Reverse_Input_Iterator<T> &copy) : ptr(copy.ptr) {}
template<class T>
Reverse_Input_Iterator<T> &Reverse_Input_Iterator<T>::operator=(const Reverse_Input_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Reverse_Input_Iterator<T>::~Reverse_Input_Iterator() {}
template<class T>
bool Reverse_Input_Iterator<T>::operator==(const Reverse_Input_Iterator<T> &iterator) { return this->ptr == iterator.ptr; }
template<class T>
bool Reverse_Input_Iterator<T>::operator!=(const Reverse_Input_Iterator<T> &iterator) { return this->ptr != iterator.ptr; }
template<class T>
Reverse_Input_Iterator<T> &Reverse_Input_Iterator<T>::operator++()
{
	--ptr;
	return *this;
}
template<class T>
Reverse_Input_Iterator<T> Reverse_Input_Iterator<T>::operator++(int)
{
	Reverse_Input_Iterator<T> copy(*this);
	--ptr;
	return copy;
}
template<class T>
T &Reverse_Input_Iterator<T>::operator*() { return *(this->ptr); }
template<class T>
T *Reverse_Input_Iterator<T>::operator->() { return this->ptr; }
