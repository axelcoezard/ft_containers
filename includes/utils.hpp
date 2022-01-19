/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:23:37 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/19 10:38:53 by acoezard         ###   ########.fr       */
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
}
