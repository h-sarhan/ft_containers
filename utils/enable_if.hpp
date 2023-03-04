/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:21:11 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 06:29:38 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
template <bool B, class T = void> struct enable_if
{
};

template <class T> struct enable_if<true, T>
{
    typedef T type;
};
};   // namespace ft

#endif