/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:09:35 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/05 16:33:49 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <functional>

#include "iterator.hpp"
#include "rbtree_iterator.hpp"
#include "rbtree.hpp"
#include "pair.hpp"
#include "utils.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef size_t										size_type;
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<key_type, mapped_type>				value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			class value_compare
			{
				protected:
					Compare										_comp;
				public:
					typedef bool								result_type;
					typedef value_type							first_argument_type;
					typedef value_type							second_argument_type;

					bool operator()(const value_type &x, const value_type &y) const
					{
						return _comp(x.first, y.first);
					}
			};

			typedef ft::rbtree<value_type, value_compare>		tree_type;
			typedef typename tree_type::iterator				iterator;
			typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::reverse_iterator		reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		private:
			tree_type											_tree;
			allocator_type										_alloc;
			key_compare											_keyComp;
			value_compare										_valComp;

		public:
			explicit map(const key_compare &comp = key_compare(),
						const allocator_type &alloc = allocator_type())
			{
				_alloc = alloc;
				_keyComp = comp;
				_valComp = value_compare();
			}

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type())
			{
				_alloc = alloc;
				_keyComp = comp;
				_valComp = value_compare();
				insert(first, last);
			}

			map(const map &x)
			{
				*this = x;
			}

			map &operator=(const map &x)
			{
				_alloc = x._alloc;
				_keyComp = x._keyComp;
				_valComp = x._valComp;
				_tree = x._tree;
				clear();
				insert(x.begin(), x.end());
				return *this;
			}

			iterator begin(void)
			{
				return iterator(_tree.begin());
			}

			const_iterator begin(void) const
			{
				return const_iterator(_tree.begin());
			}

			iterator end(void)
			{
				return iterator(_tree.end());
			}

			const_iterator end(void) const
			{
				return const_iterator(_tree.end());
			}

			reverse_iterator rbegin(void)
			{
				return reverse_iterator(_tree.rbegin());
			}

			const_reverse_iterator rbegin(void) const
			{
				return const_reverse_iterator(_tree.rbegin());
			}

			reverse_iterator rend(void)
			{
				return reverse_iterator(_tree.rend());
			}

			const_reverse_iterator rend(void) const
			{
				return const_reverse_iterator(_tree.rend());
			}

			bool empty(void) const
			{
				return _tree.size() == 0;
			}

			size_type size(void) const
			{
				return _tree.size();
			}

			size_type max_size(void) const
			{
				return _tree.max_size();
			}

			mapped_type &operator[](const key_type &k)
			{
				return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
			}

			pair<iterator, bool> insert(const value_type &val)
			{
				return _tree.insert(val);
			}

			iterator insert(iterator position, const value_type &val)
			{
				return _tree.insert(position, val);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					_tree.insert(*first++);
			}

			void erase(iterator position)
			{
				_tree.erase(position);
			}

			size_type erase(const key_type &k)
			{
				return _tree.erase(ft::make_pair(k, mapped_type()));
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					_tree.erase(first++);
			}

			void swap(map &x)
			{
				ft::swap(_alloc, x._alloc);
				ft::swap(_keyComp, x._keyComp);
				ft::swap(_valComp, x._valComp);
				_tree.swap(x._tree);
			}

			void clear(void)
			{
				_tree.clear();
			}

			key_compare key_comp(void) const
			{
				return _keyComp;
			}

			value_compare value_comp(void) const
			{
				return _valComp;
			}

			iterator find(const key_type &k)
			{
				return _tree.find(ft::make_pair(k, mapped_type()));
			}

			const_iterator find(const key_type &k) const
			{
				return _tree.find(ft::make_pair(k, mapped_type()));
			}

			size_type count(const key_type &k) const
			{
				return _tree.isIn(ft::make_pair(k, mapped_type()));
			}

			iterator lower_bound(const key_type &k)
			{
				return _tree.lower_bound(ft::make_pair(k, mapped_type()));
			}

			const_iterator lower_bound(const key_type &k) const
			{
				return _tree.lower_bound(ft::make_pair(k, mapped_type()));
			}

			iterator upper_bound(const key_type &k)
			{
				return _tree.upper_bound(ft::make_pair(k, mapped_type()));
			}

			const_iterator upper_bound(const key_type &k) const
			{
				return _tree.upper_bound(ft::make_pair(k, mapped_type()));
			}

			ft::pair<iterator, iterator> equal_range(const key_type &k)
			{
				iterator low = lower_bound(k);
				iterator up = upper_bound(k);
				return ft::make_pair(low, up);
			}
			ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			{
				const_iterator low = lower_bound(k);
				const_iterator up = upper_bound(k);
				return ft::make_pair(low, up);
			}

			allocator_type get_allocator(void) const
			{
				return _alloc;
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs > lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs)
	{
		rhs.swap(lhs);
	}
};

#endif
