#ifndef FT_CONTAINERS_INPUT_ITERATOR_TAG_HPP
#define FT_CONTAINERS_INPUT_ITERATOR_TAG_HPP

#include "base_iterator.hpp"
#include <iostream>

template<class T>
class input_iterator_tag
{
	private:
		typedef typename iterator<input_iterator_tag<T>, T> it;
		input_iterator_tag();

	public:
		input_iterator_tag(const it &);
		input_iterator_tag &operator=(const it &);
		bool operator==(const it &)
};

#endif
