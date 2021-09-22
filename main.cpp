/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:32:37 by ranaili           #+#    #+#             */
/*   Updated: 2021/09/22 17:55:38 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "containers/Utils.hpp"
#include "containers/Vector.hpp"


int main ()
{
  // constructors used in the same order as described above:
  ft::vector<int> first;                                // empty vector of ints
  ft::vector<int> second (4,100);                       // four ints with value 100
  ft::vector<int> third (second.begin(),second.end());  // iterating through second
  ft::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

// int main ()
// {
//   // constructors used in the same order as described above:
//   std::vector<int> first;                                // empty vector of ints
//   std::vector<int> second (4,100);                       // four ints with value 100
//   std::vector<int> third (second.begin(),second.end());  // iterating through second
//   std::vector<int> fourth (third);                       // a copy of third

//   // the iterator constructor can also be used to construct from arrays:
//   int myints[] = {16,2,77,29};
//   std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

//   std::cout << "The contents of fifth are:";
//   for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

//   return 0;
// }

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


int main()
{
  
    // allocator for string values
    allocator<string> myAllocator;
  
    // allocate space for three strings
    string* str = myAllocator.allocate(3);
  
    // construct these 3 strings
    myAllocator.construct(str, "Geeks");
    myAllocator.construct(str + 1, "for");
    myAllocator.construct(str + 2, "Geeks");
  
    cout << str[0] << str[1] << str[2];
  
    // destroy these 3 strings
    myAllocator.destroy(str);
    myAllocator.destroy(str + 1);
    myAllocator.destroy(str + 2);
  
    // deallocate space for 3 strings
    myAllocator.deallocate(str, 3);
}