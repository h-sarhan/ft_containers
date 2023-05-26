/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:56:58 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/26 19:52:59 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iterator>

// ! IMPLEMENT THESE
template <class T> class tree_iterator
{
};

template <class T> class map_iterator : tree_iterator<T>
{
};

template <class T> class set_iterator : tree_iterator<T>
{
};

#endif
