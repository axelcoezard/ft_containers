/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:45:20 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/17 14:38:38 by acoezard         ###   ########.fr       */
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
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

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
				return *this;
			}

			reference top(void)
			{
				return _c.back();
			}

			const_reference top(void) const
			{
				return _c.back();
			}

			bool empty(void) const
			{
				return _c.empty();
			}

			size_type size(void) const
			{
				return _c.size();
			}

			void push(const value_type& value)
			{
				_c.push_back(value);
			}

			void pop(void)
			{
				_c.pop_back();
			};

			template<class _T, class _Container>
			friend bool operator==(const ft::stack<_T, _Container>& lhs, const ft::stack<_T, _Container>& rhs);

			template<class _T, class _Container>
			friend bool operator!=(const ft::stack<_T, _Container>& lhs, const ft::stack<_T, _Container>& rhs);

			template<class _T, class _Container>
			friend bool operator<(const ft::stack<_T, _Container>& lhs, const ft::stack<_T, _Container>& rhs);

			template<class _T, class _Container>
			friend bool operator>(const ft::stack<_T, _Container>& lhs, const ft::stack<_T, _Container>& rhs);

			template<class _T, class _Container>
			friend bool operator<=(const ft::stack<_T, _Container>& lhs, const ft::stack<_T, _Container>& rhs);

			template<class _T, class _Container>
			friend bool operator>=(const ft::stack<_T, _Container>& lhs, const ft::stack<_T, _Container>& rhs);
	};

	template<class T, class Container>
	bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._c == rhs._c;
	}

	template<class T, class Container>
	bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._c != rhs._c;
	}

	template<class T, class Container>
	bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._c < rhs._c;
	}

	template<class T, class Container>
	bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._c > rhs._c;
	}

	template<class T, class Container>
	bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._c <= rhs._c;
	}

	template<class T, class Container>
	bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._c >= rhs._c;
	}
}
#endif
