/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_distance.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:34:55 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/25 16:32:58 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_DISTANCE_HPP
#define ITERATOR_DISTANCE_HPP

#include <cstddef>
#include <cstdint>

namespace ft
{
template <typename InputIterator> ptrdiff_t iterator_distance(InputIterator it1, InputIterator it2)
{
    ptrdiff_t diff = 0;
    for (InputIterator it = it1; it != it2 && diff < PTRDIFF_MAX; it++)
    {
        diff++;
    }
    return diff;
}
}   // namespace ft

#endif
