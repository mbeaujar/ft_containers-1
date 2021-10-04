/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:33:16 by ranaili           #+#    #+#             */
/*   Updated: 2021/10/04 16:00:17 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <memory>
# include <string>
# include <iostream>
# include <sstream>
# include <stdexcept>
# include "utils.hpp"
# include "iterator.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {   
        public:
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef ft::random_access_iterator<value_type>          iterator;
            typedef ft::random_access_iterator<const value_type>    const_iterator;
            typedef ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::size_type              size_type;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef typename allocator_type::const_reference        const_reference;

            /* ************************************************************************** */
            /*                              Member functions                              */
            /* ************************************************************************** */

            explicit vector (const allocator_type& alloc = allocator_type()) : 
                _arr(NULL),
                _alloc(alloc),
                _size(0),
                _capacity(0) {}

            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
                _arr(NULL),
                _alloc(alloc),
                _size(0),
                _capacity(0) { assign(n, val); }

        	template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) :
                _arr(NULL),
                _alloc(alloc),
                _size(0),
                _capacity(0) { assign(first, last); }
        
        	vector (const vector& x) :
                _arr(NULL),
                _alloc(x._alloc),
                _size(0),
                _capacity(0) { assign(x.begin(), x.end()); }

            ~vector() { clear(); _alloc.deallocate(_arr, _capacity); }

            vector & operator=(const vector& x)
            {
                if (this == &x)
                    return *this;
                clear();
                _alloc.deallocate(_arr, _capacity);
                _size = x._size;
                _alloc = x._alloc;
                _capacity = x._capacity;
                _arr = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(_arr + i, *(x._arr + i));
                return *this;
            }

            /* ************************************************************************** */
            /*                                Iterators                                   */
            /* ************************************************************************** */

            iterator begin() { return _arr; }
            
            const_iterator begin() const { return _arr; }

            iterator end() { return _arr + _size; }
            
            const_iterator end() const { return _arr + _size; }

            reverse_iterator rbegin() { return (reverse_iterator(this->end())); }

            const_reverse_iterator rbegin() const { return (reverse_iterator(this->end())); }

            reverse_iterator rend() { return (reverse_iterator(this->begin())); }

            const_reverse_iterator rend() const { return (reverse_iterator(this->begin())); }


            /* ************************************************************************** */
            /*                                 Capacity                                   */
            /* ************************************************************************** */

            size_type size() const { return _size; }

            size_type max_size() const { return allocator_type().max_size(); }

            void resize(size_type n, value_type val = value_type())
            {
                if (n <= _size)
                {
                    for (size_type i = n; i < _size; i++)
                        _alloc.destroy(_arr + i);
                    _size = n;
                }
                else if (n > _size && n <= _capacity)
                {
                    for (size_type i = _size; i < n; i++)
                        _alloc.construct(_arr + i, val);
                    _size = n;
                }
                else if (n > _capacity)
                {
                    pointer tmp;

                    tmp = _alloc.allocate(n);
                    for (size_type i = 0; i < _size; i++)
                        _alloc.construct(tmp + i, *(_arr + i));
                    for (size_type i = _size; i < n; i++)
                        _alloc.construct(tmp + i, val);
                    clear();
                    _alloc.deallocate(_arr, _capacity);
                    _arr = tmp;
                    _capacity = n;
                    _size = n;
                }
            }
            
            size_type capacity() const { return _capacity; }

            bool empty() const { return _size == 0; }

            void reserve (size_type n)
            {
                if (n > _capacity)
                {
                    pointer tmp;
                    size_type tmp_size = _size;

                    tmp = _alloc.allocate(n);
                    for (size_type i = 0; i < _size; i++)
                        _alloc.construct(tmp + i, *(_arr + i));
                    clear();
                    _alloc.deallocate(_arr, _capacity);
                    _size = tmp_size;
                    _arr = tmp;
                    _capacity = n;
                }
            }


            /* ************************************************************************** */
            /*                              Element access                                */
            /* ************************************************************************** */

            reference operator[] (size_type n) { return *(_arr + n); }

            const_reference operator[] (size_type n) const { return *(_arr + n); }

            reference at (size_type n) { 
                
                if (n > _size)
                    throw std::out_of_range("vector::_M_range_check: __n (which is " + to_string(n) + ") >= this->size() (which is " + to_string(this->size()) + ")");
                return *(_arr + n); 
            }
            
            const_reference at (size_type n) const { 

                if (n > _size)
                    throw std::out_of_range("vector::_M_range_check: __n (which is " + to_string(n) + ") >= this->size() (which is " + to_string(this->size()) + ")");
                return *(_arr + n);
            }

            reference front() { return *_arr; }

            const_reference front() const { return *_arr; }

            reference back() { return *(_arr + _size - 1); }
            
            const_reference back() const { return *(_arr + _size - 1); }


            /* ************************************************************************** */
            /*                                 Modifiers                                  */
            /* ************************************************************************** */

            template <class InputIterator>
            void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
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
                    _arr = _alloc.allocate(_capacity);
                }
                for (size_type i = 0; first != last; first++, i++)
                    _alloc.construct(_arr + i, *first);
                _size = n;
            }
	
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
                    _arr = _alloc.allocate(_capacity);
                }
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(_arr + i, val);
                _size = n;
            }
            
            void push_back (const value_type& val)
            {
                if (_size + 1 > _capacity)
                {
                    pointer tmp;
                    size_type tmp_size = _size;

                    tmp = _alloc.allocate(_capacity + 1);
                    for (size_type i = 0; i < _size; i++)
                        _alloc.construct(tmp + i, *(_arr + i));
                    clear();
                    _size = tmp_size;
                    _alloc.deallocate(_arr, _capacity);
                    _arr = tmp;
                    _capacity += 1;
                }
                _alloc.construct(_arr + _size, val);
                _size += 1;
            }

            void pop_back()
            {
                if (_size > 0)
                {
                    _alloc.destroy(_arr + _size);
                    _size -= 1;
                }
            }

            iterator insert (iterator position, const value_type& val)
            {
                size_type len = &(*position) - _arr;
                size_type i = _size;

                if (_size + 1 <= _capacity)
                {
                    for (; i > len; i--)
                    {
                        _alloc.construct(_arr + i + 1, *(_arr + i));
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
                        _alloc.construct(tmp + i, *(_arr + i));
                    _alloc.construct(tmp + i, val);
                    for (; i < _size; i++)
                        _alloc.construct(tmp + i + 1, *(_arr + i));
                    clear();
                    _size = i;
                    _alloc.deallocate(_arr, _capacity);
                    _arr = tmp;
                    _capacity++;
                }
                _size += 1;
                return iterator(_arr + len);
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                for (size_type i = 0; i < n; i++)
                    position = insert(position, val);
            }

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
            {
                InputIterator tmp_first = first;
                size_type pos = &(*position) - _arr;
                pointer   tmp;
                size_type len = 0;

                for (InputIterator to = first; to != last; to++)
                    len++;
                tmp = _alloc.allocate(len);
                for (size_type i = 0; tmp_first != last; tmp_first++, i++)
                    _alloc.construct(tmp + i, *tmp_first);
                if (_size + len > _capacity)
                {
                    size_type i = 0;
                    size_type tmp_size = _size;
                    pointer tab;

                    tab = _alloc.allocate(_capacity + len);
                    for (; i < pos; i++)
                        _alloc.construct(tab + i, *(_arr + i));
                    for (size_type l = 0; l < len; l++, i++)
                        _alloc.construct(tab + i, *(tmp + l));
                    for (; i - len < _size; i++)
                        _alloc.construct(tab + i, *(_arr + i - len));
                    clear();
                    _size = tmp_size;
                    _alloc.deallocate(_arr, _capacity);
                    for (size_type l = 0; l < len; l++)
                        _alloc.destroy(tmp + l);
                    _alloc.deallocate(tmp, len);
                    _arr = tab;
                    _capacity += len;
                    _size += len;
                }
                else
                {
                    size_type i = 0;
                    size_type tmp_size = _size;
                    pointer tab;

                    tab = _alloc.allocate(_capacity);
                    for (; i < pos; i++)
                        _alloc.construct(tab + i, *(_arr + i));
                    for (size_type l = 0; l < len; l++, i++)
                        _alloc.construct(tab + i, *(tmp + l));
                    for (; i - len < _size; i++)
                        _alloc.construct(tab + i, *(_arr + i - len));
                    clear();
                    _size = tmp_size;
                    _alloc.deallocate(_arr, _capacity);
                    for (size_type l = 0; l < len; l++)
                        _alloc.destroy(tmp + l);
                    _alloc.deallocate(tmp, len);
                    _arr = tab;
                    _size += len;
                }
            }

            iterator erase (iterator position)
            {
                size_type pos = &(*position) - _arr;

                _alloc.destroy(_arr + pos);
                for (; pos < _size - 1; pos++)
                {
                    _alloc.construct(_arr + pos, *(_arr + pos + 1));
                    _alloc.destroy(_arr + pos + 1);
                }
                _size -= 1;
                return (iterator(position));
            }
            
            iterator erase (iterator first, iterator last)
            {
                size_type n = 0;
                size_type pos = (&(*first) - _arr);
                for (iterator tmp = first; first != last; first++)
                    n++;
                if (_size > 0 && n > 0) {
                    for (size_type i = 0; i < n; i++)
                        _alloc.destroy(_arr + pos + i);
                    for (size_type l = pos; l + n < _size; l++) {
                        _alloc.construct(_arr + l, *(_arr + l + n));
                        _alloc.destroy(_arr + l + n);
                    }
                    _size -= n;
                }
                return iterator(_arr + pos);
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

            void clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_arr + i);
                _size = 0;
            }


            /* ************************************************************************** */
            /*                                 Allocator                                  */
            /* ************************************************************************** */
            
            allocator_type get_allocator() const { return allocator_type(); };

            
        private:
            pointer         _arr;
            allocator_type  _alloc;
            size_type       _size;
            size_type       _capacity;
            
            template <typename tostring>
            std::string to_string(tostring n) const
            {
                std::ostringstream ss;
                ss << n;
                return ss.str();
            }
    };


    /* ************************************************************************** */
    /*                      Non-member function overloads                         */
    /* ************************************************************************** */

    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        typename ft::vector<T, Alloc>::const_iterator it = lhs.begin();
        typename ft::vector<T, Alloc>::const_iterator first = rhs.begin();

        if (lhs.size() != rhs.size())
            return false;
        for (; first != rhs.end() && it != lhs.end(); first++, it++) {
            if (*first != *it)
                return false;
        }
        if (first != rhs.end() || it != lhs.end())
            return false;  
        return true;
    };

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
          return !(lhs == rhs);
    };

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        typename ft::vector<T, Alloc>::const_iterator it = lhs.begin();
        typename ft::vector<T, Alloc>::const_iterator first = rhs.begin();

        for (; first != rhs.end() && it != lhs.end(); it++, first++) {
            if (*it < *first)
                return true;
            if (*it > *first)
                return false;
        }
        if (it == lhs.end() && first != rhs.end())
            return true;
        return false;
    };

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
          return (lhs < rhs || lhs == rhs);
    };

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs < rhs) && lhs != rhs; 
    };

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (lhs > rhs || lhs == rhs);
    };

    template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

};

#endif
