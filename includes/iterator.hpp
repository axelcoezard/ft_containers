/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:41:05 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/05 13:05:38 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	class input_iterator_tag { };

	class output_iterator_tag { };

	class forward_iterator_tag : public input_iterator_tag { };

	class bidirectional_iterator_tag : public forward_iterator_tag { };

	class random_access_iterator_tag : public bidirectional_iterator_tag { };

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
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef random_access_iterator_tag		iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef random_access_iterator_tag		iterator_category;
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

		protected:
			pointer	_ptr;
	};

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename iterator_traits<InputIterator>::difference_type count = 0;
		while (first != last)
		{
			first++;
			count++;
		}
		return count;
	}

	template <class Iterator>
	class random_access_iterator : public iterator<random_access_iterator_tag, Iterator>
	{
		protected:
			typedef iterator<bidirectional_iterator_tag, Iterator>	iterator;
		public:
			typedef typename iterator::value_type					value_type;
			typedef typename iterator::difference_type				difference_type;
			typedef typename iterator::pointer						pointer;
			typedef typename iterator::reference					reference;
			typedef typename iterator::iterator_category			iterator_category;

		public:
			random_access_iterator(void) { this->_ptr = NULL; }
			random_access_iterator(pointer ptr) { this->_ptr = ptr; }
			random_access_iterator(const random_access_iterator & copy) { this->_ptr = copy._ptr; }

			pointer base(void) const
			{
				return this->_ptr;
			}

			reference operator*(void)
			{
				return *(this->_ptr);
			}

			reference operator*(void) const
			{
				return *(this->_ptr);
			}

			random_access_iterator &operator=(const random_access_iterator &copy)
			{
				if (*this != copy)
					this->_ptr = copy._ptr;
				return *this;
			}

			operator random_access_iterator<const Iterator>(void)
			{
				return random_access_iterator<const Iterator>(this->_ptr);
			}

			bool operator==(const random_access_iterator &it) const
			{
				return this->_ptr == it._ptr;
			}

			bool operator!=(const random_access_iterator &it) const
			{
				return this->_ptr != it._ptr;
			}

			bool operator<(const random_access_iterator &it) const
			{
				return this->_ptr < it._ptr;
			}

			bool operator>(const random_access_iterator &it) const
			{
				return this->_ptr > it._ptr;
			}

			bool operator<=(const random_access_iterator &it) const
			{
				return this->_ptr <= it._ptr;
			}

			bool operator>=(const random_access_iterator &it) const
			{
				return this->_ptr >= it._ptr;
			}

			bool operator==(random_access_iterator<const Iterator> &it) const
			{
				return this->_ptr == it.base();
			}

			bool operator!=(random_access_iterator<const Iterator> &it) const
			{
				return this->_ptr != it.base();
			}

			bool operator<(random_access_iterator<const Iterator> &it) const
			{
				return this->_ptr < it.base();
			}

			bool operator>(random_access_iterator<const Iterator> &it) const
			{
				return this->_ptr > it.base();
			}

			bool operator<=(random_access_iterator<const Iterator> &it) const
			{
				return this->_ptr <= it.base();
			}

			bool operator>=(random_access_iterator<const Iterator> &it) const
			{
				return this->_ptr >= it.base();
			}

			random_access_iterator operator+(difference_type n) const
			{
				return this->_ptr + n;
			}

			random_access_iterator operator-(difference_type n) const
			{
				return this->_ptr - n;
			}

			random_access_iterator& operator++(void)
			{
				this->_ptr += 1;
				return *this;
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator tmp(this->_ptr);
				this->_ptr += 1;
				return tmp;
			}

			random_access_iterator& operator--(void)
			{
				this->_ptr -= 1;
				return *this;
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator tmp(this->_ptr);
				this->_ptr -= 1;
				return tmp;
			}

			template <class T>
			friend random_access_iterator<T>
			operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> & rhs);

			template <class T>
			friend random_access_iterator<T>
			operator-(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> & rhs);

			random_access_iterator& operator+=(difference_type n)
			{
				this->_ptr += n;
				return *this;
			}

			random_access_iterator& operator-=(difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}

			pointer operator->(void) const
			{
				return this->_ptr;
			}

			reference operator[](difference_type n)
			{
				return *(this->_ptr + n);
			}

			reference operator[](difference_type n) const
			{
				return *(this->_ptr + n);
			}
	};

	template <typename T1, typename T2>
	bool operator==(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename T1, typename T2>
	bool operator!=(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename T1, typename T2>
	bool operator<(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename T1, typename T2>
	bool operator>(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename T1, typename T2>
	bool operator<=(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename T1, typename T2>
	bool operator>=(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template<typename T>
	random_access_iterator<T>
	operator+(typename random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& ra_it)
	{
		return ra_it.base() + n;
	}

	template <typename T1, typename T2>
	random_access_iterator<T1>
	operator-(typename random_access_iterator<T1>::difference_type n, typename ft::random_access_iterator<T2>& ra_it)
	{
		return ra_it.base() - n;
	}

	template <typename T1, typename T2>
	typename random_access_iterator<T1>::difference_type
	operator+(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return lhs.base() + rhs.base();
	}

	template <typename T1, typename T2>
	typename random_access_iterator<T1>::difference_type
	operator-(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <class T>
	class reverse_iterator
	{
		public:
			typedef T												iterator_type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;

		protected:
			iterator_type	_iter;

		public:
			reverse_iterator(void) { };

			explicit reverse_iterator(iterator_type it)
				: _iter(it) { };

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> & copy)
				: _iter(copy.base()) {}

			operator reverse_iterator<const T>(void) const
			{
				return reverse_iterator<const T>(_iter);
			}

			template<class Iterator>
			reverse_iterator &operator=(const reverse_iterator<Iterator> &copy)
			{
				if (*this != copy)
					_iter = copy.base();
				return *this;
			}

			iterator_type base(void) const
			{
				return _iter;
			}

			reference operator*(void)
			{
				iterator_type tmp(_iter);
				return *(--tmp);
			}

			const reference operator*(void) const
			{
				iterator_type tmp(_iter);
				return *(--tmp);
			}

			reverse_iterator operator+(difference_type n) const
			{
				return reverse_iterator(_iter - n);
			}

			reverse_iterator operator-(difference_type n) const
			{
				return reverse_iterator(_iter + n);
			}

			difference_type operator-(reverse_iterator rhs)
			{
				return -ft::distance(rhs._iter, _iter);
			}

			reverse_iterator& operator++(void)
			{
				_iter--;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp(*this);
				_iter--;
				return tmp;
			}

			reverse_iterator& operator--(void)
			{
				_iter++;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp(*this);
				_iter++;
				return tmp;
			}

			reverse_iterator& operator+=(difference_type n)
			{
				_iter -= n;
				return *this;
			}

			reverse_iterator& operator-=(difference_type n)
			{
				_iter += n;
				return *this;
			}

			pointer	operator->(void) const
			{
				iterator_type tmp(_iter);
				--tmp;
				return &(*tmp);
			}

			reference operator[](difference_type n)
			{
				return *(_iter - n - 1);
			}

			const reference operator[](difference_type n) const
			{
				return *(_iter - n - 1);
			}
	};

	template<class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template<class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return rhs < lhs;
	}

	template<class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs > rhs);
	}

	template<class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return rev_it + n;
	}

	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return rhs - lhs;
	}

	template <class Iterator>
	class bidirectional_iterator : public iterator<bidirectional_iterator_tag, Iterator>
	{
		protected:
			typedef iterator<bidirectional_iterator_tag, Iterator>	iterator;
		public:
			typedef typename iterator::value_type					value_type;
			typedef typename iterator::difference_type				difference_type;
			typedef typename iterator::iterator_category			iterator_category;
			typedef typename iterator::pointer						pointer;
			typedef typename iterator::reference					reference;

		public:
			bidirectional_iterator(void) {this->_ptr = NULL; };
			bidirectional_iterator(pointer ptr) { this->_ptr = ptr; };
			bidirectional_iterator(const bidirectional_iterator & copy) { *this = copy; }

			pointer base(void) const
			{
				return this->_ptr;
			}

			operator bidirectional_iterator<const Iterator>(void)
			{
				return bidirectional_iterator<const Iterator>(this->_ptr);
			}

			template<class T>
			bidirectional_iterator &operator=(const bidirectional_iterator<T>& copy)
			{
				if (*this != copy)
					this->_ptr = copy._ptr;
				return (*this);
			}

			reference operator*(void) const
			{
				return *(this->_ptr);
			}

			pointer operator->(void) const
			{
				return this->_ptr;
			}

			bidirectional_iterator& operator++(void)
			{
				this->_ptr += 1;
				return *this;
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp(this->_ptr);
				this->_ptr += 1;
				return tmp;
			}

			bidirectional_iterator& operator--(void)
			{
				this->_ptr -= 1;
				return *this;
			}

			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp(this->_ptr);
				this->_ptr -= 1;
				return tmp;
			}

			bool operator==(const bidirectional_iterator& rhs) const
			{
				return this->_ptr == rhs._ptr;
			}

			bool operator==(bidirectional_iterator<const Iterator> & rhs) const
			{
				return this->_ptr == rhs._ptr;
			}

			bool operator!=(const bidirectional_iterator & rhs) const
			{
				return this->_ptr != rhs._ptr;
			}

			bool operator!=(bidirectional_iterator<const Iterator> & rhs) const
			{
				return this->_ptr != rhs._ptr;
			}
	};

	template <class Iterator1, class Iterator2>
	bool operator==(const bidirectional_iterator<Iterator1>& lhs, const bidirectional_iterator<Iterator2>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const bidirectional_iterator<Iterator1>& lhs, const bidirectional_iterator<Iterator2>& rhs)
	{
		return lhs.base() != rhs.base();
	}
}

#endif
