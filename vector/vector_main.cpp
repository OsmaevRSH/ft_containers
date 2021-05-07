#include <iostream>
#include <vector>
#include "vector.hpp"
#include "../test.hpp"
#include <math.h>
#include <sstream>
#include <iomanip>

using namespace std;

template<class T>
void capacity_part(const vector<T> &first, const ft::vector<T> &second)
{
	cout << BLUE << "vector.size(): " << left << RESET;
	if (first.size() == second.size()) {
		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
	}
	else {
		cout << RED << "[" << "FAILED" << "]" << endl;
		cout << "vector: " << first.size() << endl;
		cout << "ft::vector: " << second.size() << RESET << endl;
	}
	cout << BLUE << "vector.capacity(): " << RESET;
	if (first.capacity() == second.capacity()) {
		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
	}
	else {
		cout << RED << "[" << "FAILED" << "]" << endl;
		cout << "vector: " << first.capacity() << endl;
		cout << "ft::vector: " << second.capacity() << RESET << endl;
	}
	cout << BLUE << "vector.empty(): " << RESET;
	if (first.empty() == second.empty()) {
		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
	}
	else {
		cout << RED << "[" << "FAILED" << "]" << endl;
		cout << "vector: " << first.empty() << endl;
		cout << "ft::vector: " << second.empty() << RESET << endl;
	}
	cout << BLUE << "vector.max_size(): " << RESET;
	if (first.max_size() == second.max_size()) {
		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
	}
	else {
		cout << RED << "[" << "FAILED" << "]" << endl;
		cout << "vector: " << first.max_size() << endl;
		cout << "ft::vector: " << second.max_size() << RESET << endl;
	}
}

template<class T>
void vec_resize(vector<T> &first, ft::vector<T> &second, int n, T value)
{
	cout << BLUE << "---------------" << endl << RESET;
	first.resize(n, value);
	second.resize(n, value);
	stringstream one;
	stringstream two;
	cout << BLUE << "vector.resize(" << n << ", " << value << "): " << RESET;
	for (int i = 0; i < first.size(); ++i)
		one << first[i] << " ";
	for (int i = 0; i < second.size(); ++i)
		two << second[i] << " ";
	if (one.str() == two.str()) {
		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
	}
	else {
		cout << RED << "[" << "FAILED" << "]" << endl;
		cout << "vector: " << one.str() << endl;
		cout << "ft::vector: " << two.str() << endl << RESET;
	}
	capacity_part(first, second);
}

template<class T>
void vec_reserve(vector<T> &first, ft::vector<T> &second, int n)
{
	cout << BLUE << "---------------" << endl << RESET;
	cout << BLUE << "vector.reserve(): " << RESET;
	first.reserve(n);
	second.reserve(n);
	if (first.capacity() == second.capacity()) {
		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
	}
	else {
		cout << "[" << "FAILED" << "]" << endl;
		cout << "vector: " << first.capacity() << endl;
		cout << "ft::vector: " << second.capacity() << endl;
	}
	capacity_part(first, second);
}

template<class T>
void vec_push_back(vector<T> &first, ft::vector<T> &second)
{
	cout << BLUE << "---------------" << endl << RESET;
	cout << BLUE << "vector.push_back(): " << RESET;
	stringstream one;
	stringstream two;
	for (int i = 0; i < 100; ++i) {
		first.push_back(pow(i, 2));
		second.push_back(pow(i, 2));
	}
	for (int i = 0; i < first.size(); ++i)
		one << first[i] << " ";
	for (int i = 0; i < second.size(); ++i)
		two << second[i] << " ";
	if (one.str() == two.str()) {
		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
	}
	else {
		cout << RED << "[" << "FAILED" << "]" << endl;
		cout << "vector: " << one.str() << endl;
		cout << "ft::vector: " << two.str() << endl << RESET;
	}
	capacity_part(first, second);
}

template<class T>
void vec_comparison(vector<T> &first, ft::vector<T> &second)
{
	cout << BLUE << "vector == ft::vector: " << RESET;
	stringstream one;
	stringstream two;
	for (int i = 0; i < first.size(); ++i)
		one << first[i] << " ";
	for (int i = 0; i < second.size(); ++i)
		two << second[i] << " ";
	if (one.str() == two.str()) {
		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
	}
	else {
		cout << RED << "[" << "FAILED" << "]" << endl;
		cout << "vector: " << one.str() << endl;
		cout << "ft::vector: " << two.str() << endl << RESET;
	}
}

int main()
{
	cout << YELLOW << "=====================vector()=====================\n" << RESET;
	{
		vector<int> first;
		ft::vector<int> second;
		capacity_part(first, second);
		vec_comparison(first, second);
	}
	cout << YELLOW << "=====================vector(size_type n)=====================\n" << RESET;
	{
		vector<int> first(10);
		ft::vector<int> second(10);
		capacity_part(first, second);
		vec_comparison(first, second);
	}
	cout << YELLOW << "=====================vector(size_type n, const value_type& val)=====================\n" << RESET;
	{
		vector<int> first(10, 4);
		ft::vector<int> second(static_cast<size_t>(10), 4);
		capacity_part(first, second);
		vec_comparison(first, second);
	}
	cout << YELLOW << "=====================push_back=====================\n" << RESET;
	{
		vector<int> first;
		ft::vector<int> second;
		vec_push_back(first, second);
		vec_comparison(first, second);
	}
	cout << YELLOW << "=====================iterators=====================\n" << RESET;
	{
		vector<int> first(10,5);
		ft::vector<int> second((size_t)10, 5);
		vector<int>::const_iterator a = first.begin();
		ft::vector<int>::const_iterator b = second.begin();
		for (int i = 0; i < 10; ++i)
		{
			cout << *a << " " << *b << endl;
			a++;
			b++;
		}
	}
}