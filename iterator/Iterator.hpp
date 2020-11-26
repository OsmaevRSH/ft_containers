#ifndef LIST_ITERATOR_ITERATOR_HPP_
#define LIST_ITERATOR_ITERATOR_HPP_

#include <cstddef>

template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
struct iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

#endif
