/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:13:38 by ranaili           #+#    #+#             */
/*   Updated: 2021/09/24 22:48:16 by ranaili          ###   ########.fr       */
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
    /*                              ITERATOR_STUFF                                */
    /* ************************************************************************** */

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
        
};

#endif