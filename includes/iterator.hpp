/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:41:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/02 10:11:19 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

// Iterator tags: https://en.cppreference.com/w/cpp/iterator/iterator_tags

namespace ft
{
	struct input_iterator_tag { };

	struct output_iterator_tag { };

	struct forward_iterator_tag : public input_iterator_tag { };

	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	struct contiguous_iterator_tag : public random_access_iterator_tag { };

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
		typedef std::ptrdiff_t						difference_type;

		typedef T									value_type;

		typedef T*									pointer;

		typedef T&									reference;

		typedef ft::random_access_iterator_tag		iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t						difference_type;

		typedef T									value_type;

		typedef const T*							pointer;

		typedef const T&							reference;

		typedef ft::random_access_iterator_tag		iterator_category;
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef T								value_type;

			typedef Distance						difference_type;

			typedef Pointer							pointer;

			typedef Reference						reference;

			typedef Category						iterator_category;

	};

	template <class Iterator>
	class reverse_iterator
	: public iterator<
		typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type,
		typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer,
		typename iterator_traits<Iterator>::reference
	> {
		protected:
			typedef iterator_traits<Iterator>				traits_type;
		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;
		protected:
			Iterator	current;
		public:
			reverse_iterator(void) : current() { };

			explicit reverse_iterator (iterator_type it) : current(it) { };

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> & copy)
			: current(copy.base()) {}

			iterator_type		base(void) const
			{ return (this->current); }

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
