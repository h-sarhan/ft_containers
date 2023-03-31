/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:35:28 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/31 21:26:06 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_PAIR_HPP
#define MAKE_PAIR_HPP

#include "pair.hpp"

namespace ft
{
template <class T1, class T2> ft::pair<T1, T2> make_pair(T1 x, T2 y)
{
    return ft::pair<T1, T2>(x, y);
}
}   // namespace ft

#endif
