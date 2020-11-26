#ifndef LIST_LIST_LIST_HPP_
#define LIST_LIST_LIST_HPP_

#include <iostream>

template<class T, class Alloc = std::allocator<T> >
class list
{
	private:
		typedef	T											value_type;
		typedef	Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
};

#endif
