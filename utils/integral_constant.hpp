/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integral_constant.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:48:38 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 06:29:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTEGRAL_CONSTANT_HPP
#define INTEGRAL_CONSTANT_HPP

namespace ft
{
template <class T, T v> struct integral_constant
{
    typedef T value_type;
    typedef integral_constant<T, v> type;
    operator T()
    {
        return v;
    }
    static const T value = v;
};
typedef integral_constant<bool, false> false_type;
typedef integral_constant<bool, true> true_type;
};   // namespace ft

#endif