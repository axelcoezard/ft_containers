/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:23:37 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/01 21:38:13 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cstddef>
#include <memory>
#include <stdexcept>

namespace ft
{
	template <bool Cond, class T = void>	struct enable_if {};
	template <class T>						struct enable_if<true, T>	{ typedef T type; };

	template <bool T>		struct is_integral_type									{ static const bool value = T; };

	template <typename T>	struct is_integral_base									: is_integral_type<false> {};
	template <>				struct is_integral_base <bool>							: is_integral_type<true> {};
	template <>				struct is_integral_base <char>							: is_integral_type<true> {};
	template <>				struct is_integral_base <wchar_t>						: is_integral_type<true> {};
	template <>				struct is_integral_base <signed char>					: is_integral_type<true> {};
	template <>				struct is_integral_base <short int>						: is_integral_type<true> {};
	template <>				struct is_integral_base <int>							: is_integral_type<true> {};
	template <>				struct is_integral_base <long int>						: is_integral_type<true> {};
	template <>				struct is_integral_base <long long int>					: is_integral_type<true> {};
	template <>				struct is_integral_base <unsigned char>					: is_integral_type<true> {};
	template <>				struct is_integral_base <unsigned short int>			: is_integral_type<true> {};
	template <>				struct is_integral_base <unsigned int>					: is_integral_type<true> {};
	template <>				struct is_integral_base <unsigned long int>				: is_integral_type<true> {};
	template <>				struct is_integral_base <unsigned long long int>		: is_integral_type<true> {};
	template <>				struct is_integral_base <const bool>					: is_integral_type<true> {};
	template <>				struct is_integral_base <const char>					: is_integral_type<true> {};
	template <>				struct is_integral_base <const wchar_t>					: is_integral_type<true> {};
	template <>				struct is_integral_base <const signed char>				: is_integral_type<true> {};
	template <>				struct is_integral_base <const short int>				: is_integral_type<true> {};
	template <>				struct is_integral_base <const int>						: is_integral_type<true> {};
	template <>				struct is_integral_base <const long int>				: is_integral_type<true> {};
	template <>				struct is_integral_base <const long long int>			: is_integral_type<true> {};
	template <>				struct is_integral_base <const unsigned char>			: is_integral_type<true> {};
	template <>				struct is_integral_base <const unsigned short int>		: is_integral_type<true> {};
	template <>				struct is_integral_base <const unsigned int>			: is_integral_type<true> {};
	template <>				struct is_integral_base <const unsigned long int>		: is_integral_type<true> {};
	template <>				struct is_integral_base <const unsigned long long int>	: is_integral_type<true> {};

	template <class T>		struct is_integral : public is_integral_base<T> {};

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
		while (first1 != last1)
		{
			if (first2 == last2) return false;
			if (*first2 < *first1) return (false);
			if (*first1 < *first2) return (true);
			++first1;
			++first2;
		}
		return first2 != last2;
	}

	template< class InputIterator1, class InputIterator2, class Comparator>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Comparator comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2) return false;
			if (comp(*first2, *first1)) return (false);
			if (comp(*first1, *first2)) return (true);
			++first1;
			++first2;
		}
		return first2 != last2;
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

#endif
