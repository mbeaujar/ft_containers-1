/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:44:36 by ranaili           #+#    #+#             */
/*   Updated: 2021/10/01 13:59:43 by ranaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <iostream>

namespace ft
{
    template < class Key,                                 // map::key_type
           class T,                                       // map::mapped_type
           class Compare = less<Key>,                     // map::key_compare
           class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
           > 
    class map
    {
        public :

        private :
            
    };
}

#endif