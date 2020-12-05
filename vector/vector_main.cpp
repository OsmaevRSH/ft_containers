#include <iostream>
#include <vector>
#include "vector.hpp"

using namespace std;

int main()
{
	cout << "=====================vector()=====================\n";
	vector<int> first;
	first.push_back(1);
	first.push_back(1);
	first.push_back(1);
	first.push_back(1);
	first.push_back(1);
	first.push_back(1);
	first.push_back(1);
	first.push_back(1);
	first.push_back(1);
	cout << first.size() << endl;
	cout << first.capacity() << endl;
	cout << first.empty() << endl;
	cout << first.max_size() << endl;
}