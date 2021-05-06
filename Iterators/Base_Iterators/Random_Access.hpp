#ifndef FT_CONTAINERS_RANDOM_ACCESS_HPP
#define FT_CONTAINERS_RANDOM_ACCESS_HPP

#include "Bidirectional.hpp"

template<class Category, class T>
class Random_Access : public Bidirectional<Category, T>
{
	public:
		Random_Access() : Bidirectional<Category, T>() {}
		Random_Access(typename Random_Access<Category, T>::pointer new_object) : Bidirectional<Category, T>(new_object) {}
		bool operator<(Random_Access<Category, T> &rhs) { return this->item < rhs.item; }
		bool operator>(Random_Access<Category, T> &rhs) { return this->item > rhs.item; }
		bool operator<=(Random_Access<Category, T> &rhs) { return this->item <= rhs.item; }
		bool operator>=(Random_Access<Category, T> &rhs) { return this->item >= rhs.item; }
		typename Random_Access<Category, T>::reference operator[](size_t n) { return *(this->item + n); }
		Random_Access<Category, T> operator+(size_t n)
		{
			Random_Access<Category, T> returned_object(*this);
			returned_object.item += n;
			return returned_object;
		}
		friend Random_Access<Category, T> operator+(size_t n, Random_Access<Category, T> &rhs)
		{
			Random_Access<Category, T> returned_object(rhs);
			returned_object.item += n;
			return returned_object;
		}
		Random_Access<Category, T> operator-(size_t n)
		{
			Random_Access<Category, T> returned_object(*this);
			returned_object.item -= n;
			return returned_object;
		}
		Random_Access<Category, T> operator-(Random_Access<Category, T> &rhs)
		{
			Random_Access<Category, T> returned_object(*this);
			returned_object.item -= rhs.item;
			return returned_object;
		}
		Random_Access<Category, T> &operator+=(size_t n)
		{
			this->item += n;
			return *this;
		}
		Random_Access<Category, T> &operator-=(size_t n)
		{
			this->item -= n;
			return *this;
		}
};


#endif
