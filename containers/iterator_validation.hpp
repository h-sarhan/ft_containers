/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_validation.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:48 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/06 03:25:03 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator_traits.hpp"
#include <iterator>

namespace ft
{
template <typename InputIterator>
static bool validate(InputIterator first, InputIterator last, size_t max_size,
                     std::input_iterator_tag)
{
    (void) first;
    (void) last;
    (void) max_size;
    return true;
}

template <typename InputIterator>
static bool validate(InputIterator first, InputIterator last, size_t max_size,
                     std::random_access_iterator_tag)
{
    const long dist = std::distance(first, last);
    if (dist < 0 || dist >= (long) max_size)
        return false;
    return true;
}

template <typename InputIterator>
static bool validate(InputIterator first, InputIterator last, size_t max_size,
                     std::forward_iterator_tag)
{
    const long dist = std::distance(first, last);
    if (dist < 0 || dist >= (long) max_size)
        return false;
    return true;
}

template <typename InputIterator>
static bool validate(InputIterator first, InputIterator last, size_t max_size,
                     std::bidirectional_iterator_tag)
{
    const long dist = std::distance(first, last);
    if (dist < 0 || dist >= (long) max_size)
        return false;
    return true;
}

template <typename InputIterator>
bool validate_iterators(InputIterator first, InputIterator last, size_t max_size)
{
    return validate(first, last, max_size, typename InputIterator::iterator_category());
}

template <typename PointerType>
bool validate_iterators(PointerType *first, PointerType *last, size_t max_size)
{
    const long dist = last - first;
    if (dist < 0 || dist >= (long) max_size)
        return false;
    return true;
}

}   // namespace ft
