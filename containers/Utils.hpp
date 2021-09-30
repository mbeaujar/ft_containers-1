/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:13:38 by ranaili           #+#    #+#             */
/*   Updated: 2021/09/30 15:58:45 by ranaili          ###   ########.fr       */
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
    
};

#endif