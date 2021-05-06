#ifndef FT_CONTAINERS_BIDIRECTIONAL_HPP
#define FT_CONTAINERS_BIDIRECTIONAL_HPP

#include "Forward.hpp"

template<class Category, class T>
class Bidirectional : public Forward<Category, T>
{
	public:
		Bidirectional() : Forward<Category, T>() {}
		Bidirectional(typename Bidirectional<Category, T>::pointer new_object) : Forward<Category, T>(new_object) {}
		Bidirectional<Category, T> &operator--()
		{
			--(this->item);
			return *this;
		}
		Bidirectional<Category, T> operator--(int)
		{
			Bidirectional<Category, T> returned_object(this->item);
			--(this->item);
			return returned_object;
		}
};


#endif
