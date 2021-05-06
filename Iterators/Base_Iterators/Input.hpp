#ifndef FT_CONTAINERS_INPUT_HPP
#define FT_CONTAINERS_INPUT_HPP

#include "Iterator.hpp"

template<class Category, class T>
class Input : public Iterator<Category, T>
{
	protected:
		Input() {}
		Input(typename Iterator<Category, T>::pointer new_object) : item(new_object) {}
		typename Iterator<Category, T>::pointer item;
	public:
		Input(const Input<Category, T> &copy) : item(copy.item) {}
		~Input() {}
		Input &operator=(const Input<Category, T> &copy)
		{
			if (*this != copy)
				item = copy.item;
			return *this;
		}
		bool operator==(const Input<Category, T> &compared_object)
		{
			return item == compared_object.item;
		}
		bool operator!=(const Input<Category, T> &compared_object)
		{
			return item != compared_object.item;
		}
		virtual typename Iterator<Category, T>::reference operator*()
		{
			return *(item);
		}
		virtual typename Iterator<Category, T>::pointer operator->()
		{
			return item;
		}
		Iterator<Category, T> &operator++()
		{
			++item;
			return *this;
		}
		Iterator<Category, T> operator++(int)
		{
			Input<Category, T> returned_object(item);
			++item;
			return returned_object;
		}
};


#endif