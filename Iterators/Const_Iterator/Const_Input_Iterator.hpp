#pragma once

#include "Input_Iterator.hpp"

template<class T>
class Const_Input_Iterator : public Input_Iterator<T>
{
	private:
		Const_Input_Iterator() {};
	public:
		Const_Input_Iterator(const Const_Input_Iterator<T> &copy);
		Const_Input_Iterator<T> &operator=(const Const_Input_Iterator<T> &copy);
		virtual ~Const_Input_Iterator();

		const T &operator*();
};
template<class T>
Const_Input_Iterator<T>::Const_Input_Iterator(const Const_Input_Iterator<T> &copy) : Input_Iterator<T>(copy) {}
template<class T>
Const_Input_Iterator<T> &Const_Input_Iterator<T>::operator=(const Const_Input_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Const_Input_Iterator<T>::~Const_Input_Iterator() {}
template<class T>
const T &Const_Input_Iterator<T>::operator*() { return *(this->ptr); }
