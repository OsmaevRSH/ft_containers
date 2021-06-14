#pragma once

namespace ft
{
	template<class T, class Alloc = std::allocator <T> >
	class list
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

			typedef struct List_Node
			{
				List_Node() {}
				explicit List_Node(const T &data) : _data(data) {}
				T *_data;
				List_Node *_next;
				List_Node *_prev;

			} node;

			class Iterator
			{
				public:
					node *ptr;
					Iterator() {}
					Iterator(node *ptr) : ptr(ptr) {}
					Iterator(const Iterator &copy) : ptr(copy.ptr) {}
					Iterator &operator=(const Iterator &copy)
					{
						if (*this != copy)
						{
							ptr = copy.ptr;
						}
						return *this;
					}
					virtual ~Iterator() {}

					friend bool operator==(const Iterator &left, const Iterator &right) { return left.ptr == right.ptr; }
					friend bool operator!=(const Iterator &left, const Iterator &right) { return left.ptr != right.ptr; }
					T &operator*() const { return *(this->ptr->_data); }
					T *operator->() const { return this->ptr->_data; }
					Iterator &operator++()
					{
						if (this->ptr)
							this->ptr = this->ptr->_next;
						return (*this);
					}
					Iterator &operator--()
					{
						if (this->ptr)
							this->ptr = this->ptr->_prev;
						return (*this);
					}
					Iterator operator++(int)
					{
						Iterator save(*this);
						if (this->ptr)
							this->ptr = this->ptr->_next;
						return (save);
					}
					Iterator operator--(int)
					{
						Iterator save(*this);
						if (this->ptr)
							this->ptr = this->ptr->_prev;
						return (save);
					}
			};

			class Const_Iterator : public Iterator
			{
				public:
					Const_Iterator(node *ptr) : Iterator(ptr) {}
					Const_Iterator(const Const_Iterator &copy) : Iterator(copy) {}
					Const_Iterator(Iterator iterator) : Iterator(iterator.ptr) {}
					Const_Iterator &operator=(const Const_Iterator &copy)
					{
						if (*this != copy)
						{
							this->ptr = copy.ptr;
						}
						return *this;
					}
					virtual ~Const_Iterator() {}

					const T &operator*() { return *(this->ptr->_data); }
					const T *operator->() { return this->ptr->_data; }
			};

			class Reverse_Iterator
			{
				public:
					node *ptr;
					Reverse_Iterator() {}
					Reverse_Iterator(node *ptr) : ptr(ptr) {}
					Reverse_Iterator(const Reverse_Iterator &copy) : ptr(copy.ptr) {}
					Reverse_Iterator &operator=(const Reverse_Iterator &copy)
					{
						if (*this != copy)
						{
							ptr = copy.ptr;
						}
						return *this;
					}
					virtual ~Reverse_Iterator() {}

					friend bool operator==(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr == right.ptr; }
					friend bool operator!=(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr != right.ptr; }
					T &operator*() const { return *(this->ptr->_data); }
					T *operator->() const { return this->ptr->_data; }
					Reverse_Iterator &operator++()
					{
						if (this->ptr)
							this->ptr = this->ptr->_prev;
						return (*this);
					}
					Reverse_Iterator &operator--()
					{
						if (this->ptr)
							this->ptr = this->ptr->_next;
						return (*this);
					}
					Reverse_Iterator operator++(int)
					{
						Reverse_Iterator save(*this);
						if (this->ptr)
							this->ptr = this->ptr->_prev;
						return (save);
					}
					Reverse_Iterator operator--(int)
					{
						Reverse_Iterator save(*this);
						if (this->ptr)
							this->ptr = this->ptr->_next;
						return (save);
					}
			};

			class Const_Reverse_Iterator : public Reverse_Iterator
			{
				public:
					Const_Reverse_Iterator(node *ptr) : Reverse_Iterator(ptr) {}
					Const_Reverse_Iterator(const Const_Reverse_Iterator &copy) : Reverse_Iterator(copy) {}
					Const_Reverse_Iterator(Reverse_Iterator iterator) : Reverse_Iterator(iterator.ptr) {}
					Const_Reverse_Iterator &operator=(const Const_Reverse_Iterator &copy)
					{
						if (*this != copy)
						{
							this->ptr = copy.ptr;
						}
						return *this;
					}
					virtual ~Const_Reverse_Iterator() {}

					const T &operator*() { return *(this->ptr->_data); }
					const T *operator->() { return this->ptr->_data; }
			};
		public:
			//member_types
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef Iterator iterator;
			typedef Const_Iterator const_iterator;
			typedef Reverse_Iterator reverse_iterator;
			typedef Const_Reverse_Iterator const_reverse_iterator;
			typedef size_t size_type;

		private:
			node *_center_element;
			node *_head;
			node *_tail;
			allocator_type _allocator;

		public:

			iterator begin() { return iterator(_head); }
			const_iterator begin() const { return const_iterator(_head); }
			iterator end() { return iterator(_center_element); }
			const_iterator end() const { return const_iterator(_center_element); }
			reverse_iterator rbegin() { return reverse_iterator(_tail); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_tail); }
			reverse_iterator rend() { return reverse_iterator(_center_element); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_center_element); }

			explicit list(const allocator_type &alloc = allocator_type())
					: _head(nullptr), _tail(nullptr), _center_element(Create_Node()), _allocator(alloc) {}

			explicit list(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type())
					: _head(nullptr), _tail(nullptr), _center_element(Create_Node()), _allocator(alloc)
			{
				for (int i = 0; i < n; ++i)
				{
					push_back(value);
				}
			}

			template<class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
					: _head(nullptr), _tail(nullptr), _center_element(Create_Node()), _allocator(alloc) { Create_List_Copy(first, last); }

			list(const list &x) : _head(nullptr), _tail(nullptr), _center_element(Create_Node()) { Create_List_Copy(x.begin(), x.end()); }

			~list()
			{
				Clear_List();
				_allocator.destroy((_center_element)->_data);
				_allocator.deallocate((_center_element)->_data, 1);
				delete _center_element;
				_center_element = nullptr;
			}

			list &operator=(const list &x)
			{
				if (this != &x)
				{
					assign(x.begin(), x.end());
				}
				return *this;
			}

		private:
			node *Create_Node(const_reference data = value_type())
			{
				node *new_node = new node;
				new_node->_data = _allocator.allocate(1);
				_allocator.construct(new_node->_data, data);
				new_node->_next = nullptr;
				new_node->_prev = nullptr;
				return new_node;
			}

			template<class InputIterator>
			void Create_List_Copy(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}

			void Clear_List()
			{
				if (_head == _tail)
				{
					_allocator.destroy((_head)->_data);
					_allocator.deallocate((_head)->_data, 1);
					delete _head;
					_head = nullptr;
				}
				else if (_head)
				{
					node *temp = _head;
					while (temp != _center_element)
					{
						temp = temp->_next;
						_allocator.destroy((_head)->_data);
						_allocator.deallocate((_head)->_data, 1);
						delete _head;
						_head = nullptr;
						_head = temp;
					}
				}
				_head = nullptr;
				_tail = nullptr;
			}

			void Clear_Range(iterator first, iterator last)
			{
				while (first != last)
				{
					node *temp = first.ptr;
					++first;
					_allocator.destroy(temp->_data);
					_allocator.deallocate(temp->_data, 1);
					delete temp;
					temp = nullptr;
				}
			}

		public:
			bool empty() const { return _head == nullptr; }

			size_type size() const
			{
				if (empty())
					return 0;
				else
				{
					int count = 0;
					node *temp = _head;
					while (temp != _center_element)
					{
						temp = temp->_next;
						++count;
					}
					return count;
				}
			}

			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(node); }

			reference front() { return _head->_data; }

			const_reference front() const { return _head->_data; }

			reference back() { return _tail->_data; }

			const_reference back() const { return _tail->_data; }

			template<class InputIterator>
			void assign(InputIterator first, InputIterator last, typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
			{
				iterator begin = iterator(_head);
				iterator end = iterator(_center_element);
				for (; _head != nullptr && _center_element != nullptr && first != last && begin != end; ++first, ++begin)
					*begin = *first;
				if (begin == end || _head == nullptr || _center_element == nullptr)
					insert(end, first, last);
				else
					erase(begin, end);
			}

			void assign(size_type n, const value_type &val)
			{
				iterator begin = iterator(_head);
				iterator end = iterator(_center_element);
				for (; _head != nullptr && _center_element != nullptr && n > 0 && begin != end; --n, ++begin)
					*begin = val;
				if (begin == end || _head == nullptr || _center_element == nullptr)
					insert(end, n, val);
				else
					erase(begin, end);
			}

			void push_back(const_reference val)
			{
				insert(end(), val);
			}

			void pop_back()
			{
				_tail->_prev->_next = _center_element;
				_center_element->_prev = _tail->_prev;
				node *temp = _tail;
				_tail = _tail->_prev;
				_allocator.destroy(temp->_data);
				_allocator.deallocate(temp->_data, 1);
				delete temp;
			}

			void push_front(const_reference val)
			{
				insert(begin(), val);
			}

			void pop_front()
			{
				_center_element->_next = _head->_next;
				_head->_next->_prev = _center_element;
				node *temp = _head;
				_head = _head->_next;
				_allocator.destroy(temp->_data);
				_allocator.deallocate(temp->_data, 1);
				delete temp;
			}

			iterator insert(iterator position, const value_type &val)
			{
				node *temp = Create_Node(val);
				if (!_head)
				{
					_tail = temp;
					_head = temp;
					_head->_prev = _center_element;
					_head->_next = _center_element;
					_center_element->_next = _head;
					_center_element->_prev = _head;
				}
				else if (position == end())
				{
					temp->_next = _center_element;
					temp->_prev = _tail;
					_tail->_next = temp;
					_center_element->_prev = temp;
					_tail = temp;
				}
				else if (position == begin())
				{
					temp->_next = _head;
					temp->_prev = _center_element;
					_center_element->_next = temp;
					_head->_prev = temp;
					_head = temp;
				}
				else
				{
					iterator it = begin();
					while (it != position)
					{
						++it;
					}
					temp->_next = it.ptr;
					temp->_prev = it.ptr->_prev;
					it.ptr->_prev = temp;
					temp->_prev->_next = temp;
				}
				return iterator(temp);
			}

			void insert(iterator position, size_type n, const value_type &val)
			{
				for (int i = 0; i < n; ++i)
				{
					position = insert(position, val);
				}
			}

			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
			{
				for (; first != last; ++first)
				{
					insert(position, *first);
				}
			}

			iterator erase(iterator position)
			{
				node *temp = position.ptr;
				node *returned;
				temp->_prev->_next = temp->_next;
				temp->_next->_prev = temp->_prev;
				returned = temp->_next;
				_allocator.destroy(temp->_data);
				_allocator.deallocate(temp->_data, 1);
				delete temp;
				temp = nullptr;
				return returned;
			}

			iterator erase(iterator first, iterator last)
			{
				node *start = first.ptr->_prev;
				node *finish = last.ptr;
				start->_next = finish;
				finish->_prev = start;
				Clear_Range(first, last);
				return last;
			}

			void swap(list &x)
			{
				node *temp_head = _head;
				node *temp_tail = _tail;
				node *temp_center_element = _center_element;

				_head = x._head;
				_tail = x._tail;
				_center_element = x._center_element;

				x._head = temp_head;
				x._tail = temp_tail;
				x._center_element = temp_center_element;
			}

			void resize(size_type n, value_type val = value_type())
			{
				iterator begin = iterator(_head);
				iterator end = iterator(_center_element);
				for (; _head != nullptr && _center_element != nullptr && n > 0 && begin != end; --n, ++begin);
				if (begin == end || _head == nullptr || _center_element == nullptr)
					insert(end, n, val);
				else
					erase(begin, end);
			}

			void clear()
			{
				Clear_List();
			}


	};

	template<class T, class Alloc>
	bool operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		typename list<T, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename list<T, Alloc>::const_iterator rhs_iter = rhs.begin();
		for (; lhs_iter != lhs.end() && rhs_iter != rhs.end(); ++lhs_iter, ++rhs_iter)
		{
			if (*lhs_iter != *rhs_iter)
				return false;
		}
		if (lhs_iter == lhs.end() && rhs_iter == rhs.end())
			return true;
		return false;
	}

	template<class T, class Alloc>
	bool operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		typename list<T, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename list<T, Alloc>::const_iterator rhs_iter = rhs.begin();
		for (; lhs_iter != lhs.end() && rhs_iter != rhs.end(); ++lhs_iter, ++rhs_iter)
		{
			if (*lhs_iter < *rhs_iter)
				return true;
			else if (*lhs_iter > *rhs_iter)
				return false;
			else
				continue;
		}
		if (lhs_iter == lhs.end() && rhs_iter != rhs.end())
			return true;
		return false;
	}

	template<class T, class Alloc>
	bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return !(lhs == rhs) }

	template<class T, class Alloc>
	bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return rhs < lhs }

	template<class T, class Alloc>
	bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return !(rhs < lhs) }

	template<class T, class Alloc>
	bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return !(lhs < rhs) }
}
