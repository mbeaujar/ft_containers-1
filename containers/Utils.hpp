/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 20:13:38 by ranaili           #+#    #+#             */
/*   Updated: 2021/09/22 18:32:10 by ranaili          ###   ########.fr       */
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
    // template struct <> is_integral<char16_t> : integral_constant<T, true> {};
    // template struct <> is_integral<char32_t> : integral_constant<T, true> {};
    template <> struct is_integral<short int> : integral_constant<bool, true> {};
    template <> struct is_integral<signed char> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned int> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned char> : integral_constant<bool, true> {};
    template <> struct is_integral<long long int> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long int> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned short int> : integral_constant<bool, true> {};
    template <> struct is_integral<unsigned long long int> : integral_constant<bool, true> {};

    
    /* ************************************************************************** */
    /*                              ITERATOR_TRAIT                                */
    /* ************************************************************************** */

    
};

#endif