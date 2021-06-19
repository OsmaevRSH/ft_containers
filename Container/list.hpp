#pragma once

#include "iostream"

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
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
				T _data;
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
						if (this != &copy)
						{
							ptr = copy.ptr;
						}
						return *this;
					}
					virtual ~Iterator() {}

					friend bool operator==(const Iterator &left, const Iterator &right) { return left.ptr == right.ptr; }
					friend bool operator!=(const Iterator &left, const Iterator &right) { return left.ptr != right.ptr; }
					T &operator*() const { return this->ptr->_data; }
					T *operator->() const { return &(this->ptr->_data); }
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
					Const_Iterator() {}
					Const_Iterator(node *ptr) : Iterator(ptr) {}
					Const_Iterator(const Const_Iterator &copy) : Iterator(copy) {}
					Const_Iterator(Iterator iterator) : Iterator(iterator.ptr) {}
					Const_Iterator &operator=(const Const_Iterator &copy)
					{
						if (this != &copy)
						{
							this->ptr = copy.ptr;
						}
						return *this;
					}
					virtual ~Const_Iterator() {}

					const T &operator*() { return this->ptr->_data; }
					const T *operator->() { return &(this->ptr->_data); }
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
						if (this != &copy)
						{
							ptr = copy.ptr;
						}
						return *this;
					}
					virtual ~Reverse_Iterator() {}

					friend bool operator==(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr == right.ptr; }
					friend bool operator!=(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr != right.ptr; }
					T &operator*() const { return this->ptr->_data; }
					T *operator->() const { return &(this->ptr->_data); }
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
					Const_Reverse_Iterator() {}
					Const_Reverse_Iterator(node *ptr) : Reverse_Iterator(ptr) {}
					Const_Reverse_Iterator(const Const_Reverse_Iterator &copy) : Reverse_Iterator(copy) {}
					Const_Reverse_Iterator(Reverse_Iterator iterator) : Reverse_Iterator(iterator.ptr) {}
					Const_Reverse_Iterator &operator=(const Const_Reverse_Iterator &copy)
					{
						if (this != &copy)
						{
							this->ptr = copy.ptr;
						}
						return *this;
					}
					virtual ~Const_Reverse_Iterator() {}

					const T &operator*() { return this->ptr->_data; }
					const T *operator->() { return &(this->ptr->_data); }
			};
		public:
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
			node *_linked_elem;
			node *_head;
			node *_tail;
			allocator_type _allocator;

		public:

			iterator begin() { return iterator(_head); }
			const_iterator begin() const { return const_iterator(_head); }
			iterator end() { return iterator(_linked_elem); }
			const_iterator end() const { return const_iterator(_linked_elem); }
			reverse_iterator rbegin() { return reverse_iterator(_tail); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_tail); }
			reverse_iterator rend() { return reverse_iterator(_linked_elem); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_linked_elem); }

			explicit list(const allocator_type &alloc = allocator_type())
					: _linked_elem(Create_Node()), _head(nullptr), _tail(nullptr), _allocator(alloc)
			{
				_head = _linked_elem;
				_tail = _linked_elem;
				_linked_elem->_next = _linked_elem;
				_linked_elem->_prev = _linked_elem;
			}

			explicit list(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type())
					: _linked_elem(Create_Node()), _head(nullptr), _tail(nullptr), _allocator(alloc)
			{
				_head = _linked_elem;
				_tail = _linked_elem;
				_linked_elem->_next = _linked_elem;
				_linked_elem->_prev = _linked_elem;
				for (size_type i = 0; i < n; ++i)
				{
					push_back(value);
				}
			}

			template<class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
					:  _linked_elem(Create_Node()), _head(nullptr), _tail(nullptr), _allocator(alloc)
			{
				_head = _linked_elem;
				_tail = _linked_elem;
				_linked_elem->_next = _linked_elem;
				_linked_elem->_prev = _linked_elem;
				Create_List_Copy(first, last);
			}

			list(const list &x) : _linked_elem(Create_Node()), _head(nullptr), _tail(nullptr)
			{
				_head = _linked_elem;
				_tail = _linked_elem;
				_linked_elem->_next = _linked_elem;
				_linked_elem->_prev = _linked_elem;
				Create_List_Copy(x.begin(), x.end());
			}

			~list()
			{
				Clear_List();
				delete _linked_elem;
				_linked_elem = nullptr;
			}

			list &operator=(const list &x)
			{
				if (this != &x)
				{
					_linked_elem = Create_Node();
					_head = _linked_elem;
					_tail = _linked_elem;
					_linked_elem->_next = _linked_elem;
					_linked_elem->_prev = _linked_elem;
					Create_List_Copy(x.begin(), x.end());
				}
				return *this;
			}

		private:
			node *Create_Node(const_reference data = value_type())
			{
				node *new_node = new node;
				new_node->_data = data;
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
				if (_head == _tail && _head != _linked_elem)
				{
					delete _head;
					_head = nullptr;
				}
				else if (_head)
				{
					node *temp = _head;
					while (temp != _linked_elem && temp != nullptr)
					{
						temp = temp->_next;
						delete _head;
						_head = nullptr;
						_head = temp;
					}
				}
				_head = _linked_elem;
				_tail = _linked_elem;
			}

			void Clear_Range(iterator first, iterator last)
			{
				while (first != last)
				{
					node *temp = first.ptr;
					++first;
					delete temp;
					temp = nullptr;
				}
			}

			static bool Unique_Binary_Predicate(const_reference lhs, const_reference rhs) { return lhs == rhs; }

			static bool Sort_Comparer(const_reference lhs, const_reference rhs) { return lhs < rhs; }

		public:
			bool empty() const { return _head == _linked_elem; }

			size_type size() const
			{
				if (empty())
					return 0;
				else
				{
					int count = 0;
					node *temp = _head;
					while (temp != _linked_elem)
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
				iterator end = iterator(_linked_elem);
				for (; first != last && begin != end; ++first, ++begin)
					*begin = *first;
				if (begin == end)
					insert(end, first, last);
				else
					erase(begin, end);
			}

			void assign(size_type n, const value_type &val)
			{
				iterator begin = iterator(_head);
				iterator end = iterator(_linked_elem);
				for (; n > 0 && begin != end; --n, ++begin)
					*begin = val;
				if (begin == end)
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
				_tail->_prev->_next = _linked_elem;
				_linked_elem->_prev = _tail->_prev;
				node *temp = _tail;
				_tail = _tail->_prev;
				delete temp;
				if (_linked_elem->_next == _linked_elem)
					_head = _linked_elem;
				temp = nullptr;
			}

			void push_front(const_reference val)
			{
				insert(begin(), val);
			}

			void pop_front()
			{
				_head->_next->_prev = _linked_elem;
				_linked_elem->_next = _head->_next;
				node *temp = _head;
				_head = _head->_next;
				delete temp;
				if (_linked_elem->_next == _linked_elem)
					_head = _linked_elem;
				temp = nullptr;
			}

			iterator insert(iterator position, const value_type &val)
			{
				node *temp = Create_Node(val);
				if (empty())
				{
					_tail = temp;
					_head = temp;
					_head->_prev = _linked_elem;
					_head->_next = _linked_elem;
					_linked_elem->_next = _head;
					_linked_elem->_prev = _tail;
				}
				else if (position == end())
				{
					_tail->_next = temp;
					temp->_next = _linked_elem;
					_linked_elem->_prev = temp;
					temp->_prev = _tail;
					_tail = temp;
				}
				else if (position == begin())
				{
					temp->_next = _head;
					temp->_prev = _linked_elem;
					_linked_elem->_next = temp;
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
				for (size_type i = 0; i < n; ++i)
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
				node *returned = temp->_next;
				temp->_prev->_next = temp->_next;
				temp->_next->_prev = temp->_prev;
				delete temp;
				temp = nullptr;
				_tail = _linked_elem->_prev;
				_head = _linked_elem->_next;
				return iterator(returned);
			}

			iterator erase(iterator first, iterator last)
			{
				if (first == begin() && last == end())
				{
					Clear_List();
					_linked_elem->_next = _linked_elem;
					_linked_elem->_prev = _linked_elem;
					return iterator(_linked_elem);
				}
				node *start = first.ptr->_prev;
				node *finish = last.ptr;
				start->_next = finish;
				finish->_prev = start;
				_tail = _linked_elem->_prev;
				_head = _linked_elem->_next;
				Clear_Range(first, last);
				return last;
			}

			void swap(list &x)
			{
				node *temp_head = _head;
				node *temp_tail = _tail;
				node *temp_center_element = _linked_elem;

				_head = x._head;
				_tail = x._tail;
				_linked_elem = x._linked_elem;

				x._head = temp_head;
				x._tail = temp_tail;
				x._linked_elem = temp_center_element;
			}

			void resize(size_type n, value_type val = value_type())
			{
				iterator begin = iterator(_head);
				iterator end = iterator(_linked_elem);
				while (n > 0 && begin != end)
				{
					--n;
					++begin;
				}
				if (begin == end)
					insert(end, n, val);
				else
					erase(begin, end);
			}

			void clear()
			{
				Clear_List();
			}

			void unique()
			{
				unique(Unique_Binary_Predicate);
			}

			template<class BinaryPredicate>
			void unique(BinaryPredicate binary_pred)
			{
				if (size() < 2)
					return;
				iterator it_first = begin();
				iterator it_second = ++begin();
				while (it_second != end())
				{
					if (binary_pred(*it_first, *it_second))
					{
						it_second = erase(it_second);
						continue;
					}
					++it_first;
					++it_second;
				}
			}

			void remove(const value_type &val)
			{
				iterator first = begin();
				while (first != end())
				{
					if (*first == val)
					{
						first = erase(first);
						continue;
					}
					++first;
				}
			}

			template<class Predicate>
			void remove_if(Predicate pred)
			{
				iterator first = begin();
				while (first != end())
				{
					if (pred(*first))
					{
						first = erase(first);
						continue;
					}
					++first;
				}
			}

			void reverse()
			{
				node *temp = nullptr;
				node *first = _linked_elem;
				do
				{
					temp = first->_prev;
					first->_prev = first->_next;
					first->_next = temp;
					first = first->_prev;
				} while (first != _linked_elem);
				_head = _linked_elem->_next;
				_tail = _linked_elem->_prev;
			}

			void splice(iterator position, list &x)
			{
				splice(position, x, x.begin(), x.end());
			}

			void splice(iterator position, list &x, iterator i)
			{
				insert(position, *i);
				x.erase(i);
			}

			void splice(iterator position, list &x, iterator first, iterator last)
			{
				insert(position, first, last);
				x.erase(first, last);
			}

			void sort()
			{
				sort(Sort_Comparer);
			}

			template<class Compare>
			void sort(Compare comp)
			{
				int i = 0;
				node *tmp = _head;
				size_type list_size = size();
				while (i != (int) (list_size - 1))
				{
					while (tmp->_next != _linked_elem)
					{
						if (comp(tmp->_data, tmp->_next->_data))
							tmp = tmp->_next;
						else
							SwapElement(tmp);
					}
					tmp = _head;
					++i;
				}
			}

			void merge(list &x)
			{
				merge(x, Sort_Comparer);
			}

			template<class Compare>
			void merge(list &x, Compare comp)
			{
				if (&x == this)
					return;
				iterator first = begin();
				iterator second = x.begin();
				while (first != end() && second != x.end())
				{
					if (comp(*second, *first))
					{
						splice(first, x, second++);
					}
					else
					{
						++first;
						continue;
					}
				}
				if (first == end())
					splice(end(), x, second, x.end());
			}

			void SwapElement(node *first)
			{
				first->_prev->_next = first->_next;
				first->_next = first->_next->_next;
				first->_prev->_next->_prev = first->_prev;
				first->_prev->_next->_next = first;
				first->_prev = first->_prev->_next;
				first->_next->_prev = first;
				_head = _linked_elem->_next;
				_tail = _linked_elem->_prev;
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
	bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return !(lhs == rhs); }

	template<class T, class Alloc>
	bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return rhs < lhs; }

	template<class T, class Alloc>
	bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return !(rhs < lhs); }

	template<class T, class Alloc>
	bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) { return !(lhs < rhs); }

	template<class T, class Alloc>
	void swap(list<T, Alloc> &x, list<T, Alloc> &y) { x.swap(y); }
}
