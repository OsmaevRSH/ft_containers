#ifndef FT_CONTAINERS_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_
#define FT_CONTAINERS_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_

#include "forward_iterator.hpp"

template<class T>
class Random_access_iterator : public Forward_iterator<T>
{
	public:
		Random_access_iterator();
		Random_access_iterator(const Random_access_iterator<T> &);
		Random_access_iterator<T> &operator=(const Random_access_iterator<T> &);
		~Random_access_iterator();

		Random_access_iterator &operator+(const int &);
		Random_access_iterator &operator+(const int &,
										  Random_access_iterator<T> &);
		Random_access_iterator &operator-(const int &);
		Random_access_iterator &operator-(const Random_access_iterator<T> &);

		Random_access_iterator &operator+=(const int &);
		Random_access_iterator &operator-=(const int &);

		bool operator<(const Random_access_iterator<T> &,
					   const Random_access_iterator<T> &);
		bool operator>(const Random_access_iterator<T> &,
					   const Random_access_iterator<T> &);
		bool operator<=(const Random_access_iterator<T> &,
						const Random_access_iterator<T> &);
		bool operator>=(const Random_access_iterator<T> &,
						const Random_access_iterator<T> &);
};

template<class T>
Random_access_iterator<T>::Random_access_iterator() : Forward_iterator<T>()
{
}

template<class T>
Random_access_iterator<T>::Random_access_iterator(const Random_access_iterator<
	T> &copy) : Forward_iterator<T>(copy)
{
}

template<class T>
Random_access_iterator<T> &Random_access_iterator<
	T>::operator=(const Random_access_iterator<T> &copy)
{
	m = copy.m;
	return *this;
}

template<class T>
Random_access_iterator<T>::~Random_access_iterator()
{
}

template<class T>
Random_access_iterator &Random_access_iterator<T>::operator+(const int &n)
{
	m += n;
	return *this;
}

template<class T>
Random_access_iterator &Random_access_iterator<T>::operator+(
	const int &r, Random_access_iterator<T> &l)
{
	m += n;
	return *this;
}

template<class T>
Random_access_iterator &Random_access_iterator<T>::operator-(const int &n)
{
	m -= n;
	return *this;
}

template<class T>
Random_access_iterator &Random_access_iterator<
	T>::operator-(const Random_access_iterator<T> &n)
{
	m -= n.m;
	return *this;
}

template<class T>
Random_access_iterator &Random_access_iterator<T>::operator+=(const int &n)
{
	m += n;
	return *this;
}

template<class T>
Random_access_iterator &Random_access_iterator<T>::operator-=(const int &n)
{
	m -= n;
	return *this;
}

template<class T>
bool Random_access_iterator<T>::operator<(const Random_access_iterator<T> &l,
										  const Random_access_iterator<T> &r)
{
	return (l.m < r.m);
}

template<class T>
bool Random_access_iterator<T>::operator>(const Random_access_iterator<T> &l,
										  const Random_access_iterator<T> &r)
{
	return (l.m > r.m);
}

template<class T>
bool Random_access_iterator<T>::operator<=(const Random_access_iterator<T> &l,
										   const Random_access_iterator<T> &r)
{
	return (l.m <= r.m);
}

template<class T>
bool Random_access_iterator<T>::operator>=(const Random_access_iterator<T> &l,
										   const Random_access_iterator<T> &r)
{
	return (l.m >= r.m);
}

#endif
