/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_distance.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:34:55 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/28 12:31:51 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_DISTANCE_HPP
#define ITERATOR_DISTANCE_HPP

#include <cstddef>
#include <limits>

namespace ft
{
template <typename InputIterator> size_t iterator_distance(InputIterator it1, InputIterator it2)
{
    size_t diff = 0;
    for (InputIterator it = it1; it != it2 && diff < std::numeric_limits<size_t>::max(); it++)
    {
        diff++;
    }
    return diff;
}
}   // namespace ft

#endif
