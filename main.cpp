#include <iostream>

// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

#ifndef FT
    #include <map>
    #include <stack>
    #include <vector>
    namespace ft = std;
#else
    #include "map.hpp"
    #include "stack.hpp"
    #include "vector.hpp"
#endif


// ---------------------- VECTOR --------------------------------------------------------------------------------


struct access {
    int id;
};

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

void vector_constructor()
{
    std::cout << " -------------- CONSTRUCTOR VECTOR --------------------" << std::endl;
    ft::vector<int> a;
    std::cout << ">> default constructor" << std::endl;
    printvector(a);

    ft::vector<int> b(2, 200);
    std::cout << ">> fill constructor" << std::endl;
    printvector(b);

    std::cout << ">> range constructor" << std::endl;
    ft::vector<int> c(b.begin(), b.end());
    printvector(c);

    std::cout << ">> copy constructor" << std::endl;
    ft::vector<int> d(c);
    printvector(d);

    // the iterator constructor can also be used to construct from arrays:
    std::cout << ">> construct from arrays" << std::endl;
    int myints[] = {16,2,77,29};
    ft::vector<int> e(myints, myints + sizeof(myints) / sizeof(int) );
    printvector(e);
}

void vector_assignation()
{
    std::cout << " -------------- ASSIGNATION VECTOR --------------------" << std::endl;
    ft::vector<int> a(3, 300);
    ft::vector<int> b(4, 400);
    ft::vector<int> c;

    std::cout << ">> before assign vector" << std::endl;
    printvector(c);

    std::cout << ">> after assign vector" << std::endl;
    c = a;                                                                                                                
    printvector(c);

    std::cout << ">> after assign vector to another vector" << std::endl;
    c = b;
    printvector(c);
}

void vector_iterators()
{
    std::cout << " -------------- ITERATORS VECTOR --------------------" << std::endl;
    int myints[] = {16,2,77,29,55,89,180,10};
    ft::vector<int> a(myints, myints + sizeof(myints) / sizeof(int) );
    
    
    std::cout << ">> default constructor" << std::endl;
    ft::vector<int>::iterator f1 = a.begin();
    std::cout << "iterator: " << *f1 << std::endl << std::endl;


    std::cout << ">> copy constructor" << std::endl;
    ft::vector<int>::iterator f2(f1);
    std::cout << "iterator: " << *f2 << std::endl << std::endl;


    std::cout << ">> assignation constructor" << std::endl;
    ft::vector<int>::iterator f3 = f2;
    std::cout << "iterator: " << *f3 << std::endl << std::endl;

    std::cout << ">> modify content iterator" << std::endl;    
    std::cout << "before: " << *f3 << std::endl << std::endl;
    *f3 = 5;
    std::cout << "after: " << *f3 << std::endl << std::endl;
    std::cout << "before: " << *f3 << std::endl << std::endl;
    f3[0] = 18;
    std::cout << "after: " << *f3 << std::endl << std::endl;

    std::cout << ">> access content iterator (->)" << std::endl;
    access test;
    test.id = 5;
    ft::vector<access> oui(1, test);
    ft::vector<access>::iterator f4 = oui.begin();
    std::cout << "id: " << f4->id << std::endl << std::endl;

    std::cout << ">> default iterators" << std::endl;
    printvector(a);

    std::cout << ">> const iterators" << std::endl;
    ft::vector<int>::const_iterator it;
    int i = 0;
    for (it = a.begin(); it != a.end(); it++, i++)
    	std::cout << "#" << i << " " << *it << std::endl;
	std::cout << "size: " << a.size() << std::endl;
	std::cout << "capacity: " << a.capacity() << std::endl;
	std::cout << std::endl;

    std::cout << ">> reverse iterators" << std::endl;
    ft::vector<int>::reverse_iterator rit;
    i = 0;
    for (rit = a.rbegin(); rit != a.rend(); rit++)
    		std::cout << "#" << i << " " << *rit << std::endl;
	std::cout << "size: " << a.size() << std::endl;
	std::cout << "capacity: " << a.capacity() << std::endl;
	std::cout << std::endl;

    std::cout << ">> const reverse iterators" << std::endl;
    ft::vector<int>::const_reverse_iterator crit;
    i = 0;
    for (crit = a.rbegin(); crit != a.rend(); crit++)
    		std::cout << "#" << i << " " << *crit << std::endl;
	std::cout << "size: " << a.size() << std::endl;
	std::cout << "capacity: " << a.capacity() << std::endl;
	std::cout << std::endl;

    std::cout << ">> comparaison between iterators (n1 and n2)" << std::endl;
    ft::vector<int>::iterator n1 = a.begin();
    ft::vector<int>::iterator n2 = a.end();

    if (n1 < n2)
        std::cout << "n1 is less than n2" << std::endl << std::endl;
    n1 = n2;
    n2 = a.begin();
    if (n1 > n2)
        std::cout << "n1 is greater than n2"  << std::endl << std::endl;
    if (n1 != n2)
        std::cout << "n1 is not equal to n2" << std::endl << std::endl;
    n1 = n2;
    if (n1 == n2)
        std::cout << "n1 is equal to n2" << std::endl << std::endl;
    if (n1 <= n2)
        std::cout << "n1 is equal or less than  n2" << std::endl << std::endl;
    if (n1 >= n2)
        std::cout << "n1 is equal or greater than n2" << std::endl << std::endl;

    ft::vector<int>::const_iterator n3 = a.end();
    std::cout << "comparaison between iterator const and non const" << std::endl;
    if (n1 > n3)
        std::cout << "n1 is greater than n3"  << std::endl << std::endl;
    if (n1 != n3)
        std::cout << "n1 is not equal to n3" << std::endl << std::endl;
    n3 = n1;
    if (n1 == n3)
        std::cout << "n1 is equal to n2" << std::endl << std::endl;
    if (n1 <= n3)
        std::cout << "n1 is equal or less than  n2" << std::endl << std::endl;
    if (n1 >= n3)
        std::cout << "n1 is equal or greater than n2" << std::endl << std::endl;

    std::cout << ">> increment/decrement iterator" << std::endl;
    n1 = a.begin();
    std::cout << "n1 + 2    : " << *(n1 + 2) << std::endl;
    n1 += 2;
    std::cout << "n1 += 2   : " << *n1 << std::endl;
    std::cout << "n1 - 2    : " << *(n1 - 2) << std::endl;
    n1 -= 2;
    std::cout << "n1 -= 2   : " << *n1 << std::endl;
    std::cout << "n1[2]     : " << n1[2] << std::endl;
    std::cout << std::endl;
}

void vector_capacity()
{
    std::cout << " -------------- CAPACITY VECTOR --------------------" << std::endl;
    std::cout << ">> size" << std::endl;
    ft::vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert (myints.end(),10,100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';

    std::cout << std::endl;
    std::cout << ">> max_size" << std::endl;
    ft::vector<int> myvector;

    // set some content in the vector:
    for (int i=0; i<100; i++) myvector.push_back(i);

    std::cout << "size: " << myvector.size() << "\n";
    std::cout << "capacity: " << myvector.capacity() << "\n";
    std::cout << "max_size: " << myvector.max_size() << "\n";

    std::cout << std::endl;
    std::cout << ">> resize" << std::endl;

    ft::vector<int> myvecto;

    // set some initial content:
    for (int i=1;i<10;i++) myvecto.push_back(i);

    std::cout << "myvecto size before: " << myvecto.size() << std::endl;
    myvecto.resize(5);
    std::cout << "myvecto size after: " << myvecto.size() << std::endl;
    myvecto.resize(10, 10);
    std::cout << "myvecto size after: " << myvecto.size() << std::endl;
    try {
        myvecto.resize(-1);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;

    std::cout << ">> empty" << std::endl;
    ft::vector<int> b1;
    std::cout << "b1 is empty : " << std::boolalpha << b1.empty() << std::endl;
    b1.push_back(25);
    std::cout << "b1 is empty : " << std::boolalpha << b1.empty() << std::endl;

    std::cout << std::endl;
    std::cout << ">> reserve" << std::endl;

    ft::vector<int> b2;
    std::cout << "capacity: " << b2.capacity() << std::endl;
    b2.reserve(10);
    std::cout << "capacity: " << b2.capacity() << std::endl;
    try {
        b2.reserve(-1);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;
}

void vector_element_access()
{
    std::cout << " -------------- ELEMENT ACCESS VECTOR --------------------" << std::endl;
    std::cout << ">> operator element access" << std::endl;
    ft::vector<int> a(3, 460);
    
    ft::vector<int>::size_type n;
    for (n = 0; n < a.size(); n++)
        std::cout << a[n] << std::endl;
    std::cout << "a[0] before: " << a[0] << std::endl;
    a[0] = 6;
    std::cout << "a[0] after: " << a[0] << std::endl;
    const ft::vector<int> b(1, 10);
    const int &c = b[0];
    std::cout << "const value: " << c << std::endl;
    std::cout << std::endl;
    std::cout << ">> at " << std::endl;
    std::cout << "container a at 0: " << a.at(0) << std::endl;
    std::cout << "container b at 0: " << b.at(0) << std::endl;
    std::cout << std::endl;
    std::cout << ">> front" << std::endl;
    std::cout << "container a front: " << a.front() << std::endl;
    std::cout << "container b front: " << b.front() << std::endl;
    std::cout << std::endl;
    std::cout << ">> back" << std::endl;
    std::cout << "container a back: " << a.back() << std::endl;
    std::cout << "container b back: " << b.back() << std::endl;
    std::cout << std::endl;
}

void vector_modifiers() 
{
    std::cout << " -------------- MODIFIERS VECTOR --------------------" << std::endl;
    std::cout << ">> assign" << std::endl;
    ft::vector<int> a(3, 450);
    ft::vector<int> b;
    std::cout << "vector b before: " << std::endl;
    printvector(b);
    b.assign(a.begin(), a.end());
    std::cout << "vector b after: " << std::endl;
    printvector(b);
    std::cout << "vector b after: " << std::endl;
    b.assign(1, 10);
    printvector(b);

    std::cout << ">> push_back" << std::endl;
    ft::vector<int> c;
    c.push_back(10);
    c.push_back(11);
    c.push_back(12);
    c.push_back(13);
    printvector(c);

    std::cout << ">> pop_back" << std::endl;
    while (c.size() > 0)
        c.pop_back();
    printvector(c);

    std::cout << ">> insert" << std::endl;
    ft::vector<int> d;
    d.insert(d.begin(), 10);
    std::cout << "insert 10 in the beginning" << std::endl;
    printvector(d);
    d.insert(d.begin(), 3, 15);
    printvector(d);
    d.insert(d.end(), b.begin(), b.end());
    printvector(d);

    std::cout << ">> erase" << std::endl;
    std::cout << "before" << std::endl;
    printvector(d);
    std::cout << "after" << std::endl;
    d.erase(d.begin());
    printvector(d);
    std::cout << "after" << std::endl;
    d.erase(d.begin(), d.end());
    printvector(d);

    std::cout << ">> swap" << std::endl;
    ft::vector<int> b1(2, 200);
    ft::vector<int> b2(2, 400);
    std::cout << "before swap" << std::endl;
    printvector(b1);
    printvector(b2);
    b1.swap(b2);
    std::cout << "after swap" << std::endl;
    printvector(b1);
    printvector(b2);

    std::cout << ">> clear" << std::endl;
    printvector(b1);
    std::cout << "clear b1" << std::endl;
    b1.clear();
    printvector(b1);

    std::cout << ">> get allocator" << std::endl;
    std::cout << b1.get_allocator().max_size() << std::endl;
    std::cout << std::endl;
}

void vector_relational_operators()
{
    std::cout << " -------------- RELATIONAL OPERATORS VECTOR --------------------" << std::endl;
    ft::vector<int> a(2, 200);
    ft::vector<int> b(2, 200);
    std::cout << ">> a(2, 200)" << std::endl; 
    std::cout << ">> b(2, 200)" << std::endl; 
    if (a == b)
        std::cout << "a and b are equal" << std::endl;
    if (!(a != b))
        std::cout << "a and b are not different" << std::endl;
    if (a >= b)
        std::cout << "a is equal or greater than b" << std::endl;
    if (a <= b)
        std::cout << "a is equal or less than b" << std::endl;
    a.push_back(25);
    if (a > b)
        std::cout << "a is greater than b" << std::endl;
    if (b < a)
        std::cout << "b is less than a" << std::endl;
    std::cout << std::endl;
    std::cout << ">> swap non-member" << std::endl;
    std::cout << "> before" << std::endl;
    printvector(a);
    printvector(b);
    swap(a, b);
    std::cout << "> after" << std::endl;
    printvector(a);
    printvector(b);
}

int vector()
{
    vector_constructor();
    vector_assignation();
    vector_iterators();
    vector_capacity();
    vector_element_access();
    vector_modifiers();
    vector_relational_operators();
    std::cout << std::endl;
    return 0;
}


// ------------------------ STACK -------------------------------------------------------------------------------


int stack()
{
    std::cout << " -------------- MEMBER FUNCTION STACK --------------------" << std::endl;
    std::cout << ">> default constructor" << std::endl;
    ft::stack<int> a;
    std::cout << "size: " << a.empty() << std::endl;

    ft::vector<int> b(2, 300);
    std::cout << ">> container constructor" << std::endl;
    ft::stack<int, ft::vector<int> > c(b);
    std::cout << "size: " << c.size() << std::endl;

    std::cout << ">> copy constructor" << std::endl;
    ft::stack<int, ft::vector<int> > d(c);
    std::cout << "size: " << d.size() << std::endl;

    std::cout << ">> operator assignation" << std::endl;
    a.push(25);
    std::cout << "size a: " << a.size() << std::endl;
    ft::stack<int> e;
    std::cout << "size e: " << e.size() << std::endl;
    e = a;
    std::cout << "e = a" << std::endl;
    std::cout << "size e: " << e.size() << std::endl;

    std::cout << ">> empty" << std::endl;
    std::cout << "e empty: " << std::boolalpha << e.empty() << std::endl;
    ft::stack<int> f;
    std::cout << "f empty: " << std::boolalpha << f.empty() << std::endl;

    std::cout << ">> top" << std::endl;
    std::cout << "b top: " << c.top() << std::endl;
    std::cout << "e top: " << e.top() << std::endl;
    ft::stack<int> n1;
    n1.push(31);
    int &test = n1.top();
    const int &t = n1.top();
    std::cout << "n1 top: " << test << std::endl;
    std::cout << "n1 top: " << t << std::endl;

    std::cout << ">> push" << std::endl;
    std::cout << "n1 top before push: " << n1.top() << std::endl;
    n1.push(45);
    std::cout << "n1 top after push: " << n1.top() << std::endl;

    std::cout << ">> pop" << std::endl;
    std::cout << "size : " << n1.size() << std::endl;
    n1.pop();
    std::cout << "size : " << n1.size() << std::endl;
    ft::stack<int> n2;
    //n2.pop();

    std::cout << ">> relational operators" << std::endl;
    ft::stack<int> n3;
    ft::stack<int> n4;
    n3.push(10);
    n3.push(25);
    n4.push(10);
    n2 = n3;
    n1 = n4;
    std::cout << "n2 size : " << n2.size() << std::endl;
    std::cout << "n1 size : " << n1.size() << std::endl;
    if (n2 > n1)
        std::cout << "stack n2 is greater than n1" << std::endl;
    if (n1 < n2)
        std::cout << "stack n2 is greater than n1" << std::endl;
    if (n1 != n2)
        std::cout << "stack n2 is different than n1" << std::endl;
    n2.pop();
    if (n2 >= n1)
        std::cout << "stack n2 is equal or greater than n1" << std::endl;
    if (n1 <= n2)
        std::cout << "stack n2 is equal or greater than n1" << std::endl;
    if (n1 == n2)
        std::cout << "stack n2 is equal to n1" << std::endl; 
    std::cout << std::endl;
    return 0;
}


// ----------------------- MAP ----------------------------------------------------------------------------------


template <typename T>
void printmap(T a)
{
    typename T::iterator it;
    int i = 0;
    for (it = a.begin(); it != a.end(); it++, i++)
        std::cout << "#" << i << " " << it->first << " " << it->second << std::endl;
    std::cout << "size: " << a.size() << std::endl;
    std::cout << std::endl;
}

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

void map_constructor()
{
    std::cout << " -------------- CONSTRUCTOR MAP --------------------" << std::endl;
    std::cout << ">> empty constructor" << std::endl;
    ft::map<int, int> a;
    printmap(a);
    ft::map<int, int,bool(*)(int,int)> b(fncomp);
    printmap(b);

    std::cout << ">> range constructor" << std::endl;
    ft::map<int, int> c;
    c.insert(ft::make_pair(25, 5));
    c.insert(ft::make_pair(50, 5));
    c.insert(ft::make_pair(26, 5));
    std::cout << "> map c" << std::endl;
    printmap(c);
    std::cout << "> map d from c" << std::endl;
    ft::map<int, int> d(c.begin(), c.end());
    printmap(d);
    std::cout << std::endl;

    std::cout << ">> copy constructor" << std::endl;
    ft::map<int, int> e(d);
    std::cout << "> map e from d" << std::endl;
    printmap(e);

    std::cout << ">> operator assignation" << std::endl;
    ft::map<int, int> f;
    f = e;
    std::cout << "> map f from e" << std::endl;
    printmap(f);
}

void map_iterators()
{
    std::cout << " -------------- ITERATORS MAP --------------------" << std::endl;
    ft::map<int, int> a;
    a.insert(ft::make_pair(1, 5));
    a.insert(ft::make_pair(80, 5));
    a.insert(ft::make_pair(25, 5));
    a.insert(ft::make_pair(50, 5));
    a.insert(ft::make_pair(3, 5));
    a.insert(ft::make_pair(5, 5));
    std::cout << ">> default constructor" << std::endl;
    ft::map<int, int>::iterator f1 = a.begin();
    std::cout << "iterator: " << f1->first << " " << f1->second << std::endl;

    std::cout << ">> copy constructor" << std::endl;
    ft::map<int, int>::iterator f2(f1);
    std::cout << "iterator: " << f2->first << " " << f2->second << std::endl;

    std::cout << ">> assignation operator" << std::endl;
    ft::map<int, int>::iterator f3 = f2;
    std::cout << "iterator: " << f3->first << " " << f3->second << std::endl;

    std::cout << ">> iterators" << std::endl;
    printmap(a);

    std::cout << ">> const iterators" << std::endl;
    ft::map<int, int>::const_iterator it = a.begin();
    ft::map<int, int>::const_iterator ite = a.end();
    int i = 0;
    for (; it != ite; it++, i++)
        std::cout << "#" << i << " " << it->first << " " << it->second << std::endl;
    std::cout << std::endl;
    std::cout << ">> comparaison between iterator and const iterator" << std::endl;
    f1 = a.begin();
    it = a.begin();
    if (it == f1)
        std::cout << "it is equal to f1" << std::endl;
    f1++;
    if (f1 != it)
        std::cout << "it is not equal to f1" << std::endl;

    std::cout << std::endl;
    std::cout << ">> reverse iterators" << std::endl;
    ft::map<int, int>::reverse_iterator n1 = a.rbegin(); 
    ft::map<int, int>::reverse_iterator n2 = a.rend();
    for (i = 0; n1 != n2; n1++, i++)
        std::cout << "#" << i << " " << n1->first << " " << n1->second << std::endl;

    std::cout << std::endl;
    std::cout << ">> const reverse iterators" << std::endl;
    ft::map<int, int>::const_reverse_iterator n3 = a.rbegin();
    ft::map<int, int>::const_reverse_iterator n4 = a.rend();
    for (i = 0; n3 != n4; n3++, i++)
        std::cout << "#" << i << " " << n3->first << " " << n3->second << std::endl;
    n1 = a.rbegin();
    n3 = a.rbegin();
    if (n1 == n3)
        std::cout << "n1 is equal to n3" << std::endl;
    n3++;
    if (n1 != n3)
        std::cout << "n1 is not equal to n3" << std::endl;

    std::cout << std::endl;
    std::cout << " -------------- CAPACITY MAP --------------------" << std::endl;
    std::cout << ">> empty / size" << std::endl;
    ft::map<int, int> p1;
    std::cout << "p1 is empty: " << std::boolalpha << p1.empty() << std::endl;
    std::cout << "p1 size: " << p1.size() << std::endl;
    p1.insert(ft::make_pair(25, 5));
    std::cout << "p1 is empty: " << std::boolalpha << p1.empty() << std::endl;
    std::cout << "p1 size: " << p1.size() << std::endl;
    std::cout << "p1 max_size: " << p1.max_size() << std::endl;

    std::cout << std::endl;
    std::cout << ">> operator access element " << std::endl;
    ft::map<int, int> p2;
    std::cout << "p2 is empty: " << p2.empty() << std::endl;
    std::cout << "p2[10] : " << p2[10] << std::endl;
    p2[10] = 5;
    std::cout << "p2[10] : " << p2[10] << std::endl;
    p2.insert(ft::make_pair(25, 88));
    std::cout << "p2[25] : " << p2[25] << std::endl;
    std::cout << std::endl;
}

void map_modifiers()
{
    std::cout << " -------------- MODIFIERS MAP --------------------" << std::endl;
    std::cout << ">> insert" << std::endl;
    ft::map<int, int> a;
    std::cout << "a size: " << a.size() << std::endl;
    a.insert(ft::make_pair(25, 8));
    printmap(a);

    a.insert(a.begin(), ft::make_pair(10, 25));
    printmap(a);

    a.insert(ft::make_pair(75, 10));
    a.insert(ft::make_pair(76, 10));
    a.insert(ft::make_pair(77, 10));
    a.insert(ft::make_pair(78, 10));
    a.insert(ft::make_pair(79, 10));
    ft::map<int,int> b(a.begin(), a.end());
    printmap(b);

    std::cout << ">> erase" << std::endl;
    b.erase(b.begin());
    printmap(b);


    b.erase(77);
    printmap(b);

    b.erase(b.begin(), b.end());
    printmap(b);

    b.insert(ft::make_pair(10, 10));
    std::cout << ">> swap" << std::endl;
    std::cout << "> before swap:" << std::endl; 
    printmap(b);
    printmap(a);
    a.swap(b);
    std::cout << "> after swap:" << std::endl;
    printmap(b); 
    printmap(a);

    std::cout << ">> clear" << std::endl;
    a.clear();
    std::cout << "a size: " << a.size() << std::endl;
    ft::map<int, int> c(b);
    b.clear();

    std::cout << ">> key_comp" << std::endl;
    ft::map<int, int>::key_compare comp = c.key_comp();
    ft::map<int, int>::iterator t1 = c.begin();
    ft::map<int, int>::iterator t2 = c.begin();
    t2++;
    std::cout << "comp t1 and t2 : " << comp(t1->first, t2->first) << std::endl;

    std::cout << ">> value_comp " << std::endl;

    std::cout << "value_comp t1 and t2 : " << c.value_comp()(*t1, *t2) << std::endl;
    std::cout << std::endl;
}

void map_operations()
{
    std::cout << " -------------- OPERATIONS MAP --------------------" << std::endl;
    std::cout << ">> find" << std::endl;
    ft::map<char, int> mymap;

    mymap['a'] = 50;
    mymap['b'] = 100;
    mymap['c'] = 150;
    mymap['d'] = 200;

    std::cout << "find 'a' : " << mymap.find('a')->second << std::endl;
    std::cout << "find 'b' : " << mymap.find('b')->second << std::endl;
    std::cout << "find 'c' : " << mymap.find('c')->second << std::endl;
    std::cout << "find 'd' : " << mymap.find('d')->second << std::endl;
    if (mymap.find('z') == mymap.end())
        std::cout << "cannot find 'z'" << std::endl;
    std::cout << std::endl;
    std::cout << ">> count" << std::endl;
    std::cout << "count 'a' : " << mymap.count('a') << std::endl;
    std::cout << "count 'b' : " << mymap.count('b') << std::endl;
    std::cout << "count 'z' : " << mymap.count('z') << std::endl;

    std::cout << std::endl;
    std::cout << ">> lower_bound / upper_bound" << std::endl;
    ft::map<char, int> m;
    ft::map<char, int>::iterator itlow, itup;

    m['a'] = 20;
    m['b'] = 40;
    m['c'] = 60;
    m['d'] = 80;
    m['e'] = 100;

    itlow = m.lower_bound('b'); // itlow points to b
    itup = m.upper_bound('d');  // itup points to e (not d!)

    m.erase(itlow, itup); // erases [itlow,itup)

    // print content:
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    m.clear();
    itlow = m.lower_bound('b'); // itlow points to b
    itup = m.upper_bound('d');  // itup points to e (not d!)
    for (ft::map<char, int>::iterator it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    std::cout << std::endl;
    std::cout << ">> equal_range" << std::endl;
    ft::map<char, int> i;

    i['a'] = 10;
    i['b'] = 20;
    i['c'] = 30;

    ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
    ret = i.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';

    std::cout << std::endl;
    std::cout << ">> get_allocator" << std::endl;

    std::cout << "max_size : " << i.get_allocator().max_size() << std::endl;
}

int map()
{
    map_constructor();
    map_iterators();
    map_modifiers();
    map_operations();
    std::cout << std::endl;
    return 0;
}

// ----------------------------------------------------------------------------------

int main()
{
    vector();
    stack();
    map();
    return 0;
}