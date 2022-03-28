/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_node.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:30:13 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/28 22:24:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_NODE_HPP
#define RBTREE_NODE_HPP

#define RED		true
#define BLACK	false

namespace ft
{
	template <class T>
	struct rbtree_node
	{
		typedef T		value_type;

		rbtree_node*	left;
		rbtree_node*	right;
		rbtree_node*	parent;

		bool			color;

		value_type		data;

		rbtree_node(value_type const &src) : data(src) {}
	};
}

#endif
