/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:41:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/03 12:34:06 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "utils.hpp"

// Iterator tags: https://en.cppreference.com/w/cpp/iterator/iterator_tags

namespace ft
{
	class input_iterator_tag { };

	class output_iterator_tag { };

	class forward_iterator_tag : public input_iterator_tag { };

	class bidirectional_iterator_tag : public forward_iterator_tag { };

	class random_access_iterator_tag : public bidirectional_iterator_tag { };

	class contiguous_iterator_tag : public random_access_iterator_tag { };

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
		typedef ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef random_access_iterator_tag			iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef random_access_iterator_tag			iterator_category;
	};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef T								value_type;
			typedef Distance						difference_type;
			typedef Pointer							pointer;
			typedef Reference						reference;
			typedef Category						iterator_category;

	};

	template <typename T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		public:
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef T*	pointer;
			typedef T&	reference;
		
		private:
			pointer		_ptr;
		
		public:
			random_access_iterator(void)
				: _ptr(nullptr) {}

			random_access_iterator(pointer ptr)
				: _ptr(ptr) {}

			random_access_iterator(const random_access_iterator & copy)
				: _ptr(copy.base()) {}

			~random_access_iterator(void) {}
			
			pointer	base(void) const
			{
				return (_ptr);
			}
			
			reference	operator*(void) const
			{
				return *(_ptr);
			}
			
			random_access_iterator	operator+(difference_type n) const
			{
				return (_ptr + n);
			}

			random_access_iterator	operator-(difference_type n) const
			{
				return (_ptr - n);
			}

			random_access_iterator&	operator++(void)
			{
				_ptr++;
				return (*this);
			}

			random_access_iterator	operator++(int) //post-inc
			{
				random_access_iterator	tmp(*this);
				operator++();
				return (tmp);
			}

			random_access_iterator&	operator--(void)
			{
				_ptr--;
				return (*this);
			}

			random_access_iterator	operator--(int)
			{
				random_access_iterator	tmp(*this);
				operator--();
				return (tmp);
			}

			random_access_iterator&	operator+=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}

			random_access_iterator&	operator-=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}
			
			pointer	operator->() const
			{
				return (&operator*());
			}

			reference	operator[](difference_type n) const
			{
				return *(operator+(n));
			}
	};
	
	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator==(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator!=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator<(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator>(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator<=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator>=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T>
	random_access_iterator<T>
	operator+(typename random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& ra_it)
	{
		return (&(*ra_it) + n);
	}

	template <typename T>
	typename random_access_iterator<T>::difference_type
	operator-(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <class Iterator>
	class reverse_iterator : public iterator <
		typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type,
		typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer,
		typename iterator_traits<Iterator>::reference
	> {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		protected:
			iterator_type	_iter;

		public:
			reverse_iterator(void)
				: _iter(nullptr) { };

			explicit reverse_iterator (iterator_type it)
				: _iter(it) { };

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> & copy)
				: _iter(copy.base()) {}

			iterator_type	base(void) const
			{
				return (_iter);
			}

			reference	operator*(void) const
			{
				iterator_type	tmp(_iter);
				return *(--tmp);	
			}
			
			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(_iter - n));
			}

			reverse_iterator	operator-(difference_type n) const
			{
				return (reverse_iterator(_iter + n));
			}

			reverse_iterator&	operator++(void)
			{
				--_iter;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(*this);
				operator++();
				return (tmp);
			}

			reverse_iterator&	operator--(void)
			{
				++_iter;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);
				operator--();
				return (tmp);
			}

			reverse_iterator&	operator+=(difference_type n)
			{
				_iter -= n;
				return (*this);
			}

			reverse_iterator&	operator-=(difference_type n)
			{
				_iter += n;
				return (*this);
			}
			
			pointer	operator->() const
			{
				return (&operator*());
			}

			reference	operator[](difference_type n) const
			{
				return (this->base()[-n - 1]); 
			}
	};

	template <class Iterator1, class Iterator2>
	bool	operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Iterator1, class Iterator2>
	bool	operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool	operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs > rhs);
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs < rhs);
	}
	
	template<class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}

	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type	distance(InputIterator first, InputIterator last)
	{
		typename iterator_traits<InputIterator>::difference_type count = 0;
		while (first != last)
		{
			first++;
			count++;
		}
		return (count);
	}
}

#endif
