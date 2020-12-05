#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iostream>
#include <cmath>
#include "../iterator/random_access_iterator.hpp"

namespace ft
{
	template<class T>
	class vector
	{
		private:
			T *ptr;
			int vector_len;
			int alloc_size;

		public:

			//Constructor
			explicit vector();
			explicit vector(size_t n, const T &val = T());
			template<class InputIterator>
			vector(InputIterator first, InputIterator last);
			vector(const vector &x);

			//Destructor
			~vector();

			//Operator
			vector &operator=(const vector &x);
			T &operator[](const size_t &);
			friend bool operator==(const vector<T> &lhs, const vector<T> &rhs);
			friend bool operator!=(const vector<T> &lhs, const vector<T> &rhs);
			friend bool operator<(const vector<T> &lhs, const vector<T> &rhs);
			friend bool operator<=(const vector<T> &lhs, const vector<T> &rhs);
			friend bool operator>(const vector<T> &lhs, const vector<T> &rhs);
			friend bool operator>=(const vector<T> &lhs, const vector<T> &rhs);

			//Capacity
			size_t size() const;
			size_t max_size() const;
			size_t capacity() const;
			void resize(size_t n, T val = T());
			void reserve(size_t n);
			bool empty() const;

			//Function
			void push_back(const T &val);

			//Iterator
			class iterator : public Random_access_iterator<T>
			{
				public:
					iterator();
					explicit iterator(const T *);
					iterator(const iterator &);
					iterator &operator=(const iterator &);
					~iterator();
			};

			iterator &begin();
			iterator &end();
	};

	template<class T>
	vector<T>::iterator::iterator() : Random_access_iterator<T>()
	{
	}

	template<class T>
	vector<T>::iterator::iterator(const vector::iterator &copy)
			: Random_access_iterator<T>(copy)
	{
	}

	template<class T>
	typename vector<T>::iterator &vector<T>::iterator::operator=(const vector::iterator &copy)
	{
		this->m = copy.m;
		return *this;
	}

	template<class T>
	vector<T>::iterator::~iterator()
	{
	}

	template<class T>
	vector<T>::iterator::iterator(const T *c)
	{
		this->m = c;
	}

	template<class T>
	vector<T>::vector() : vector_len(0), alloc_size(0)
	{
		ptr = new T[0];
	}

	template<class T>
	vector<T>::vector(size_t n, const T &val)
			: vector_len(n), alloc_size(ceil(log(n)/log(2)))
	{
		ptr = new T[(int)pow(2, ceil(log(vector_len)/log(2)))];
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
		ptr = new T[(int)pow(2, ceil(log(vector_len)/log(2)))];
		alloc_size = (int)pow(2, ceil(log(vector_len)/log(2)));
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
	vector<T> &vector<T>::operator=(const vector &x)
	{
		if (x != *this)
		{
			delete[] ptr;
			vector_len = x.vector_len;
			alloc_size = x.alloc_size;
			ptr = new T[alloc_size];
			for (int i = 0; i < vector_len; ++i)
				ptr[i] = x.ptr[i];
		}
		return *this;
	}

	template<class T>
	void vector<T>::push_back(const T &val)
	{
		if (vector_len < alloc_size - 1)
		{
			ptr[vector_len] = val;
			++vector_len;
		}
		else
		{
			++vector_len;
			T *tmp_ptr = new T[alloc_size = pow(2, ceil(log(vector_len)/log(2)))];
			for (int i = 0; i < vector_len - 1; ++i)
				tmp_ptr[i] = ptr[i];
			tmp_ptr[vector_len - 1] = val;
			delete[] ptr;
			ptr = tmp_ptr;
		}
	}
	template<class T>
	T &vector<T>::operator[](const size_t &i)
	{
		return ptr[i];
	}
	template<class T>

	bool operator==(const vector<T> &lhs, const vector<T> &rhs)
	{

	}
	template<class T>
	bool operator!=(const vector<T> &lhs, const vector<T> &rhs)
	{
		if (lhs.vector_len == rhs.vector_len)
			return false;
		return true;
	}
	template<class T>
	bool operator<(const vector<T> &lhs, const vector<T> &rhs)
	{
		if (lhs.vector_len < rhs.vector_len)
			return true;
		return false;
	}
	template<class T>
	bool operator<=(const vector<T> &lhs, const vector<T> &rhs)
	{
		return false;
	}
	template<class T>
	bool operator>(const vector<T> &lhs, const vector<T> &rhs)
	{
		return false;
	}
	template<class T>
	bool operator>=(const vector<T> &lhs, const vector<T> &rhs)
	{
		return false;
	}

	template<class T>
	typename vector<T>::iterator &vector<T>::begin()
	{
		return iterator(this->ptr[0]);
	}

	template<class T>
	typename vector<T>::iterator &vector<T>::end()
	{
		return iterator(this->ptr[this->vector_len]);
	}

	template<class T>
	size_t vector<T>::size() const
	{
		return vector_len;
	}

	template<class T>
	size_t vector<T>::capacity() const
	{
		return alloc_size;
	}

	template<class T>
	bool vector<T>::empty() const
	{
		return vector_len == 0;
	}

	template<class T>
	size_t vector<T>::max_size() const
	{
		size_t tmp = -1 / sizeof(T);
		return tmp;
	}

	template<class T>
	void vector<T>::resize(size_t n, T val)
	{
		if (n < vector_len)
		{
			T *tmp = new T[n];
			for (int i = 0; i < n; ++i)
				tmp[i] = ptr[i];
			delete[] ptr;
			ptr = tmp;
		}
		else
		{
			T *tmp = new T[n];
			for (int i = 0; i < vector_len; ++i)
				tmp[i] = ptr[i];
			for (int i = vector_len; i < n; ++i)
				tmp[i] = val;
			delete[] ptr;
			ptr = tmp;
		}
		if (n > alloc_size)
			alloc_size = pow(2, ceil(log(n)/log(2)));
		vector_len = n;
	}

	template<class T>
	void vector<T>::reserve(size_t n)
	{
		if (n > alloc_size)
		{
			T *tmp = new T[n];
			for (int i = 0; i < vector_len; ++i)
				tmp[i] = ptr[i];
			delete[] ptr;
			ptr = tmp;
			alloc_size = n;
		}
	}
}

#endif
