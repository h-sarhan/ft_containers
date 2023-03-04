/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:34:36 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 06:29:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include "integral_constant.hpp"

namespace ft
{
template <class T> struct is_integral : public false_type
{
};

template <> struct is_integral<int> : public true_type
{
};

template <> struct is_integral<bool> : public true_type
{
};

template <> struct is_integral<char> : public true_type
{
};

template <> struct is_integral<signed char> : public true_type
{
};

template <> struct is_integral<short int> : public true_type
{
};

template <> struct is_integral<long int> : public true_type
{
};

template <> struct is_integral<long long int> : public true_type
{
};

template <> struct is_integral<unsigned char> : public true_type
{
};

template <> struct is_integral<unsigned short int> : public true_type
{
};

template <> struct is_integral<unsigned int> : public true_type
{
};

template <> struct is_integral<unsigned long int> : public true_type
{
};

template <> struct is_integral<unsigned long long int> : public true_type
{
};

};   // namespace ft
#endif