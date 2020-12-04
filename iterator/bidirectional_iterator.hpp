#ifndef FT_CONTAINERS_ITERATOR_BIDIRECTIONAL_ITERATOR_HPP_
#define FT_CONTAINERS_ITERATOR_BIDIRECTIONAL_ITERATOR_HPP_

#include "forward_iterator.hpp"

template<class T>
class Bidirectional_iterator : public Forward_iterator<T>
{
	public:
		explicit Bidirectional_iterator(const T *);
		Bidirectional_iterator(const Bidirectional_iterator<T> &);
		Bidirectional_iterator<T> &operator=(const Bidirectional_iterator<T> &);
		~Bidirectional_iterator();

		Bidirectional_iterator &operator--();
		const Bidirectional_iterator<T> operator--(int);
};

template<class T>
Bidirectional_iterator<T>::Bidirectional_iterator(const T *c)
	: Forward_iterator<T>(c)
{
}

template<class T>
Bidirectional_iterator<T>::Bidirectional_iterator(const Bidirectional_iterator<
	T> &copy) : Forward_iterator<T>(copy)
{
}

template<class T>
Bidirectional_iterator<T> &Bidirectional_iterator<
	T>::operator=(const Bidirectional_iterator<T> &copy)
{
	this->m = copy.m;
	return *this;
}

template<class T>
Bidirectional_iterator<T>::~Bidirectional_iterator()
{
}

template<class T>
Bidirectional_iterator<T> &Bidirectional_iterator<T>::operator--()
{
	--this->m;
	return *this;
}

template<class T>
const Bidirectional_iterator<T> Bidirectional_iterator<T>::operator--(int)
{
	Bidirectional_iterator<T> tmp(*this);
	--this->m;
	return tmp;
}

#endif
