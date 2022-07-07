/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:20:22 by abbelhac          #+#    #+#             */
/*   Updated: 2022/07/06 21:56:14 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "pair.hpp"
#include "AVL_Tree.hpp"

namespace ft
{
	template < class Key,                                         // map::key_type
		   class T,                                              // map::mapped_type
		   class Compare = std::less<Key>,                      // map::key_compare
		   class Alloc = std::allocator<pair<const Key,T> >    // map::allocator_type
		   > class map
		   {
			   // SECTION - Member types :

				public :

				typedef	Key                                                key_type;
				typedef	T                                                  mapped_type;
				typedef	std::pair<const key_type, mapped_type>             value_type;
				typedef	Compare                                            key_compare;
				typedef	Alloc                                              allocator_type;
				typedef typename allocator_type::reference					reference;
				typedef typename allocator_type::const_reference			const_reference;
				typedef typename allocator_type::pointer					pointer;
				typedef typename allocator_type::const_pointer				const_pointer;
				typedef	typename allocator_type::difference_type 			difference_type;
				typedef	typename allocator_type::size_type 					size_type;
				typedef AvlTree<value_type, key_compare, allocator_type>	tree;

				// NOTE - Value_compare Nested function class 

				class value_compare
				{
					friend class map;
					protected:
						key_compare comp;
						value_compare (key_compare c) : comp(c) {}
					public:
						bool operator() (const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						}
				};
				
				// SECTION - Private data members :
				
				private :
				
				tree				_tree;
				key_compare			_cmp;
				allocator_type		_alloc;

				
				
		   };
};

#endif