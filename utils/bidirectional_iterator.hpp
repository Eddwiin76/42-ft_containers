/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:50:24 by tpierre           #+#    #+#             */
/*   Updated: 2022/03/04 11:06:59 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "iterator.hpp"
# include "RBT.hpp"

// https://www.cplusplus.com/reference/iterator/BidirectionalIterator/

namespace ft {

	template <typename T, class N>
	class	bidirectional_iterator : public iterator<ft::bidirectional_iterator_tag, T> {

		public:

		typedef T										value_type;
		typedef T										&reference;
		typedef T										*pointer;
		typedef const T									&const_reference;
		typedef const T									*const_pointer;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
		typedef typename ft::bidirectional_iterator_tag	iterator_category;

		typedef N										node_type;
		typedef N*										node_ptr;

		private:
			node_ptr	_ptr;
			node_ptr	_root;
			node_ptr	_nill;

		public:

			bidirectional_iterator(): _ptr(0), _root(0), _nill(0) {}
			bidirectional_iterator(node_ptr ptr, node_ptr root, node_ptr nill):_ptr(ptr), _root(root), _nill(nill) {}
			bidirectional_iterator(bidirectional_iterator const &src):_ptr(src._ptr), _root(src._root), _nill(src._nill) {}
			virtual ~bidirectional_iterator() {}

			operator bidirectional_iterator<const value_type, const node_type>()const {
				return bidirectional_iterator<const value_type, const node_type>(_ptr, _root, _nill);
			}

			bidirectional_iterator &operator=(bidirectional_iterator const &src){
				if (this != &src){
					_ptr = src._ptr;
					_root = src._root;
					_nill = src._nill;
				}
				return *this;
			}

			reference operator*() {
				return _ptr->data;
			}

			const_reference operator*() const {
				return _ptr->data;
			}

			pointer operator->() {
				return &(_ptr->data);
			}

			const_pointer operator->() const {
				return &(_ptr->data);
			}

			bidirectional_iterator &operator++(void) {
				if (_ptr != _nill)
					_ptr = successor(_ptr);
				return *this;
			}

			bidirectional_iterator operator++(int) {
				bidirectional_iterator old(*this);
				this->operator++();
				return old;
			}

			bidirectional_iterator &operator--(void) {
				if(_ptr == _nill)
					_ptr = max(_root);
				else
					_ptr = predecessor(_ptr);
				return *this;
			}

			bidirectional_iterator operator--(int) {
				bidirectional_iterator  old(*this);
				this->operator--();
				return old;
			}

			bool operator==(const bidirectional_iterator &lhs) {
				return _ptr == lhs._ptr;
			}
			bool operator!=(const bidirectional_iterator &lhs) {
				return _ptr != lhs._ptr;
			}

			template <class Iter1, class Iter2>
			friend bool operator==(ft::bidirectional_iterator<Iter1, Node<Iter1> > const &lhs, ft::bidirectional_iterator<Iter2, Node<Iter2> > const &rhs);

			template <class Iter1, class Iter2>
			friend bool operator!=(ft::bidirectional_iterator<Iter1, Node<Iter1> > const &lhs, ft::bidirectional_iterator<Iter2, Node<Iter2> > const &rhs);

		private:

			node_ptr successor(node_ptr node) {
				if(node->right != _nill)
					return min(node->right);
				node_ptr y = node->parent;
				while(y != NULL && node == y->right) {
					node = y;
					y = y->parent;
				}
				if (y == NULL)
					return _nill;
				return y;
			}

			node_ptr predecessor(node_ptr node) {
				if(node->left != _nill)
					return (max(node->left));
				node_ptr    y = node->parent;
				while(y != NULL && node == y->left) {
					node = y;
					y = y->parent;
				}
				return y;
			}

			node_ptr min(node_ptr node) {
				while(node->left != _nill)
					node = node->left;
				return (node);
			}

			node_ptr max(node_ptr node) {
				while(node->right != _nill)
					node = node->right;
				return node;
			}

	};

	template <class Iter1, class Iter2>
	bool operator==(ft::bidirectional_iterator<Iter1, Node<Iter1> > const &lhs, ft::bidirectional_iterator<Iter2, Node<Iter2> > const &rhs) {
		return (lhs._ptr == rhs._ptr);
	}

	template <class Iter1, class Iter2>
	bool operator!=(ft::bidirectional_iterator<Iter1, Node<Iter1> > const &lhs, ft::bidirectional_iterator<Iter2, Node<Iter2> > const &rhs) {
		return (lhs._ptr != rhs._ptr);
	}

}

#endif
