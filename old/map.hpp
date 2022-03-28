/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:45:22 by acoezard          #+#    #+#             */
/*   Updated: 2022/02/15 11:25:00 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <functional>
#include "pair.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key								key_type;
			typedef T								mapped_type;
			typedef ft::pair<const Key, T>			value_type;
			typedef std::size_t						size_type;
			typedef std::ptrdiff_t					difference_type;
			typedef Compare							key_compare;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef Allocator						allocator_type;
			typedef allocator_type::pointer			pointer;
			typedef allocator_type::const_pointer	const_pointer;
			// TODO: #17 Ajouter les iterator (const) et reverse_iterator (const) du RBTree

			class value_compare
			{
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

				protected:
					Compare _comp;
					value_compare(Compare c) : _comp(c) {}

				public:
					bool operator()( const value_type& lhs, const value_type& rhs ) const
					{ return (_comp(lhs.first, rhs.first)); }
			};

		protected:
			allocator_type	_alloc;
			key_compare		_keyComp;
			value_compare	_valueComp;

		public:
			explicit map(const Compare& comp, const Allocator& alloc = Allocator())
				: _alloc(alloc), _keyComp(comp)
			{ _valueComp = value_compare();	}

			template<class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
				: _alloc(alloc), _keyComp(comp)
			{
				_valueComp = value_compare();
				// TODO: #16 Utiliser les iterator first et last
			}

			map(const map& copy)
			{ *this = copy; }

			~map(void)
			{}

			map& operator=(const map& copy)
			{
				_alloc = copy._alloc;
				_keyComp = copy._keyComp;
				_valueComp = copy._valueComp;
				return (*this);
			}

			mapped_type& at(const key_type& key)
			{}

			const mapped_type& at(const key_type& key) const
			{}

			mapped_type& operator[](const key_type& key)
			{}

			iterator begin(void)
			{}

			const_iterator begin(void) const
			{}

			iterator end(void)
			{}

			const_iterator end(void) const
			{}

			reverse_iterator rbegin(void)
			{}

			const_reverse_iterator rbegin(void) const
			{}

			reverse_iterator rend(void)
			{}

			const_reverse_iterator rend(void) const
			{}

			bool empty(void) const
			{}

			size_type size(void) const
			{}

			size_type max_size(void) const
			{}

			void clear(void)
			{}

			ft::pair<iterator, bool> insert(const value_type& value)
			{}

			iterator insert(iterator hint, const value_type& value)
			{}

			void erase(iterator pos)
			{}

			void erase(iterator first, iterator last)
			{}

			void swap(map& other)
			{}

			size_type count(const key_type& key) const
			{}

			iterator find(const key_type& key)
			{}

			const_iterator find(const key_type& key) const
			{}

			ft::pair<iterator, iterator> equal_range(const key_type& key)
			{}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
			{}

			iterator lower_bound(const key_type& key)
			{}

			const_iterator lower_bound(const key_type& key) const
			{}

			iterator upper_bound(const key_type& key)
			{}

			const_iterator upper_bound(const key_type& key) const
			{}

			key_compare key_comp(void) const
			{
				return (_keyComp);
			}

			value_compare value_comp() const
			{
				return (_valueComp);
				}

			allocator_type get_allocator(void) const
			{
				return (_alloc);
			}
	};
}

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs)
{}

#endif
