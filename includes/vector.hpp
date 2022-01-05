/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:00:55 by acoezard          #+#    #+#             */
/*   Updated: 2022/01/05 16:37:50 by acoezard         ###   ########.fr       */
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

namespace ft
{
	template <class T, class Allocator = std::allocator<T>>
	class vector
	{
		private:
		protected:
		public:
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename allocator_type::size_type					size_type;
			typedef typename allocator_type::difference_type			difference_type;
			typedef typename std::reverse_iterator<std::iterator>		iterator;
			typedef typename std::reverse_iterator<std::const_iterator>	const_iterator;

			vector(void)
			{
			
			}
			
			explicit vector(const allocator_type & alloc = allocator_type())
			{
			
			}

			explicit vector (
				size_type count,
				const value_type & value = value_type(),
				const allocator_type & alloc = allocator_type()
			) {
			
			}
			
			template<class InputIterator>
			vector(
				InputIterator first, InputIterator last,
				const allocator_type & alloc = allocator_type()
			) {
			
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

			/* **********************************************
			 * ITERATORS
			 * *********************************************/
			
			iterator	begin(void)
			{
			
			}

			const_iterator	begin(void) const
			{
			
			}

			iterator	end(void)
			{
			
			}

			const_iterator	end(void) const
			{
			
			}

			reverse_iterator	rbegin(void)
			{
			
			}

			const_reverse_iterator	rbegin(void) const
			{
			
			}

			reverse_iterator	rend(void)
			{
				
			}
			
			const_reverse_iterator	rend(void) const
			{
			
			}

			/* **********************************************
			 * ELEMENT ACCESS
			 * *********************************************/

			reference	at(size_t index)
			{
			
			}
			
			const_reference	at(size_t index) const
			{
			
			}

			reference	operator[](size_t index)
			{
			
			}

			const_reference	operator[](size_t index) const
			{
			
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
			
			}

			const value_type*	data(void) const
			{
			
			}

			/* **********************************************
			 * MODIFIERS
			 * *********************************************/

			void	assign(size_type count, const value_type& value)
			{

			}

			template<class InputIterator>
			void	assign(InputIterator first, InputIterator last)
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
			
			}

			void	clear(void)
			{
			
			}

			/* **********************************************
			 * CAPACITY
			 * *********************************************/

			bool	empty(void) const
			{
			
			}

			size_type	size(void) const
			{
			
			}

			size_type	max_size(void) const
			{
			
			}

			void	reserve(size_type new_cap)
			{
			
			}

			size_type	capacity(void) const
			{
			
			}
			
			void resize(size_type count, value_type value = value_type())
			{
			
			}

			/* **********************************************
			 * ALLOCATORS
			 * *********************************************/
		
			allocator_type	get_allocator() const
			{
			
			}
	}; 

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
	
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
	
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
	
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
	
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
	
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
	
	}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc> & x, vector<T, Alloc> & y)
	{
	
	}
}
