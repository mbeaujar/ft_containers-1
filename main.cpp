#include <map>
#include <iostream>

template <typename T>
void printmap(T &a) 
{
	typename T::iterator it = a.begin();
	typename T::iterator ite = a.end();

	for (; it != ite; it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}
}

int main()
{
	std::map<int, std::string> a;
	a.insert(std::make_pair(10, "mael"));
	a.insert(std::make_pair(12, "ramzi"));
	a.insert(std::make_pair(11, "ali"));
	a.insert(std::make_pair(9, "sofiane"));
	a.insert(std::pair<int, std::string>(1, "miguel"));
	printmap(a);
	return 0;
}