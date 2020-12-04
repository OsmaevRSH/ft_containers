#ifndef FT_CONTAINERS_ITERATOR_FORWARD_ITERATOR_HPP_
#define FT_CONTAINERS_ITERATOR_FORWARD_ITERATOR_HPP_

#include "base_iterator.hpp"

template<class T>
class Forward_iterator : public Base_iterator<T>
{
	public:
		Forward_iterator();
		Forward_iterator(const Forward_iterator<T> &);
		Forward_iterator<T> &operator=(const Forward_iterator<T> &);
		~Forward_iterator();
};

template<class T>
Forward_iterator<T>::Forward_iterator() : Base_iterator<T>()
{
}

template<class T>
Forward_iterator<T>::Forward_iterator(const Forward_iterator<T> &copy)
	: Base_iterator<T>(copy)
{
}

template<class T>
Forward_iterator<T> &Forward_iterator<T>::operator=(const Forward_iterator<T> &copy)
{
	m = copy.m;
	return *this;
}

template<class T>
Forward_iterator<T>::~Forward_iterator()
{
}
#endif
