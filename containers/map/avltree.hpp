/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_Tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbelhac <abbelhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:17:09 by abbelhac          #+#    #+#             */
/*   Updated: 2022/06/29 20:57:54 by abbelhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

# include <iostream>
#include <queue>
#include <fstream>

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
			Node() : element(0), left(nullptr), right(nullptr), parent(nullptr) {}
			Node(const T& value) : element(value), left(nullptr), right(nullptr), parent(nullptr), bf(0), height(0) {}
			Node(const T& value, int keep) : element(value) { keep = 0; }
		};

	template <class Type> struct rebind {
	typedef std::allocator<Type> other;
	};
	template < class T, class Alloc = std::allocator<T> >
		class AvlTree
		{
			public	:
			
			typedef	T																		value_type;
			typedef	Node<T>*																node_pointer;
			typedef	typename Alloc::template rebind<Node<value_type> >::other				allocator_type;

			
			private	:
						node_pointer			root;
						allocator_type			_alloc;
						int						tree_size;
						int						length;
						
			public	:

						AvlTree() : root(nullptr), tree_size(0), length(0) {}
						AvlTree(value_type value)
						{
							root = _alloc.allocate(1);
							_alloc.construct(root, value);
							tree_size = 1;
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
						
						int     size()
						{
							return (tree_size);
						}

						bool    is_empty()
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
							root = insert(root, value);
							tree_size++;
							if (length < getLenght(value))
								length = getLenght(value);
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
							if (value < node->element)
								return contains(node->left, value);
							else if (value > node->element)
								return (contains(node->right, value));
							return (true);
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
							if (value < node->element)
								node->left = insert(node->left, value, node);
							else if (value > node->element)
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
							if (value < node->element)
								node->left = remove(node->left, value);
							else if (value > node->element)
								node->right = remove(node->right, value);
							else
							{
								if (!node->left || !node->right)
								{
									// std::cout << "enter if one side is null \n";
									node_pointer tmp = (node->right) ? node->right : node->left;
									if (tmp)
										tmp->parent = node->parent;
									_alloc.deallocate(node, 1);
									node = tmp;
								}
								else if (node->left->height > node->right->height)
								{
									value_type Max_value = getMax(node->left);
									_alloc.construct(node, Max_value, 1);
									node->left = remove(node->left, Max_value);
								}
								else
								{
									value_type Min_value = getMin(node->right);
									_alloc.construct(node, Min_value, 1);
									node->right = remove(node->right, Min_value);
								}
							}
							update(node);
							return (balance(node));
							
						}
						
						// find max value method

						value_type	getMax(node_pointer node)
						{
							while (node != nullptr)
								node = node->right;
							return node->element;
						}

						// find min value method

						value_type	getMin(node_pointer node)
						{
							while (node != nullptr)
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
							std::ofstream	outfile("outfile");
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
								repeat = (length) - (getLenght(current->element));
								while (repeat--)
									outfile << " ";
								outfile << current->element;
								outfile << "|";
								if (current->parent)
									outfile << current->parent->element;
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