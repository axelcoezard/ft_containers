/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:19:41 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/01 14:20:26 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "utils.hpp"
#include "iterator.hpp"

namespace ft
{
	template <class T>
	class rbtree_iterator
	{
		public:
			typedef T								value_type;
			typedef T*								node_ptr;
			typedef typename T::value_type			data;
			typedef data&							reference;
			typedef data*							pointer;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::bidirectional_iterator_tag	iterator_category;

		protected:
			node_ptr	_it;
			node_ptr	_root;
			node_ptr	_NIL;

		public:
			rbtree_iterator() : _it(NULL), _root(NULL), _NIL(NULL) {}
			rbtree_iterator(node_ptr it, node_ptr root, node_ptr NIL) : _it(it), _root(root), _NIL(NIL) {}
			rbtree_iterator(const rbtree_iterator &cpy) : _it(cpy._it), _root(cpy._root), _NIL(cpy._NIL) {}

			rbtree_iterator &operator=(const rbtree_iterator &it)
			{
				_it = it._it;
				_root = it._root;
				_NIL = it._NIL;
				return *this;
			}

			bool operator==(const rbtree_iterator &it) const
			{
				return _it == it._it;
			}

			bool operator!=(const rbtree_iterator &it) const
			{
				return _it != it._it;
			}

			reference operator*(void)
			{
				return _it->data;
			}

			reference operator*(void) const
			{
				return _it->data;
			}

			pointer operator->(void) const
			{
				return &_it->data;
			}

			rbtree_iterator &operator++()
			{
				if (_it != _NIL)
					_it = _findNext();
				return *this;
			}

			rbtree_iterator operator++(int)
			{
				rbtree_iterator tmp(*this);
				++(*this);
				return tmp;
			}

			rbtree_iterator &operator--()
			{
				if (_it != _NIL)
					_it = _findPrev();
				else
					_it = _findMax(_root);
				return *this;
			}

			rbtree_iterator operator--(int)
			{
				rbtree_iterator tmp(*this);
				--(*this);
				return tmp;
			}

			node_ptr getCurrent() const
			{
				return _it;
			}

		private:
			node_ptr _findMin(node_ptr n)
			{
				while (n->left != _NIL)
					n = n->left;
				return n;
			}

			node_ptr _findMax(node_ptr n)
			{
				while (n->right != _NIL)
					n = n->right;
				return n;
			}

			node_ptr _findNext()
			{
				node_ptr n = _it;
				if (n->right != _NIL)
					return _findMin(n->right);
				node_ptr next = n->parent;
				while (next != _NIL && n == next->right)
				{
					n = next;
					next = next->parent;
				}
				return next;
			}

			node_ptr _findPrev()
			{
				node_ptr n = _it;
				if (n->left != _NIL)
					return _findMax(n->left);
				node_ptr prev = n->parent;
				while (prev != _NIL && n == prev->left)
				{
					n = prev;
					prev = prev->parent;
				}
				return prev;
			}
		};
}

#endif
