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

int main(void)
{
	ft::map<int, int> a;
	for (int i = 0; i < 2; i++)
		a.insert(ft::make_pair(i, 15));
	a.printBST();
	a.erase(a.begin());
	a.printBST();
	a.erase(a.begin());
	a.printBST();
	return (0);
}