#ifndef FT_CONTAINERS_VECTOR_ITERATOR_HPP
#define FT_CONTAINERS_VECTOR_ITERATOR_HPP

#include "Random_Access.hpp"

template<class T>
class Vector_Iterator : public Random_Access<std::random_access_iterator_tag, T>
{
	public:
		Vector_Iterator() : Random_Access<std::random_access_iterator_tag, T>() {}
		Vector_Iterator(typename Random_Access<std::random_access_iterator_tag, T>::pointer new_object)
				: Random_Access<std::random_access_iterator_tag, T>(new_object) {}
};


#endif
