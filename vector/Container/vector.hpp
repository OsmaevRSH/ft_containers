#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iostream>
#include <cmath>
#include "Iterator.hpp"

namespace ft
{
	template<bool B, class T = void>
	struct enable_if
	{
	};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
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
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

		private:
			//vector_types
			pointer _vector_start;
			size_type _curent_size;
			size_type _alloc_size;
			allocator_type _new_alloc;

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
					: _alloc_size(0), _curent_size(0), _vector_start(nullptr), _new_alloc(alloc) {}
			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
					: _alloc_size(n), _curent_size(n), _new_alloc(alloc)
			{
				_vector_start = _new_alloc.allocate(n);
				for (int i = 0; i < n; ++i)
				{
					_new_alloc.construct(_vector_start + i, val);
				}
			}
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
					: _curent_size(static_cast<size_type>(last - first)), _alloc_size(last - first), _new_alloc(alloc)
			{
				_vector_start = _new_alloc.allocate(last - first);
				for (int i = 0; first < last; ++first, ++i)
				{
					_new_alloc.construct(_vector_start + i, *first);
				}
			}
			vector(const vector &x) : _alloc_size(x._alloc_size), _curent_size(x._curent_size), _new_alloc(x._new_alloc)
			{
				_vector_start = _new_alloc.allocate(_curent_size);
				for (int i = 0; i < _curent_size; ++i)
				{
					_new_alloc.construct(_vector_start + i, x._vector_start[i]);
				}
			}

			//destructor
			~vector()
			{
				for (int i = 0; i < _curent_size; ++i)
				{
					_new_alloc.destroy(_vector_start + i);
				}
				_new_alloc.deallocate(_vector_start, _alloc_size);
			}

			//operator
			vector &operator=(const vector &x)
			{
				if (x != *this)
				{
					_new_alloc = x._new_alloc;
					_curent_size = x._curent_size;
					_alloc_size = x._alloc_size;
					_vector_start = _new_alloc.allocate(_alloc_size);
					for (int i = 0; i < _curent_size; ++i)
					{
						_new_alloc.construct(_vector_start + i, x._vector_start[i]);
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
			size_type max_size() const { return -1 / sizeof(value_type); }
			void resize(size_type n, value_type val = value_type())
			{
				{
					if (n <= _curent_size)
					{
						for (int i = n; i < _curent_size; ++i)
						{
							_new_alloc.destroy(_vector_start + i);
						}
						_new_alloc.deallocate(_vector_start + n, _curent_size - n);
					}
					else
					{
						pointer resized;
						resized = _new_alloc.allocate(n);
						for (int i = 0; i < _curent_size; ++i)
						{
							_new_alloc.construct(resized + i, _vector_start[i]);
						}
						for (int i = 0; i < _curent_size; ++i)
						{
							_new_alloc.destroy(_vector_start + i);
						}
						_new_alloc.deallocate(_vector_start + n, _curent_size - n);
						for (int i = _curent_size; i < n; ++i)
						{
							_new_alloc.construct(resized + i, val);
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
						pointer reserve = _new_alloc.allocate(n);
						for (int i = 0; i < _curent_size; ++i)
						{
							_new_alloc.construct(reserve + i, _vector_start[i]);
							_new_alloc.destroy(_vector_start + i);
						}
						_new_alloc.deallocate(_vector_start, _alloc_size);
						_alloc_size = n;
						_vector_start = reserve;
					}
				}
			}

			//modifiers
			template<class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				int length = std::abs(last - first);
				for (int i = 0; i < _curent_size; ++i)
				{
					_new_alloc.destroy(_vector_start + i);
				}
				_curent_size = length;
				if (length > _alloc_size)
				{
					_new_alloc.deallocate(_vector_start, _alloc_size);
					_alloc_size = _curent_size;
					_vector_start = _new_alloc.allocate(_curent_size);
					for (int i = 0; first < last; ++first, ++i)
					{
						_new_alloc.construct(_vector_start + i, *first);
					}
				}
				else
				{
					for (int i = 0; first < last; ++first, ++i)
					{
						_new_alloc.construct(_vector_start + i, *first);
					}
				}
			}
			void assign(size_type n, const value_type &val)
			{
				for (int i = 0; i < _curent_size; ++i)
				{
					_new_alloc.destroy(_vector_start + i);
				}
				_curent_size = n;
				if (n > _alloc_size)
				{
					_new_alloc.deallocate(_vector_start, _alloc_size);
					_alloc_size = _curent_size;
					_vector_start = _new_alloc.allocate(_curent_size);
					for (int i = 0; i < n; ++i)
					{
						_new_alloc.construct(_vector_start + i, val);
					}
				}
				else
				{
					for (int i = 0; i < n; ++i)
					{
						_new_alloc.construct(_vector_start + i, val);
					}
				}
			}
			void push_back(const value_type &val)
			{
				pointer push_back;
				if (_curent_size < _alloc_size)
				{
					_new_alloc.construct(_vector_start + _curent_size++, val);
				}
				else
				{
					_alloc_size = _alloc_size == 0 ? 1 : _alloc_size;
					if (_alloc_size == 0)
						push_back = _new_alloc.allocate(1);
					else
						push_back = _new_alloc.allocate(_alloc_size * 2);
					for (int i = 0; i < _curent_size; ++i)
					{
						_new_alloc.construct(push_back + i, _vector_start[i]);
					}
					for (int i = 0; i < _curent_size; ++i)
					{
						_new_alloc.destroy(_vector_start + i);
					}
					_new_alloc.deallocate(_vector_start, _alloc_size);
					_new_alloc.construct(push_back + _curent_size++, val);
					_alloc_size *= 2;
					_vector_start = push_back;
				}
			}
			void pop_back() { _new_alloc.destroy(_vector_start + --_curent_size); }
			iterator insert(iterator position, const value_type &val);
			void insert(iterator position, size_type n, const value_type &val);
			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
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

				allocator_type tmp_new_alloc = x._new_alloc;
				x._new_alloc = _new_alloc;
				_new_alloc = tmp_new_alloc;
			}
			void clear()
			{
				for (int i = 0; i < _curent_size; ++i)
				{
					_new_alloc.destroy(_vector_start + i);
				}
				_curent_size = 0;
			}
	};
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(vector::iterator position, const value_type &val)
	{
		iterator start = this->begin();
		pointer tmp;
		bool check = false;
		size_type iter_val;
		if (_curent_size < _alloc_size)
		{
			tmp = _new_alloc.allocate(_alloc_size);
		}
		else
		{
			if (_alloc_size == 0)
				tmp = _new_alloc.allocate(_alloc_size = 1);
			else
				tmp = _new_alloc.allocate(_alloc_size *= 2);
			check = true;
		}
		if (!tmp)
		{
			throw std::bad_alloc();
		}
		for (_curent_size = 0; start < position; ++start, ++_curent_size)
		{
			tmp[_curent_size] = *start;
		}
		tmp[iter_val = _curent_size++] = *position;
		for (; start < this->end(); ++start, ++_curent_size)
		{
			tmp[_curent_size] = *start;
		}
		_new_alloc.deallocate(_vector_start, check ? _alloc_size / 2 : _alloc_size);
		_vector_start = tmp;
		return vector_iterator(_vector_start, iter_val);
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::insert(vector::iterator position, vector::size_type n, const value_type &val)
	{
		iterator start = this->begin();
		pointer tmp;
		bool check = false;
		if (_curent_size + n < _alloc_size)
		{
			tmp = _new_alloc.allocate(_alloc_size);
		}
		else
		{
			tmp = _new_alloc.allocate(_alloc_size + n);
			check = true;
		}
		if (!tmp)
		{
			throw std::bad_alloc();
		}
		for (_curent_size = 0; start < position; ++start, ++_curent_size)
		{
			tmp[_curent_size] = *start;
		}
		for (int i = 0; i < n; ++i, ++_curent_size)
		{
			tmp[_curent_size] = val;
		}
		for (; start < this->end(); ++start, ++_curent_size)
		{
			tmp[_curent_size] = *start;
		}
		_new_alloc.deallocate(_vector_start, _alloc_size);
		check ? _alloc_size = _curent_size : 0;
		_vector_start = tmp;
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::insert(vector::iterator position, InputIterator first, InputIterator last)
	{
		iterator start = this->begin();
		pointer tmp;
		bool check = false;
		if (_curent_size + (last - first) < _alloc_size)
		{
			tmp = _new_alloc.allocate(_alloc_size);
		}
		else
		{
			tmp = _new_alloc.allocate(_alloc_size + (last - first));
			check = true;
		}
		if (!tmp)
		{
			throw std::bad_alloc();
		}
		for (_curent_size = 0; start < position; ++start, ++_curent_size)
		{
			tmp[_curent_size] = *start;
		}
		for (; first < last; ++first, ++_curent_size)
		{
			tmp[_curent_size] = *first;
		}
		for (; start < this->end(); ++start, ++_curent_size)
		{
			tmp[_curent_size] = *start;
		}
		_new_alloc.deallocate(_vector_start, _alloc_size);
		check ? _alloc_size = _curent_size : 0;
		_vector_start = tmp;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector::iterator position)
	{
		pointer tmp = _new_alloc.allocate(_alloc_size);
		iterator it = this->begin();
		size_type save_pos;
		for (_curent_size = 0; it < position; ++it, ++_curent_size)
		{
			tmp[_curent_size] = *it;
		}
		++it;
		save_pos = _curent_size;
		for (; it < this->end(); ++it, ++_curent_size)
		{
			tmp[_curent_size] = *it;
		}
		_new_alloc.deallocate(_vector_start, _alloc_size);
		_vector_start = tmp;
		return vector_iterator(_vector_start, save_pos);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector::iterator first, vector::iterator last)
	{
		pointer tmp = _new_alloc.allocate(_alloc_size);
		iterator it = this->begin();
		size_type save_pos;
		for (_curent_size = 0; it < first; ++it, ++_curent_size)
		{
			tmp[_curent_size] = *it;
		}
		it = last;
		save_pos = _curent_size;
		for (; it < this->end(); ++it, ++_curent_size)
		{
			tmp[_curent_size] = *it;
		}
		_new_alloc.deallocate(_vector_start, _alloc_size);
		_vector_start = tmp;
		return vector_iterator(_vector_start, save_pos);
	}


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

#endif
