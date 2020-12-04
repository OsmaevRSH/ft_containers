#ifndef FT_CONTAINERS_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_
#define FT_CONTAINERS_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_

#include "bidirectional_iterator.hpp"

template<class T>
class Random_access_iterator : public Bidirectional_iterator<T>
{
	public:
		explicit Random_access_iterator(const T *);
		Random_access_iterator(const Random_access_iterator<T> &);
		Random_access_iterator<T> &operator=(const Random_access_iterator<T> &);
		~Random_access_iterator();

		Random_access_iterator &operator-(const int &);
		Random_access_iterator &operator-(const Random_access_iterator<T> &);

		Random_access_iterator &operator+=(const int &);
		Random_access_iterator &operator-=(const int &);

		friend Random_access_iterator &operator+(Random_access_iterator<T> &,
												 const int &);
		friend Random_access_iterator &operator+(const int &,
												 Random_access_iterator<T> &);
		friend bool operator<(const Random_access_iterator<T> &,
							  const Random_access_iterator<T> &);
		friend bool operator>(const Random_access_iterator<T> &,
							  const Random_access_iterator<T> &);
		friend bool operator<=(const Random_access_iterator<T> &,
							   const Random_access_iterator<T> &);
		friend bool operator>=(const Random_access_iterator<T> &,
							   const Random_access_iterator<T> &);
};

template<class T>
Random_access_iterator<T>::Random_access_iterator(const T *c)
	: Bidirectional_iterator<T>(c)
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
	this->m = copy.m;
	return *this;
}

template<class T>
Random_access_iterator<T>::~Random_access_iterator()
{
}

template<class T>
Random_access_iterator<T> &Random_access_iterator<T>::operator-(const int &n)
{
	this->m -= n;
	return *this;
}

template<class T>
Random_access_iterator<T> &Random_access_iterator<
	T>::operator-(const Random_access_iterator<T> &n)
{
	this->m -= n.m;
	return *this;
}

template<class T>
Random_access_iterator<T> &Random_access_iterator<T>::operator+=(const int &n)
{
	this->m += n;
	return *this;
}

template<class T>
Random_access_iterator<T> &Random_access_iterator<T>::operator-=(const int &n)
{
	this->m -= n;
	return *this;
}

template<class T>
bool operator<(const Random_access_iterator<T> &l,
			   const Random_access_iterator<T> &r)
{
	return (l.m < r.m);
}

template<class T>
bool operator>(const Random_access_iterator<T> &l,
			   const Random_access_iterator<T> &r)
{
	return (l.m > r.m);
}

template<class T>
bool operator<=(const Random_access_iterator<T> &l,
				const Random_access_iterator<T> &r)
{
	return (l.m <= r.m);
}

template<class T>
bool operator>=(const Random_access_iterator<T> &l,
				const Random_access_iterator<T> &r)
{
	return (l.m >= r.m);
}
template<class T>
Random_access_iterator<T> &operator+(Random_access_iterator<T> &l, const int &r)
{
	return Random_access_iterator<T>(l.m + r);
}

template<class T>
Random_access_iterator<T> &operator+(const int &l, Random_access_iterator<T> &r)
{
	return Random_access_iterator<T>(r.m + l);
}

#endif
