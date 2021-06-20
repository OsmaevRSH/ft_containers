//#include <string>
//
//#include <iostream>
//#include <vector>
//#include <list>
//#include "vector.hpp"
//#include "list.hpp"
//#include "test.hpp"
//#include "stack.hpp"
//#include "map.hpp"
//#include <math.h>
//#include <sstream>
//#include <deque>
//#include <map>
////
////using namespace std;
////
//////template<class T>
//////void capacity_part(const vector<T> &first, const ft::vector<T> &second)
//////{
//////	cout << BLUE << "vector.size(): " << left << RESET;
//////	if (first.size() == second.size())
//////	{
//////		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
//////	}
//////	else
//////	{
//////		cout << RED << "[" << "FAILED" << "]" << endl;
//////		cout << "vector: " << first.size() << endl;
//////		cout << "ft::vector: " << second.size() << RESET << endl;
//////	}
//////	cout << BLUE << "vector.capacity(): " << RESET;
//////	if (first.capacity() == second.capacity())
//////	{
//////		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
//////	}
//////	else
//////	{
//////		cout << RED << "[" << "FAILED" << "]" << endl;
//////		cout << "vector: " << first.capacity() << endl;
//////		cout << "ft::vector: " << second.capacity() << RESET << endl;
//////	}
//////	cout << BLUE << "vector.empty(): " << RESET;
//////	if (first.empty() == second.empty())
//////	{
//////		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
//////	}
//////	else
//////	{
//////		cout << RED << "[" << "FAILED" << "]" << endl;
//////		cout << "vector: " << first.empty() << endl;
//////		cout << "ft::vector: " << second.empty() << RESET << endl;
//////	}
//////	cout << BLUE << "vector.max_size(): " << RESET;
//////	if (first.max_size() == second.max_size())
//////	{
//////		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
//////	}
//////	else
//////	{
//////		cout << RED << "[" << "FAILED" << "]" << endl;
//////		cout << "vector: " << first.max_size() << endl;
//////		cout << "ft::vector: " << second.max_size() << RESET << endl;
//////	}
//////}
//////
//////template<class T>
//////void vec_resize(vector<T> &first, ft::vector<T> &second, int n, T value)
//////{
//////	cout << BLUE << "---------------" << endl << RESET;
//////	first.resize(n, value);
//////	second.resize(n, value);
//////	stringstream one;
//////	stringstream two;
//////	cout << BLUE << "vector.resize(" << n << ", " << value << "): " << RESET;
//////	for (int i = 0; i < first.size(); ++i)
//////		one << first[i] << " ";
//////	for (int i = 0; i < second.size(); ++i)
//////		two << second[i] << " ";
//////	if (one.str() == two.str())
//////	{
//////		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
//////	}
//////	else
//////	{
//////		cout << RED << "[" << "FAILED" << "]" << endl;
//////		cout << "vector: " << one.str() << endl;
//////		cout << "ft::vector: " << two.str() << endl << RESET;
//////	}
//////	capacity_part(first, second);
//////}
//////
//////template<class T>
//////void vec_reserve(vector<T> &first, ft::vector<T> &second, int n)
//////{
//////	cout << BLUE << "---------------" << endl << RESET;
//////	cout << BLUE << "vector.reserve(): " << RESET;
//////	first.reserve(n);
//////	second.reserve(n);
//////	if (first.capacity() == second.capacity())
//////	{
//////		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
//////	}
//////	else
//////	{
//////		cout << "[" << "FAILED" << "]" << endl;
//////		cout << "vector: " << first.capacity() << endl;
//////		cout << "ft::vector: " << second.capacity() << endl;
//////	}
//////	capacity_part(first, second);
//////}
//////
//////template<class T>
//////void vec_push_back(vector<T> &first, ft::vector<T> &second)
//////{
//////	cout << BLUE << "---------------" << endl << RESET;
//////	cout << BLUE << "vector.push_back(): " << RESET;
//////	stringstream one;
//////	stringstream two;
//////	for (int i = 0; i < 100; ++i)
//////	{
//////		first.push_back(pow(i, 2));
//////		second.push_back(pow(i, 2));
//////	}
//////	for (int i = 0; i < first.size(); ++i)
//////		one << first[i] << " ";
//////	for (int i = 0; i < second.size(); ++i)
//////		two << second[i] << " ";
//////	if (one.str() == two.str())
//////	{
//////		cout << GREEN << "[" << "OK" << "]" << RESET << endl;
//////	}
//////	else
//////	{
//////		cout << RED << "[" << "FAILED" << "]" << endl;
//////		cout << "vector: " << one.str() << endl;
//////		cout << "ft::vector: " << two.str() << endl << RESET;
//////	}
//////	capacity_part(first, second);
//////}
////
////
//int main ()
//{
//	srand(time(NULL));
//	std::string various_strings[] = {"lesha", "good", "nice", "loooool", "not_bad)", "good_map"};
//	std::string working_str;
//	int working_int;
//
//	ft::map<int, std::string> ft_map_f;
//	std::map<int, std::string> std_map_f;
//
//	for (int i = 0; i < 20; ++i)
//	{
//		working_int = rand() % 100;
//		working_str = various_strings[rand() % 6];
//		ft_map_f.insert(std::make_pair(working_int, working_str));
//		std_map_f.insert(std::make_pair(working_int, working_str));
//	}
//	ft::map<int, std::string>::iterator first = ft_map_f.begin();
//	ft::map<int, std::string>::iterator last = ft_map_f.end();
//int i = 0;
//	while (first != last)
//	{
//		++i;
//		std::cout <<  first->first << ":" << first->second <<  "   ";
//		++first;
//	}
//
//	return 0;
//}