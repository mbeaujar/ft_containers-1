/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:33:16 by ranaili           #+#    #+#             */
/*   Updated: 2021/09/22 22:28:15 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <memory>
# include <iostream>

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
            
        public:
            typedef T value_type;	
            typedef Alloc allocator_type;
            typedef typename allocator_type::size_type       size_type; 
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef typename allocator_type::const_reference const_reference;


            /* ************************************************************************** */
            /*                              CONSTRUCTORS                                  */
            /* ************************************************************************** */


            // Constructs an empty container, with no elements.
            explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _arr(NULL) {}

            // Constructs a container with n elements. Each element is a copy of val.
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
                _size(0),
                _arr(NULL),
                _capacity(0),
                _alloc(alloc)
            {
                assign(n, val);
            }

            // Constructs a container with as many elements as the range [first,last), with each element 
            // constructed from its corresponding element in that range, in the same order.
        	template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
                _size(0),
                _arr(NULL),
                _capacity(0),
                _alloc(alloc)
            {
                assign(first, last);
            }
        
            // Constructs a container with a copy of each of the elements in x, in the same order.
        	vector (const vector& x)
            {
                *this = x; // faire en sorte de pas use le =
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
                    if ((_capacity * 2) >= n)
                        _capacity *= 2;
                    else
                        _capacity += n;
                    _arr = _alloc.allocate(_capacity);
                }
                for (; first != last; first++)
                    _alloc.construct(_arr, first);
                _size = n;
            }
	
            // In the fill version, the new contents are n elements, each initialized to a copy of val.
            void assign (size_type n, const value_type& val)
            {
                clear();
                if (_capacity < n)
                {
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

    // template<>
    // class random_assiterator
    // {

    // };
};

#endif
