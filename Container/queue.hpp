#pragma once

namespace ft
{
	template<class T, class Container = list <T> >
	class queue
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

		private:
			Container base;

		public:
			explicit queue(const container_type &container = container_type()) : base(container) {}
			bool empty() const { return base.empty(); }
			size_type size() const { return base.size(); }
			value_type &front() { return base.front(); }
			const value_type &front() const { return base.front(); }
			value_type &back() { return base.back(); }
			const value_type &back() const { return base.back(); }
			void push(const value_type &val) { base.push_back(val); }
			void pop() { base.pop_back(); }

			friend bool operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs) { return lhs.base == rhs.base; }
			friend bool operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs) { return lhs.base != rhs.base; }
			friend bool operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs) { return lhs.base < rhs.base; }
			friend bool operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs) { return lhs.base > rhs.base; }
			friend bool operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs) { return lhs.base <= rhs.base; }
			friend bool operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs) { return lhs.base >= rhs.base; }
	};
}
