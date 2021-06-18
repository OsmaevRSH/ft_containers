#pragma once

#include <iostream>

template<class Key, class T, class Compare = std::less<Key>, class Alloc = allocator <std::pair<const Key, T>>>
class map
{
	private:
		typedef struct Map_Node
		{
			Map_Node() {}
			Map_Node(const std::pair<Key, T> &x) : data(x), lower(nullptr), upper(nullptr), parent(nullptr) {}
			Map_Node(const Map_Node &x) : data(x.data), lower(x.lower), upper(x.upper), parent(x.parent) {}
			std::pair<Key, T> data;
			Map_Node *lower;
			Map_Node *upper;
			Map_Node *parent;
		} node;

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
		key_compare _comp;

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
				return std::pair<iterator(_root), true>();
			}
			copy = _root;
			while (copy)
			{
				if (copy->data.first == val.first)
				{
					return std::pair<iterator(copy), false>();
				}
				else if (_comp(copy->data.first, val.first))
				{
					if (copy->lower == nullptr)
					{
						copy->lower = Create_Node(val);
						copy->lower->parent = copy;
						return std::pair<iterator(copy->lower), true>();
					}
					else
						copy = copy->lower;
				}
				else
				{
					if (copy->upper == nullptr)
					{
						copy->upper = Create_Node(val);
						copy->upper->parent = copy;
						return std::pair<iterator(copy->upper), true>();
					}
					else
						copy = copy->upper;
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
		node *Create_Node(const value_type &value)
		{
			node *new_node = new node(value);
			new_node->parent = nullptr;
			new_node->lower = nullptr;
			new_node->upper = nullptr;
			return new_node;
		}


};
