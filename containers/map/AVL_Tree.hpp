/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_Tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:17:09 by abbelhac          #+#    #+#             */
/*   Updated: 2022/06/20 20:22:19 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

# include <iostream>

template < typename T >
    struct Node
    {
        T       element;
        Node    *left;
        Node    *right;
        int     bf;
        int     height;
    
        Node(const T value) : element(value), left(nullptr), right(nullptr), bf(0), height(0) {}
    
    };

template < typename T, class Alloc >
    class AvlTree
    {
        typedef T               value_type;
        typedef Node<T>*        node_pointer;
        typedef Alloc           allocator_type;

        
        private :
                    node_pointer            *root;
                    allocator_type  _alloc;
                    
        public  :

                    AvlTree() : root(nullptr) {}
                    AvlTree(value_type value) : root(_alloc.allocate(1, value)) {}
                    ~AvlTree(){_alloc.deallocate(root, 1);}
                    
        
    };

#endif