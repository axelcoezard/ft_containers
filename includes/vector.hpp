/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:00:55 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/01 14:18:57 by acoezard         ###   ########.fr       */
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
	template <class T, class Allocator = std::allocator<T>>
	class vector
	{
		public:
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename allocator_type::size_type					size_type;
			typedef typename allocator_type::difference_type			difference_type;
			typedef typename ft::iterator<value_type>					iterator;
			typedef typename ft::iterator<const value_type>				const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		protected:
			size_type		_size;
			pointer			_begin;
			pointer			_end;
			allocator_type	_alloc;

		public:
			vector(void)
			{
			
			}
			
			explicit vector(const allocator_type & alloc = allocator_type())
			{
			
			}

			explicit vector (size_type count,
				const value_type & value = value_type(), 
				const allocator_type & alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_pointer = this->_alloc.allocate(count);
				for (int i = 0; i < count; i++)
					this->push_back(new value_type(value));
			}
			
			template<class InputIterator>
			vector(InputIterator first, InputIterator last,
				const allocator_type & alloc = allocator_type())
			{
				this->_begin = first;
				this->_end = last;
				this->_alloc = alloc;
			}

			vector(const vector & copy)
			{
					
			}

			~vector(void)
			{
					
			}

			vector&	operator=(const vector & copy)
			{
			
			}

			iterator	begin(void)
			{
				return (iterator(this->begin, this));	
			}

			const_iterator	begin(void) const
			{
				return (const_iterator(this->begin, this));	
			}

			iterator	end(void)
			{
				return (iterator(this->end, this));	
			}

			const_iterator	end(void) const
			{
				return (const_iterator(this->end, this));	
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
				if (index > 0 && index < this->size)
					return (this->operator[](index));
				throw (std::out_of_range("vector::at"));
			}
			
			const_reference	at(size_t index) const
			{
				if (index > 0 && index < this->size)
					return (this->operator[](index));
				throw (std::out_of_range("vector::at"));
			}

			reference	operator[](size_t index)
			{
				return *(this->begin + index);	
			}

			const_reference	operator[](size_t index) const
			{
				return *(this->begin + index);	
			}

			reference	front(void)
			{

			}

			const_reference	front(void) const
			{
			
			}


			reference	back(void)
			{
			
			}

			const_reference	back(void) const
			{
			
			}

			value_type*	data(void)
			{
				return (this->_begin);	
			}

			const value_type*	data(void) const
			{
				return (this->_begin);	
			}

			void	assign(size_type count, const value_type& value)
			{

			}

			template<class InputIterator>
			void	assign(InputIterator first, InputIterator last)
			{
			
			}
			
			void	push_back(const value_type& value)
			{
			
			}

			void	pop_back(void)
			{
			
			}

			iterator	insert(iterator position, const value_type& value)
			{
			
			}

			void	insert(iterator position, size_type count, const value_type& value)
			{
			
			}

			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last)
			{
			
			}
			
			iterator	erase(iterator position)
			{
			
			}

			iterator	erase(iterator first, iterator last)
			{
			
			}

			void	swap(vector & x)
			{
				if (x == *this)
					return ;
				
				ft::swap(this->size, x.size);
				ft::swap(this->begin, x.begin);
				ft::swap(this->end, x.end);
				ft::swap(this->alloc, x.alloc);
			}

			void	clear(void)
			{
				
			}

			bool	empty(void) const
			{
				return (this->_size == 0)	
			}

			size_type	size(void) const
			{
				return (this->_size);	
			}

			size_type	max_size(void) const
			{
				return (this->_alloc.max_size());
			}

			void	reserve(size_type new_cap)
			{
					
			}

			size_type	capacity(void) const
			{
				return (this->_end - this->_begin);
			}
			
			void resize(size_type new_size, value_type value = value_type())
			{
				size_type	old_size = this->size();
				if (old_size > new_size)
					this->size = new_size;
				if (old_size < new_size)
				{
					iterator	iter;
					size_type	old_cap = this->capacity();
					size_type	diff = new_size - old_size;

					if (diff <= old_cap && old_size <= old_cap - diff)
					{
						iter = end();
						this->_size = old_size + diff; 
					}
					else
					{
						vector	vec(this->_alloc())
						vec.reserve(old_size + diff);
						vec._size = old_size + diff;
						iter = ft::copy(this->_begin, this->_end, vec.begin());	
						swap(vec);
					}
					ft::fill_n(iter, diff, value);
				}
			}

			allocator_type	get_allocator() const
			{
				return (this->_alloc);
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
		return (ft::lexiographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	
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
