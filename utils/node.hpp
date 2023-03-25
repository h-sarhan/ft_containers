/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:07:03 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/25 15:06:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#include <cstddef>

namespace ft
{
template <class DataType> struct node
{
    typedef DataType pair_type;

    DataType data;
    node<DataType> *parent;
    node<DataType> *left;
    node<DataType> *right;
    bool is_black;

    // * Default constructor
    node(void) : data(), parent(NULL), left(NULL), right(NULL), is_black(false)
    {
    }

    // * Constructor
    node(const DataType &data) : data(data), parent(NULL), left(NULL), right(NULL), is_black(false)
    {
    }

    // * Copy constructor
    node(const node &old)
        : data(old.data), parent(old.parent), left(old.left), right(old.right),
          is_black(old.is_black)
    {
    }

    // * Copy assignment constructor
    node &operator=(const node &rhs)
    {
        if (this == &rhs)
            return *this;
        data = rhs.data;
        parent = rhs.parent;
        left = rhs.left;
        right = rhs.right;
        is_black = rhs.is_black;
        return *this;
    }
};
}   // namespace ft

#endif
