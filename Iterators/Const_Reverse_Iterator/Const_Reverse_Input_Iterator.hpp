#pragma once

#include "Reverse_Input_Iterator.hpp"

template<class T>
class Const_Reverse_Input_Iterator : public Reverse_Input_Iterator<T>
{
	private:
		Const_Reverse_Input_Iterator() {};
	public:
		Const_Reverse_Input_Iterator(const Const_Reverse_Input_Iterator<T> &copy);
		Const_Reverse_Input_Iterator<T> &operator=(const Const_Reverse_Input_Iterator<T> &copy);
		virtual ~Const_Reverse_Input_Iterator();

		const T &operator*();
};
template<class T>
Const_Reverse_Input_Iterator<T>::Const_Reverse_Input_Iterator(const Const_Reverse_Input_Iterator<T> &copy)
		: Reverse_Input_Iterator<T>(copy) {}
template<class T>
Const_Reverse_Input_Iterator<T> &Const_Reverse_Input_Iterator<T>::operator=(const Const_Reverse_Input_Iterator<T> &copy)
{
	if (*this != copy)
		this->ptr = copy.ptr;
	return *this;
}
template<class T>
Const_Reverse_Input_Iterator<T>::~Const_Reverse_Input_Iterator() {}
template<class T>
const T &Const_Reverse_Input_Iterator<T>::operator*() { return *(this->ptr); }