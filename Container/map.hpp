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


			iterator begin() { return iterator(_root ? SearchBeginElement() : _rend, _rend, _lend); }
			const_iterator begin() const { return const_iterator(_root ? SearchBeginElement() : _rend, _rend, _lend); }
			iterator end() { return iterator(_rend, _rend, _lend); }
			const_iterator end() const { return const_iterator(_rend, _rend, _lend); }
			reverse_iterator rbegin() { return reverse_iterator(_root ? SearchRBeginElement() : _lend, _rend, _lend); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_root ? SearchRBeginElement() : _lend, _rend, _lend); }
			reverse_iterator rend() { return reverse_iterator(_lend, _rend, _lend); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_lend, _rend, _lend); }

			class value_compare
			{
					friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type &x, const value_type &y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			node *_root;
			node *_rend;
			node *_lend;
			key_compare _comp;

			class Iterator
			{
				protected:
					node *ptr;
					node *rend;
					node *lend;
				public:
					Iterator() {}
					Iterator(node *x, node *rend, node *lend) : ptr(x), rend(rend), lend(lend) {}
					Iterator(const Iterator &it) : ptr(it.ptr), rend(it.lend), lend(it.lend) {}
					Iterator &operator=(const Iterator &it)
					{
						if (&it != this)
						{
							ptr = it.ptr;
							rend = it.rend;
							lend = it.lend;
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
						if (ptr == rend)
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
							node *temp = ptr;
							ptr = ptr->parent;
							while (ptr->left != temp)
							{
								temp = ptr;
								ptr = ptr->parent;
							}
							return *this;
						}
						return *this;
					}
					Iterator &operator--()
					{
						if (ptr == lend)
							return *this;
						if (ptr->left != nullptr)
						{
							ptr = ptr->left;
							while (ptr->right != nullptr)
							{
								ptr = ptr->right;
							}
							return *this;
						}
						if (ptr->parent->right == ptr)
						{
							ptr = ptr->parent;
							return *this;
						}
						if (ptr->parent->left == ptr)
						{
							node *temp = ptr;
							ptr = ptr->parent;
							while (ptr->right != temp)
							{
								temp = ptr;
								ptr = ptr->parent;
							}
							return *this;
						}
						return *this;
					}
					Iterator operator++(int)
					{
						Iterator copy(*this);
						++(*this);
						return copy;
					}
					Iterator operator--(int)
					{
						Iterator copy(*this);
						--(*this);
						return copy;
					}
			};

			class Const_Iterator : public Iterator
			{
				public:
					Const_Iterator() {}
					Const_Iterator(node *x, node *rend, node *lend) : Iterator(x, rend, lend) {}
					Const_Iterator(const Const_Iterator &it) : Iterator(it) {}
					Const_Iterator(Iterator it) : Iterator(it) {}
					Const_Iterator &operator=(const Const_Iterator &it)
					{
						if (&it != this)
						{
							this->ptr = it.ptr;
							this->rend = it.rend;
							this->lend = it.lend;
						}
						return *this;
					}
					virtual ~Const_Iterator() {}

					value_type &operator*() const { return this->ptr->data; }
					value_type *operator->() const { return &(this->ptr->data); }
			};

			class Reverse_Iterator
			{
				protected:
					node *ptr;
					node *rend;
					node *lend;
				public:
					Reverse_Iterator() {}
					Reverse_Iterator(node *x, node *rend, node *lend) : ptr(x), rend(rend), lend(lend) {}
					Reverse_Iterator(const Reverse_Iterator &it) : ptr(it.ptr), rend(it.rend), lend(it.lend) {}
					Reverse_Iterator &operator=(const Reverse_Iterator &it)
					{
						if (&it != this)
						{
							ptr = it.ptr;
							rend = it.rend;
							lend = it.lend;
						}
						return *this;
					}
					virtual ~Reverse_Iterator() {}

					friend bool operator==(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr == right.ptr; }
					friend bool operator!=(const Reverse_Iterator &left, const Reverse_Iterator &right) { return left.ptr != right.ptr; }
					value_type &operator*() const { return this->ptr->data; }
					value_type *operator->() const { return &(this->ptr->data); }
					Reverse_Iterator &operator++()
					{
						if (ptr == lend)
							return *this;
						if (ptr->left != nullptr)
						{
							ptr = ptr->left;
							while (ptr->right != nullptr)
							{
								ptr = ptr->right;
							}
							return *this;
						}
						if (ptr->parent->right == ptr)
						{
							ptr = ptr->parent;
							return *this;
						}
						if (ptr->parent->left == ptr)
						{
							node *temp = ptr;
							ptr = ptr->parent;
							while (ptr->right != temp)
							{
								temp = ptr;
								ptr = ptr->parent;
							}
							return *this;
						}
						return *this;
					}
					Reverse_Iterator &operator--()
					{
						if (ptr == rend)
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
							node *temp = ptr;
							ptr = ptr->parent;
							while (ptr->left != temp)
							{
								temp = ptr;
								ptr = ptr->parent;
							}
							return *this;
						}
						return *this;
					}
					Reverse_Iterator operator++(int)
					{
						Reverse_Iterator copy(*this);
						++(*this);
						return copy;
					}
					Reverse_Iterator operator--(int)
					{
						Reverse_Iterator copy(*this);
						--(*this);
						return copy;
					}
			};
			//
			class Const_Reverse_Iterator : public Reverse_Iterator
			{
				public:
					Const_Reverse_Iterator() {}
					Const_Reverse_Iterator(node *x, node *rend, node *lend) : Reverse_Iterator(x, rend, lend) {}
					Const_Reverse_Iterator(const Const_Reverse_Iterator &it) : Reverse_Iterator(it) {}
					Const_Reverse_Iterator(Reverse_Iterator it) : Reverse_Iterator(it) {}
					Const_Reverse_Iterator &operator=(const Const_Reverse_Iterator &it)
					{
						if (&it != this)
						{
							this->ptr = it.ptr;
							this->rend = it.rend;
							this->lend = it.lend;
						}
						return *this;
					}
					virtual ~Const_Reverse_Iterator() {}

					value_type &operator*() const { return this->ptr->data; }
					value_type *operator->() const { return &(this->ptr->data); }
			};

		public:
			explicit map(const key_compare &comp = key_compare(), const allocator_type & = allocator_type())
					: _root(nullptr), _rend(nullptr), _lend(nullptr), _comp(comp) {}

			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type & = allocator_type())
					: _root(nullptr), _rend(nullptr), _lend(nullptr), _comp(comp) { insert(first, last); }

			map(const map &x) : _root(nullptr), _rend(nullptr), _lend(nullptr), _comp(x._comp)
			{
				Create_Three_Copy(x._root, x._rend, x._lend);
			}

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
					return std::pair<iterator, bool>(iterator(copy, _rend, _lend), true);
				}
				DeleteEndElements();
				copy = _root;
				while (copy)
				{
					if (!_comp(val.first, copy->data.first) && !_comp(copy->data.first, val.first))
					{
						Add_LEnd_Element();
						Add_REnd_Element();
						return std::pair<iterator, bool>(iterator(copy, _rend, _lend), false);
					}
					else if (_comp(val.first, copy->data.first))
					{
						if (copy->left == nullptr)
						{
							copy->left = Create_Node(val);
							copy->left->parent = copy;
							Add_LEnd_Element();
							Add_REnd_Element();
							return std::pair<iterator, bool>(iterator(copy->left, _rend, _lend), true);
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
							Add_REnd_Element();
							Add_LEnd_Element();
							return std::pair<iterator, bool>(iterator(copy->right, _rend, _lend), true);
						}
						else
							copy = copy->right;
					}
				}
				return std::pair<iterator, bool>(iterator(_root, _rend, _lend), true);
			}

			iterator insert(iterator, const value_type &val)
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
				iterator temp = Find_Elem(k);
				if ((!_comp(k, temp.operator->()->first) && !_comp(temp.operator->()->first, k)))
					return temp;
				return end();
			}

			const_iterator find(const key_type &k) const
			{
				iterator temp = Find_Elem(k);
				if ((!_comp(k, temp.operator->()->first) && !_comp(temp.operator->()->first, k)))
					return temp;
				return end();
			}

			size_type count(const key_type &k) const
			{
				if (find(k) != end())
					return 1;
				return 0;
			}

			iterator lower_bound(const key_type &k)
			{
				return Find_Elem(k);
			}

			const_iterator lower_bound(const key_type &k) const
			{
				return Find_Elem(k);
			}

			iterator upper_bound(const key_type &k)
			{
				iterator temp = Find_Elem(k);
				if ((!_comp(k, temp.operator->()->first) && !_comp(temp.operator->()->first, k)))
					return ++temp;
				return temp == end() ? end() : temp;
			}

			const_iterator upper_bound(const key_type &k) const
			{
				const_iterator temp = Find_Elem(k);
				if ((!_comp(k, temp.operator->()->first) && !_comp(temp.operator->()->first, k)))
					return ++temp;
				return temp == end() ? end() : temp;
			}

			void clear()
			{
				DeleteEndElements();
				node *temp = _root;
				Clear_Three(temp);
				_root = nullptr;
				delete _rend;
				_rend = nullptr;
				delete _lend;
				_lend = nullptr;
			}

			mapped_type &operator[](const key_type &k)
			{
				return insert(std::pair<key_type, mapped_type>(k, mapped_type())).first.operator->()->second;
			}

			size_type size() const
			{
				int count = 0;
				node *temp = _root;
				Get_Three_Size(count, temp);
				return count;
			}

			size_type max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(_root)); }

			void swap(map &x)
			{
				key_compare c = _comp;
				_comp = x._comp;
				x._comp = c;
				node *r = _root;
				_root = x._root;
				x._root = r;
				node *re = _rend;
				_rend = x._rend;
				x._rend = re;
				node *le = _lend;
				_lend = x._lend;
				x._lend = le;
			}

			key_compare key_comp() const { return _comp; }

			value_compare value_comp() const { return value_compare(_comp).comp; }

			std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			{
				return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}

			std::pair<iterator, iterator> equal_range(const key_type &k)
			{
				return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}

			size_type erase(const key_type &k)
			{
				int out = 0;
				if (find(k) != end())
				{
					del_node(k);
					out = 1;
				}
				return out;
			}

			void erase(iterator position)
			{
				erase(position.operator->()->first);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
				{
					del_node((first++).operator->()->first);
				}
			}


		private:
			void Clear_Three(node *x)
			{
				if (x != nullptr)
				{
					Clear_Three(x->left);
					Clear_Three(x->right);
					x->left = nullptr;
					x->right = nullptr;
					x->parent = nullptr;
					delete x;
					x = nullptr;
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

			node *SearchBeginElement() const
			{
				return _lend->parent;
			}

			node *SearchRBeginElement() const
			{
				return _rend->parent;
			}

			void DeleteEndElements()
			{
				node *temp = SearchRBeginElement();
				temp->right = nullptr;
				_rend->parent = nullptr;
				temp = SearchBeginElement();
				temp->left = nullptr;
				_lend->parent = nullptr;
			}

			iterator Find_Elem(const key_type &k) const
			{
				iterator begin(_root ? SearchBeginElement() : _rend, _rend, _lend);
				iterator end(_rend, _rend, _lend);
				while (begin != end)
				{
					if (_comp(k, begin.operator->()->first) ||
					    (!_comp(k, begin.operator->()->first) && !_comp(begin.operator->()->first, k)))
						return begin;
					++begin;
				}
				return begin;
			}

			//			node *Find_Element(const key_type &k, node *x) const
			//			{
			//				if (x == _rend || x == _lend || x == nullptr || (!_comp(k, x->data.first) && !_comp(x->data.first, k)))
			//					return x;
			//				else
			//					return _comp(k, x->data.first) ? Find_Element(k, x->left) : Find_Element(k, x->right);
			//			}

			void Create_Three_Copy(node *x, node *rend, node *lend)
			{
				if (x == nullptr || x == rend || x == lend)
					return;
				insert(x->data);
				Create_Three_Copy(x->left, rend, lend);
				Create_Three_Copy(x->right, rend, lend);
			}

			void Get_Three_Size(int &count, node *x) const
			{
				if (x != nullptr && x != _rend && x != _lend)
				{
					Get_Three_Size(count, x->left);
					Get_Three_Size(count, x->right);
					++count;
				}
			}

			void Add_REnd_Element()
			{
				node *temp = _root;
				while (temp->right)
				{
					temp = temp->right;
				}
				temp->right = _rend;
				_rend->parent = temp;
			}

			void Add_LEnd_Element()
			{
				node *temp = _root;
				while (temp->left)
				{
					temp = temp->left;
				}
				temp->left = _lend;
				_lend->parent = temp;
			}

			void del_node(const key_type &k)
			{
				DeleteEndElements();
				_root = Delete_Node(_root, k);
				if (_root)
				{
					Add_LEnd_Element();
					Add_REnd_Element();
				}
			}

			node *Delete_Node(node *root, const key_type &k)
			{
				if (root == nullptr)
					return root;
				if (_comp(k, root->data.first))
				{
					root->left = Delete_Node(root->left, k);
					if (root->left)
						root->left->parent = root;
				}
				else if (_comp(root->data.first, k))
				{
					root->right = Delete_Node(root->right, k);
					if (root->right)
						root->right->parent = root;
				}
				else
				{
					if (Check_What_Right_And_Left_Empty(root))
					{
						delete root;
						root = nullptr;
					}
					else if (Check_What_Right_Or_Left_Empty(root))
					{
						node *temp;
						if (root->left)
							temp = root->left;
						else
							temp = root->right;
						delete root;
						root = temp;
					}
					else
					{
						node *temp;
						if (!root->right->left)
						{
							root->right->left = root->left;
							root->left->parent = root->right;
							temp = root->right;
							delete root;
							root = temp;
						}
						else
						{
							temp = Search_left_from_current_node(root->right);
							temp->parent->left = nullptr;
							temp->right = root->right;
							root->right->parent = temp;
							temp->left = root->left;
							root->left->parent = temp;
							delete root;
							root = temp;
						}
					}
				}
				return root;
			}

			node *Search_left_from_current_node(node *root)
			{
				if (root->left == nullptr)
					return root;
				return Search_left_from_current_node(root->left);
			}

			bool Check_What_Right_And_Left_Empty(node *root)
			{
				if (root->left == nullptr && root->right == nullptr)
					return true;
				return false;
			}

			bool Check_What_Right_Or_Left_Empty(node *root)
			{
				if ((root->left == nullptr && root->right != nullptr) || (root->left != nullptr && root->right == nullptr))
					return true;
				return false;
			}
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		typename map<Key, T, Compare, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator rhs_iter = rhs.begin();
		for (; lhs_iter != lhs.end() && rhs_iter != rhs.end(); ++lhs_iter, ++rhs_iter)
		{
			if (*lhs_iter != *rhs_iter)
				return false;
		}
		if (lhs_iter == lhs.end() && rhs_iter == rhs.end())
			return true;
		return false;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		typename map<Key, T, Compare, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator rhs_iter = rhs.begin();
		for (; lhs_iter != lhs.end() && rhs_iter != rhs.end(); ++lhs_iter, ++rhs_iter)
		{
			if (*lhs_iter < *rhs_iter)
				return true;
			else if (*rhs_iter < *lhs_iter)
				return false;
			else
				continue;
		}
		if (lhs_iter == lhs.end() && rhs_iter != rhs.end())
			return true;
		return false;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return !(lhs == rhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return rhs < lhs; }

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return !(rhs < lhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) { return !(lhs < rhs); }

	template<class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs) { lhs.swap(rhs); }
}
