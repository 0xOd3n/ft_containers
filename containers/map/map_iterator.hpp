/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:14:53 by abbelhac          #+#    #+#             */
/*   Updated: 2022/07/20 02:17:35 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iostream>
#include "../iterator_traits.hpp"

namespace ft
{
	//SECTION - ITERATOR
    
	template <class T, class nodePtr>
	class mapiterator
	{
		//SECTION - MEMBER TYPES
        
		public:
			typedef typename iterator_traits<T>::difference_type  	difference_type;
			typedef typename iterator_traits<T>::value_type  		value_type;
			typedef typename iterator_traits<T>::pointer  			pointer;
			typedef typename iterator_traits<T>::reference			reference;
			typedef std::bidirectional_iterator_tag					iterator_category;
		
		private:
			nodePtr	node;

		//SECTION - MEMBER FUNCTIONS
        
		public:
			mapiterator() : node(nullptr) {}
			explicit mapiterator(nodePtr ptr) : node(ptr) {}
			template <class Iter, class nodeptr>
			mapiterator (const mapiterator<Iter, nodePtr>& it) : node(it.node) {}
			nodePtr base() const{return node;}
			reference operator*() const{return node->element;}
			pointer operator->() const {return (&(node->element));}
			mapiterator& operator++()
			{
				node = successor();
				return (*this);
			}
			mapiterator operator++(int)
			{
				mapiterator tmp(*this);
				++(*this);
				return (tmp);
			}
			mapiterator& operator--()
			{
				node = predecessor();
				return (*this);
			}
			mapiterator operator--(int)
			{
				mapiterator tmp(*this);
				--(*this);
				return (tmp);
			}
		private:
        
			nodePtr	successor()
			{
				nodePtr	parent = node->parent;
				nodePtr	tmp = node;
				if (tmp->right)
				{
					tmp = tmp->right;
					while (tmp->left)
						tmp = tmp->left;
					return tmp;
				}
				else
				{
					while (parent && tmp == parent->right)
					{
						tmp = parent;
						parent = tmp->parent;
					}
					return (parent);
				}
			}
			nodePtr	predecessor()
			{
				nodePtr	parent = node->parent;
				nodePtr	tmp = node;
				if (tmp->left)
				{
					tmp = tmp->left;
					while (tmp->right)
						tmp = tmp->right;
					return tmp;
				}
				else
				{
					while (parent && tmp == parent->left)
					{
						tmp = parent;
						parent = tmp->parent;
					}
					return (parent);
				}
			}
	};
    
	//SECTION - NON MEMBER FUNCTION OVERLOADS
    
	template <class Iter, class nodeptr>
	bool operator== (const mapiterator<Iter, nodeptr>& lhs,
					const mapiterator<Iter, nodeptr>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class Iter, class nodeptr>
	bool operator!= (const mapiterator<Iter, nodeptr>& lhs,
					const mapiterator<Iter, nodeptr>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
}

#endif