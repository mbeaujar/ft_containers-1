#include <map>
#include <iostream>
#include "containers/map.hpp"

template <typename T>
void printmap(T &a) 
{
	typename T::iterator it = a.begin();
	typename T::iterator ite = a.end();

	for (; it != ite; it++) {
		std::cout << "key: " << it->first << " " << "value: " << it->second << std::endl;
	}
}

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

int main()
{
	ft::map<int, int> a;
	ft::map<int, int>::iterator it = a.begin();
	for (int i = 0; i < 20000; i++)
		it = a.insert(it,  ft::make_pair(i, 15));
	printmap(a);
	ft::map<int, int> b;
	b.insert(a.begin(), a.end());
	printmap(b);
	return 0;
}