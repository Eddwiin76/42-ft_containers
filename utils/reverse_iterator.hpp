/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:23:16 by tpierre           #+#    #+#             */
/*   Updated: 2022/03/04 13:12:52 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

// https://www.cplusplus.com/reference/iterator/reverse_iterator/

namespace ft {

	template <class Iterator>
	class reverse_iterator {

	public:

		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

	private:

		iterator_type _it;

	public:

		reverse_iterator() : _it() {}
		explicit reverse_iterator (iterator_type it) : _it(it) {}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) :_it(rev_it.base()) {}
		virtual ~reverse_iterator(void){};

		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other ) {
			_it = other.base();
			return *this;
		}

		iterator_type base() const {
			iterator_type tmp = _it;
			return tmp;
		}

		reference operator*() const {
			iterator_type tmp = _it;
			return *--tmp;
		}

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(_it - n);
		}

		reverse_iterator& operator++() {
			_it--;
			return *this;
		}

		reverse_iterator  operator++(int) {
			reverse_iterator tmp = *this;
			_it--;
			return tmp;
		}

		reverse_iterator& operator+=(difference_type n) {
			_it -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(_it + n);
		}

		reverse_iterator& operator--() {
			_it++;
			return *this;
		}

		reverse_iterator  operator--(int) {
			reverse_iterator tmp = *this;
			_it++;
			return tmp;
		}

		reverse_iterator& operator-=(difference_type n) {
			_it += n;
			return *this;
		}

		pointer operator->() const {
			return &(operator*());
		}

		reference operator[](difference_type n) const {
			return *(_it - n - 1);
		}

	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return rev_it + n;
	}

	template <class Iterator1, class Iterator2>
	reverse_iterator<Iterator1> operator+( typename reverse_iterator<Iterator1>::difference_type n, const reverse_iterator<Iterator2>& rev_it) {
		return rev_it + n;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (rhs.base() - lhs.base());
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return (rhs.base() - lhs.base());
	}

}

#endif
