#ifndef FT_CONTAINERS_CONST_BIDIRECTIONAL_HPP
#define FT_CONTAINERS_CONST_BIDIRECTIONAL_HPP


#include "Bidirectional.hpp"

template<class Category, class T>
class Const_Bidirectional : public Bidirectional<Category, T>
{
	public:
		typename Iterator<Category, T>::reference operator*()
		{
			return *(this->item);
		}
};


#endif
