#pragma once

#include "list.hpp"

namespace ft
{
	template<class T, class Container = list <T> >
	class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

		private:
			Container base;

		public:
			explicit stack(const container_type &container = container_type()) : base(container) {}
			bool empty() const { return base.empty(); }
			size_type size() const { return base.size(); }
			value_type &top() { return base.back(); }
			const value_type &top() const { return base.back(); }
			void push(const value_type &val) { base.push_back(val); }
			void pop() { base.pop_back(); }

			friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.base == rhs.base; }
			friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.base != rhs.base; }
			friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.base < rhs.base; }
			friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.base > rhs.base; }
			friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.base <= rhs.base; }
			friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.base >= rhs.base; }
	};
}
