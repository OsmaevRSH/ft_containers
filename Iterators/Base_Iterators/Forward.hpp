#ifndef FT_CONTAINERS_FORWARD_HPP
#define FT_CONTAINERS_FORWARD_HPP

#include "Input.hpp"

template<class Category, class T>
class Forward : public Input<Category, T>
{
	public:
		Forward() : Input<Category, T>() {}
		Forward(typename Iterator<Category, T>::pointer new_object) : Input<Category, T>(new_object) {}
};


#endif
