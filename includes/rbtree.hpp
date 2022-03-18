/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:11:33 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/18 12:44:13 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include "rbtree_node.hpp"

namespace ft
{
	template <typename T, class Compare = std::less<T>, class Alloc = std::allocator<rbtree_node<T> > >
	class rbtree
	{
		public:
			typedef typename T::first_type								key_type;
			typedef T													value_type;
			typedef Compare												value_compare;
			typedef size_t												size_type;
			typedef rbtree_node<value_type>								node_type;
			typedef rbtree_node<const value_type>						const_node_type;
			typedef node_type*											node_ptr;
			typedef const_node_type*									const_node_ptr;
			typedef typename Alloc::template rebind<node_type>::other	allocator_type;

		private:
			size_type		_size;
			allocator_type	_alloc;
			value_compare	_comp;
			node_ptr		_root;
			node_ptr		NIL;

		public:
			tree(void)
			{}

			~tree(void)
			{}

			void insert(const value_type &val)
			{
				node_ptr
					y = NIL,
					x = _root;

				while (x != NIL)
				{
					y = x;
					if (_comp(val, x->value))
						x = x->left;
					else
						x = x->right;
				}

				node_ptr
					z = _alloc.allocate(1);
				_alloc.construct(z, val);

				z->parent = y;
				if (y == NIL)
					_root = z;
				else if (_comp(val, y->value))
					y->left = z;
				else
					y->right = z;

				insert_fixup(z);
				++_size;
			}

			void insert_fixup(node_ptr z)
			{
				while (z->parent->color == red)
				{
					if (z->parent == z->parent->parent->left)
					{
						node_ptr
							y = z->parent->parent->right;
						if (y->color == red)
						{
							z->parent->color = black;
							y->color = black;
							z->parent->parent->color = red;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->right)
							{
								z = z->parent;
								left_rotate(z);
							}
							z->parent->color = black;
							z->parent->parent->color = red;
							right_rotate(z->parent->parent);
						}
					}
					else
					{
						node_ptr
							y = z->parent->parent->left;
						if (y->color == red)
						{
							z->parent->color = black;
							y->color = black;
							z->parent->parent->color = red;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->left)
							{
								z = z->parent;
								right_rotate(z);
							}
							z->parent->color = black;
							z->parent->parent->color = red;
							left_rotate(z->parent->parent);
						}
					}
				}
				_root->color = black;
			}

			void left_rotate(node_ptr x)
			{
				node_ptr
					y = x->right;

				x->right = y->left;
				if (y->left != NIL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == NIL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void right_rotate(node_ptr x)
			{
				node_ptr
					y = x->left;

				x->left = y->right;
				if (y->right != NIL)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NIL)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->right = x;
				x->parent = y;
			}

			void erase(const value_type &val)
			{
				node_ptr
					z = find(val);

				if (z == NIL)
					return;

				node_ptr
					y = z,
					x;

				bool
					y_original_color = y->color;

				if (z->left == NIL)
				{
					x = z->right;
					transplant(z, z->right);
				}
				else if (z->right == NIL)
				{
					x = z->left;
					transplant(z, z->left);
				}
				else
				{
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}

				if (y_original_color == black)
					erase_fixup(x);
				--_size;
			}

			void erase_fixup(node_ptr x)
			{
				while (x != _root && x->color == black)
				{
					if (x == x->parent->left)
					{
						node_ptr
							w = x->parent->right;
						if (w->color == red)
						{
							w->color = black;
							x->parent->color = red;
							left_rotate(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == black && w->right->color == black)
						{
							w->color = red;
							x = x->parent;
						}
						else
						{
							if (w->right->color == black)
							{
								w->left->color = black;
								w->color = red;
								right_rotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = black;
							w->right->color = black;
							left_rotate(x->parent);
							x = _root;
						}
					}
					else
					{
						node_ptr
							w = x->parent->left;
						if (w->color == red)
						{
							w->color = black;
							x->parent->color = red;
							right_rotate(x->parent);
							w = x->parent->left;
						}
						if (w->right->color == black && w->left->color == black)
						{
							w->color = red;
							x = x->parent;
						}
						else
						{
							if (w->left->color == black)
							{
								w->right->color = black;
								w->color = red;
								left_rotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = black;
							w->left->color = black;
							right_rotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = black;
			}

			void transplant(node_ptr u, node_ptr v)
			{
				if (u->parent == NIL)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			node_ptr minimum(node_ptr x)
			{
				while (x->left != NIL)
					x = x->left;
				return x;
			}

			node_ptr maximum(node_ptr x)
			{
				while (x->right != NIL)
					x = x->right;
				return x;
			}

			node_ptr successor(node_ptr x)
			{
				if (x->right != NIL)
					return minimum(x->right);
				node_ptr
					y = x->parent;
				while (y != NIL && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			node_ptr predecessor(node_ptr x)
			{
				if (x->left != NIL)
					return maximum(x->left);
				node_ptr
					y = x->parent;
				while (y != NIL && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

	};
}

#endif
