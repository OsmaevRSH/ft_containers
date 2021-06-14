#pragma once

#include <iostream>
#include <cmath>
#include "Vector_Iterator.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		private:
			template<bool B, class T1 = void>
			struct enable_if
			{
			};

			template<class T1>
			struct enable_if<true, T1>
			{
				typedef T1 type;
			};
		public:
			//member_types
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef Iterator<T> iterator;
			typedef Const_Iterator<T> const_iterator;
			typedef Reverse_Iterator<T> reverse_iterator;
			typedef Const_Reverse_Iterator<T> const_reverse_iterator;
			typedef size_t size_type;

		private:
			//vector_types
			pointer _vector_start;
			size_type _curent_size;
			size_type _alloc_size;
			allocator_type _allocator;

		public:
			//iterator_func
			iterator begin() { return iterator(this->_vector_start); }
			const_iterator begin() const { return const_iterator(this->_vector_start); }
			iterator end() { return iterator(this->_vector_start + _curent_size); }
			const_iterator end() const { return const_iterator(this->_vector_start + _curent_size); }
			reverse_iterator rbegin() { return reverse_iterator(this->_vector_start + _curent_size - 1); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_vector_start + _curent_size - 1); }
			reverse_iterator rend() { return reverse_iterator(this->_vector_start - 1); }
			const_reverse_iterator rend() const { return const_reverse_iterator(this->_vector_start - 1); }

			//constructor
			explicit vector(const allocator_type &alloc = allocator_type())
					: _alloc_size(0), _curent_size(0), _vector_start(nullptr), _allocator(alloc) {}
			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
					: _alloc_size(n), _curent_size(n), _allocator(alloc)
			{
				_vector_start = _allocator.allocate(n);
				for (int i = 0; i < n; ++i)
				{
					_allocator.construct(_vector_start + i, val);
				}
			}
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
					: _curent_size(static_cast<size_type>(last - first)), _alloc_size(last - first), _allocator(alloc)
			{
				_vector_start = _allocator.allocate(last.operator->() - first.operator->());
				for (int i = 0; first < last; ++first, ++i)
				{
					_allocator.construct(_vector_start + i, *first);
				}
			}
			vector(const vector &x) : _alloc_size(x._alloc_size), _curent_size(x._curent_size), _allocator(x._allocator)
			{
				_vector_start = _allocator.allocate(_curent_size);
				for (int i = 0; i < _curent_size; ++i)
				{
					_allocator.construct(_vector_start + i, x._vector_start[i]);
				}
			}

			//destructor
			~vector()
			{
				for (int i = 0; i < _curent_size; ++i)
				{
					_allocator.destroy(_vector_start + i);
				}
				_allocator.deallocate(_vector_start, _alloc_size);
			}

			//operator
			vector &operator=(const vector &x)
			{
				if (&x != this)
				{
					_allocator = x._allocator;
					_curent_size = x._curent_size;
					_alloc_size = x._alloc_size;
					_vector_start = _allocator.allocate(_alloc_size);
					for (int i = 0; i < _curent_size; ++i)
					{
						_allocator.construct(_vector_start + i, x._vector_start[i]);
					}
				}
				return *this;
			}

			//element_access
			reference operator[](size_type n) { return _vector_start[n]; }
			const_reference operator[](size_type n) const { return _vector_start[n]; }
			reference at(size_type n)
			{
				if (n < 0 || n >= _curent_size)
				{
					throw std::out_of_range("vector");
				}
				return _vector_start[n];
			}
			const_reference at(size_type n) const
			{
				if (n < 0 || n >= _curent_size)
				{
					throw std::out_of_range("vector");
				}
				return _vector_start[n];
			}
			reference front() { return _vector_start[0]; }
			const_reference front() const { return _vector_start[0]; }
			reference back() { return _vector_start[_curent_size - 1]; }
			const_reference back() const { return _vector_start[_curent_size - 1]; }

			//capacity_func
			size_type size() const { return _curent_size; }
			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }
			void resize(size_type n, value_type val = value_type())
			{
				{
					if (n <= _curent_size)
					{
						for (int i = n; i < _curent_size; ++i)
						{
							_allocator.destroy(_vector_start + i);
						}
					}
					else
					{
						pointer resized;
						resized = _allocator.allocate(n);
						for (int i = 0; i < _curent_size; ++i)
						{
							_allocator.construct(resized + i, _vector_start[i]);
						}
						for (int i = 0; i < _curent_size; ++i)
						{
							_allocator.destroy(_vector_start + i);
						}
						_allocator.deallocate(_vector_start, _curent_size);
						for (int i = _curent_size; i < n; ++i)
						{
							_allocator.construct(resized + i, val);
						}
						_vector_start = resized;
					}
					_curent_size = n;
					_alloc_size = n;
				}
			}
			size_type capacity() const { return _alloc_size; }
			bool empty() const { return _curent_size == 0; }
			void reserve(size_type n)
			{
				{
					if (n > _alloc_size)
					{
						pointer reserve = _allocator.allocate(n);
						for (int i = 0; i < _curent_size; ++i)
						{
							_allocator.construct(reserve + i, _vector_start[i]);
							_allocator.destroy(_vector_start + i);
						}
						_allocator.deallocate(_vector_start, _alloc_size);
						_alloc_size = n;
						_vector_start = reserve;
					}
				}
			}

			//modifiers
			template<class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				int length = std::abs(last.operator->() - first.operator->());
				for (int i = 0; i < _curent_size; ++i)
				{
					_allocator.destroy(_vector_start + i);
				}
				_curent_size = length;
				if (length > _alloc_size)
				{
					_allocator.deallocate(_vector_start, _alloc_size);
					_alloc_size = _curent_size;
					_vector_start = _allocator.allocate(_curent_size);
					for (int i = 0; first < last; ++first, ++i)
					{
						_allocator.construct(_vector_start + i, *first);
					}
				}
				else
				{
					for (int i = 0; first < last; ++first, ++i)
					{
						_allocator.construct(_vector_start + i, *first);
					}
				}
			}
			void assign(size_type n, const value_type &val)
			{
				for (int i = 0; i < _curent_size; ++i)
				{
					_allocator.destroy(_vector_start + i);
				}
				_curent_size = n;
				if (n > _alloc_size)
				{
					_allocator.deallocate(_vector_start, _alloc_size);
					_alloc_size = _curent_size;
					_vector_start = _allocator.allocate(_curent_size);
					for (int i = 0; i < n; ++i)
					{
						_allocator.construct(_vector_start + i, val);
					}
				}
				else
				{
					for (int i = 0; i < n; ++i)
					{
						_allocator.construct(_vector_start + i, val);
					}
				}
			}
			void push_back(const value_type &val)
			{
				pointer push_back;
				if (_curent_size < _alloc_size)
				{
					_allocator.construct(_vector_start + _curent_size++, val);
				}
				else
				{
					_alloc_size = _alloc_size == 0 ? 1 : _alloc_size;
					if (_alloc_size == 0)
						push_back = _allocator.allocate(1);
					else
						push_back = _allocator.allocate(_alloc_size * 2);
					for (int i = 0; i < _curent_size; ++i)
					{
						_allocator.construct(push_back + i, _vector_start[i]);
					}
					for (int i = 0; i < _curent_size; ++i)
					{
						_allocator.destroy(_vector_start + i);
					}
					_allocator.deallocate(_vector_start, _alloc_size);
					_allocator.construct(push_back + _curent_size++, val);
					_alloc_size *= 2;
					_vector_start = push_back;
				}
			}
			void pop_back() { _allocator.destroy(_vector_start + --_curent_size); }
			iterator insert(iterator position, const value_type &val)
			{
				pointer save_ptr = nullptr;
				if (_curent_size >= _alloc_size)
				{
					pointer reserve = _allocator.allocate(_alloc_size * 2);
					for (int i = 0; i < _curent_size; ++i)
					{
						if (_vector_start + i == position.operator->())
							save_ptr = reserve + i;
						_allocator.construct(reserve + i, _vector_start[i]);
						_allocator.destroy(_vector_start + i);
					}
					_allocator.deallocate(_vector_start, _alloc_size);
					_vector_start = reserve;
					_alloc_size *= 2;
					iterator it = begin();
					while (it.operator->() != save_ptr)
					{
						++it;
					}
					position = it;
				}
				for (iterator it = end() - 1; it >= position; --it)
				{
					_allocator.construct(it.operator->() + 1, *it);
					_allocator.destroy(it.operator->());
				}
				_allocator.construct(position.operator->(), val);
				++_curent_size;

				return position;
			}
			void insert(iterator position, size_type n, const value_type &val)
			{
				pointer save_ptr = nullptr;
				int alloc_size = n / _alloc_size >= 1 ? _curent_size + n : _alloc_size * 2;
				if (_curent_size + n - 1 >= _alloc_size)
				{

					pointer reserve = _allocator.allocate(alloc_size);
					for (int i = 0; i <= _curent_size; ++i)
					{
						if (_vector_start + i == position.operator->())
							save_ptr = reserve + i;
						_allocator.construct(reserve + i, _vector_start[i]);
						_allocator.destroy(_vector_start + i);
					}
					_allocator.deallocate(_vector_start, _alloc_size);
					_vector_start = reserve;
					_alloc_size = alloc_size;
					iterator it = begin();
					while (it.operator->() != save_ptr)
					{
						++it;
					}
					position = it;
				}
				for (iterator it = end() - 1; it >= position; --it)
				{
					_allocator.construct(it.operator->() + n, *it);
					_allocator.destroy(it.operator->());
				}
				for (int i = 0; i < n; ++i)
				{
					_allocator.construct(position.operator->() + i, val);
					++_curent_size;
				}
			}
			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
			{
				int n = std::abs(last.operator->() - first.operator->());
				pointer save_ptr = nullptr;
				int alloc_size = (n / _alloc_size) >= 1 ? _curent_size + n : _alloc_size * 2;
				if (_curent_size + n - 1 >= _alloc_size)
				{

					pointer reserve = _allocator.allocate(alloc_size);
					for (int i = 0; i <= _curent_size; ++i)
					{
						if (_vector_start + i == position.operator->())
							save_ptr = reserve + i;
						_allocator.construct(reserve + i, _vector_start[i]);
						_allocator.destroy(_vector_start + i);
					}
					_allocator.deallocate(_vector_start, _alloc_size);
					_vector_start = reserve;
					_alloc_size = alloc_size;
					iterator it = begin();
					while (it.operator->() != save_ptr)
					{
						++it;
					}
					position = it;
				}
				for (iterator it = end() - 1; it >= position; --it)
				{
					_allocator.construct(it.operator->() + n, *it);
					_allocator.destroy(it.operator->());
				}
				for (int i = 0; first < last; ++first, ++i)
				{
					_allocator.construct(position.operator->() + i, *first);
					++_curent_size;
				}
			}
			iterator erase(iterator position)
			{
				for (iterator iter = position; iter < end() - 1; ++iter)
				{
					_allocator.destroy(iter.operator->());
					_allocator.construct(iter.operator->(), *(iter + 1));
				}
				_allocator.destroy((end() - 1).operator->());
				--_curent_size;
				return position;
			}
			iterator erase(iterator first, iterator last)
			{
				int size = std::abs(last.operator->() - first.operator->());
				int size_to_end = std::abs(end().operator->() - last.operator->());
				if (size_to_end >= size)
				{
					for (; last < end(); ++first, ++last)
					{
						_allocator.destroy(first.operator->());
						_allocator.construct(first.operator->(), *last);
					}
					_allocator.destroy(last.operator->());
				}
				else
				{
					for (iterator it = first; it < last; ++it)
					{
						_allocator.destroy(it.operator->());
					}
					for (; last < end(); ++last, ++first)
					{
						_allocator.construct(first.operator->(), *last);
						_allocator.destroy(first.operator->());
					}
				}
				_curent_size -= size;
				return first;
			}
			void swap(vector &x)
			{
				pointer tmp_vector_start = x._vector_start;
				x._vector_start = _vector_start;
				_vector_start = tmp_vector_start;

				size_type tmp_cur_size = x._curent_size;
				x._curent_size = _curent_size;
				_curent_size = tmp_cur_size;

				size_type tmp_alloc_size = x._alloc_size;
				x._alloc_size = _alloc_size;
				_alloc_size = tmp_alloc_size;

				allocator_type tmp_new_alloc = x._allocator;
				x._allocator = _allocator;
				_allocator = tmp_new_alloc;
			}
			void clear()
			{
				for (int i = 0; i < _curent_size; ++i)
				{
					_allocator.destroy(_vector_start + i);
				}
				_curent_size = 0;
			}
	};

	//Non_member
	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		for (int i = 0; i < lhs.size() || i < rhs.size(); ++i)
		{
			if (lhs[i] != rhs[i])
			{
				return false;
			}
		}
		return true;
	}
	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		for (int i = 0; i < lhs.size() || i < rhs.size(); ++i)
		{
			if (lhs[i] == rhs[i])
			{
				return false;
			}
		}
		return true;
	}
	template<class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		for (int i = 0; i < lhs.size() || i < rhs.size(); ++i)
		{
			if (lhs[i] <= rhs[i])
			{
				return false;
			}
		}
		return true;
	}
	template<class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		for (int i = 0; i < lhs.size() || i < rhs.size(); ++i)
		{
			if (lhs[i] >= rhs[i])
			{
				return false;
			}
		}
		return true;
	}
	template<class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		for (int i = 0; i < lhs.size() || i < rhs.size(); ++i)
		{
			if (lhs[i] < rhs[i])
			{
				return false;
			}
		}
		return true;
	}
	template<class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		for (int i = 0; i < lhs.size() || i < rhs.size(); ++i)
		{
			if (lhs[i] > rhs[i])
			{
				return false;
			}
		}
		return true;
	}
	template<class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}