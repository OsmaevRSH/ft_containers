#ifndef FT_CONTAINERS_ITERATOR_BASE_ITERATOR_HPP_
#define FT_CONTAINERS_ITERATOR_BASE_ITERATOR_HPP_

#include <iostream>

template<class T>
class Base_iterator
{
	protected:
		Base_iterator();
		T *m;
	public:
		Base_iterator(const Base_iterator<T> &);
		Base_iterator &operator=(const Base_iterator<T> &);
		virtual ~Base_iterator();

		bool operator==(const Base_iterator<T> &, const Base_iterator<T> &);
		bool operator!=(const Base_iterator<T> &, const Base_iterator<T> &);
		T &operator*();
		T &operator->();
		Base_iterator &operator++();
		const Base_iterator<T> operator++(int);
};

template<class T>
Base_iterator<T>::Base_iterator(const Base_iterator<T> &copy) : m(copy.m)
{
}

template<class T>
Base_iterator<T> &Base_iterator<T>::operator=(const Base_iterator<T> &copy)
{
	m = copy.m;
	return *this;
}

template<class T>
Base_iterator<T>::~Base_iterator()
{
}

template<class T>
bool Base_iterator<T>::operator==(const Base_iterator<T> &l,
								  const Base_iterator<T> &r)
{
	return (l.m == r.m);
}

template<class T>
bool Base_iterator<T>::operator!=(const Base_iterator<T> &l,
								  const Base_iterator<T> &r)
{
	return (l.m != r.m);
}

template<class T>
T &Base_iterator<T>::operator*()
{
	return *m;
}

template<class T>
T &Base_iterator<T>::operator->()
{
	return *m;
}

template<class T>
Base_iterator<T> &Base_iterator<T>::operator++()
{
	++m;
	return *this;
}

template<class T>
const Base_iterator<T> Base_iterator<T>::operator++(int)
{
	Base_iterator<T> tmp(*this);
	++m;
	return tmp;
}

template<class T>
Base_iterator<T>::Base_iterator()
{
}

#endif
