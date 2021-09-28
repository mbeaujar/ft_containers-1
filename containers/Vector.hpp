/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:33:16 by ranaili           #+#    #+#             */
/*   Updated: 2021/09/28 23:10:48 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <memory>
# include <iostream>
# include "Utils.hpp"

namespace ft
{
    /* ************************************************************************** */
    /*                                  ITER                                      */
    /* ************************************************************************** */

    template<typename T>
    class random_access_iterator : private ft::iterator<ft::random_access_iterator_tag, T>
    {
        public :
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer           pointer;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference         reference;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;

            random_access_iterator() : m_ptr(0) {};
            random_access_iterator(pointer ptr) : m_ptr(ptr) {};
            ~random_access_iterator() {};
            random_access_iterator(random_access_iterator const & src) { *this = src; }

            reference           operator*() const { return *m_ptr; }
            pointer             operator->() const { return &(operator*()); }
            reference           operator[](difference_type off) const { return m_ptr[off]; }

            //Increment / Decrement
            random_access_iterator& operator++() { ++m_ptr; return *this; }
            random_access_iterator  operator++(int) { pointer tmp = m_ptr; ++*this; return random_access_iterator(tmp); }
            random_access_iterator& operator--() { --m_ptr; return *this; }
            random_access_iterator  operator--(int) { pointer tmp = m_ptr; --*this; return random_access_iterator(tmp); }

            //Arithmetic
            random_access_iterator&       operator=(difference_type off) { *this->m_ptr = off.m_ptr; return *this; }
            random_access_iterator&       operator+=(difference_type off) { m_ptr += off; return *this; }
            random_access_iterator        operator+(difference_type off) const { return random_access_iterator(m_ptr + off); }
            friend random_access_iterator operator+(difference_type off, const random_access_iterator& right) { return random_access_iterator(off + right.m_ptr);}
            random_access_iterator&       operator-=(difference_type off) { m_ptr -= off; return *this; }
            random_access_iterator        operator-(difference_type off) const { return random_access_iterator(m_ptr - off); }
            difference_type               operator-(const random_access_iterator& right) const { return m_ptr - right.m_ptr; }
            
            //Comparison operators
            bool operator==   (const random_access_iterator& r) const { return m_ptr == r.m_ptr; }
            bool operator!=   (const random_access_iterator& r) const { return m_ptr != r.m_ptr; }
            bool operator<    (const random_access_iterator& r) const { return m_ptr < r.m_ptr; }
            bool operator<=   (const random_access_iterator& r) const { return m_ptr <= r.m_ptr; }
            bool operator>    (const random_access_iterator& r) const { return m_ptr > r.m_ptr; }
            bool operator>=   (const random_access_iterator& r) const { return m_ptr >= r.m_ptr; }

            pointer base() const { return m_ptr; }
        private :
            pointer m_ptr;


    };

    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
            
        public:
            typedef T value_type;	
            typedef Alloc allocator_type;
            typedef ft::random_access_iterator<T>                iterator;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::size_type       size_type; 
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef typename allocator_type::const_reference const_reference;


            /* ************************************************************************** */
            /*                              CONSTRUCTORS                                  */
            /* ************************************************************************** */


            // Constructs an empty container, with no elements.
            explicit vector (const allocator_type& alloc = allocator_type()) : _arr(NULL), _alloc(alloc), _size(0), _capacity(0) {}

            // Constructs a container with n elements. Each element is a copy of val.
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
                _arr(NULL),
                _alloc(alloc),
                _size(0),
                _capacity(0)
            {
                assign(n, val);
            }

            // Constructs a container with as many elements as the range [first,last), with each element 
            // constructed from its corresponding element in that range, in the same order.
        	template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
                _arr(NULL),
                _alloc(alloc),
                _size(0),
                _capacity(0)
            {
                assign(first, last);
            }
        
            // Constructs a container with a copy of each of the elements in x, in the same order.
        	vector (const vector& x)
            {
                clear();
                _alloc.deallocate(_arr, _capacity);
                _size = x._size;
                _alloc = x._alloc;
                _capacity = x._capacity;
                _arr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(_arr + i, *(x._arr + i)); // _arr[i] = x._arr[i];
            }
        

            /* ************************************************************************** */
            /*                              DESTRUCTORS                                   */
            /* ************************************************************************** */

            // This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
            ~vector()
            {
                clear();
                _alloc.deallocate(_arr, _capacity);
            }

            vector & operator=(const vector& x)
            {
                clear();
                _alloc.deallocate(_arr, _capacity);
                _size = x._size;
                _alloc = x._alloc;
                _capacity = x._capacity;
                _arr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(_arr + i, x._arr + i); // _arr[i] = x._arr[i];
            }

            reference operator[] (size_type n) { return *(_arr + n); }

            const_reference operator[] (size_type n) const { return *(_arr + n); }

            reference at (size_type n) { return *(_arr + n); }
            
            const_reference at (size_type n) const { return *(_arr + n); }

            reference front() { return *_arr; }

            const_reference front() const { return *_arr; }

            reference back() { return *(_arr + _size - 1); }
            
            const_reference back() const { return *(_arr + _size - 1); }

            iterator begin() { return _arr; }
            
            // const_iterator begin() const { return _arr; }

            iterator end() { return _arr + _size; }
            
            // const_iterator end() const { return _arr + _size; }

            void push_back (const value_type& val)
            {
                if (_size + 1 > _capacity)
                {
                    pointer tmp;

                    tmp = _alloc.allocate(_capacity + 1);
                    for (int i = 0; i < _size; i++)
                        _alloc.construct(tmp + i, _arr + i); // tmp[i] = _arr[i];
                    clear();
                    _alloc.deallocate(_arr, _capacity);
                    _arr = tmp;
                    _alloc.construct(_arr + _size + 1, val);
                    _capacity += 1;
                    _size += 1;
                }
                else
                {
                    _alloc.construct(_arr + _size + 1, val);
                    _size += 1;
                }
            }

            void pop_back()
            {
                if (_size > 0)
                {
                    _alloc.destroy(_arr + _size);
                    _size -= 1;
                }
            }

            void swap (vector& x)
            {
                if (this == &x)
                    return;
                allocator_type tmp_alloc   = x._alloc;
                pointer tmp_arr            = x._arr;
                size_type tmp_capacity     = x._capacity;
                size_type tmp_size         = x._size;
                x._alloc                   = this->_alloc;
                x._arr                     = this->_arr;
                x._capacity                = this->_capacity;
                x._size                    = this->_size;
                this->_alloc               = tmp_alloc;
                this->_arr                 = tmp_arr;
                this->_capacity            = tmp_capacity;
                this->_size                = tmp_size;
            }

            iterator insert (iterator position, const value_type& val)
            {
                size_type len = &(*position) - _arr;
                size_type i = _size;

                if (_size + 1 <= _capacity)
                {
                    for (; i > len; i--)
                    {
                        _alloc.construct(_arr + i + 1, _arr + i);
                        _alloc.destroy(_arr + i);
                    }
                    _alloc.destroy(_arr + i);
                    _alloc.construct(_arr + i, val);
                }
                else
                {
                    pointer tmp;

                    tmp = _alloc.allocate(_capacity + 1);
                    for (i = 0; i < len; i++)
                        _alloc.construct(tmp + i, _arr + i);
                    _alloc.construct(tmp + i, val);
                    for (; i < _size; i++)
                        _alloc.construct(tmp + i + 1, _arr + i);
                    clear();
                    _alloc.deallocate(_arr, _capacity);
                    _arr = tmp;
                    _capacity++;
                }
                _size += 1;
                return _arr + len;
            }

            void insert (iterator position, size_type n, const value_type& val);

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last);

            /*
            template <class T, class Alloc>
            bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

            template <class T, class Alloc>
            bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

            template <class T, class Alloc>
            bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

            template <class T, class Alloc>
            bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

            template <class T, class Alloc>
            bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

            template <class T, class Alloc>
            bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
            */

            size_type size() const { return _size; }

            size_type max_size() const { return allocator_type().max_size(); }

            // size_type max_size() const { return allocator_traits_type::max_size(_alloc()); }

            size_type capacity() const { return _capacity; }

            bool empty() const { return _size == 0; }

            void reserve (size_type n)
            {
                if (n > _capacity)
                {
                    pointer tmp;

                    tmp = _alloc.allocate(n);
                    for (int i = 0; i < _size; i++)
                        _alloc.construct(tmp + i, _arr + i); // tmp[i] = _arr[i];
                    clear();
                    _alloc.deallocate(_arr, _capacity);
                    _arr = tmp;
                    _capacity = n;
                }
            }



            void resize(size_type n, value_type val = value_type())
            {
                if (n < _size)
                {
                    for (int i = n; i < _size; i++)
                        _alloc.destroy(_arr + i);
                    _size = n;
                }
                else if (n > _size && n <= _capacity)
                {
                    for (int i = _size; i < n; i++)
                        _alloc.construct(_arr + i, val); // _arr[i] = val;
                    _size = n;
                }
                else if (n > _capacity)
                {
                    size_type *tmp;

                    tmp = _alloc.allocate(n);
                    for (int i = 0; i < _size; i++)
                        _alloc.construct(tmp + i, _arr + i); // tmp[i] = _arr[i];
                    for (int i = _size; i < n; i++)
                        _alloc.construct(tmp + i, val);  // tmp[i] = val;
                    clear();
                    _alloc.deallocate(_arr, _capacity);
                    _arr = tmp;
                    _capacity = n;
                    _size = n;
                }
            }

            /* ************************************************************************** */
            /*                                ASSIGN                                      */
            /* ************************************************************************** */

            // In the range version, the new contents are elements constructed from each of the 
            // elements in the range between first and last, in the same order.
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {
                size_type n = 0;
            
                clear();
                for (InputIterator tmp = first; tmp != last; tmp++)
                    n++;
                if (_capacity < n)
                {
                    _alloc.deallocate(_arr, _capacity);
                    if ((_capacity * 2) >= n)
                        _capacity *= 2;
                    else
                        _capacity += n;
                    _arr = _alloc.allocate(_capacity); // add the catch for en eventual throw
                }
                for (size_type i = 0; first != last; first++, i++)
                    _alloc.construct(_arr + i, first);
                _size = n;
            }
	
            // In the fill version, the new contents are n elements, each initialized to a copy of val.
            void assign (size_type n, const value_type& val)
            {
                clear();
                if (_capacity < n)
                {
                    _alloc.deallocate(_arr, _capacity);
                    if ((_capacity * 2) >= n)
                        _capacity *= 2;
                    else
                        _capacity += n;
                    _arr = _alloc.allocate(_capacity); // add the catch for en eventual throw
                }
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_arr + i, val);
                _size = n;
            }

            /* ************************************************************************** */
            /*                                 CLEAR                                      */
            /* ************************************************************************** */

            // Removes all elements from the vector 
            // (which are destroyed), leaving the container with a size of 0.
            void clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_arr + i);
                _size = 0;
            }


        private:
            pointer         _arr;
            allocator_type  _alloc;
            size_type       _size;
            size_type       _capacity;
    };
    

    template<typename T, typename U>
    bool operator==(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) { return lhs.base() == rhs.base(); }
    template<typename T, typename U>
    bool operator!=(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) { return lhs.base() != rhs.base(); }
    template<typename T, typename U>
    bool operator<(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) { return lhs.base() < rhs.base(); }
    template<typename T, typename U>
    bool operator<=(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) { return lhs.base() <= rhs.base(); }
    template<typename T, typename U>
    bool operator>(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) { return lhs.base() > rhs.base(); }
    template<typename T, typename U>
    bool operator>=(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) { return lhs.base() >= rhs.base(); }

};

#endif
