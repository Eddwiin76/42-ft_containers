/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:27:31 by tpierre           #+#    #+#             */
/*   Updated: 2021/11/29 16:27:31 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include "utils/reverse_iterator.hpp"
#include "utils/random_access_iterator.hpp"
#include "utils/algorithm.hpp"
#include "utils/is_integral.hpp"
#include "utils/enable_if.hpp"
#include "utils/pair.hpp"

// https://www.cplusplus.com/reference/vector/vector/

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class	vector {

	public:

		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename ft::random_access_iterator<T>			iterator;
		typedef typename ft::random_access_iterator<const T>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t									difference_type;
		typedef size_t											size_type;

	private:

		allocator_type	_alloc;
		value_type		*_ptr;
		size_t			_size;
		size_t			_capacity;

	public:

		//default (1)
		explicit vector( const allocator_type &alloc = allocator_type()): _alloc(alloc), _ptr(0), _size(0), _capacity(0) {}

		//fill (2)
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(n) {
			_ptr = _alloc.allocate(n);
			for(size_t i = 0; i < n; i++)
				push_back(val);
		}

		//range (3)
		template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : _alloc(alloc), _size(0) {
			difference_type n = ft::distance(first, last);
			_ptr = _alloc.allocate(n);
			_capacity = n;
			for(;first != last; first++)
				push_back(*first);
		}

		//copy (4)
		vector(const vector& x): _alloc(allocator_type()), _ptr(0), _size(0), _capacity(0) {
			*this = x;
		}

		//destructor
		virtual ~vector( void ) {
			clear();
			_alloc.deallocate(_ptr, _capacity);
		}

		vector	&operator=( vector const &x ) {
			if (*this != x ) {
				assign(x.begin(), x.end());
				if (_capacity < x._capacity)
					reserve(x._capacity);
			}
			return *this;
		}

		//Iterators
		iterator				begin() {
			return iterator(_ptr);
		}

		const_iterator			begin() const {
			return const_iterator(_ptr);
		}

		iterator				end() {
			return iterator(_ptr + _size);
		}

		const_iterator			end() const {
			return const_iterator(_ptr + _size);
		}

		reverse_iterator		rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator		rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator	rend() const {
			return const_reverse_iterator(begin());
		}

		//Capacity
		size_type				size() const {
			return _size;
		}

		size_type				max_size() const {
			return Alloc().max_size();
		}

		void					resize(size_type n, value_type val = value_type()) {
			if (n < _size) {
				while (n < _size)
					pop_back();
			}
			else if (n > _size) {
				if (n > _capacity)
					reserve(n);
				while (n > _size)
					push_back(val);
			}
		}

		size_type				capacity() const {
			return _capacity;
		}

		bool					empty() const {
			return _size == 0;
		}

		void					reserve(size_type n) {
			if (n > this->max_size())
				throw (std::length_error("vector::reserve"));
			else if (n > _capacity) {
				value_type *tmp = _alloc.allocate(n);
				for(size_t i = 0; i < _size; i++)
					_alloc.construct(tmp + i, _ptr[i]);
				_alloc.deallocate(_ptr, _capacity);
				_capacity = n;
				_ptr = tmp;
			}
		}

		//Element access
		reference				operator[](size_type n) {
			return _ptr[n];
		}

		const_reference			operator[](size_type n) const {
			return _ptr[n];
		}

		reference				at(size_type n) {
			if (n >= _size)
				throw std::out_of_range("vector");
			return _ptr[n];
		}

		const_reference			at(size_type n) const {
			if (n >= _size)
				throw std::out_of_range("vector");
			return _ptr[n];
		}

		reference				front() {
			return *_ptr;
		}
		const_reference			front() const {
			return *_ptr;
		}
		reference				back() {
			return _ptr[_size - 1];
		}
		const_reference			back() const {
			return _ptr[_size - 1];

		}

		//Modifiers
		template <class InputIterator>
		void					assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
			clear();
			_alloc.deallocate(_ptr, _capacity);
			size_t n = ft::distance(first, last);
			_ptr = _alloc.allocate(n);
			if (n > _capacity)
				_capacity = n;
			for(;first != last; first++)
				push_back(*first);
		}

		void					assign(size_type n, const value_type& val) {
			clear();
			_alloc.deallocate(_ptr, _capacity);
			if (n > _capacity)
				_capacity = n;
			_ptr = _alloc.allocate(_capacity);
			for(size_t i = 0; i < n; i++)
				push_back(val);
		}

		void					push_back(const value_type &val) {
			if (_size == _capacity)
				reserve(!_capacity ? 1 : _capacity * 2);
			_alloc.construct(_ptr + _size, val);
			_size++;
		}

		void					pop_back() {
			_alloc.destroy(_ptr + (_size - 1));
			_size--;
		}

		iterator				insert(iterator position, const value_type& val) {

			difference_type index = position - begin();
			insert(position, 1, val);
			return &_ptr[index];
		}

		void					insert(iterator position, size_type n, const value_type& val) {
			difference_type index = position - begin();
			if (_size + n > _capacity)
				reserve(_capacity + n);
			position = &_ptr[index];
			if (position != end()) {
				for(difference_type i = _size - 1; i + 1 != index; --i) {
					_alloc.construct(_ptr + i + n, _ptr[i]);
					_alloc.destroy(_ptr + i);
				}
			}
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&(*position++), val);
			_size += n;
		}

		template <class InputIterator>
		void					insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
			size_type n = ft::distance(first, last);
			difference_type index = position - begin();
			if (_size + n > _capacity)
				reserve(_capacity + n);
			position = &_ptr[index];
			if (position != end()) {
				for(difference_type i = _size - 1; i + 1 != index; --i) {
					_alloc.construct(_ptr + i + n, _ptr[i]);
					_alloc.destroy(_ptr + i);
				}
			}
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&(*position++), *first++);
			_size += n;
		}

		iterator				erase(iterator position) {
			return erase(position, position + 1);
		}

		iterator				erase(iterator first, iterator last) {
			if (empty())
				return begin();
			if (first == end() || first == last)
				return first;
			difference_type index = first - begin();
			if (last < end()) {
				for (; first != end(); ++first, ++last) {
					_alloc.destroy(&(*first));
					if (last < end())
						_alloc.construct(&(*(first)), *last);
				}
				_size -= static_cast<size_type>(last - first);
			}
			else {
				size_type newSize = _size - static_cast<size_type>(last - first);
				while (_size != newSize)
					pop_back();
			}
			return &_ptr[index];
		}

		void					swap(vector<T, Alloc>& x) {
			allocator_type	tmp_alloc = _alloc;
			value_type		*tmp_ptr = _ptr;
			size_t			tmp_size = _size;
			size_t			tmp_capacity = _capacity;

			_alloc = x._alloc;
			_ptr = x._ptr;
			_size = x._size;
			_capacity = x._capacity;

			x._alloc = tmp_alloc;
			x._ptr = tmp_ptr;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
		}

		void					clear() {
			while (_size)
				pop_back();
		}

		//Allocator
		allocator_type			get_allocator() const {
			return _alloc;
		}

	};

	//Non_member function overloads
	template <class T, class Alloc>
		bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template <class T, class Alloc>
		bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return (!(lhs == rhs));
		}

	template <class T, class Alloc>
		bool operator< (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class T, class Alloc>
		bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			//a<=b	->	!(b < a)
			return (!(rhs < lhs));
		}

	template <class T, class Alloc>
		bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			//a>b		->  b<a
			return (rhs < lhs);
		}

	template <class T, class Alloc>
		bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			//a>=b	->	!(a<b)
			return (!(lhs < rhs));
		}

	template <class T, class Alloc>
		void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
			x.swap(y);
		}

}

//std::ostream	&operator<<( std::ostream &o, vector const &i );

#endif
