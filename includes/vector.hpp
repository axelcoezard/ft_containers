/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:00:55 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/03 10:19:41 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * SOURCES:
 *
 * https://en.cppreference.com/w/cpp/container/vector
 * https://www.cplusplus.com/reference/vector/vector
 * https://opensource.apple.com/source/libcpp/libcpp-31/include/vector.auto.html
 */

#pragma once

#include "utils.hpp"
#include "iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename allocator_type::difference_type				difference_type;

		protected:
			pointer			_begin;
			pointer			_end;
			pointer			_end_capacity;
			allocator_type	_alloc;

		public:
			explicit vector(const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _begin(nullptr), _end(nullptr), _end_capacity(nullptr)
			{}

			explicit vector (size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _begin(nullptr), _end(nullptr), _end_capacity(nullptr)
			{
				_begin = _alloc.allocate(count);
				_end = _begin;
				_end_capacity = _begin + count;
				while (count)
				{
					_alloc.construct(_end++, value);	
					count--;
				}
			}
			
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: _alloc(alloc),
				_begin(nullptr),
				_end(nullptr),
				_end_capacity(nullptr)
			{
				difference_type count = ft::distance(first, last);
				_begin = _alloc.allocate(count);
				_end = _begin;
				_end_capacity = _begin + count;
				while (count)
				{
					_alloc.construct(_end++, *first++);	
					count--;
				}
			}

			vector(const vector& copy)
			{
				(void) copy;
			}

			~vector(void)
			{
				this->clear();	
				_alloc.deallocate(_begin, this->capacity());
			}

			vector&	operator=(const vector& copy)
			{
				(void) copy;	
			}

			iterator	begin(void)
			{
				return (iterator(_begin));	
			}

			const_iterator	begin(void) const
			{
				return (const_iterator(_begin));	
			}

			iterator	end(void)
			{
				if (this->empty())
					return (this->begin());
				return (iterator(_end));	
			}

			const_iterator	end(void) const
			{
				if (this->empty())
					return (this->begin());
				return (const_iterator(_end));	
			}

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(this->end()));	
			}

			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(this->end()));	
			}

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(this->begin()));	
			}
			
			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(this->begin()));	
			}

			reference	at(size_t index)
			{
				if (index > 0 && index < this->size())
					return (this->operator[](index));
				throw (std::out_of_range("vector::at"));
			}
			
			const_reference	at(size_t index) const
			{
				if (index > 0 && index < this->size())
					return (this->operator[](index));
				throw (std::out_of_range("vector::at"));
			}

			reference	operator[](size_t index)
			{
				return *(_begin + index);	
			}

			const_reference	operator[](size_t index) const
			{
				return *(_begin + index);	
			}

			reference	front(void)
			{
				return *(_begin);
			}

			const_reference	front(void) const
			{
				return *(_begin);
			}


			reference	back(void)
			{
				return *(_end - 1);
			}

			const_reference	back(void) const
			{
				return *(_end - 1);
			}

			value_type*	data(void)
			{
				return (_begin);	
			}

			const value_type*	data(void) const
			{
				return (_begin);	
			}

			void	assign(size_type count, const value_type& value)
			{
				this->clear();
				if (count == 0)
					return ;
				if (this->capacity() < count)
				{
					_alloc.deallocate(_begin, this->capacity());
					_begin = _alloc.allocate(count);
					_end = _begin;
					_end_capacity = _begin + count;
				}
				while (count)
					_alloc.construct(_end++, value), count--;
			}

			template<class InputIterator>
			void	assign(InputIterator first, InputIterator last)
			{
				(void) first;
				(void) last;
			}
			
			void	push_back(const value_type& value)
			{
				(void) value;	
			}

			void	pop_back(void)
			{
				_alloc.destroy(&this->back());
				_end--;
			}

			iterator	insert(iterator position, const value_type& value)
			{
				(void) position;
				(void) value;
			}

			void	insert(iterator position, size_type count, const value_type& value)
			{
				(void) position;
				(void) count;
				(void) value;
			}

			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last)
			{
				(void) position;
				(void) first;
				(void) last;
			}
			
			iterator	erase(iterator position)
			{
				(void) position;
			}

			iterator	erase(iterator first, iterator last)
			{
				(void) first;
				(void) last;
			}

			void	swap(vector & x)
			{
				if (x == *this)
					return ;
				
				ft::swap(_begin, x._begin);
				ft::swap(_end, x._end);
				ft::swap(_end_capacity, x._end_capacity);
				ft::swap(_alloc, x._alloc);
			}

			void	clear(void)
			{
				size_type	size = this->size();
				for (size_type i = 0; i < size; i++)
				{
					_end--;
					_alloc.destroy(_end);
				}
			}

			bool	empty(void) const
			{
				return (this->size() == 0);	
			}

			size_type	size(void) const
			{
				return (_end - _begin);	
			}

			size_type	max_size(void) const
			{
				return (_alloc.max_size());
			}

			void	reserve(size_type new_cap)
			{
				(void) new_cap;	
			}

			size_type	capacity(void) const
			{
				return (_end_capacity - _begin);
			}
			
			void resize(size_type new_size, value_type value = value_type())
			{
				size_type	old_size = this->size();
				if (old_size > new_size)
					_end = _begin + new_size;
				if (old_size < new_size)
				{
					iterator	iter;
					size_type	old_cap = this->capacity();
					size_type	diff = new_size - old_size;

					if (diff <= old_cap && old_size <= old_cap - diff)
					{
						iter = this->end();
						_end = _begin + old_size + diff;
					}
					else
					{
						vector	vec(_alloc);
						vec.reserve(old_size + diff);
						vec._end = vec._begin + old_size + diff;
						iter = ft::copy(_begin, _end_capacity, vec.begin());	
						swap(vec);
					}
					ft::fill_n(iter, diff, value);
				}
			}

			allocator_type	get_allocator() const
			{
				return (_alloc);
			}
	}; 

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return !(lhs == rhs);	
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc> & x, vector<T, Alloc> & y)
	{
		x.swqp(y);
	}
}
