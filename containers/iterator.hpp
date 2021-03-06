/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:57:09 by ranaili           #+#    #+#             */
/*   Updated: 2021/10/04 16:41:56 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include <iostream>
# include "utils.hpp"

namespace ft
{
    struct random_access_iterator_tag {};

    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Pointer                                   pointer;
        typedef Reference                                 reference;
        typedef T                                         value_type;
        typedef Distance                                  difference_type;
        typedef Category                                  iterator_category;
    };

    template< class Iter >
    struct iterator_traits
    {
        typedef typename Iter::pointer                    pointer;
        typedef typename Iter::reference                  reference;
        typedef typename Iter::value_type                 value_type;
        typedef typename Iter::difference_type            difference_type;
        typedef typename Iter::iterator_category          iterator_category;
    };

    template< class T >
    struct iterator_traits<T*>
    {
        typedef T*                                        pointer;
        typedef T&                                        reference;
        typedef T                                         value_type;
        typedef typename std::ptrdiff_t                   difference_type;
        typedef typename ft::random_access_iterator_tag   iterator_category;
    };
    
    template< class T >
    struct iterator_traits<const T*>
    {
        typedef const T*                                  pointer;
        typedef const T&                                  reference;
        typedef T                                         value_type;
        typedef typename std::ptrdiff_t                   difference_type;
        typedef typename ft::random_access_iterator_tag   iterator_category;
    };

    template <class Iterator>
    class reverse_iterator
    {
        public:

            typedef Iterator                                           iterator_type;
            typedef typename ft::iterator_traits<Iterator>::pointer           pointer;            
            typedef typename ft::iterator_traits<Iterator>::reference         reference;
            typedef typename ft::iterator_traits<Iterator>::value_type        value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type   difference_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
            
            reverse_iterator() : current() {}
           
            explicit reverse_iterator (iterator_type it) : current(it) {}
           
            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {}
           
            iterator_type base() const { return (current); }

            reverse_iterator&   operator--() { ++current; return (*this); }
            reverse_iterator&   operator++() { --current; return (*this); }
            pointer             operator->() const { return &(operator*()); }
            reverse_iterator&   operator+= (difference_type n) { current -= n;return (*this); }
            reverse_iterator&   operator-= (difference_type n) { current += n; return (*this); }

            reference           operator*() const { iterator_type tmp = current; return (*(--tmp)); }

            reference           operator[] (difference_type n) const { return (this->base()[-n - 1]); }
            reverse_iterator    operator--(int) { reverse_iterator tmp = *this; --(*this); return (tmp); }
            reverse_iterator    operator++(int) { reverse_iterator tmp = *this; ++(*this); return (tmp); }
            reverse_iterator    operator- (difference_type n) const { return (reverse_iterator(current + n)); }
            reverse_iterator    operator+ (difference_type n) const { return (reverse_iterator(current - n)); }

            difference_type operator-(reverse_iterator const &r) { return r.base() - this->base(); }

        protected:
            iterator_type     current;
    };

    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator== (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator!= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator< (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator<= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator>
    bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator> (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() < rhs.base()); }

    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator_L, class Iterator_R>
    bool operator>= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }

    template<typename T>
    class random_access_iterator : private ft::iterator<ft::random_access_iterator_tag, T>
    {
        public :
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
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

            operator random_access_iterator<const T>() { return random_access_iterator<const T>(m_ptr); }

            pointer base() const { return m_ptr; }
        private :
            pointer m_ptr;
    };

    template<typename T, typename U>
    typename ft::random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) { return lhs.base() - rhs.base(); }

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

    /**************************************************************************************************************************/

    struct bidirectional_iterator_tag {};

    /**
     * @brief define value_type to value_type
     * 
     * @tparam isConst bool is const or not
     * @tparam T 
     */
    template <bool isConst, typename T>
    struct enable_if_const { typedef typename T::value_type value_type; };

    /**
     * @brief define const value_type to value_type
     * 
     * @tparam T 
     */
    template <typename T>
    struct enable_if_const<true, T> { typedef const typename T::value_type value_type; };



    template <typename T, bool isConst>
    class bidirectional_iterator : private ft::iterator<bidirectional_iterator_tag, T> {
        public:
            // typedef typename T::value_type                                                      value_type;
            typedef typename ft::enable_if_const<isConst, T>::value_type                        value_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer           pointer;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference         reference;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;

        bidirectional_iterator() {};

        bidirectional_iterator(T* ptr)
            : _M_node(ptr) {};

        T* base() { return _M_node; }

        template <typename U, bool fuckConst>
        bidirectional_iterator(bidirectional_iterator<U, fuckConst> const &copy, typename ft::enable_if<!fuckConst, U>::type* = 0)
            : _M_node(copy._M_node) {}

        ~bidirectional_iterator() {};

        bidirectional_iterator operator=(bidirectional_iterator const &copy) {

            if (this == &copy)
                return *this;
            _M_node = copy._M_node;
            return *this;
        }

        bool operator==(bidirectional_iterator const &lhs) { return (_M_node == lhs._M_node); }
        bool operator!=(bidirectional_iterator const &lhs) { return (_M_node != lhs._M_node); }
       
        reference operator*() const { return _M_node->data; }
        pointer operator->() const { return &(operator*()); }

        bidirectional_iterator &operator++()
        {
            if (_M_node->right)
            {
                _M_node = _M_node->right;
                while (_M_node->left)
                    _M_node = _M_node->left;
            }
            else
            {
                while (_M_node->parent && _M_node->parent->right == _M_node)
                    _M_node = _M_node->parent;
                if (_M_node->parent)
                    _M_node = _M_node->parent;
            }
            return *this;
        }

        bidirectional_iterator operator++(int)
        {
            bidirectional_iterator tmp(*this);
            operator++();
            return tmp;
        }

        bidirectional_iterator &operator--()
        {
            if (_M_node->left)
            {
                _M_node = _M_node->left;
                while (_M_node->right)
                    _M_node = _M_node->right;
            }
            else
            {
                while (_M_node->parent && _M_node->parent->left == _M_node)
                    _M_node = _M_node->parent;
                if (_M_node->parent)
                    _M_node = _M_node->parent;
            }
            return *this;
        }

        bidirectional_iterator operator--(int)
        {
            bidirectional_iterator tmp(*this);
            operator--();
            return tmp;
        } 

        operator bidirectional_iterator<const T, true>() { return bidirectional_iterator<const T, true>(_M_node); }

        operator const T*() { return _M_node; }

        T* _M_node;
    };

    // template  
}

#endif