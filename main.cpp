#include <map>
#include <iostream>

template <typename T>
void printmap(T &a) 
{
	typename T::iterator it = a.begin();
	typename T::iterator ite = a.end();

	for (; it != ite; it++) {
		std::cout << "key: " << it->first << " " << "value: " << it->second << std::endl;
	}
}

int main()
{
	std::map<int, std::string> a;

	a.insert(std::make_pair(15, "mael"));
	a.insert(std::make_pair(5, "ramzi"));

	// printmap(a);


	std::map<std::string, std::string> b;

	b.insert(std::make_pair("PSG", "club de merde"));
	b.insert(std::make_pair("OM", "club de pauvre"));

	std::cout << "ici: " << b["OM"] << std::endl;

	b["OL"] = "fuck saint-etienne";
	std::cout << "ici: " << b["OL"] << std::endl;
	// printmap(b);

	// a.insert(std::pair<int, std::string>(1, "miguel"));
	return 0;
}