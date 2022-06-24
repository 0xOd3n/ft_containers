/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_Tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:17:09 by abbelhac          #+#    #+#             */
/*   Updated: 2022/06/24 20:39:54 by abbelhac         ###   ########.fr       */
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
        Node    *parent;
        int     bf;
        int     height;
        Node(const T &value) : element(value), left(nullptr), right(nullptr), bf(0), height(0) {}
        Node(const T &value, int keep) : elment(value) { keep = 0; }
    };

template < class T, class Alloc >
    class AvlTree
    {
        typedef T               value_type;
        typedef Node<T>*        node_pointer;
        typedef Alloc           allocator_type;

        
        private :
                    node_pointer            *root;
                    allocator_type          _alloc;
                    
        public  :

                    AvlTree() : root(nullptr) {}
                    AvlTree(value_type &value) : root(_alloc.allocate(1, value)) {}
                    // ~AvlTree()
                    // {
                    //     _alloc.deallocate(root, 1);
                    //     root = nullptr;
                    // }

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
            
    };

#endif