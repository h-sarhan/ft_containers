/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:07:03 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/25 23:12:38 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#include <cstddef>

#define BLACK false
#define RED true

namespace ft
{
template <class DataType> struct node
{
    typedef DataType pair_type;

    DataType data;
    node<DataType> *parent;
    node<DataType> *left;
    node<DataType> *right;
    bool color;

    // * Default constructor
    node(void) : data(), parent(NULL), left(NULL), right(NULL), color(BLACK)
    {
    }

    // * Constructor
    node(const DataType &data, bool color)
        : data(data), parent(NULL), left(NULL), right(NULL), color(color)
    {
    }

    // * Copy constructor
    node(const node &old)
        : data(old.data), parent(old.parent), left(old.left), right(old.right), color(old.color)
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
        color = rhs.color;
        return *this;
    }
};
}   // namespace ft

#endif
