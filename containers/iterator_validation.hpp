/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_validation.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:22:48 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/29 23:57:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_VALIDATION_HPP
#define ITERATOR_VALIDATION_HPP
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
bool validate_iterators(InputIterator first, InputIterator last,
                        size_t max_size)
{
    return validate(first, last, max_size,
                    typename InputIterator::iterator_category());
}

template <typename PointerType>
bool validate_iterators(PointerType *first, PointerType *last, size_t max_size)
{
    const long dist = last - first;
    if (dist < 0 || dist >= (long) max_size)
        return false;
    return true;
}

inline bool one_way_check(std::input_iterator_tag cat)
{
    (void) cat;
    return true;
}

inline bool one_way_check(std::random_access_iterator_tag cat)
{
    (void) cat;
    return false;
}

inline bool one_way_check(std::forward_iterator_tag cat)
{
    (void) cat;
    return false;
}

inline bool one_way_check(std::bidirectional_iterator_tag cat)
{
    (void) cat;
    return false;
}

template <typename InputIterator> bool is_one_way(InputIterator it)
{
    (void) it;
    return one_way_check(typename InputIterator::iterator_category());
}

template <typename PointerType> bool is_one_way(PointerType *it)
{
    (void) it;
    return false;
}

}   // namespace ft

#endif
