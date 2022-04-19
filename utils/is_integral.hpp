/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:14:10 by tpierre           #+#    #+#             */
/*   Updated: 2022/03/04 11:08:57 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

// https://www.cplusplus.com/reference/type_traits/is_integral/
// https://www.cplusplus.com/reference/type_traits/integral_constant/

namespace ft {

	template <class T, T v>
	struct integral_constant {

		static const T					value = v;
		typedef T						value_type;
		typedef integral_constant<T,v>	type;
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template <class T>
	struct is_integral : public false_type {};

	template <>
	struct is_integral<bool> : public true_type {};
	template <>
	struct is_integral<char> : public true_type {};
	template <>
	struct is_integral<wchar_t> : public true_type {};
	template <>
	struct is_integral<signed char> : public true_type {};
	template <>
	struct is_integral<short int> : public true_type {};
	template <>
	struct is_integral<int> : public true_type {};
	template <>
	struct is_integral<long int> : public true_type {};
	template <>
	struct is_integral<long long int> : public true_type {};
	template <>
	struct is_integral<unsigned char> : public true_type {};
	template <>
	struct is_integral<unsigned short int> : public true_type {};
	template <>
	struct is_integral<unsigned int> : public true_type {};
	template <>
	struct is_integral<unsigned long int> : public true_type {};
	template <>
	struct is_integral<unsigned long long int> : public true_type {};

	template <>
	struct is_integral<const bool> : public true_type {};
	template <>
	struct is_integral<const char> : public true_type {};
	template <>
	struct is_integral<const wchar_t> : public true_type {};
	template <>
	struct is_integral<const signed char> : public true_type {};
	template <>
	struct is_integral<const short int> : public true_type {};
	template <>
	struct is_integral<const int> : public true_type {};
	template <>
	struct is_integral<const long int> : public true_type {};
	template <>
	struct is_integral<const long long int> : public true_type {};
	template <>
	struct is_integral<const unsigned char> : public true_type {};
	template <>
	struct is_integral<const unsigned short int> : public true_type {};
	template <>
	struct is_integral<const unsigned int> : public true_type {};
	template <>
	struct is_integral<const unsigned long int> : public true_type {};
	template <>
	struct is_integral<const unsigned long long int> : public true_type {};

}

#endif
