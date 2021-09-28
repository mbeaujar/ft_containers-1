/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:32:37 by ranaili           #+#    #+#             */
/*   Updated: 2021/09/28 23:01:58 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "containers/Utils.hpp"
#include "containers/Vector.hpp"

template <typename T>
void printvector(ft::vector<T> a)
{
    typename ft::vector<T>::iterator it;
    int i = 0;
    for (it = a.begin(); it != a.end(); it++, i++)
        std::cout << "#" << i << " " << *it << std::endl;
    std::cout << "size: " << a.size() << std::endl;
    std::cout << "capacity: " << a.capacity() << std::endl;
    std::cout << std::endl;
}

int main ()
{
  // constructors used in the same order as described above:
  ft::vector<int> first;                                // empty vector of ints
  ft::vector<int> second (4,100);                       // four ints with value 100
  ft::vector<int> fourth (second);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  // int myints[] = {16,2,77,29};
  // ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  printvector(fourth);

  std::cout << "The contents of fifth are:";
  std::cout << '\n';

  return 0;
}

// int main()
// {
//     std::cout << std::boolalpha;
//     std::cout << "is_integral:" << std::endl;
//     std::cout << "char: " << ft::is_integral<char>::value << std::endl;
//     std::cout << "int: " << ft::is_integral<int>::value << std::endl;
//     std::cout << "float: " << ft::is_integral<float>::value << std::endl;

//     std::vector<int> a;

//     std::vector<int>::iterator b;

//     return 0; 
// }


