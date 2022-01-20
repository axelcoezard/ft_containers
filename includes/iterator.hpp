/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:41:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/20 16:46:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

namespace ft
{
	template <class Iterator>
	struct iterator_traits;

	template <class T>
	struct iterator_traits<T*>;

	template <class T>
	struct iterator_traits<const T*>;

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
		private:

		public:
			iterator(void)
			{
				
			}
	};

	class const_iterator;

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator								iterator_type;
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
		private:

		public:
			reverse_iterator(void);

			explicit reverse_iterator (iterator_type it);

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> & rev_it);

			iterator_type		base(void) const;

			reference			operator*(void) const;
			reverse_iterator	operator+(difference_type n) const;
			reverse_iterator&	operator++();

			reverse_iterator	operator++(int) //post-inc
			{
				reverse_iterator	tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator&	operator+=(difference_type n);
			reverse_iterator	operator-(difference_type n) const;
			reverse_iterator&	operator--();

			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp = *this;
				--(*this);
				return (tmp);
			}

			reverse_iterator&	operator-=(difference_type n);
			
			pointer				operator->() const
			{
				return (&operator*());
			}

			reference			operator[](difference_type n) const;
	};


}
