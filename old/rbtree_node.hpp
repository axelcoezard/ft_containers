/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_node.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:14:02 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/25 18:54:44 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_NODE_HPP
#define RBTREE_NODE_HPP

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
		rbtree_node			*NIL;

		rbtree_node(void) : value(), color(black), left(NULL), right(NULL), parent(NULL), NIL(NULL) {}
		rbtree_node(const value_type &val) : value(val), color(black), left(NULL), right(NULL), parent(NULL), NIL(NULL) {}
	};
}

#endif
