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

        value_type data;    //           <- <- <- <- <-
        node *left;        //           | | |3| |  |
        node *right;      //            |5| | | |1 |
        node *parent;    //           6 | |4| |2|  |0
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
            class value_compare : std::binary_function<value_type, value_type, bool> {
            public:
                friend class map;
                bool operator()(const value_type &lhs, const value_type &rhs) const { return comp(lhs.first, rhs.first); }
            protected:
                Compare comp;
                value_compare(Compare c) : comp(c) {}
            };
            typedef Alloc allocator_type;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::size_type          size_type;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef typename allocator_type::difference_type    difference_type;
            typedef typename allocator_type::const_reference    const_reference;
            typedef ft::bidirectional_iterator<ft::node<value_type, allocator_type> >    iterator;
            typedef ft::bidirectional_iterator<const ft::node<value_type, allocator_type> >    const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            

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
                // erase(this->begin(), this->end());
            };


            iterator begin() { return _begin; }
            const_iterator begin() const { return _begin; }

            iterator end() { return _end; }
            const_iterator end() const { return _end; }

            reverse_iterator rbegin(){ return (reverse_iterator(this->end())); }
            const_reverse_iterator rbegin() const{ return (reverse_iterator(this->end())); }

            reverse_iterator rend(){ return (reverse_iterator(this->begin())); }
            const_reverse_iterator rend() const{ return (reverse_iterator(this->begin())); }

            bool empty() const{ return _size == 0; }
            size_type size() const{ return _size; }
            size_type max_size() const { return allocator_node().max_size(); }

            // mapped_type& operator[] (const key_type& k)
            // {
            //     iterator position = 
            // }

            // void swap (map& x)
            // {
            //     node*           _root_tmp;
            //     node*           _begin_tmp;
            //     node*           _end_tmp;
            //     size_type       _size_tmp;
            //     key_compare     _comp_tmp;
            //     allocator_type  _alloc_tmp;
            //     allocator_node  _allocNode_tmp;
            // }
            
            /**
             * @brief insert a new element to the list 
             * 
             * @param val element to add
             * @return ft::pair<iterator,bool> 
             */
            ft::pair<iterator,bool> insert (const value_type& val) {
                iterator position = insert(_root, val);
                if (position == _end)
                    return ft::make_pair(position, false);
                return ft::make_pair(position, true);
            }

            /**
             * @brief add a new element to the list 
             * 
             * @param position position to add
             * @param val element to add
             * @return iterator on the element (new or old) 
             */
            iterator insert (iterator position, const value_type& val) { 
                if (_root == _end)
                    return insertNode(_root, val);             
                if (_comp(position->first, val.first)) {
                    while (_comp(position->first, val.first) && position != _end)
                        ++position;
                    if (!_comp(position->first, val.first) && !_comp(val.first, position->first))
                        return position;
                    --position;
                    return insertNode(position._M_node, val);
                } 
                else {
                    while (_comp(val.first, position->first) && position != _begin)
                        --position;
                    if (!_comp(position->first, val.first) && !_comp(val.first, position->first))
                        return position;
                    ++position;
                    return insertNode(position._M_node, val);
                }
                return position;
            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last) {
                InputIterator position = this->begin();
                for (; first != last; first++) {
                    position = insert(position, *first);
                }
            }

            // size_type erase(const key_type &k)
            // {
            //     node *clear = searchNode(k)._M_node;

            //     if (clear == _end)
            //         return 0;
            //     if (!clear->left && !clear->right)
            //     {
            //         deallocateNode(clear)
            //         if (clear->parent->right == clear)
            //             clear->parent->right = NULL;
            //         else
            //             clear->parent->left = NULL;
            //     }
            //     else if (!clear->left || !clear->right)
            //     {
            //         bool left_exist = !(clear->left == NULL);
            //         deallocateNode(clear)
            //         if (clear->parent->left == clear && left_exist)
            //             clear->parent->left = clear->left;
            //         else if (clear->parent->left == clear && !left_exist)
            //             clear->parent->left = clear->right;
            //         else if (clear->parent->right == clear && left_exist)
            //             clear->parent->right = clear->left;
            //         else if (clear->parent->right == clear == !left_exist)
            //             clear->parent->rigth = clear->right;
            //     }
            //     return 1;
            // }

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

            /**
             * @brief deallocate a node
             * 
             * @param to_clear node to clear
             */
            void deallocateNode(node *to_clear) {
                
                _allocNode.destroy(to_clear);
                _allocNode.deallocate(to_clear, 1);
                _size--;
            }

            /**
             * @brief search a element 
             * 
             * @param k key to find
             * @return iterator on the element (_end if not found)
             */
            iterator searchNode(const key_type &k) {

                node* find = _root;
                while (!_comp(find->data.first, k) && !_comp(k, find->data.first)) {
                    if (_comp(find->data.first, k)) {
                        find = find->left;
                    } else {
                        find = find->right;
                    }
                    if (!find)
                        break;
                }
                if (!find)
                    return _end;
                return find;
            }

            /**
             * @brief insert a new element to the list
             * 
             * @param pos position to insert
             * @param val value_type to insert
             * @return iterator to the new element
             */
            iterator insertNode(node* pos, const value_type& val) {
                if (_root == _end)  {
                    node* tmp = _allocNode.allocate(1);
                    _allocNode.construct(tmp, node(val));
                    _root = tmp;
                    tmp->right = _end;
                    _end->parent = tmp;
                    _begin = _root;
                    _size++;
                    return tmp;
                }
                while (1) 
                {
                    if (!_comp(pos->data.first, val.first) && !_comp(val.first, pos->data.first))
                        break;
                    if (_comp(val.first, pos->data.first)) {
                        if (pos->left) {
                            pos = pos->left;
                        } else {
                            node* tmp = _allocNode.allocate(1);
                            _allocNode.construct(tmp, node(val));
                            if (pos == _begin) {
                                _begin = tmp;
                            }
                            pos->left = tmp;
                            tmp->parent = pos;
                            _size++;
                            return tmp;
                        }
                    } else {
                        if (pos->right && pos->right != _end) {
                            pos = pos->right;
                        } else {
                            node *tmp = _allocNode.allocate(1);
                            _allocNode.construct(tmp, node(val));
                            if (pos->right == _end) {
                                tmp->right = _end;
                                _end->parent = tmp;
                            }
                            pos->right = tmp;
                            tmp->parent = pos;
                            _size++;
                            return tmp;
                        }
                    }
                }
                return pos;
            }
    };
}

#endif