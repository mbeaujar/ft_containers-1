/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:44:36 by ranaili           #+#    #+#             */
/*   Updated: 2021/10/04 16:04:35 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <iostream>
# include "utils.hpp"
# include "iterator.hpp"

namespace ft
{
    template <typename T, class Alloc>
    struct node {
        typedef T value_type;
        // typedef typename Alloc::pointer pointer;

        node(value_type const &data, node* left = NULL, node* right = NULL, node* parent = NULL)
            : data(data),
              left(left),
              right(right),
              parent(parent) {}
        
        node(node const &copy)
            : data(copy.data),
              left(copy.left),
              right(copy.right),
              parent(copy.parent) {}

        ~node() {}

        node& operator=(node const &copy) {
            if (this == &copy)
                return *this;
            data = copy.data;
            left = copy.left;
            right = copy.right;
            parent = copy.parent;
            return *this;
        }

        value_type data;
        node *left;
        node *right;
        node *parent;
    };


    template < class Key,                                 // map::key_type
           class T,                                       // map::mapped_type
           class Compare = ft::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           > 
    class map
    {
        public :
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const Key, T> value_type;
            typedef Compare               key_compare;
            // value _compare
            typedef Alloc allocator_type;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::size_type          size_type;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef typename allocator_type::difference_type    difference_type;
            typedef typename allocator_type::const_reference    const_reference;
            typedef ft::bidirectional_iterator<ft::node<value_type, allocator_type> >    iterator;
            typedef ft::bidirectional_iterator<const ft::node<value_type, allocator_type> >    const_iterator;
            

            /**
             * @brief Construct a new empty map object
             * 
             * @param comp 
             * @param alloc 
             */
            explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
                : _size(0),
                  _comp(comp),
                  _alloc(alloc),
                  _allocNode()
            {
                _end = _allocNode.allocate(1);
                _allocNode.construct(_end, node(value_type()));
                _root = _end;
                _begin = _root;
            }

            /**
             * @brief Destroy the map object
             * 
             */
            ~map() {
                // _allocNode.destroy(_end);
                // _allocNode.deallocate(_end, 1);
            };


            iterator begin() { return _begin; }

            iterator end() { return _end; }

            // _root = _allocNode.allocate(1);
            // _allocNode.construct(_root, node(val));
            
            // ft::pair<iterator, bool> insert (const value_type& val) {
            //     insert val;
            //     return pair;
            // }
	
            iterator insert (iterator position, const value_type& val) {
                
            }


        private :
            //  allocator_node -> https://newbedev.com/cpp/memory/allocator
            typedef ft::node<value_type, allocator_type>    node;
            typedef typename allocator_type::template rebind<node>::other allocator_node;

            node*           _root;
            node*           _begin;
            node*           _end;
            size_type       _size;
            key_compare     _comp;
            allocator_type  _alloc;
            allocator_node  _allocNode;
    };
}

#endif