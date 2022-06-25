/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_Tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:17:09 by abbelhac          #+#    #+#             */
/*   Updated: 2022/06/25 23:58:10 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

# include <iostream>

namespace ft
{
	template < typename T >
		struct Node
		{
			T       element;
			Node    *left;
			Node    *right;
			Node    *parent;
			int     bf;
			int     height;
			Node(const T& value) : element(value), left(nullptr), right(nullptr), bf(0), height(0) {}
			Node(const T& value, int keep) : element(value) { keep = 0; }
		};

	template <class Type> struct rebind {
	typedef std::allocator<Type> other;
	};
	template < class T, class Alloc = std::allocator<T> >
		class AvlTree
		{
			typedef T                                                                       value_type;
			typedef Node<T>*                                                                node_pointer;
			typedef typename Alloc::template rebind<Node<value_type> >::other              allocator_type;

			
			private :
						node_pointer            root;
						allocator_type          _alloc;
						int                     tree_size;
						
			public  :

						AvlTree() : root(nullptr), tree_size(0) {}
						AvlTree(value_type value)
						{
							root = _alloc.allocate(1);
							_alloc.construct(root, value);
							tree_size = 1;
						}
						~AvlTree()
						{
							if (root)
							{
								_alloc.deallocate(root, 1);
								root = nullptr;
							}
						}

						node_pointer    clear_all(node_pointer node)
						{
							if (node != nullptr)
							{
								clear_all(node->left);
								clear_all(node->right);
								_alloc.deallocate(node, 1);
							}
							return nullptr;
						}
						
						int     height()
						{
							if (root == nullptr)
								return (0);
							return root->height;
						}

						int     size()
						{
							return (tree_size);
						}

						bool    is_empty()
						{
							return (size() == 0);
						}
						
						bool    contains(const value_type& value) const
						{
							return (contains(root, value));
						}
				
			private :

						bool    contains(node_pointer node, const value_type& value)
						{
							if (node == nullptr)
								return (false);
							if (value < node->element)
								return contains(node->left, value);
							else if (value > node->element)
								return (contains(node->right, value));
							return (true);
						}
		};
}

#endif