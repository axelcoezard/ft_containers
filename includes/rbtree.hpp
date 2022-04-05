/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:25:19 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/05 14:38:43 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>
#include <functional>
#include <iostream>

#include "iterator.hpp"
#include "rbtree_iterator.hpp"
#include "rbtree_node.hpp"
#include "pair.hpp"
#include "utils.hpp"

namespace ft
{
	template <class T, class Compare, class Alloc = std::allocator<rbtree_node<T> > >
	class rbtree
	{
		public:
			typedef T												value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef size_t											size_type;
			typedef rbtree_node<value_type>							node;
			typedef node*											node_ptr;
			typedef ft::rbtree_iterator<value_type, node>			iterator;
			typedef ft::rbtree_iterator<const value_type, node>		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		protected:
			node_ptr										_root;
			node_ptr										_NIL;
			size_type										_size;
			allocator_type									_alloc;
			key_compare										_comp;

		public:
			rbtree(const allocator_type &alloc = allocator_type()) : _comp(key_compare())
			{
				_size = 0;
				_alloc = alloc;
				_NIL = _alloc.allocate(1);
				_NIL->parent = _NIL;
				_NIL->right = _NIL;
				_NIL->left = _NIL;
				_NIL->color = BLACK;
				_root = _NIL;
			}

			rbtree(const rbtree &copy)
			{
				_alloc = copy._alloc;
				_comp = copy._comp;
				_size = copy._size;
				_NIL = _alloc.allocate(1);
				_NIL->parent = _NIL;
				_NIL->right = _NIL;
				_NIL->left = _NIL;
				_NIL->color = BLACK;

				_root = _NIL;
				_deepCopy(*this, copy._root, copy._NIL);
			}

			~rbtree(void)
			{
				clear();
				_alloc.deallocate(_NIL, 1);
			}

			rbtree &operator=(const rbtree &copy)
			{
				clear();
				_deepCopy(*this, copy._root, copy._NIL);
				return *this;
			}

			iterator begin(void)
			{
				return iterator(_findMin(_root), _root, _NIL);
			}

			const_iterator begin(void) const
			{
				return const_iterator(_findMin(_root), _root, _NIL);
			}

			iterator end(void)
			{
				return iterator(_NIL, _root, _NIL);
			}

			const_iterator end(void) const
			{
				return const_iterator(_NIL, _root, _NIL);
			}

			reverse_iterator rbegin(void)
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin(void) const
			{
				return const_reverse_iterator(end());
			}
			reverse_iterator rend(void)
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend(void) const
			{
				return const_reverse_iterator(begin());
			}

			void clear(void)
			{
				_deepClear(_root);
				_root = _NIL;
				_size = 0;
			}

			size_type size(void) const
			{
				return _size;
			}

			size_type max_size(void) const
			{
				return _alloc.max_size();
			}

			ft::pair<iterator, bool> insert(const value_type &val)
			{
				node_ptr newNode = _newNode(val);
				ft::pair<node_ptr, bool> ret = _deepInsert(_root, newNode);
				if (ret.second)
				{
					_size++;
					if (newNode->parent == _NIL)
						newNode->color = BLACK;
					else
						_insertFix(newNode);
					_root = _getRoot(newNode);
					return ft::make_pair(iterator(newNode, _root, _NIL), true);
				}
				else
				{
					_alloc.destroy(newNode);
					_alloc.deallocate(newNode, 1);
					return ft::make_pair(iterator(ret.first, _root, _NIL), false);
				}
			}

			iterator insert(iterator hint, const value_type &value)
			{
				node_ptr next = _next(hint.base());
				if (_comp(hint.base()->data, value) && _comp(value, next->data))
				{
					node_ptr newNode = _newNode(value);
					ft::pair<node_ptr, bool> r = _deepInsert(hint.base(), newNode);
					_size++;
					return iterator(r.first, _root, _NIL);
				}
				return insert(value).first;
			}

			void erase(iterator position)
			{
				if (position.base() != _NIL)
					_deepRemove(position.base());
			}

			size_type erase(value_type const &k)
			{
				node_ptr tmp = _find(k);
				if (tmp)
					return _deepRemove(tmp);
				return 0;
			}

			void swap(rbtree &x)
			{
				ft::swap(x._root, _root);
				ft::swap(x._NIL, _NIL);
				ft::swap(x._size, _size);
				ft::swap(x._alloc, _alloc);
				ft::swap(x._comp, _comp);
			}

			iterator find(const value_type &k)
			{
				node_ptr ret = _find(k);
				if (!ret)	return end();
				else		return iterator(ret, _root, _NIL);
			}
			const_iterator find(const value_type &k) const
			{
				node_ptr ret = _find(k);
				if (!ret)	return end();
				else		return const_iterator(ret, _root, _NIL);
			}

			bool isIn(const value_type &k) const
			{
				return _find(k) != NULL;
			}

			iterator lower_bound(const value_type &k)
			{
				iterator it = begin();
				while (it != end())
				{
					node_ptr tmp = it.base();
					if (_comp(k, tmp->data) || (!_comp(k, tmp->data) && !_comp(tmp->data, k)))
						return it;
					it++;
				}
				return it;
			}

			const_iterator lower_bound(const value_type &k) const
			{
				const_iterator it = begin();
				while (it != end())
				{
					node_ptr tmp = it.base();
					if (_comp(k, tmp->data) || (!_comp(k, tmp->data) && !_comp(tmp->data, k)))
						return it;
					it++;
				}
				return it;
			}

			iterator upper_bound(const value_type &k)
			{
				iterator it = begin();
				while (it != end())
				{
					node_ptr tmp = it.base();
					if (_comp(k, tmp->data))
						return it;
					it++;
				}
				return it;
			}

			const_iterator upper_bound(const value_type &k) const
			{
				const_iterator it = begin();
				while (it != end())
				{
					node_ptr tmp = it.base();
					if (_comp(k, tmp->data))
						return it;
					it++;
				}
				return it;
			}

		private:
			int _deepRemove(node_ptr z)
			{
				node_ptr y = z;
				node_ptr x;
				bool y_original_color = y->color;

				if (z->left == _NIL)
				{
					x = z->right;
					_invert(z, z->right);
				}
				else if (z->right == _NIL)
				{
					x = z->left;
					_invert(z, z->left);
				}
				else
				{
					y = _findMin(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						_invert(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					_invert(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				_alloc.destroy(z);
				_alloc.deallocate(z, 1);
				_size--;
				if (y_original_color == BLACK)
					_removeFix(x);
				return 1;
			}

			void _removeFix(node_ptr x)
			{
				node_ptr s;
				while (x != _root && x->color == BLACK)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == RED)
						{
							s->color = BLACK;
							x->parent->color = RED;
							_leftRotate(x->parent);
							s = x->parent->right;
						}
						if (s->left->color == BLACK && s->right->color == BLACK)
						{
							s->color = RED;
							x = x->parent;
						}
						else
						{
							if (s->right->color == BLACK)
							{
								s->left->color = BLACK;
								s->color = RED;
								_rightRotate(s);
								s = x->parent->right;
							}
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->right->color = BLACK;
							_leftRotate(x->parent);
							x = _root;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == RED)
						{
							s->color = BLACK;
							x->parent->color = RED;
							_rightRotate(x->parent);
							s = x->parent->left;
						}
						if (s->right->color == BLACK && s->left->color == BLACK)
						{
							s->color = RED;
							x = x->parent;
						}
						else
						{
							if (s->left->color == BLACK)
							{
								s->right->color = BLACK;
								s->color = RED;
								_leftRotate(s);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->left->color = BLACK;
							_rightRotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK;
			}

			void _invert(node_ptr old, node_ptr latest)
			{
				if (old->parent == _NIL)
					_root = latest;
				else if (old == old->parent->left)
					old->parent->left = latest;
				else
					old->parent->right = latest;
				latest->parent = old->parent;
			}

			node_ptr _findMin(node_ptr root) const
			{
				while (root->left != _NIL)
					root = root->left;
				return root;
			}

			node_ptr _findMax(node_ptr root) const
			{
				while (root->right != _NIL)
					root = root->right;
				return root;
			}

			node_ptr _find(value_type const &val) const
			{
				node_ptr tmp = _root;
				while (tmp != _NIL)
				{
					if (_comp(val, tmp->data))
						tmp = tmp->left;
					else if (_comp(tmp->data, val))
						tmp = tmp->right;
					else
						return tmp;
				}
				return NULL;
			}

			node_ptr _getRoot(node_ptr n) const
			{
				node_ptr tmp = n;

				while (tmp->parent != _NIL)
					tmp = tmp->parent;
				return tmp;
			}

			void _deepCopy(rbtree &tree_dst, node_ptr root_src, node_ptr nil_src)
			{
				if (root_src != nil_src)
				{
					_deepCopy(tree_dst, root_src->left, nil_src);
					tree_dst.insert(root_src->data);
					_deepCopy(tree_dst, root_src->right, nil_src);
				}
			}

			void _deepClear(node_ptr src = NULL)
			{
				if (src == NULL)
					src = _root;
				if (src != _NIL)
				{
					_deepClear(src->left);
					_deepClear(src->right);
					_alloc.destroy(src);
					_alloc.deallocate(src, 1);
				}
			}

			ft::pair<node_ptr, bool> _deepInsert(node_ptr root, node_ptr n)
			{
				if (root != _NIL && _comp(n->data, root->data))
				{
					if (root->left != _NIL)
						return _deepInsert(root->left, n);
					else
						root->left = n;
				}
				else if (root != _NIL && _comp(root->data, n->data))
				{
					if (root->right != _NIL)
						return _deepInsert(root->right, n);
					else
						root->right = n;
				}
				else if (root != _NIL)
					return ft::make_pair(root, false);
				n->parent = root;
				n->color = RED;
				n->left = _NIL;
				n->right = _NIL;
				return ft::make_pair(n, true);
			}

			node_ptr _newNode(const value_type &data)
			{
				node_ptr newNode = _alloc.allocate(1);
				_alloc.construct(newNode, data);
				newNode->color = RED;
				newNode->left = _NIL;
				newNode->right = _NIL;
				newNode->parent = _NIL;
				return newNode;
			}

			void _leftRotate(node_ptr x)
			{
				node_ptr y = x->right;
				x->right = y->left;
				if (y->left != _NIL)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == _NIL)
					this->_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			node_ptr _next(node_ptr n) const
			{
				node_ptr tmp = _NIL;

				if (n->right != _NIL)
					return _findMin(n->right);
				tmp = n->parent;
				while (tmp != _NIL && n == tmp->right)
				{
					n = tmp;
					tmp = tmp->parent;
				}
				return tmp;
			}

			void _rightRotate(node_ptr x)
			{
				node_ptr y = x->left;
				x->left = y->right;
				if (y->right != _NIL)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == _NIL)
					this->_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			void _insertFix(node_ptr k)
			{
				node_ptr u;

				while (k->parent->color == RED)
				{
					if (k->parent == k->parent->parent->right)
					{
						u = k->parent->parent->left;
						if (u->color == RED)
						{
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left)
							{
								k = k->parent;
								_rightRotate(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							_leftRotate(k->parent->parent);
						}
					}
					else
					{
						u = k->parent->parent->right;

						if (u->color == RED)
						{
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->right)
							{
								k = k->parent;
								_leftRotate(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							_rightRotate(k->parent->parent);
						}
					}
					if (k == _root)
						break;
				}
				_root->color = BLACK;
			}
		};
}

#endif
