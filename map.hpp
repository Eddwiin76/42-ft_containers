/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:27:25 by tpierre           #+#    #+#             */
/*   Updated: 2021/11/29 16:27:25 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "utils/pair.hpp"
#include "utils/bidirectional_iterator.hpp"
#include "utils/reverse_iterator.hpp"
#include "utils/RBT.hpp"
#include "utils/algorithm.hpp"

// https://cplusplus.com/reference/map/map/

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {

	public:

		typedef Key																					key_type;
		typedef T																					mapped_type;
		typedef pair<const key_type, mapped_type>													value_type;
		typedef Compare																				key_compare;
		class																						value_compare;
		typedef Alloc																				allocator_type;
		typedef typename allocator_type::reference													reference;
		typedef typename allocator_type::const_reference											const_reference;
		typedef typename allocator_type::pointer													pointer;
		typedef typename allocator_type::const_pointer												const_pointer;
		typedef Node<value_type>																	node_type;
		typedef node_type*																			node_ptr;
		typedef typename ft::bidirectional_iterator<value_type, node_type>							iterator;
		typedef typename ft::bidirectional_iterator<const value_type, const node_type>				const_iterator;
		typedef typename ft::reverse_iterator<iterator>												reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>										const_reverse_iterator;
		typedef std::ptrdiff_t																		difference_type;
		typedef size_t																				size_type;
		typedef ft::RBT<key_type, value_type,ft::selectFirst<value_type, key_type>, key_compare>	tree_type;

	private:

		allocator_type				_alloc;
		key_compare					_comp;
		tree_type					_tree;

	public:

		// empty (1)
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(comp), _tree() {}

		// range (2)
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(comp), _tree() {
			insert(first, last);
		}

		// copy (3)
		map (const map& x) {
			*this = x;
		}

		// destructor
		virtual ~map() {}

		map& operator= (const map& x) {
			if (*this != x) {
				clear();
				_alloc = x._alloc;
				_comp = x._comp;
				insert(x.begin(), x.end());
			}
			return *this;
		}

		// Iterators:
		iterator begin() {
			return iterator(_tree.min(),_tree.getRoot(), _tree.getNill());
		}

		const_iterator begin() const {
			return const_iterator(_tree.min(), _tree.getRoot(), _tree.getNill());
		}

		iterator end() {
			return iterator(_tree.getNill(), _tree.getRoot(), _tree.getNill());
		}

		const_iterator end() const {
			return const_iterator(_tree.getNill(), _tree.getRoot(), _tree.getNill());
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		// Capacity:
		bool empty() const {
			return _tree.getSize() == 0;
		}

		size_type size() const {
			return _tree.getSize();
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		// Element access:
		mapped_type& operator[] (const key_type& k) {
			node_ptr tmp = _tree.search(k);

			if (tmp != _tree.getNill())
				return (tmp->data.second);
			_tree.insert(value_type(k, mapped_type()));
			tmp = _tree.search(k);
			return (tmp->data.second);
		}

		// Modifiers:
		pair<iterator,bool> insert (const value_type& val) {
			bool succes = _tree.insert(val);
			iterator it = find(val.first);
			return ft::pair<iterator,bool>(it, succes);
		}

		iterator insert (iterator position, const value_type& val) {
			(void)position;
			return insert(val).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			while (first != last) {
				_tree.insert(*(first++));
			}
		}

		void erase (iterator position) {
			erase(position->first);
		}

		size_type erase (const key_type& k) {
			if (find(k) == end())
					return (0);
			if (_tree.deleteNode(k))
				return 1;
			return 0;
		}

		void erase (iterator first, iterator last) {
			while (first != last) {
				erase(first++);
			}
		}

		void swap (map& x) {
			_tree.swap(x._tree);
		}

		void clear() {
			erase(begin(), end());
		}

		// // Observers:
		key_compare key_comp() const {
			return _comp;
		}

		value_compare value_comp() const {
			return value_compare(_comp);
		}

		// // Operations:
		iterator find (const key_type& k) {
			node_ptr tmp = _tree.search(k);

			if (tmp != _tree.getNill())
				return (iterator(tmp, _tree.getRoot(), _tree.getNill()));
			return end();
		}

		const_iterator find (const key_type& k) const {
			node_ptr tmp = _tree.search(k);

			if (tmp != _tree.getNill())
				return (const_iterator(tmp, _tree.getRoot(), _tree.getNill()));
			return end();
		}

		size_type count (const key_type& k) const {
			node_ptr tmp = _tree.search(k);

			if (tmp == _tree.getNill())
				return 0;
			return 1;
		}

		iterator lower_bound (const key_type& k) {
			iterator it = begin();

			for (; it != end(); it++)
				if (_comp(it->first, k) == false)
					break;
			return it;
		}

		const_iterator lower_bound (const key_type& k) const {
			const_iterator it = begin();

			for (; it != end(); it++)
				if (_comp(it->first, k) == false)
					break;
			return it;
		}

		iterator upper_bound (const key_type& k) {
			iterator it = begin();

			for (; it != end(); ++it)
				if (_comp(k, it->first) == true)
					break;

			return it;
		}

		const_iterator upper_bound (const key_type& k) const {
			const_iterator it = begin();

			for (; it != end(); ++it)
				if (_comp(k, it->first) == true)
					break;

			return it;
		}

		ft::pair<iterator,iterator> equal_range (const key_type& k) {
			return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}

		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

		// Allocator:
		allocator_type get_allocator() const {
			return _alloc;
		}

	};

	//Non_member function overloads
	template <class Key, class T, class Compare, class Alloc>
		bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
		bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return (!(rhs == lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
		bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
		bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
		bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare {
		friend class map;

		protected:

			Compare comp;
			value_compare (Compare c) : comp(c) {}

		public:

			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
	};

}

//std::ostream	&operator<<( std::ostream &o, map const &i );

#endif
