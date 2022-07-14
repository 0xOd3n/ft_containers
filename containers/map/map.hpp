/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:20:22 by abbelhac          #+#    #+#             */
/*   Updated: 2022/07/14 22:20:05 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "pair.hpp"
#include "AVL_Tree.hpp"
#include "map_iterator.hpp"
#include "../reverse_iterator.hpp"




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

					typedef	Key                                                	key_type;
					typedef	T                                                  	mapped_type;
					typedef	std::pair<const key_type, mapped_type>             	value_type;
					typedef	Compare                                            	key_compare;
					typedef	Alloc                                              	allocator_type;
					typedef typename allocator_type::reference					reference;
					typedef typename allocator_type::const_reference			const_reference;
					typedef typename allocator_type::pointer					pointer;
					typedef typename allocator_type::const_pointer				const_pointer;
					typedef	typename allocator_type::difference_type 			difference_type;
					typedef	typename allocator_type::size_type 					size_type;
					typedef AvlTree<value_type, key_compare, allocator_type>	tree;
					typedef typename tree::node_pointer							nodePtr;
					typedef	ft::mapiterator<pointer, nodePtr>					iterator;
					typedef	ft::mapiterator<const_pointer, nodePtr>				const_iterator;
					typedef	ft::reverse_iterator<iterator>						reverse_iterator;



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

				// SECTION - Member functions : constructor
				
				public :
				
					explicit map (const key_compare& comp = key_compare(), const allocator_type alloc = allocator_type()) : _tree(), _cmp(comp), _alloc(alloc) {}
					
					template <class InputIterator>
					map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(), _cmp(comp), _alloc(alloc)
					{
						while (first != last)
						{
							_tree.insert(*first)
							first++;
						}
					}
					
					map (const map& x) : _cmp(x._cmp), _alloc(x._alloc)
					{
						*this = x;
					}
					
					map&	operator=(const map& x)
					{
						if (this == &x)
							return *this;
						_tree.clear();
						if (x.size())
							insert(x.begin(), X.end());
						_alloc = x._alloc;
						_cmp = x._cmp;
						return *this;
					}

					~map() {}
					
				// SECTION - Itertaors

				iterator	begin()
				{
					return (iterator(_tree.getMin()));
				}
				
				const_iterator	begin() const
				{
					return (const_iterator(_tree.getMin()));
				}

				iterator end()
				{
					return (iterator(_tree.getEnd()));
				}
				const_iterator end() const
				{
					return (const_iterator(_tree.getEnd()));
				}

				// Reverse iterator

				reverse_iterator rbegin()
				{
					return (reverse_iterator(this->end()));
				}

				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(this->end()));
				}

				reverse_iterator rend()
				{
					return (reverse_iterator(this->begin()));
				}

				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(this->begin()));
				}

				// Capacity

				bool empty() const {return (_tree.is_empty());}
				size_type	size() const {return (_tree.size());}
				size_type	max_size() const {return (_tree.max_size());}

				// Element access
				
				

				// Modifiers
				
				void clear() {_tree.clear_all();}
				
				// Allocator
				
				allocator_type get_allocator() const {return (this->_alloc);}
		   };
};

#endif