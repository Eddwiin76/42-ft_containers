/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:27:09 by tpierre           #+#    #+#             */
/*   Updated: 2022/03/04 11:05:45 by tpierre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

// https://www.cplusplus.com/reference/iterator/iterator/
// https://www.cplusplus.com/reference/iterator/iterator_traits/

namespace ft {

	struct input_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator {

		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class Iterator>
	struct iterator_traits {

			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;

	};

	template <class T>
	struct iterator_traits<T*> {

			typedef ptrdiff_t							difference_type;
			typedef T									value_type;
			typedef T									*pointer;
			typedef T									&reference;
			typedef ft::random_access_iterator_tag		iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*> {

			typedef ptrdiff_t							difference_type;
			typedef T									value_type;
			typedef T									*pointer;
			typedef T									&reference;
			typedef ft::random_access_iterator_tag		iterator_category;
	};
}

#endif
