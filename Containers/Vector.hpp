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
			size_t alloc_size;
		public:
			explicit vector();
			explicit vector(size_t n, const T &val = value_type());
			template<class InputIterator>
			vector(InputIterator first, InputIterator last);
			vector(const vector &x);
			~vector();

			vector &operator=(const vector &x)
			void push_back(const value_type &val);
	};

	template<class T>
	vector<T>::vector() : vector_len(0), alloc_size(0)
	{
		ptr = new T[0];
	}

	template<class T>
	vector<T>::vector(size_t n, const T &val)
		: vector_len(n), alloc_size((n / 8) * 8 + 8)
	{
		ptr = new T[(n / 8) * 8 + 8];
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
		ptr = new T[(size / 8) * 8 + 8];
		for (int i = 0; i < size; ++i)
		{
			ptr[i] = *first;
			++first;
		}
	}

	template<class T>
	vector<T>::vector(const vector &x)
		: vector_len(x.vector_len), alloc_size(x.alloc_size)
	{
		ptr = new T[x.vector_len];
		for (int i = 0; i < x.vector_len; ++i)
			ptr[i] = x.ptr[i];
	}

	template<class T>
	vector<T>::~vector()
	{
		delete[] ptr;
	}

	template<class T>
	vector &vector<T>::operator=(const vector &x)
	{
		delete[] ptr;
		vector_len = x.vector_len;
		alloc_size = x.alloc_size;
		ptr = new T[alloc_size];
		for (int i = 0; i < vector_len; ++i)
			ptr[i] = x.ptr[i];
		return *this;
	}

	template<class T>
	void vector<T>::push_back(const value_type &val)
	{
		if (vector_len < alloc_size - 1)
		{
			ptr[vector_len] = val;
			++vector_len;
		}
		else
		{
			T tmp_ptr = new T[alloc_size];
			for (int i = 0; i < alloc_size; ++i)
				tmp_ptr[i] = ptr[i];
			alloc_size += 8;
			delete[] ptr;
			ptr = new T[alloc_size];
			for (int i = 0; i < alloc_size; ++i)
				ptr[i] = tmp_ptr[i];
			ptr[++vector_len] = val;
			for (int i = vector_len; i < alloc_size; ++i)
				ptr[i] = 0;
		}
	}
}
#endif
