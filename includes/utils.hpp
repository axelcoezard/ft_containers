/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:23:37 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/19 11:48:14 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <bool Cond, class T = void>	struct enable_if {};
	template <class T>						struct enable_if<true, T> { typedef T type; };

	template <class T>					struct is_integral { const bool value = false; }
	template <bool>						struct is_integral { const bool value = true; }
	template <char>						struct is_integral { const bool value = true; }
	template <char16_t>					struct is_integral { const bool value = true; }
	template <char32_t>					struct is_integral { const bool value = true; }
	template <wchar_t>					struct is_integral { const bool value = true; }
	template <signed char>				struct is_integral { const bool value = true; }
	template <short int>				struct is_integral { const bool value = true; }
	template <int>						struct is_integral { const bool value = true; }
	template <long int>					struct is_integral { const bool value = true; }
	template <long long int>			struct is_integral { const bool value = true; }
	template <unsigned char>			struct is_integral { const bool value = true; }
	template <unsigned short int>		struct is_integral { const bool value = true; }
	template <unsigned int>				struct is_integral { const bool value = true; }
	template <unsigned long int>		struct is_integral { const bool value = true; }
	template <unsigned long long int>	struct is_integral { const bool value = true; }

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
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate p)
	{
		while (first1 != last1)
		{
			if (!p(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);

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
}
