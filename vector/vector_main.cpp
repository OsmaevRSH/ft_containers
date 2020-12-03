#include <iostream>
#include <vector>
#include "vector.hpp"

using namespace std;

int main()
{
	cout << "vector()" << endl;
	vector<int> first;
	ft::vector<int> second;
	cout << endl;

	cout << "size_type n, const value_type& val = value_type()" << endl;
	vector<int> c(5, 7);
	for (int i = 0; i < 5; ++i)
		cout << c[i];
	cout << endl;
	ft::vector<int> d((size_t) 5, 7);
	for (int i = 0; i < 5; ++i)
		cout << d[i];
	cout << endl;

	cout << "template <class InputIterator>\n"
			"         vector (InputIterator first, InputIterator last,\n"
			"                 const allocator_type& alloc = allocator_type());" << endl;
	vector<int> e(c.begin(), c.end());
	for (int i = 0; i < 5; ++i)
		cout << c[i];
	cout << endl;
	ft::vector<int> f(c.begin(), c.end());
	for (int i = 0; i < 5; ++i)
		cout << d[i];
	cout << endl;

	cout << "vector (const vector& x);" << endl;
	vector<int> g(e);
	for (int i = 0; i < 5; ++i)
		cout << c[i];
	cout << endl;
	ft::vector<int> h(f);
	for (int i = 0; i < 5; ++i)
		cout << d[i];
	cout << endl;
}