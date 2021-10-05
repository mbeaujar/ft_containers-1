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
        // bool color;
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
             * @brief Construct a new map object
             * 
             * @tparam InputIterator 
             * @param first 
             * @param last 
             * @param comp 
             * @param alloc 
             */
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
                : _size(0),
                  _comp(comp),
                  _alloc(alloc),
                  _allocNode()
            {
                _end = _allocNode.allocate(1);
                _allocNode.construct(_end, node(value_type()));
                _root = _end;
                _begin = _root;
                this->insert(first, last);
            }

            /**
             * @brief Construct a new map object
             * 
             * @param x 
             */
            map (const map& x)
                : _size(0),
                  _comp(x._comp),
                  _alloc(x._alloc),
                  _allocNode(x._allocNode)
            {
                _end = _allocNode.allocate(1);
                _allocNode.construct(_end, node(value_type()));
                _root = _end;
                _begin = _root;
                this->insert(x.begin(), x.end());
            }

            /**
             * @brief assign map Object 
             * 
             * @param x 
             * @return map& 
             */
            map& operator= (const map& x) {
                if (this == &x)
                    return *this;
                this->clear();
                _alloc = x._alloc;
                _allocNode = x._allocNode;
                _comp = x._comp;
                this->insert(x.begin(), x.end());
                return *this;
            }
            
            /**
             * @brief Destroy the map object
             * 
             */
            ~map() {
                // erase(this->begin(), this->end());
                // _allocNode.destroy(_end);
                // _allocNode.deallocate(_end, 1);
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
            size_type max_size() const { return _allocNode.max_size(); }

            /**
             * @brief search a element with the key k 
             * 
             * @param k element to search
             * @return mapped_type& 
             */
            mapped_type& operator[] (const key_type& k)
            {
                iterator find = searchNode(k);
                if (find._M_node == _end)
                    return insertNode(_root, ft::make_pair(k, mapped_type()))->second;
                return find->second;
            }

            
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
                    if (position._M_node->parent)
                        return insertNode(position._M_node->parent, val);
                    return insertNode(position._M_node, val);
                } 
                else {
                    while (_comp(val.first, position->first) && position != _begin)
                        --position;
                    if (!_comp(position->first, val.first) && !_comp(val.first, position->first))
                        return position;
                    ++position;
                    if (position._M_node->parent)
                        return insertNode(position._M_node->parent, val);
                    return insertNode(position._M_node, val);
                }
                return position;
            }

            /**
             * @brief insert a range of element to the list
             * 
             * @tparam InputIterator 
             * @param first the beginning of the range
             * @param last the end of the range
             */
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last) {
                InputIterator position = this->begin();
                for (; first != last; first++) {
                    position = insert(position, *first);
                }
            }

            void erase (iterator position) { erase(position->first); }

            size_type erase(const key_type &k)
            {
                // bool root = clear == root;
                // bool begin = clear == begin;
                node *clear = searchNode(k)._M_node;

                if (clear == _end)
                    return 0;
                    //std::cout << "size = " << _size << std::endl;
                if (!clear->left && !clear->right)
                {
                    if (clear->parent->right == clear)
                        clear->parent->right = NULL;
                    else
                        clear->parent->left = NULL;
                    deallocateNode(clear);
                    if (_root == clear)
                        _root = _end;
                }
                else if (!clear->left || !clear->right)
                {
                    bool left_exist = !(clear->left == NULL);
                    if (clear->parent->left == clear && left_exist)
                    {
                        clear->parent->left = clear->left;
                        clear->left->parent = clear->parent->left;
                    }
                    else if (clear->parent->left == clear && !left_exist)
                    {
                        clear->parent->left = clear->right;
                        clear->right->parent = clear->parent->left;
                    }
                    else if (clear->parent->right == clear && left_exist)
                    {
                        clear->parent->right = clear->left;
                        clear->left->parent = clear->parent->right;
                    }
                    else if (clear->parent->right == clear == !left_exist)
                    {
                        clear->parent->right = clear->right;
                        clear->right->parent = clear->parent->right;
                    }
                    deallocateNode(clear);
                }
                else if (clear->left && clear->right)
                {
                    node *car = NULL;
                    
                    if (clear->left->right)
                    {
                        car = clear->left->right;
                        while (car->right)
                            car = car->right;
                        car->parent->right = NULL;
                    }
                    else if (clear->right->left)
                    {
                        car = clear->right->left;
                        while (car->left)
                            car = car->left;
                        car->parent->left = NULL;
                    }
                    if (clear->parent->right == clear)
                        clear->parent->right = car;
                    else if (clear->parent->left == clear)
                        clear->parent->left = car;
                    
                    if (car->parent->right == car)
                    {
                        car->left = car->parent->right;
                        car->right = clear->right;
                    }
                    else if (car->parent->left == car)
                    {
                        car->right = car->parent->left;
                        car->left = clear->left;
                    }
                    deallocateNode(clear);
                }
                return 1;
            }

            void erase (iterator first, iterator last) {
                while (first != last)
                    erase(first++);
            }


            void swap (map& x)
            {
                if (this == &x)
				    return;
                node*           _root_tmp = _root;
                node*           _begin_tmp = _begin;
                node*           _end_tmp = _end;
                size_type       _size_tmp = _size;
                key_compare     _comp_tmp = _comp;
                allocator_type  _alloc_tmp = _alloc;
                allocator_node  _allocNode_tmp = _allocNode;

                _root = x._root;
                _begin = x._begin;
                _end = x._end;
                _size = x._size;
                _comp = x._comp;
                _alloc = x._alloc;
                _allocNode = x._allocNode;
                
                x._root = _root_tmp;
                x._begin = _begin_tmp;
                x._end = _end_tmp;
                x._size = _size_tmp;
                x._comp = _comp_tmp;
                x._alloc = _alloc_tmp;
                x._allocNode = _allocNode_tmp;
            }
            
            void clear() { erase(this->begin(), this->end()); }

            key_compare key_comp() const { return _comp; }
            value_compare value_comp() const { return value_compare(_comp); }


            iterator find (const key_type& k) { return (searchNode(k)); }

            const_iterator find (const key_type& k) const { return (searchNode(k)); }

            size_type count (const key_type& k) const 
            {
                if (searchNode(k) == end())
                    return 0;
                return 1;
            }

            iterator lower_bound (const key_type& k)
            {
                iterator first = begin();
                iterator last = end();
                while (first != last && _comp(k, first->first))
                    first++;
                return first;
            }
            
            const_iterator lower_bound (const key_type& k) const
            {
                iterator first = begin();
                iterator last = end();
                while (first != last && _comp(k, first->first))
                    first++;
                return first;
            }

            iterator upper_bound (const key_type& k)
            {
                iterator first = begin();
                iterator last = end();
                while (first != last && _comp(k, first->first) == false)
                    first++;
                return first;
            }

            const_iterator upper_bound (const key_type& k) const
            {
                iterator first = begin();
                iterator last = end();
                while (first != last && _comp(k, first->first) == false)
                    first++;
                return first;
            }
            
            ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const { ft::make_pair(lower_bound(k), upper_bound(k)); }
            
            ft::pair<iterator,iterator>             equal_range (const key_type& k) { ft::make_pair(lower_bound(k), upper_bound(k)); }


            allocator_type get_allocator() const { return _allocNode; }


            void printBST() { printBST("", _root, false); }
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


            void printBST(std::string prefix, node* root, bool isLeft)
            {
                if (root != NULL && root != _end)
                {
                    std::cout << prefix;
                    std::cout << (isLeft ? "├──" : "└──");
                    std::cout << root->data.first << std::endl;
                    printBST(prefix + (isLeft ? "│   " : "    "), root->left, true);
                    printBST(prefix + (isLeft ? "│   " : "    "), root->right, false);
                }
            }

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
                    if (!_comp(val.first, pos->data.first) && !_comp(pos->data.first, val.first))
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

//     template< class Key, class T, class Compare, class Alloc >
//     bool operator==( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

//     template< class Key, class T, class Compare, class Alloc >

// bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs,
//                  const std::map<Key,T,Compare,Alloc>& rhs );
}

#endif