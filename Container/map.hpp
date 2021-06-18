#pragma once

#include <iostream>

template<class Key, class T, class Compare = std::less<Key>, class Alloc = allocator <std::pair<const Key, T>>>
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

		class Iterator
		{
			protected:
				node *ptr;
			public:
				Iterator() {}
				Iterator(node *x) : ptr(x) {}
				Iterator(const Iterator &it) : ptr(it.ptr) {}
				Iterator &operator=(const Iterator &it)
				{
					if (&it != this)
						ptr = it.ptr;
					return *this;
				}
				virtual ~Iterator() {}

				friend bool operator==(const Iterator &left, const Iterator &right) { return left.ptr == right.ptr; }
				friend bool operator!=(const Iterator &left, const Iterator &right) { return left.ptr != right.ptr; }
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

		class Const_Iterator : public Iterator
		{
			public:
				Const_Iterator() {}
				Const_Iterator(node *x) : Iterator(x) {}
				Const_Iterator(const Const_Iterator &it) : Iterator(it) {}
				Const_Iterator &operator=(const Const_Iterator &it)
				{
					if (&it != this)
						ptr = it.ptr;
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
						ptr = it.ptr;
					return *this;
				}
				virtual ~Const_Reverse_Iterator() {}

				friend bool operator==(const Const_Reverse_Iterator &left, const Const_Reverse_Iterator &right) { return left.ptr == right.ptr; }
				friend bool operator!=(const Const_Reverse_Iterator &left, const Const_Reverse_Iterator &right) { return left.ptr != right.ptr; }
				const T &operator*() const { return this->ptr->data; }
				const T *operator->() const { return &(this->ptr->data); }
		};

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
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
		node *_end;
		key_compare _comp;

		iterator begin() { return iterator(SearchBeginElement()); }
		const_iterator begin() const { return const_iterator(SearchBeginElement()); }
		iterator end() { return iterator(SearchRBeginElement()->right); }
		const_iterator end() const { return const_iterator(SearchRBeginElement()->right); }
		reverse_iterator rbegin() { return reverse_iterator(SearchRBeginElement()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(SearchRBeginElement()); }
		reverse_iterator rend() { return reverse_iterator(SearchBeginElement()->left); }
		const_reverse_iterator rend() const { return const_reverse_iterator(SearchBeginElement()->left); }

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
				_end = Create_Node();
				_root->right = _end;
				_end->right = _root;
				_root->left = _end;
				_end->left = _root;
				return std::pair<iterator(_root), true>();
			}
			DeleteEndElements();
			copy = _root;
			while (copy)
			{
				if (copy->data.first == val.first)
				{
					return std::pair<iterator(copy), false>();
				}
				else if (_comp(val.first, copy->data.first))
				{
					if (copy->left == nullptr)
					{
						copy->left = Create_Node(val);
						copy->left->parent = copy;
						copy->left->left = _end;
						_end->left = copy->left;
						return std::pair<iterator(copy->left), true>();
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
						copy->right->right = _end;
						_end->right = copy->right;
						return std::pair<iterator(copy->right), true>();
					}
					else
						copy = copy->right;
				}
			}
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


	private:
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
			while (temp->left != _end)
				temp = temp->left;
			return temp;
		}

		node *SearchRBeginElement()
		{
			node *temp = _root;
			while (temp->right != _end)
				temp = temp->right;
			return temp->right;
		}

		void DeleteEndElements()
		{
			node *temp = SearchRBeginElement();
			_end->right = nullptr;
			temp->right = nullptr;
			temp = SearchBeginElement();
			_end->left = nullptr;
			temp->left = nullptr;
		}


};
