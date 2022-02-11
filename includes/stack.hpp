/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:45:20 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/11 06:18:54 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container					container_type;
			typedef Container::value_type		value_type;
			typedef Container::size_type		size_type;
			typedef Container::reference		reference;
			typedef Container::const_reference	const_reference;

		protected:
			container_type	_c;

		public:
			explicit stack(const container_type& cont = container_type())
				: _c(cont)
			{}

			~stack(void)
			{}

			stack& operator=(const stack& copy)
			{
				_c = copy._c;
				return (*this);
			}

			reference top(void)
			{
				return (this->_c.back())
			}

			const_reference top(void) const
			{
				return (this->_c.back());
			}

			bool empty(void) const
			{
				return (this->_c.empty());
			}

			size_type size(void) const
			{
				return (this->_c.size());
			}

			void push(const value_type& value)
			{
				this->_c.push_back();
			}

			void pop(void)
			{
				this->_c.pop_back();
			};
	};
}

template<class T, class Container>
bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs._c == rhs._c);
}

template<class T, class Container>
bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs._c != rhs._c);
}

template<class T, class Container>
bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs._c < rhs._c);
}

template<class T, class Container>
bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs._c > rhs._c);
}

template<class T, class Container>
bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs._c <= rhs._c);
}

template<class T, class Container>
bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{
	return (lhs._c >= rhs._c);
}

#endif
