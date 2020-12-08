#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iostream>
#include <cmath>

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		private:
			class vector_iterator;
			class reverse_vector_iterator;
		public:
			//member_types
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename vector<T, Alloc>::vector_iterator iterator;
			typedef typename vector<T, Alloc>::vector_iterator const_iterator;
			typedef typename vector<T, Alloc>::reverse_vector_iterator reverse_iterator;
			typedef typename vector<T, Alloc>::reverse_vector_iterator const_reverse_iterator;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;

			//iterator_func
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			//constructor
			explicit vector(const allocator_type &alloc = allocator_type());
			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
			vector(const vector &x);

			//destructor
			~vector();

			//operator
			vector<T, Alloc> &operator=(const vector &x);

			//element_access
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			reference at(size_type n);
			const_reference at(size_type n) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			//capacity_func
			size_type size() const;
			size_type max_size() const;
			void resize(size_type n, value_type val = value_type());
			size_type capacity() const;
			bool empty() const;
			void reserve(size_type n);

			//modifiers
			template<class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const value_type &val);
			void push_back(const value_type &val);
			void pop_back();
			iterator insert(iterator position, const value_type &val);
			void insert(iterator position, size_type n, const value_type &val);
			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(vector &x);
			void clear();

		private:
			//vector_types
			pointer _vector_start;
			size_type _curent_size;
			size_type _alloc_size;
			allocator_type _new_alloc;

			//iterator_class
			class base_iterator
			{
				protected:
					pointer ptr;
				public:
					base_iterator() {};
					base_iterator(pointer m) : ptr(m) {};
					base_iterator(const vector_iterator &copy) : ptr(copy.ptr) {};
					base_iterator &operator=(const base_iterator &copy)
					{
						if (copy != *this) {
							ptr = copy.ptr;
						}
						return *this;
					};
					~base_iterator() {};

					friend bool operator==(const_iterator &lhs, const_iterator &rhs);
					friend bool operator!=(const_iterator &lhs, const_iterator &rhs);
					friend bool operator<(const_iterator &lhs, const_iterator &rhs);
					friend bool operator>(const_iterator &lhs, const_iterator &rhs);
					friend bool operator<=(const_iterator &lhs, const_iterator &rhs);
					friend bool operator>=(const_iterator &lhs, const_iterator &rhs);
					virtual reference operator*();
					pointer operator->();
					virtual base_iterator &operator++();
					virtual base_iterator &operator++(int);
					virtual base_iterator &operator--();
					virtual base_iterator &operator--(int);
					friend base_iterator operator+(const_iterator &lhs, size_type n);
					base_iterator operator+(size_type n, const_iterator &rhs);
			};
			class vector_iterator : public base_iterator
			{
				public:
					vector_iterator() : base_iterator() {};
					vector_iterator(pointer m) : base_iterator(m) {};
					vector_iterator(const vector_iterator &copy) : base_iterator(copy) {};
					vector_iterator &operator=(const vector_iterator &copy)
					{
						if (*this != copy)
							this->ptr = copy.ptr;
						return *this;
					}
			};
			class reverse_vector_iterator : public base_iterator
			{
			};
	};
	template<class T, class Alloc>
	bool operator==(typename vector<T, Alloc>::const_iterator &lhs, typename vector<T, Alloc>::const_iterator &rhs)
	{
		return (lhs.ptr == rhs.ptr);
	}
	template<class T, class Alloc>
	bool operator!=(typename vector<T, Alloc>::const_iterator &lhs, typename vector<T, Alloc>::const_iterator &rhs)
	{
		return !(lhs == rhs);
	}
	template<class T, class Alloc>
	bool operator<(typename vector<T, Alloc>::const_iterator &lhs, typename vector<T, Alloc>::const_iterator &rhs)
	{
		return (lhs.ptr < rhs.ptr);
	}
	template<class T, class Alloc>
	bool operator>(typename vector<T, Alloc>::const_iterator &lhs, typename vector<T, Alloc>::const_iterator &rhs)
	{
		return (rhs < lhs);
	}
	template<class T, class Alloc>
	bool operator<=(typename vector<T, Alloc>::const_iterator &lhs, typename vector<T, Alloc>::const_iterator &rhs)
	{
		return !(rhs < lhs);
	}
	template<class T, class Alloc>
	bool operator>=(typename vector<T, Alloc>::const_iterator &lhs, typename vector<T, Alloc>::const_iterator &rhs)
	{
		return !(lhs < rhs);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::base_iterator::operator*()
	{
		return *ptr;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::pointer vector<T, Alloc>::base_iterator::operator->()
	{
		return ptr;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::base_iterator &vector<T, Alloc>::base_iterator::operator++()
	{
		++ptr;
		return *this;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::base_iterator &vector<T, Alloc>::base_iterator::operator++(int)
	{
		vector<T, Alloc>::base_iterator tmp = vector<T, Alloc>::base_iterator(*this);
		++ptr;
		return tmp;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::base_iterator &vector<T, Alloc>::base_iterator::operator--()
	{
		--ptr;
		return *this;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::base_iterator &vector<T, Alloc>::base_iterator::operator--(int)
	{
		vector<T, Alloc>::base_iterator tmp = vector<T, Alloc>::base_iterator(*this);
		--ptr;
		return tmp;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::base_iterator operator+(typename vector<T, Alloc>::const_iterator &lhs, typename vector<T, Alloc>::size_type n)
	{
		return typename vector<T, Alloc>::base_iterator();
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::begin()
	{
		return vector_iterator(this->_vector_start, 0);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const
	{
		vector<T, Alloc>::const_iterator tmp = vector_iterator(this->_vector_start, 0);
		return tmp;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::end()
	{
		return vector_iterator(this->_vector_start, _curent_size);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const
	{
		return vector_iterator(this->_vector_start, _curent_size);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin()
	{
		return vector_iterator(this->_vector_start, _curent_size - 1);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const
	{
		return vector_iterator(this->_vector_start, _curent_size - 1);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend()
	{
		return vector_iterator(this->_vector_start, -1);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const
	{
		return vector_iterator(this->_vector_start, -1);
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type &alloc)
			: _alloc_size(0), _curent_size(0), _vector_start(nullptr), _new_alloc(alloc)
	{
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(vector::size_type n, const value_type &val, const allocator_type &alloc)
			: _alloc_size(n), _curent_size(n), _new_alloc(alloc)
	{
		_vector_start = _new_alloc.allocate(n);
		for (int i = 0; i < n; ++i) {
			_vector_start[i] = val;
		}
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](vector::size_type n)
	{
		return _vector_start[n];
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](vector::size_type n) const
	{
		return _vector_start[n];
	}
	template<class T, class Alloc>
	template<class InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc)
			: _curent_size(last - first), _alloc_size(last - first), _new_alloc(alloc)
	{
		_vector_start = _new_alloc.allocate(last - first);
		for (int i = 0; first < last; ++first, ++i) {
			_vector_start[i] = *first;
		}
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(const vector &x)
			: _alloc_size(x._alloc_size), _curent_size(x._curent_size), _new_alloc(x._new_alloc)
	{
		_vector_start = _new_alloc.allocate(_curent_size);
		for (int i = 0; i < _curent_size; ++i) {
			_vector_start[i] = x._vector_start[i];
		}
	}
	template<class T, class Alloc>
	vector<T, Alloc>::~vector() { _new_alloc.deallocate(_vector_start, _alloc_size); }
	template<class T, class Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &x)
	{
		if (x != *this) {
			_new_alloc = x._new_alloc;
			_curent_size = x._curent_size;
			_alloc_size = x._alloc_size;
			_vector_start = _new_alloc.allocate(_alloc_size);
			for (int i = 0; i < _curent_size; ++i) {
				_vector_start[i] = x._vector_start[i];
			}
		}
		return *this;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
	{
		return _curent_size;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
	{
		return -1 / sizeof(value_type);
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::resize(vector::size_type n, value_type val)
	{
		pointer tmp = _new_alloc.allocate(n);
		if (n < _curent_size) {
			for (int i = 0; i < n; ++i) {
				tmp[i] = _vector_start[i];
			}
		}
		else {
			for (int i = 0; i < _curent_size; ++i) {
				tmp[i] = _vector_start[i];
			}
			for (int i = _curent_size; i < n; ++i) {
				tmp[i] = val;
			}
		}
		_new_alloc.deallocate(_vector_start, _alloc_size);
		_curent_size = n;
		_alloc_size = n;
		_vector_start = tmp;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
	{
		return _alloc_size;
	}
	template<class T, class Alloc>
	bool vector<T, Alloc>::empty() const
	{
		return _curent_size == 0;
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::reserve(vector::size_type n)
	{
		if (n > _alloc_size) {
			pointer tmp = _new_alloc.allocate(n);
			for (int i = 0; i < _curent_size; ++i) {
				tmp[i] = _vector_start[i];
			}
			_new_alloc.deallocate(_vector_start, _alloc_size);
			_alloc_size = n;
			_vector_start = tmp;
		}
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::at(vector::size_type n)
	{
		if (n < 0 || n >= _curent_size) {
			throw std::out_of_range("vector");
		}
		return _vector_start[n];
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(vector::size_type n) const
	{
		if (n < 0 || n >= _curent_size) {
			throw std::out_of_range("vector");
		}
		return _vector_start[n];
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::front()
	{
		return _vector_start[0];
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const
	{
		return _vector_start[0];;
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::back()
	{
		return _vector_start[_curent_size - 1];
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
	{
		return _vector_start[_curent_size - 1];
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::assign(InputIterator first, InputIterator last)
	{
		if (last - first > _curent_size) {
			_curent_size = last - first;
			allocator_type tmp = _new_alloc.allocate(_curent_size);
			for (int i = 0; first < last; ++first, ++i) {
				tmp[i] = *first;
			}
			_new_alloc.reallocate(_vector_start, _alloc_size);
			_alloc_size = _curent_size;
			_vector_start = tmp;
		}
		else {
			for (_curent_size = 0; first < last; ++first, ++_curent_size) {
				_vector_start[_curent_size] = *first;
			}
			for (int i = _curent_size; i < _alloc_size; ++i) {
				_vector_start[i] = value_type();
			}
		}
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::assign(vector::size_type n, const value_type &val)
	{
		if (n > _curent_size) {
			_curent_size = n;
			allocator_type tmp = _new_alloc.allocate(_curent_size);
			for (int i = 0; i < _curent_size; ++i) {
				tmp[i] = val;
			}
			_new_alloc.reallocate(_vector_start, _alloc_size);
			_alloc_size = _curent_size;
			_vector_start = tmp;
		}
		else {
			for (_curent_size = 0; _curent_size < n; ++_curent_size) {
				_vector_start[_curent_size] = val;
			}
			for (int i = _curent_size; i < _alloc_size; ++i) {
				_vector_start[i] = value_type();
			}
		}
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type &val)
	{
		if (_curent_size < _alloc_size) {
			_vector_start[_curent_size++] = val;
		}
		else {
			pointer tmp = _new_alloc.allocate(_alloc_size * 2);
			for (int i = 0; i < _curent_size; ++i) {
				tmp[i] = _vector_start[i];
			}
			tmp[_curent_size++] = val;
			_new_alloc.deallocate(_vector_start, _alloc_size);
			_alloc_size *= 2;
			_vector_start = tmp;
		}
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::pop_back()
	{
		_vector_start[--_curent_size] = value_type();
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(vector::iterator position, const value_type &val)
	{
		iterator start = this->begin();
		pointer tmp;
		bool check = false;
		size_type iter_val;
		if (_curent_size < _alloc_size) {
			tmp = _new_alloc.allocate(_alloc_size);
		}
		else {
			tmp = _new_alloc.allocate(_alloc_size *= 2);
			check = true;
		}
		if (!tmp) {
			throw std::bad_alloc();
		}
		for (_curent_size = 0; start < position; ++start, ++_curent_size) {
			tmp[_curent_size] = *start;
		}
		tmp[iter_val = _curent_size++] = *position;
		for (; start < this->end(); ++start, ++_curent_size) {
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
		if (_curent_size + n < _alloc_size) {
			tmp = _new_alloc.allocate(_alloc_size);
		}
		else {
			tmp = _new_alloc.allocate(_alloc_size + n);
			check = true;
		}
		if (!tmp) {
			throw std::bad_alloc();
		}
		for (_curent_size = 0; start < position; ++start, ++_curent_size) {
			tmp[_curent_size] = *start;
		}
		for (int i = 0; i < n; ++i, ++_curent_size) {
			tmp[_curent_size] = val;
		}
		for (; start < this->end(); ++start, ++_curent_size) {
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
		if (_curent_size + (last - first) < _alloc_size) {
			tmp = _new_alloc.allocate(_alloc_size);
		}
		else {
			tmp = _new_alloc.allocate(_alloc_size + (last - first));
			check = true;
		}
		if (!tmp) {
			throw std::bad_alloc();
		}
		for (_curent_size = 0; start < position; ++start, ++_curent_size) {
			tmp[_curent_size] = *start;
		}
		for (; first < last; ++first, ++_curent_size) {
			tmp[_curent_size] = *first;
		}
		for (; start < this->end(); ++start, ++_curent_size) {
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
		for (_curent_size = 0; it < position; ++it, ++_curent_size) {
			tmp[_curent_size] = *it;
		}
		++it;
		save_pos = _curent_size;
		for (; it < this->end(); ++it, ++_curent_size) {
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
		for (_curent_size = 0; it < first; ++it, ++_curent_size) {
			tmp[_curent_size] = *it;
		}
		it = last;
		save_pos = _curent_size;
		for (; it < this->end(); ++it, ++_curent_size) {
			tmp[_curent_size] = *it;
		}
		_new_alloc.deallocate(_vector_start, _alloc_size);
		_vector_start = tmp;
		return vector_iterator(_vector_start, save_pos);
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::swap(vector &x)
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
	template<class T, class Alloc>
	void vector<T, Alloc>::clear()
	{
		_curent_size = 0;
	}
	template<class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size()) {
			return false;
		}
		else {
			for (int i = 0; i < lhs.size(); ++i) {
				if (lhs[i] != rhs[i]) {
					return false;
				}
			}
		}
		return true;
	}
	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	template<class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		for (int i = 0; i < lhs.size() || i < rhs.size(); ++i) {
			if (lhs[i] >= rhs[i]) {
				return false;
			}
		}
		return true;
	}
	template<class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	template<class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template<class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
