/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_Tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:17:09 by abbelhac          #+#    #+#             */
/*   Updated: 2022/07/14 22:14:59 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

#include <iostream>
#include <queue>
#include <fstream>

namespace ft
{
	// Node Data Structure :
	template < class T >
		struct Node
		{
			T       element;
			Node    *left;
			Node    *right;
			Node    *parent;
			int     bf;
			int     height;
			Node() : left(nullptr), right(nullptr), parent(nullptr), bf(0), height(0){}
			Node(const T& value) : element(value), left(nullptr), right(nullptr), parent(nullptr), bf(0), height(0) {}
			Node(const T& value, int keep) : element(value) { keep = 0; }
		};

	// Avl Balanced Tree :  

	template <class Type> struct rebind {
	typedef std::allocator<Type> other;
	};
	template < class T, class Compare, class Alloc = std::allocator<T> >
		class AvlTree
		{
			public	:
			
			typedef	T																		value_type;
			typedef	Compare																	key_compare;
			typedef	Node<T>*																node_pointer;
			typedef	typename Alloc::template rebind<Node<value_type> >::other				allocator_type;
			typedef	typename allocator_type::size_type										size_type;

			
			private	:
						node_pointer			root;
						node_pointer			_end;
						allocator_type			_alloc;
						size_type				tree_size;
						key_compare				_cmp;
						
						int						length;
						
			public	:

						AvlTree(const allocator_type& alloc = allocator_type(), const key_compare& cmp = key_compare()) : root(nullptr), tree_size(0),_cmp(cmp), length(0) {
							_end = _alloc.allocate(1);
						}
						AvlTree(value_type value)
						{
							_end = _alloc.allocate(1);
							root = _alloc.allocate(1);
							_alloc.construct(root, value);
							tree_size = 1;
							_end->left = root;
							length = getLenght(value);
						}
						~AvlTree()
						{
							root = clear_all(root);
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
						
						// get the root's height
						
						int     height()
						{
							if (root == nullptr)
								return (0);
							return root->height;
						}

						// get the tree size
						
						int		size()
						{
							return (tree_size);
						}

						size_type max_size() const 
						{
							return _alloc.max_size();
						}

						allocator_type get_allocator() const 
						{
							return (this->_alloc);
						}

						bool	is_empty()
						{
							return (size() == 0);
						}
						
						// check if a value is already exist

						bool    contains(const value_type& value) const
						{
							return (contains(root, value));
						}

						// insert a new value inside the tree

						bool	insert(const value_type& value)
						{
							if (contains(root, value))
								return (false);
							root = insert(root, value, _end);
							tree_size++;
							if (length < getLenght(value.first))
								length = getLenght(value.first);
							return (true);
						}

						// Remove a value from the tree

						bool	remove(value_type value)
						{
							if (!contains(root, value))
								return (false);
							else
							{
								root = remove(root, value);
								tree_size--;
								return (true);
							}
						}

						nodePtr	getEnd() const
						{
							return (this->_end);
						}

						node_pointer	getMin(node_pointer node = nullptr) const
						{
							if (!node)
								node = _root;
							while (node && node->left)
								node = node->left;
							return node;
						}
						node_pointer	getMax(node_pointer node = nullptr)
						{
							if (!node)
								node = _root;
							while (node && node->right)
								node = node->right;
							return node;
						}

						void	print()
						{
							levelOrder();
						}
				
			private :
						
						// check if the value is already exist in the tree (recursive search)

						bool    contains(node_pointer node, const value_type& value)  const
						{
							if (node == nullptr)
								return (false);
							if (value.first == node->element.first)
								return (true);
							if (_cmp(value.first, node->element.first))
								return contains(node->left, value);
							else
								return (contains(node->right, value));
						}
						
						// insert a new value inside the tree

						node_pointer	insert(node_pointer node, const value_type& value, node_pointer parent = nullptr)
						{
							if (node == nullptr)
							{
								node = _alloc.allocate(1);
								_alloc.construct(node, value);
								node->parent = parent;
								return (node);
							}
							if (_cmp(value.first, node->element.first))
								node->left = insert(node->left, value, node);
							else
								node->right = insert(node->right, value, node);
							update(node);
							return (balance(node));
						}
						
						// update node's height and balance factor
						
						void	update(node_pointer node)
						{
							int left_node_height = (node->left == nullptr) ? -1 : node->left->height;
							int right_node_height = (node->right == nullptr) ? -1 : node->right->height;
							node->height = 1 + ((left_node_height > right_node_height) ? left_node_height : right_node_height);
							node->bf = (right_node_height - left_node_height);
						}
						
						// rebalance a node if the balance factor is +2 or -2

						node_pointer	balance(node_pointer node)
						{
							if (node->bf == -2)
							{
								if (node->left->bf <= 0)
									return (leftLeftcase(node));
								return (leftRightcase(node));
							}
							else if (node->bf == 2)
							{
								if (node->right->bf >= 0)
									return (rightRightcase(node));
								return (rightLeftcase(node));
							}
							// do nothing if balance factor is 0, 1 or -1 which is fine
							return (node);
						}
						
						node_pointer	leftLeftcase(node_pointer node)
						{
							return (rightRotation(node));
						}

						node_pointer	leftRightcase(node_pointer node)
						{
							node->left = leftRotation(node->left);
							return (leftLeftcase(node));
						}

						node_pointer	rightRightcase(node_pointer node)
						{
							return (leftRotation(node));
						}

						node_pointer	rightLeftcase(node_pointer node)
						{
							node->right = rightRotation(node->right);
							return (rightRightcase(node));
						}

						// **	Rotation methods	**

						// Left Rotation

						node_pointer	leftRotation(node_pointer node)
						{
							node_pointer node_parent = node->parent;
							node_pointer newRoot = node->right;
							node->right = newRoot->left;
							if (node->right)
								node->right->parent = node;
							node->parent = newRoot;
							newRoot->left = node;
							newRoot->parent = node_parent;
							update(node);
							update(newRoot);
							return (newRoot);
						}

						// Right Rotation

						node_pointer	rightRotation(node_pointer node)
						{
							node_pointer node_parent = node->parent;
							node_pointer newRoot = node->left;
							node->left = newRoot->right;
							if (node->left)
								node->left->parent = node;
							node->parent = newRoot;
							newRoot->right = node;
							newRoot->parent = node_parent;
							update(node);
							update(newRoot);
							return (newRoot);
						}

						// remove method						

						node_pointer	remove(node_pointer node, value_type value)
						{
							if (!node)
								return (nullptr);
							if (value.first == node->element.first)
							{
								if (!node->left || !node->right)
								{
									node_pointer tmp = (node->right) ? node->right : node->left;
									if (tmp)
										tmp->parent = node->parent;
									_alloc.deallocate(node, 1);
									return (tmp);
								}
								else if (node->left->height > node->right->height)
								{
									value_type Max_value = findMax(node->left);
									_alloc.construct(node, Max_value, 1);
									node->left = remove(node->left, Max_value);
								}
								else
								{
									value_type Min_value = findMin(node->right);
									_alloc.construct(node, Min_value, 1);
									node->right = remove(node->right, Min_value);
								}
							}
							else if (_cmp(value.first, node->element.first))
								node->left = remove(node->left, value);
							else
								node->right = remove(node->right, value);
							update(node);
							return (balance(node));
						}
						
						// find max value method

						value_type	findMax(node_pointer node)
						{
							while (node->right != nullptr)
								node = node->right;
							return node->element;
						}

						// find min value method

						value_type	findMin(node_pointer node)
						{
							while (node->left != nullptr)
								node = node->left;
							return (node->element);
						}
						
						// methods for printing the tree

						int		getLenght(int data)
						{
							return (std::to_string(data).length());
						}
						int		getLenght(std::string data)
						{
							return (data.length());
						}
						int		getLenght(char data)
						{
							data = 'a';
							return (1);
						}
						void	levelOrder()
						{
							node_pointer node = root;
							std::ofstream	outfile("outfile",std::ios_base::app);
							outfile << "\n\n\n\n";
							std::queue<node_pointer > q;
							node_pointer empty = _alloc.allocate(1);
							_alloc.construct(empty);
							int	spaces = 0;
							int	currentSpaces = 0;
							int	level = 0;
							int	childs = 0;
							int	repeat;
							int	height = root->height;
							int len = (length * 2) + 3;
							// length += 2;
							
							q.push(root);
							while (height >= 0)
							{
								node_pointer current = q.front();
								if (current->left)
									q.push(current->left);
								else
									q.push(empty);
								if (current->right)
									q.push(current->right);
								else
									q.push(empty);
								q.pop();
								currentSpaces = (std::pow(2, height) * len) - len;
								if (level && (childs == (std::pow(2, level) - 1)))
								{
									repeat = pow(2, level);
									spaces = currentSpaces;
									while (spaces--)
										outfile << " ";
									while (--repeat)
									{
										if (repeat % 2)
										{
											spaces = (currentSpaces * 2) + (len * 3) - 2;
											outfile << "+";
											while (spaces--)
												outfile << "-";
											outfile << "+";
										}
										else
										{
											spaces = (currentSpaces * 2) + (len * 1);
											while (spaces--)
												outfile << " ";
										}
									}
									outfile << "\n";
								}
								spaces = currentSpaces;
								while (spaces--)
									outfile << " ";
								outfile << "(";
								repeat = (length) - (getLenght(current->element.first));
								while (repeat--)
									outfile << " ";
								outfile << current->element.first;
								outfile << "|";
								if (current->parent)
									outfile << current->parent->element.first;
								else
									outfile << "000";
								outfile << ")";
								spaces = currentSpaces + len;
								while (childs && spaces--)
									outfile << " ";
								if (!childs)
								{
									height--;
									level++;
									childs = std::pow(2, level);
									outfile << "\n";
								}
								childs--;
							}
						}
						
						
		};
}

#endif