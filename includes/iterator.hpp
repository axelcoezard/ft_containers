/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:41:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/18 12:43:37 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "utils.hpp"
#include "rbtree_node.hpp"

namespace ft
{
	class input_iterator_tag { };

	class output_iterator_tag { };

	class forward_iterator_tag : public input_iterator_tag { };

	class bidirectional_iterator_tag : public forward_iterator_tag { };

	class random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef random_access_iterator_tag		iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef random_access_iterator_tag		iterator_category;
	};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef T								value_type;
			typedef Distance						difference_type;
			typedef Pointer							pointer;
			typedef Reference						reference;
			typedef Category						iterator_category;
	};

	template <typename T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		public:
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef T*	pointer;
			typedef T&	reference;

		protected:
			pointer		_ptr;

		public:
			random_access_iterator(void)
				: _ptr(nullptr) {}

			random_access_iterator(pointer ptr)
				: _ptr(ptr) {}

			random_access_iterator(const random_access_iterator & copy)
				: _ptr(copy.base()) {}

			~random_access_iterator(void) {}

			pointer base(void) const
			{
				return _ptr;
			}

			reference operator*(void) const
			{
				return *_ptr;
			}

			random_access_iterator &operator=(const random_access_iterator &copy)
			{
				_ptr = copy._ptr;
				return *this;
			}

			operator random_access_iterator<const T>(void) const
			{
				return random_access_iterator<const T>(_ptr);
			}

			difference_type operator==(const random_access_iterator &it) const
			{
				return _ptr == it._ptr;
			}

			difference_type operator!=(const random_access_iterator &it) const
			{
				return _ptr != it._ptr;
			}

			difference_type operator<(const random_access_iterator &it) const
			{
				return _ptr < it._ptr;
			}

			difference_type operator>(const random_access_iterator &it) const
			{
				return _ptr > it._ptr;
			}

			difference_type operator<=(const random_access_iterator &it) const
			{
				return _ptr <= it._ptr;
			}

			difference_type operator>=(const random_access_iterator &it) const
			{
				return _ptr >= it._ptr;
			}

			random_access_iterator operator+(difference_type n) const
			{
				return _ptr + n;
			}

			random_access_iterator operator-(difference_type n) const
			{
				return _ptr - n;
			}

			difference_type operator+(const random_access_iterator &it)
			{
				return _ptr + it._ptr;
			}

			difference_type operator-(const random_access_iterator &it)
			{
				return _ptr - it._ptr;
			}

			random_access_iterator& operator++(void)
			{
				_ptr++;
				return *this;
			}

			random_access_iterator operator++(int) //post-inc
			{
				random_access_iterator tmp(*this);
				operator++();
				return tmp;
			}

			random_access_iterator& operator--(void)
			{
				_ptr--;
				return *this;
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator tmp(*this);
				operator--();
				return tmp;
			}

			random_access_iterator& operator+=(difference_type n)
			{
				_ptr += n;
				return *this;
			}

			random_access_iterator& operator-=(difference_type n)
			{
				_ptr -= n;
				return *this;
			}

			pointer operator->() const
			{
				return &operator*();
			}

			reference operator[](difference_type n) const
			{
				return *operator+(n);
			}
	};

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator==(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator!=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator<(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator>(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator<=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator>=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template<typename T>
	random_access_iterator<T>
	operator+(typename random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& ra_it)
	{
		return &(*ra_it) + n;
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator-(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <class T>
	class reverse_iterator
	{
		public:
			typedef T												iterator_type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;

		protected:
			iterator_type	_iter;

		public:
			reverse_iterator(void)
				: _iter(nullptr) { };

			explicit reverse_iterator(iterator_type it)
				: _iter(it) { };

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> & copy)
				: _iter(copy.base()) {}

			reverse_iterator &operator=(const reverse_iterator &copy)
			{
				_iter = copy.base();
				return *this;
			}

			iterator_type base(void) const
			{
				return _iter;
			}

			reference operator*(void) const
			{
				iterator_type	tmp(_iter);
				return *(--tmp);
			}

			reverse_iterator operator+(difference_type n) const
			{
				return reverse_iterator(_iter - n);
			}

			reverse_iterator operator-(difference_type n) const
			{
				return reverse_iterator(_iter + n);
			}

			reverse_iterator& operator++(void)
			{
				--_iter;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator	tmp(*this);
				operator++();
				return tmp;
			}

			reverse_iterator& operator--(void)
			{
				++_iter;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator	tmp(*this);
				operator--();
				return tmp;
			}

			reverse_iterator& operator+=(difference_type n)
			{
				_iter -= n;
				return *this;
			}

			reverse_iterator& operator-=(difference_type n)
			{
				_iter += n;
				return *this;
			}

			pointer	operator->() const
			{
				return &operator*();
			}

			reference	operator[](difference_type n) const
			{
				return this->base()[-n - 1];
			}
	};

	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs > rhs);
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return rev_it + n;
	}

	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <class T, bool isConst = false>
	class bidirectional_iterator
	{
		public:
			typedef T							value_type;
			typedef bidirectional_iterator_tag	iterator_category;
			typedef size_t						difference_type;
			typedef value_type*					pointer;
			typedef value_type&					reference;
			typedef typename rbtree_node<T>		node_type;
			typedef node_type*					node_pointer;

		protected:
			node_pointer	_node;
			node_pointer	_last_node;

		public:
			bidirectional_iterator(void)
				: _node(NULL), _last_node(NULL) { }

			bidirectional_iterator(node_pointer node, node_pointer last_node = nullptr)
				: _node(node), _last_node(last_node) { }

			template <class Iter>
			bidirectional_iterator(const bidirectional_iterator<Iter> & copy)
				: _node(copy._node), _last_node(copy._last_node) {}

			~bidirectional_iterator(void) { }

			pointer base(void) const
			{
				return &_node->data;
			}

			pointer base_node(void) const
			{
				return &_node;
			}

			template <class Iter>
			bidirectional_iterator &operator=(const bidirectional_iterator<Iter> &copy)
			{
				_node = copy._node;
				_last_node = copy._last_node;
				return *this;
			}

			reference operator*(void) const
			{
				return _node->data;
			}

			reference operator*(void)
			{
				return _node->data;
			}

			pointer operator->(void) const
			{
				return &_node->data;
			}

			bidirectional_iterator& operator++(void)
			{
				if (_node == _last_node)
					_node = _node->NIL;
				else if (_node != _node->NIL && _node->right != _node->NIL)
				{
					_node = _node->right;
					while (_node->left != _node->NILi && _node->left != nullptr)
						_node = _node->left;
				}
				else
				{
					while (_node != _node->NIL && _node == _node->parent->right)
						_node = _node->parent;
					_node = _node->parent;
				}
				return *this;
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp(*this);
				operator++();
				return tmp;
			}

			bidirectional_iterator& operator--(void)
			{
				if (_node == _node->NIL || _node->NIL == NULL)
				{
					_node = _last_node;
					return *this;
				}
				else if (_node->left != _node->NIL)
				{
					_node = _node->left;
					while (_node->right != _node->NIL && _node->right != _node->NIL)
						_node = _node->right;
				}
				else
				{
					while (_node->parent != _node->NIL && _node == _node->parent->left)
						_node = _node->parent;
					_node = _node->parent;
				}
				return *this;
			}

			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp(*this);
				operator--();
				return tmp;
			}
	};

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename iterator_traits<InputIterator>::difference_type count = 0;
		while (first != last)
		{
			first++;
			count++;
		}
		return count;
	}
}

#endif
