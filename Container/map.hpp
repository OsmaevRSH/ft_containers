#pragma once

#include <iostream>

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
		private:
			typedef struct Map_Node
			{
				Map_Node() {}
				Map_Node(const std::pair<Key, T> &x) : data(x), left(nullptr), right(nullptr), parent(nullptr) {}
				Map_Node(const Map_Node &x) : data(x.data), left(x.left), right(x.right), parent(x.parent) {}
				std::pair<Key, T> data;
				Map_Node *left;
				Map_Node *right;
				Map_Node *parent;
			} node;

			class Iterator;
			class Const_Iterator;
			class Reverse_Iterator;
			class Const_Reverse_Iterator;

		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<key_type, mapped_type> value_type;
			typedef Compare key_compare;
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


			node *_root;
			node *_rend;
			node *_lend;
			key_compare _comp;

			iterator begin() { return iterator(SearchBeginElement(), _rend); }
			const_iterator begin() const { return const_iterator(SearchBeginElement()); }
			iterator end() { return iterator(SearchRBeginElement()->right, _rend); }
			const_iterator end() const { return const_iterator(SearchRBeginElement()->right); }
			reverse_iterator rbegin() { return reverse_iterator(SearchRBeginElement()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(SearchRBeginElement()); }
			reverse_iterator rend() { return reverse_iterator(SearchBeginElement()->left); }
			const_reverse_iterator rend() const { return const_reverse_iterator(SearchBeginElement()->left); }

		private:
			class Iterator
			{
				protected:
					node *ptr;
					node *end;
				public:
					Iterator() {}
					Iterator(node *x, node *end) : ptr(x), end(end) {}
					Iterator(const Iterator &it) : ptr(it.ptr), end(it.end) {}
					Iterator &operator=(const Iterator &it)
					{
						if (&it != this)
						{
							ptr = it.ptr;
							end = it.end;
						}
						return *this;
					}
					virtual ~Iterator() {}

					friend bool operator==(const Iterator &left, const Iterator &right) { return left.ptr == right.ptr; }
					friend bool operator!=(const Iterator &left, const Iterator &right) { return left.ptr != right.ptr; }
					value_type &operator*() const { return this->ptr->data; }
					value_type *operator->() const { return &(this->ptr->data); }
					Iterator &operator++()
					{
						if (ptr == end)
							return *this;
						if (ptr->right != nullptr)
						{
							ptr = ptr->right;
							while (ptr->left != nullptr)
							{
								ptr = ptr->left;
							}
							return *this;
						}
						if (ptr->parent->left == ptr)
						{
							ptr = ptr->parent;
							return *this;
						}
						if (ptr->parent->right == ptr)
						{
							ptr = ptr->parent->parent;
							return *this;
						}
						return *this;
					}
					Iterator &operator--()
					{
					}
					Iterator operator++(int)
					{
					}
					Iterator operator--(int)
					{
					}
			};

			class Const_Iterator : public Iterator
			{
				public:
					Const_Iterator() {}
					Const_Iterator(node *x) : Iterator(x) {}
					Const_Iterator(const Const_Iterator &it) : Iterator(it) {}
					Const_Iterator &operator=(const Const_Iterator &it)
					{
						if (&it != this)
							this->ptr = it.ptr;
						return *this;
					}
					virtual ~Const_Iterator() {}

					friend bool operator==(const Const_Iterator &left, const Const_Iterator &right) { return left.ptr == right.ptr; }
					friend bool operator!=(const Const_Iterator &left, const Const_Iterator &right) { return left.ptr != right.ptr; }
					const T &operator*() const { return this->ptr->data; }
					const T *operator->() const { return &(this->ptr->data); }
			};

			class Reverse_Iterator
			{
				protected:
					node *ptr;
				public:
					Reverse_Iterator() {}
					Reverse_Iterator(node *x) : ptr(x) {}
					Reverse_Iterator(const Reverse_Iterator &it) : ptr(it.ptr) {}
					Reverse_Iterator &operator=(const Reverse_Iterator &it)
					{
						if (&it != this)
							ptr = it.ptr;
						return *this;
					}
					virtual ~Reverse_Iterator() {}

					friend bool operator==(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr == right.ptr; }
					friend bool operator!=(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr != right.ptr; }
					T &operator*() const { return this->ptr->data; }
					T *operator->() const { return &(this->ptr->data); }
					Iterator &operator++()
					{
					}
					Iterator &operator--()
					{
					}
					Iterator operator++(int)
					{
					}
					Iterator operator--(int)
					{
					}
			};

			class Const_Reverse_Iterator : public Reverse_Iterator
			{
				public:
					Const_Reverse_Iterator() {}
					Const_Reverse_Iterator(node *x) : Reverse_Iterator(x) {}
					Const_Reverse_Iterator(const Const_Iterator &it) : Reverse_Iterator(it) {}
					Const_Reverse_Iterator &operator=(const Const_Reverse_Iterator &it)
					{
						if (&it != this)
							this->ptr = it.ptr;
						return *this;
					}
					virtual ~Const_Reverse_Iterator() {}

					friend bool operator==(const Const_Reverse_Iterator &left, const Const_Reverse_Iterator &right)
					{
						return left.ptr == right.ptr;
					}
					friend bool operator!=(const Const_Reverse_Iterator &left, const Const_Reverse_Iterator &right)
					{
						return left.ptr != right.ptr;
					}
					const T &operator*() const { return this->ptr->data; }
					const T *operator->() const { return &(this->ptr->data); }
			};

		public:
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
					: _root(nullptr), _comp(comp) {}

			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
					: _root(nullptr), _comp(comp) { insert(first, last); }

			map(const map &x) : _root(nullptr), _comp(x._comp) { insert(x.begin(), x.end()); }

			std::pair<iterator, bool> insert(const value_type &val)
			{
				node *copy;
				if (_root == nullptr)
				{
					_root = Create_Node(val);
					_rend = Create_Node();
					_lend = Create_Node();
					_root->right = _rend;
					_rend->parent = _root;
					_root->left = _lend;
					_lend->parent = _root;
					copy = _root;
					return std::pair<iterator, bool>(iterator(copy, _rend), true);
				}
				DeleteEndElements();
				copy = _root;
				while (copy)
				{
					if (!_comp(val.first, copy->data.first) && !_comp(copy->data.first, val.first))
					{
						return std::pair<iterator, bool>(iterator(copy, _rend), false);
					}
					else if (_comp(val.first, copy->data.first))
					{
						if (copy->left == nullptr)
						{
							copy->left = Create_Node(val);
							copy->left->parent = copy;
							copy->left->left = _lend;
							_lend->parent = copy->left;
							node *temp = _root;
							while (temp->right)
							{
								temp = temp->right;
							}
							temp->right = _rend;
							_rend->parent = temp;
							return std::pair<iterator, bool>(iterator(copy->left, _rend), true);
						}
						else
							copy = copy->left;
					}
					else
					{
						if (copy->right == nullptr)
						{
							copy->right = Create_Node(val);
							copy->right->parent = copy;
							copy->right->right = _rend;
							_rend->parent = copy->right;
							node *temp = _root;
							while (temp->left)
							{
								temp = temp->left;
							}
							temp->left = _lend;
							_lend->parent = temp;
							return std::pair<iterator, bool>(iterator(copy->right, _rend), true);
						}
						else
							copy = copy->right;
					}
				}
				return std::pair<iterator, bool>(iterator(_root, _rend), true);
			}

			iterator insert(iterator position, const value_type &val)
			{
				std::pair<iterator, bool> returned_value = insert(val);
				return returned_value.first;
			}

			template<class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first++);
				}
			}

			bool empty() const { return _root == nullptr; }

			iterator find(const key_type &k)
			{
				node *temp = _root;
				return iterator(Find_Element(k, temp), _rend);
			}

			const_iterator find(const key_type &k) const
			{
				node *temp = _root;
				return const_iterator(Find_Element(k, temp));
			}

			size_type count(const key_type &k) const
			{
				node *temp = _root;
				temp = Find_Element(k, temp);
				return temp == _rend ? 0 : 1;
			}

			iterator lower_bound(const key_type &k)
			{
				iterator temp = find(k);
				return temp == end() ? end() : --temp;
			}

			const_iterator lower_bound(const key_type &k) const
			{
				const_iterator temp = find(k);
				return temp == end() ? end() : --temp;
			}

			iterator upper_bound(const key_type &k)
			{
				iterator temp = find(k);
				return temp == end() ? end() : ++temp;
			}

			const_iterator upper_bound(const key_type &k) const
			{
				const_iterator temp = find(k);
				return temp == end() ? end() : ++temp;
			}

			void clear()
			{
				DeleteEndElements();
				Clear_Three();
				delete _rend;
				delete _lend;
			}

			mapped_type &operator[](const key_type &k)
			{
				return insert(std::pair<key_type, mapped_type>(k, mapped_type())).first.operator->()->second;
			}

			//		std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			//		{
			//		}
			//
			//		std::pair<iterator, iterator> equal_range(const key_type &k)
			//		{
			//
			//		}

		private:
			void Clear_Three(node *x)
			{
				if (x != nullptr)
				{
					Clear_Three(x->left);
					Clear_Three(x->right);
					delete x;
				}
			}

			node *Create_Node(const value_type &value = value_type())
			{
				node *new_node = new node(value);
				new_node->parent = nullptr;
				new_node->left = nullptr;
				new_node->right = nullptr;
				return new_node;
			}

			node *SearchBeginElement()
			{
				node *temp = _root;
				while (temp->left != _lend)
				{
					temp = temp->left;
				}
				return temp;
			}

			node *SearchRBeginElement()
			{
				node *temp = _root;
				while (temp->right != _rend)
				{
					temp = temp->right;
				}
				return temp;
			}

			void DeleteEndElements()
			{
				node *temp = SearchRBeginElement();
				_rend->parent = nullptr;
				temp->right = nullptr;
				temp = SearchBeginElement();
				_lend->parent = nullptr;
				temp->left = nullptr;
			}

			node *Find_Element(const key_type &k, node *x)
			{
				if (x == _rend || x == _lend)
					return x == _rend ? _rend : _lend;
				if (!_comp(k, x->data.first) && !_comp(x->data.first, k))
					return x;
				else
					return _comp(k, x->data.first) ? Find_Element(k, x->left) : Find_Element(k, x->right);
			}
	};
}
