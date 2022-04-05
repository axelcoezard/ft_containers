/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:00:55 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/05 16:40:11 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"
#include "iterator.hpp"
#include <cstring>

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
			size_type		_size;
			pointer			_begin;

		private:
			void _alloc_copy(size_type tmp_cap)
			{
				pointer 	buffer = _alloc.allocate(tmp_cap);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(buffer + i, *(_begin + i));
					_alloc.destroy(_begin + i);
				}
				_alloc.deallocate(_begin, _capacity);
				_begin = buffer;
				_capacity = tmp_cap;
			}

			void _alloc_re(void)
			{
				size_type	tmp_cap = _capacity * 2;
				if (!_capacity) tmp_cap = 1;
				if (tmp_cap > max_size()) throw std::exception();
				_alloc_copy(tmp_cap);
			}

		public:
			explicit vector(const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _capacity(0), _size(0), _begin(NULL)
			{}

			explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _capacity(0), _size(0), _begin(NULL)
			{
				size_type	i = 0;
				while (i < count)
					push_back(value), i++;
			}

			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				: _alloc(alloc), _capacity(0), _size(0), _begin(NULL)
			{
				assign(first, last);
			}

			vector(const vector& copy)
				: _alloc(allocator_type()), _capacity(0), _size(0), _begin(NULL)
			{
				const_iterator begin = copy.begin();
				const_iterator end = copy.end();

				assign(begin, end);
			}

			~vector(void)
			{
				clear();
				_alloc.deallocate(_begin, _capacity);
			}

			vector& operator=(const vector& copy)
			{
				vector tmp (copy);
				swap(tmp);
				return *this;
			}

			iterator begin(void)
			{
				return iterator(_begin);
			}

			const_iterator begin(void) const
			{
				return const_iterator(_begin);
			}

			iterator end(void)
			{
				if (empty())
					return begin();
				return iterator(_begin + _size);
			}

			const_iterator end(void) const
			{
				if (empty())
					return begin();
				return const_iterator(_begin + _size);
			}

			reverse_iterator rbegin(void)
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin(void) const
			{
				return const_reverse_iterator(end());
			}

			reverse_iterator rend(void)
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend(void) const
			{
				return const_reverse_iterator(begin());
			}

			reference at(size_t index)
			{
				if (index < _size)
					return operator[](index);
				throw std::out_of_range("vector::at");
			}

			const_reference at(size_t index) const
			{
				if (index < _size)
					return operator[](index);
				throw std::out_of_range("vector::at");
			}

			reference operator[](size_t index)
			{
				return *(_begin + index);
			}

			const_reference operator[](size_t index) const
			{
				return *(_begin + index);
			}

			reference front(void)
			{
				return *_begin;
			}

			const_reference front(void) const
			{
				return *_begin;
			}

			reference back(void)
			{
				return *(_begin + _size - 1);
			}

			const_reference back(void) const
			{
				return *(_begin + _size - 1);
			}

			value_type* data(void)
			{
				return _begin;
			}

			const value_type* data(void) const
			{
				return _begin;
			}

			void assign(size_type count, const value_type& value)
			{
				clear();
				if (count > _capacity)
				{
					_alloc.deallocate(_begin, _capacity);
					_capacity = count * 2;
					_begin = _alloc.allocate(_capacity);
				}
				pointer _end = _begin;
				while (count--)
					_alloc.construct(_end++, value), _size++;
			}

			template<class InputIterator>
			void assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!(ft::is_integral<InputIterator>::value) >::type* = NULL)
			{
				size_type dist = ft::distance(first, last);
				clear();
				if (dist > _capacity)
				{
					_alloc.deallocate(_begin, _capacity);
					_capacity = dist * 2;
					_begin = _alloc.allocate(_capacity);
				}
				pointer _end = _begin;
				while (first != last)
					_alloc.construct(_end++, *first++), _size++;
			}

			void push_back(const value_type& value)
			{
				if (_size >= _capacity)
					_alloc_re();
				_alloc.construct(_begin + _size, value);
				_size++;
			}

			void pop_back(void)
			{
				_alloc.destroy(_begin + _size - 1);
				_size--;
			}

			iterator insert(iterator pos, const T& value)
			{
				difference_type int_pos = pos - begin();
				if (capacity() == size())
					_alloc_re();
				vector temp(iterator(begin() + int_pos), end());
				for (size_t i = 0; i < temp.size(); i++)
					pop_back();
				push_back(value);
				iterator it = temp.begin();
				for (size_t i = 0; i < temp.size(); i++, it++)
					push_back(*it);
				return begin() + int_pos;
			}

			void insert(iterator pos, size_type count, const T& value)
			{
				difference_type int_pos = pos - this->begin();
				while (capacity() - size() < count)
					_alloc_re();
				vector temp(begin() + int_pos, end());
				for (size_t i = 0; i < temp.size(); i++)
					pop_back();
				while (count > 0)
					push_back(value), count--;
				for (iterator it = temp.begin(); it != temp.end(); it++)
					push_back(*it);
			}

			template<class InputIterator>
			void insert(iterator pos, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				difference_type int_pos = pos - this->begin();
				while (capacity() - size() < 0)
					_alloc_re();
				vector temp(begin() + int_pos, end());
				for (size_t i = 0; i < temp.size(); i++)
					pop_back();
				while (first != last)
					push_back(*first), first++;
				for (iterator it = temp.begin(); it != temp.end(); it++)
					push_back(*it);
			};

			iterator erase (iterator position)
			{
				for (size_type i = 0; i < _size ; i++)
				{
					iterator it(_begin + i);
					if (position != it)
						continue;
					_alloc.destroy(_begin + i);
					for (size_type j = i + 1; j < _size; j++, i++)
						_alloc.construct(&_begin[i], _begin[j]);
					_size -= 1;
					return it;
				}
				return position;
			}

			iterator erase (iterator first, iterator last)
			{
				size_type dist = ft::distance(first, last);
				size_type k = 0;
				for (size_type i = 0; i < _size ; i++)
				{
					if (first != _begin + i) continue;
					size_type save = i;
					size_type j = i;
					for (; i < _size; i++ )
					{
						for (; k < dist; k++, i++)
							_alloc.destroy(_begin + i);
						if (i != _size)
						{
							_alloc.construct(&_begin[j++], _begin[i]);
							_alloc.destroy(_begin + i);
						}
					}
					_size -= dist;
					return iterator(_begin + save);
				}
				return first;
			};

			void swap(vector & x)
			{
				if (x == *this)
					return ;

				ft::swap(_begin, x._begin);
				ft::swap(_capacity, x._capacity);
				ft::swap(_size, x._size);
				ft::swap(_alloc, x._alloc);
			}

			void clear(void)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_size = 0;
				_capacity = 0;
			}

			size_type size(void) const
			{
				return _size;
			}

			bool empty(void) const
			{
				return _size == 0;
			}

			size_type max_size(void) const
			{
				return _alloc.max_size();
			}

			void reserve(size_type new_cap)
			{
				if (new_cap <= _capacity) return;
				if (new_cap <= max_size()) return;
				_alloc_copy(new_cap);
			}

			size_type capacity(void) const
			{
				return _capacity;
			}

			void resize(size_type new_size, value_type value = value_type())
			{
				while (new_size < _size)
					pop_back();
				while (new_size > _size)
					push_back(value);
			}

			allocator_type get_allocator() const
			{
				return _alloc;
			}
	};

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return rhs < lhs;
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
