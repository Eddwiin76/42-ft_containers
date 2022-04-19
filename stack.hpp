/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:27:22 by tpierre           #+#    #+#             */
/*   Updated: 2021/11/29 16:27:22 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

// https://cplusplus.com/reference/stack/stack/

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class	stack {

	public:

		typedef T											value_type;
		typedef Container									container_type;
		typedef size_t										size_type;

		explicit stack (const container_type& ctnr = container_type()): c(ctnr) {}

		virtual ~stack() {}

		bool empty() const {
			return c.empty();
		}

		size_type size() const {
			return c.size();
		}

		value_type& top() {
			return c.back();
		}

		const value_type& top() const {
			return c.back();
		}

		void push (const value_type& val) {
			c.push_back(val);
		}

		void pop() {
			c.pop_back();
		}

		template <class U, class Ctr>
		friend bool operator==(const ft::stack<U, Ctr> &lhs,const ft::stack<U, Ctr> &rhs);

		template <class U, class Ctr>
		friend bool operator!=(const ft::stack<U, Ctr> &lhs,const ft::stack<U, Ctr> &rhs);

		template <class U, class Ctr>
		friend bool operator<(const ft::stack<U, Ctr> &lhs,const ft::stack<U, Ctr> &rhs);

		template <class U, class Ctr>
		friend bool operator<=(const ft::stack<U, Ctr> &lhs,const ft::stack<U, Ctr> &rhs);

		template <class U, class Ctr>
		friend bool operator>(const ft::stack<U, Ctr> &lhs,const ft::stack<U, Ctr> &rhs);

		template <class U, class Ctr>
		friend bool operator>=(const ft::stack<U, Ctr> &lhs,const ft::stack<U, Ctr> &rhs);

	protected:

		container_type	c;

	};

	template <class T, class Container>
		bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs.c == rhs.c);
		}

	template <class T, class Container>
		bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (!(lhs.c == rhs.c));
		}

	template <class T, class Container>
		bool operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs.c < rhs.c);
		}

	template <class T, class Container>
		bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (!(rhs.c < lhs.c));
		}

	template <class T, class Container>
		bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (rhs.c < lhs.c);
		}

	template <class T, class Container>
		bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (!(lhs.c < rhs.c));
		}

}

//std::ostream	&operator<<( std::ostream &o, stack const &i );

#endif
