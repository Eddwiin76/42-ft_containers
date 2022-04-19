/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:40:55 by tpierre           #+#    #+#             */
/*   Updated: 2022/03/04 11:07:22 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

// https://www.cplusplus.com/reference/iterator/RandomAccessIterator/

namespace ft {

	template<typename T>
	class random_access_iterator : public iterator<ft::random_access_iterator_tag, T> {

	public:

		typedef T											value_type;
		typedef T&											reference;
		typedef T*											pointer;
		typedef const T&									const_reference;
		typedef const T*									const_pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;
		typedef typename ft::random_access_iterator_tag		iterator_category;

	private:

		T *_ptr;

	public:

		random_access_iterator(): _ptr(0) {}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator(random_access_iterator<T> const &src): _ptr(src._ptr) {}
		virtual ~random_access_iterator() {}

		operator random_access_iterator<const T>() const {
			return random_access_iterator<const T>(_ptr);
		}

		random_access_iterator &operator=(random_access_iterator<T> const &src) {
			if (this != &src)
				_ptr = src._ptr;
			return *this;
		}

		pointer base() const {
			pointer tmp = _ptr;
			return tmp;
		}

		bool operator==(const random_access_iterator &src) const {
			return _ptr == src._ptr;
		}
		bool operator!=(const random_access_iterator &src) const {
			return _ptr != src._ptr;
		}
		bool operator>(const random_access_iterator &src) const {
			return _ptr > src._ptr;
		}
		bool operator>=(const random_access_iterator &src) const {
			return _ptr >= src._ptr;
		}
		bool operator<(const random_access_iterator &src) const {
			return _ptr < src._ptr;
		}
		bool operator<=(const random_access_iterator &src) const {
			return _ptr <= src._ptr;
		}

		reference operator*() const {
			return *_ptr;
		}

		random_access_iterator operator+(difference_type n) const {
			return random_access_iterator(_ptr + n);
		}

		random_access_iterator& operator++() {
			_ptr++;
			return *this;
		}

		random_access_iterator  operator++(int) {
			random_access_iterator tmp = *this;
			_ptr++;
			return tmp;
		}

		random_access_iterator& operator+=(difference_type n) {
			_ptr += n;
			return *this;
		}

		random_access_iterator operator-(difference_type n) const {
			return random_access_iterator(_ptr - n);
		}

		random_access_iterator& operator--() {
			_ptr--;
			return *this;
		}

		random_access_iterator  operator--(int) {
			random_access_iterator tmp = *this;
			_ptr--;
			return tmp;
		}

		random_access_iterator& operator-=(difference_type n) {
			_ptr -= n;
			return *this;
		}

		pointer operator->() const {
			return &(operator*());
		}

		reference operator[](difference_type n) const {
			return *(_ptr + n);
		}

	};

	template <class Iterator1, class Iterator2>
	bool operator==(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator< (const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const random_access_iterator<Iterator1>& lhs,const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator> (const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> const & rhs) {
		return rhs + n;
	}

	template <typename T, typename U>
	ptrdiff_t	operator-(const random_access_iterator<T> &lhs, const random_access_iterator<U> &rhs) {
		return (lhs.base() - rhs.base());
	}

}

#endif
