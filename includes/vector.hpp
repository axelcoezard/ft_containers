/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:00:55 by acoezard          #+#    #+#             */
/*   Updated: 2022/03/01 18:26:20 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * SOURCES:
 *
 * https://en.cppreference.com/w/cpp/container/vector
 * https://www.cplusplus.com/reference/vector/vector
 * https://opensource.apple.com/source/libcpp/libcpp-31/include/vector.auto.html
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

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
			typedef typename allocator_type::difference_type				difference_type;
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		protected:
			allocator_type	_alloc;
			size_type		_capacity;
			pointer			_begin;
			pointer			_end;

		public:
			explicit vector(const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _capacity(0), _begin(nullptr), _end(nullptr)
			{}

			explicit vector (size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _capacity(count), _begin(nullptr), _end(nullptr)
			{
				_begin = _alloc.allocate(count);
				_end = _begin;
				while (count--)
					_alloc.construct(_end++, value);
			}

			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
				: _alloc(alloc), _begin(nullptr), _end(nullptr)
			{
				//size_type count = ft::distance(first, last);
				//_capacity = count;
				//_begin = _alloc.allocate(count);
				//_end = _begin;
				//while (count--)
				//	_alloc.construct(_end++, *first);

				this->assign(first, last);
			}

			vector(const vector& copy)
				: _alloc(allocator_type()), _capacity(0), _begin(nullptr), _end(nullptr)
			{
				const_iterator begin = copy.begin();
				const_iterator end = copy.end();

				this->assign(begin, end);
			}

			~vector(void)
			{
				this->clear();
				_alloc.deallocate(_begin, _capacity);
			}

			vector&	operator=(const vector& copy)
			{
				(void) copy;
				return *this;
			}

			iterator	begin(void)
			{
				return iterator(_begin);
			}

			const_iterator	begin(void) const
			{
				return const_iterator(_begin);
			}

			iterator	end(void)
			{
				if (this->empty())
					return this->begin();
				return iterator(_end);
			}

			const_iterator	end(void) const
			{
				if (this->empty())
					return this->begin();
				return const_iterator(_end);
			}

			reverse_iterator	rbegin(void)
			{
				return reverse_iterator(this->end());
			}

			const_reverse_iterator	rbegin(void) const
			{
				return const_reverse_iterator(this->end());
			}

			reverse_iterator	rend(void)
			{
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator	rend(void) const
			{
				return const_reverse_iterator(this->begin());
			}

			reference	at(size_t index)
			{
				if (index < this->size())
					return this->operator[](index);
				throw std::out_of_range("vector::at");
			}

			const_reference	at(size_t index) const
			{
				if (index < this->size())
					return this->operator[](index);
				throw std::out_of_range("vector::at");
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
				return *_begin;
			}

			const_reference	front(void) const
			{
				return *_begin;
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
				if (count > _capacity)
				{
					_alloc.deallocate(_begin, _capacity);
					_capacity = count * 2;
					_begin = _alloc.allocate(_capacity);
					_end = _begin;
				}
				while (count--)
					_alloc.construct(_end++, value);
			}

			template<class InputIterator>
			void	assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!(ft::is_integral<InputIterator>::value) >::type*  = nullptr)
			{
				this->clear();
				if (last - first > _capacity)
				{
					_alloc.deallocate(_begin, _capacity);
					_capacity = (last - first) * 2;
					_begin = _alloc.allocate(_capacity);
					_end = _begin;
				}
				while (first != last)
					_alloc.construct(_end++, *first++);
			}

			void	push_back(const value_type& value)
			{
				if (this->size() >= _capacity)
				{
					size_type	tmp_cap = _capacity * 2;
					if (!_capacity) tmp_cap = 1;
					if (tmp_cap > this->max_size()) throw std::exception();
					// TODO: duplicate alloc
				}
				_alloc.construct(_end, value);
				_end++;
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
				ft::swap(_capacity, x._capacity);
				ft::swap(_end, x._end);
				ft::swap(_alloc, x._alloc);
			}

			void	clear(void)
			{
				size_type	size = this->size();
				for (size_type i = 0; i < size; i++)
				{
					_alloc.destroy(_begin + i);
				}
			}

			size_type	size(void) const
			{
				return _end - _begin;
			}

			bool	empty(void) const
			{
				return this->size() == 0;
			}

			size_type	max_size(void) const
			{
				return _alloc.max_size();
			}

			void	reserve(size_type new_cap)
			{
				(void) new_cap;
			}

			size_type	capacity(void) const
			{
				return _capacity;
			}

			void resize(size_type new_size, value_type value = value_type())
			{
				size_type	old_size = this->size();
				if (old_size > new_size)
					_end = _begin + new_size;
				else if (old_size < new_size)
				{
					iterator	iter;
					size_type	old_cap = _capacity;
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
						iter = ft::copy(_begin, _begin + _capacity, vec.begin());
						this->swap(vec);
					}
					ft::fill_n(iter, diff, value);
				}
			}

			allocator_type	get_allocator() const
			{
				return _alloc;
			}
	};

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
