#ifndef FT_CONTAINERS_ITERATOR_BIDIRECTIONAL_ITERATOR_HPP_
#define FT_CONTAINERS_ITERATOR_BIDIRECTIONAL_ITERATOR_HPP_

#include "forward_iterator.hpp"

template<class T>
class Bidirectional_iterator : public Forward_iterator<T>
{
	public:
		Bidirectional_iterator();
		Bidirectional_iterator(const Bidirectional_iterator<T> &);
		Bidirectional_iterator<T> &operator=(const Bidirectional_iterator<T> &);
		~Bidirectional_iterator();

		Bidirectional_iterator &operator--();
		const Bidirectional_iterator<T> operator--(int);
};

template<class T>
Bidirectional_iterator<T>::Bidirectional_iterator() : Forward_iterator<T>()
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
	m = copy.m;
	return *this;
}

template<class T>
Bidirectional_iterator<T>::~Bidirectional_iterator()
{
}

template<class T>
Bidirectional_iterator &Bidirectional_iterator<T>::operator--()
{
	--m;
	return *this;
}

template<class T>
const Bidirectional_iterator<T> Bidirectional_iterator<T>::operator--(int)
{
	Bidirectional_iterator<T> tmp(*this);
	--m;
	return tmp;
}

#endif
