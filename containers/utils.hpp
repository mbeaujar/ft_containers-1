/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:13:38 by ranaili           #+#    #+#             */
/*   Updated: 2021/10/04 16:41:41 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_HPP__
# define __UTILS_HPP__

# include <iostream>

namespace ft
{
    /* ************************************************************************** */
    /*                              IS_INTEGRAL                                   */
    /* ************************************************************************** */

    template <class T, bool is>
    struct integral_constant
    {
        typedef T type;
        const static bool value = is;
    };

    template <class T> struct is_integral : integral_constant<T, false> {};

    template <> struct is_integral<int> : integral_constant<bool, true> {};
    template <> struct is_integral<bool> : integral_constant<bool, true> {};
    template <> struct is_integral<char> : integral_constant<bool, true> {};
    template <> struct is_integral<wchar_t> : integral_constant<bool, true> {};
    template <> struct is_integral<long int> : integral_constant<bool, true> {};
    template <> struct is_integral<short int> : integral_constant<bool, true> {};
    template <> struct is_integral<signed char> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned int> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned char> : integral_constant<bool, true> {};
    template <> struct is_integral<long long int> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long int> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned short int> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long long int> : integral_constant<bool, true> {};

    /* ************************************************************************** */
    /*                               ENABLE_IF                                    */
    /* ************************************************************************** */


    template<bool Cond, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };


    /* ************************************************************************** */
    /*                       LEXICOGRAPHICAL_COMPARE                              */
    /* ************************************************************************** */

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1, *first2))
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template<class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2)) // or: if (!pred(*first1,*first2)), for version 2
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template< class InputIt1, class InputIt2, class BinaryPredicate >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p );

    /* ************************************************************************** */
    /*                                  PAIR                                      */
    /* ************************************************************************** */

    /**
     * @brief structure with 2 elements, key and value
     * 
     * @tparam T1 key_type
     * @tparam T2 value_type
     */
    template<class T1, class T2> 
    struct pair 
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair() : first(), second() {};

        pair( const T1& x, const T2& y ) : first(x), second(y) {};

        template< class U1, class U2 >
        pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {};

        pair& operator=( const pair& other ) {
            if (this == &other)
                return *this;
            first = other.first; // 
            second = other.second; 
            return *this;
        };
    };

    template< class T1, class T2 >
    bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template< class T1, class T2 >
    bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(lhs == rhs); }

    template< class T1, class T2 >
    bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { 
    
        if (lhs.first < rhs.first)
            return true;
        else if (rhs.first < lhs.first)
            return false;
        else if (lhs.second < rhs.second)
            return true;
        return false;
    };

    template< class T1, class T2 >
    bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(rhs < lhs); }

    template< class T1, class T2 >
    bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return rhs < lhs; }

    template< class T1, class T2 >
    bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) { return !(rhs < lhs); }


    /* ************************************************************************** */
    /*                               MAKE_PAIR                                    */
    /* ************************************************************************** */

    /**
     * @brief create a pair
     * 
     * @tparam T1 
     * @tparam T2 
     * @param t 
     * @param u 
     * @return ft::pair<T1,T2> 
     */
    template< class T1, class T2 >
    ft::pair<T1,T2> make_pair( T1 t, T2 u ) { return ft::pair<T1, T2>(t, u); };

    /* ************************************************************************** */
    /*                                LESS                                        */
    /* ************************************************************************** */

    template <class T>
    struct less : std::binary_function<T, T, bool>
    {
        bool operator() (const T& x, const T& y) const { return (x < y); }
    };

    
};

#endif