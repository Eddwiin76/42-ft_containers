/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:57:10 by tpierre           #+#    #+#             */
/*   Updated: 2022/03/04 11:10:47 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

// https://cplusplus.com/reference/utility/pair/
// https://www.cplusplus.com/reference/utility/make_pair/

namespace ft {

	template <class Input, class Output>
	struct selectFirst {
		const Output &operator()(const Input &x) const {
			return x.first;
		}
	};

	template <class Input, class Output>
	struct selectKey {
		const Output &operator()(const Input &x) const {
			return (x);
		}
	};

	template <class T1, class T2>
	struct pair {

		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		//default (1)
		pair(): first((first_type())), second(second_type()) {}

		//copy (2)
		template<class U, class V>
		pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}

		//initialization (3)
		pair (const first_type& a, const second_type& b): first(a), second(b) {}

		~pair() {};

		pair& operator= (const pair& pr) {

			if (this != &pr) {
				first = pr.first;
				second = pr.second;
			}
			return *this;
		}

	};

	template <class T1, class T2>
		ft::pair<T1, T2> make_pair(T1 x, T2 y) {
			return (ft::pair<T1, T2>(x, y));
		}

	template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return lhs.first==rhs.first && lhs.second==rhs.second;
		}

	template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return !(lhs==rhs);
		}

	template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
		}

	template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return !(rhs<lhs);
		}

	template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return rhs<lhs;
		}

	template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return !(lhs<rhs);
		}

}

#endif
