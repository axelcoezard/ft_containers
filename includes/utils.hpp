/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:23:37 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/03 12:33:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>

namespace ft
{
	template <bool Cond, class T = void>	struct enable_if {};
	template <class T>						struct enable_if<true, T> { typedef T type; };

	template <class T>	struct is_integral							{ static const bool value = false; };
	template <>			struct is_integral <bool>					{ static const bool value = true; };
	template <>			struct is_integral <char>					{ static const bool value = true; };
	template <>			struct is_integral <char16_t>				{ static const bool value = true; };
	template <>			struct is_integral <char32_t>				{ static const bool value = true; };
	template <>			struct is_integral <wchar_t>				{ static const bool value = true; };
	template <>			struct is_integral <signed char>			{ static const bool value = true; };
	template <>			struct is_integral <short int>				{ static const bool value = true; };
	template <>			struct is_integral <int>					{ static const bool value = true; };
	template <>			struct is_integral <long int>				{ static const bool value = true; };
	template <>			struct is_integral <long long int>			{ static const bool value = true; };
	template <>			struct is_integral <unsigned char>			{ static const bool value = true; };
	template <>			struct is_integral <unsigned short int>		{ static const bool value = true; };
	template <>			struct is_integral <unsigned int>			{ static const bool value = true; };
	template <>			struct is_integral <unsigned long int>		{ static const bool value = true; };
	template <>			struct is_integral <unsigned long long int>	{ static const bool value = true; };

	template <class T1, class T2>
	struct pair 
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;
		public:
			first_type	u;
			second_type	v;
		public:
			pair(first_type & u, second_type & v) : u(u), v(v) {};
			~pair(void) {};
	};

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 u, T2 v)
	{
		pair<T1, T2>	npair(u, v);
		return (npair);	
	}

	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2) return (true);
			if (*first2 < *first1) return (false);
			++first1;
			++first2;
		}
		return (first1 == last1 && first2 != last2);
	}

	template< class InputIterator1, class InputIterator2, class Comparator>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Comparator comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2)) return (true);
			if (comp(*first2, *first1)) return (false);
			++first1;
			++first2;
		}
		return (first1 == last1 && first2 != last2);
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator	copy(InputIterator first, InputIterator last, OutputIterator d_first)
	{
		while (first != last)
		{
			*d_first = *first;
			d_first++;
			first++;
		}
		return (d_first);
	}

	template <class OutputIterator, class Size, class T>
	OutputIterator	fill_n(OutputIterator first, Size n, const T & value)
	{
		while (n > 0)
		{
			*first = value;
			++first;
			--n;
		}
		return (first);
	}

	template<class T>
	void	swap(T & a, T & b)
	{
		T	tmp(a);
		a = b;
		b = tmp;
	}
}
