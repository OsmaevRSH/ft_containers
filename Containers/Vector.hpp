#ifndef CONTAINERS_CONTAINERS_VECTOR_HPP_
#define CONTAINERS_CONTAINERS_VECTOR_HPP_

#include <iostream>

namespace ft
{
	template<class T>
	class vector
	{
		private:
			typename T *ptr;
			size_t vector_len;
		public:
			explicit vector();
			explicit vector(size_t n, const T &val = value_type());
			template<class InputIterator>
			vector(InputIterator first, InputIterator last);
			vector (const vector& x);
	};

	template<class T>
	vector<T>::vector() : vector_len(0)
	{
		ptr = new T[0];
	}

	template<class T>
	vector<T>::vector(size_t n, const T &val) : vector_len(n)
	{
		ptr = new T[n];
		for (int i = 0; i < n; ++i)
			ptr[i] = val;
	}

	template<class T>
	template<class InputIterator>
	vector<T>::vector(InputIterator first, InputIterator last)
	{
		size_t size = 0;
		InputIterator copy_first_iter = first;
		for (; copy_first_iter < last; ++copy_first_iter)
			++size;
		vector_len = size;
		ptr = new T[size];
		for (int i = 0; i < size; ++i)
		{
			ptr[i] = *first;
			++first;
		}
	}

	template<class T>
	vector<T>::vector(const vector &x) : vector_len(x.vector_len)
	{
		ptr = new T[x.vector_len];
		for (int i = 0; i < x.vector_len; ++i)
			ptr[i] = x.ptr[i];
	}
}
#endif
