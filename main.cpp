/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:32:37 by ranaili           #+#    #+#             */
/*   Updated: 2021/09/30 20:30:50 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "containers/Utils.hpp"
#include "containers/vector.hpp"
#include "containers/iterator.hpp"

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "m = size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

class foo {
	public:
		foo(void) { };
		~foo(void) { };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(int src) { this->value = src; return *this; };
		int getValue(void) const { return this->value; };
	private:
		int	value;
};

std::ostream	&operator<<(std::ostream &o, foo const &bar) {
	o << bar.getValue();
	return o;
}

void	is_empty(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct)
{
	std::cout << "m = is_empty: " << vct.empty() << std::endl;
}


// #define TESTED_TYPE int



template <class T, class Alloc>
void	cmp(const TESTED_NAMESPACE::vector<T, Alloc> &lhs, const TESTED_NAMESPACE::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(4);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2(4);

	cmp(vct, vct);  // 0
	cmp(vct, vct2); // 1

	vct2.resize(10);

	cmp(vct, vct2); // 2
	cmp(vct2, vct); // 3

	vct[2] = 42;

	cmp(vct, vct2); // 4
	cmp(vct2, vct); // 5

	swap(vct, vct2);

	cmp(vct, vct2); // 6
	cmp(vct2, vct); // 7

	return (0);
}


// int		main(void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(5);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin(), ite = vct.end();

// 	std::cout << "len: " << (ite - it) << std::endl;
// 	for (; it != ite; ++it)
// 		*it = (ite - it);

// 	it = vct.begin();
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_range(it, --(--ite));
// 	for (int i = 0; it != ite; ++it)
// 		*it = ++i * 5;

// 	it = vct.begin();
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_copy(vct);
// 	for (int i = 0; it != ite; ++it)
// 		*it = ++i * 7;
// 	vct_copy.push_back(42);
// 	vct_copy.push_back(21);

// 	std::cout << "\t-- PART ONE --" << std::endl;
// 	printSize(vct);
// 	printSize(vct_range);
// 	printSize(vct_copy);

// 	vct = vct_copy;
// 	vct_copy = vct_range;
// 	vct_range.clear();

// 	std::cout << "\t-- PART TWO --" << std::endl;
// 	printSize(vct);
// 	printSize(vct_range);
// 	printSize(vct_copy);
// 	return (0);
// }

