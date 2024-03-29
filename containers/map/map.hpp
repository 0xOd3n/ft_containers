/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:20:22 by abbelhac          #+#    #+#             */
/*   Updated: 2022/07/20 02:29:10 by abbelhac         ###   ########.fr       */
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
					typedef	ft::pair<const key_type, mapped_type>             	value_type;
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
					typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;



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
							_tree.insert(*first);
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
							insert(x.begin(), x.end());
						_alloc = x._alloc;
						_cmp = x._cmp;
						return *this;
					}

					~map() {}
					
				// SECTION - Iterator

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
				
				mapped_type&	operator[] (const key_type& k)
				{
					value_type element = ft::make_pair(k, mapped_type());
					nodePtr node = _tree.find(element);
					if (!node || node == _tree.getEnd())
					{
						_tree.insert(element);
						node = _tree.find(element);
					}
					return (node->element.second);
				}

				// Modifiers
				
				void clear() {_tree.clear();}

				pair<iterator, bool> insert (const value_type& val)
				{
					nodePtr	node = _tree.find(val);
					bool	notInserted = false;
					if (!node || node == _tree.getEnd())
					{
						_tree.insert(val);
						node = _tree.find(val);
						notInserted = true;
					}
					return (ft::make_pair(iterator(node), notInserted));
				}

				iterator insert (iterator position, const value_type& val)
				{
					static_cast<void>(position);
					nodePtr	node = _tree.find(val);
					if (!node || node == _tree.getEnd())
					{
						_tree.insert(val);
						node = _tree.find(val);
					}
					return (iterator(node));
				}

				template <class InputIterator>
				void	insert(InputIterator first, InputIterator last)
				{
					while (first != last)
					{
						_tree.insert(*first);
						first++;
					}
				}
				
				void	erase(iterator position)
				{
					nodePtr node = position.base();
					if (node)
						_tree.erase(*position);
				}

				size_type	erase(const key_type& k)
				{
					nodePtr node = _tree.find(ft::make_pair(k, mapped_type()));
					if (!node || node == _tree.getEnd())
					return (0);
					_tree.erase(node->element);
					return (1);
				}

				void	erase(iterator first, iterator last)
				{
					iterator tmp;
					while (first != last)
					{
						tmp = first++;
						erase(tmp);
						if (first == iterator(_tree.getEnd()))
							return;
					}
				}

				void	swap(map& other)
				{
					allocator_type alloc = _alloc;
					key_compare	cmp = _cmp;
					this->_alloc = other._alloc;
					this->_cmp = other._cmp;
					other._alloc = alloc;
					other._cmp = cmp;
					_tree.swap(other._tree);
				}

				// Lookup

				size_type	count(const key_type& k) const
				{
					nodePtr node = _tree.find(ft::make_pair(k, mapped_type()));
					if (!node || node == _tree.getEnd())
						return (0);
					return (1);
				}

				iterator find(const key_type& k)
				{
					nodePtr	node = _tree.find(ft::make_pair(k, mapped_type()));
					return (iterator(node));
				}

				const_iterator find(const key_type& k) const
				{
					nodePtr	node = _tree.find(ft::make_pair(k, mapped_type()));
					return (const_iterator(node));
				}

				iterator	lower_bound(const key_type& k)
				{
					iterator iter = find(k);
					if (iter.base() == _tree.getEnd())
						iter = iterator(_tree.lowerBound(ft::make_pair(k, mapped_type())));
					return (iter);
				}

				const iterator	lower_bound(const key_type& k) const
				{
					const iterator const_iter = find(k);
					if (const_iter.base() == _tree.getEnd())
						const_iter = const_iterator(_tree.lowerBound(ft::make_pair(k, mapped_type())));
					return (const_iter);
				}
				
				iterator upper_bound (const key_type& k)
				{
					iterator iter = find(k);
					if (iter.base() != _tree.getEnd())
						++iter;
					else
						iter = iterator(_tree.upperBound(ft::make_pair(k, mapped_type())));
					return (iter);
				}
				const_iterator upper_bound (const key_type& k) const
				{
					const_iterator const_iter = find(k);
					if (const_iter.base() != _tree.getEnd())
						++const_iter;
					else
						const_iter = const_iterator(_tree.upperBound(ft::make_pair(k, mapped_type())));
					return (const_iter);
				}

				pair<iterator, iterator> equal_range(const key_type& k)
				{
					return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
				}
				
				pair<const_iterator, const_iterator> equal_range(const key_type& k) const
				{
					return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
				}
				
				// Observers

				key_compare key_comp() const
				{
					return (this->_cmp);
				}
				
				value_compare value_comp() const
				{
					return (value_compare(_cmp));
				}
				
				// Allocator
				
				allocator_type get_allocator() const {return (this->_alloc);}
		   };
};

#endif