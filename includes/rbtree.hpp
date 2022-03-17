/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:11:33 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/17 17:11:58 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include <functional>

namespace ft
{
	template <typename value_type>
	class rbtree_node
	{
		value_type			value;

		enum { red, black }	color;

		rbtree_node			*left;
		rbtree_node			*right;
		rbtree_node			*parent;
	};

	template <typename T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
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


	};
}

#endif