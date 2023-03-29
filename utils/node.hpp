/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:07:03 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/29 16:27:18 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#include <cstddef>

#define BLACK false
#define RED   true
#define LEFT  0
#define RIGHT 1

namespace ft
{
template <class DataType> struct node
{
    typedef bool color;
    typedef DataType data_type;

    DataType data;
    node<DataType> *child[2];
    color col;

    // * Default constructor
    node(void) : data(), col(BLACK)
    {
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
    }

    // * Constructor
    node(const DataType &data, bool color) : data(data), col(color)
    {
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
    }

    // * Copy constructor
    node(const node &old) : data(old.data), col(old.col)
    {
        child[LEFT] = old.child[LEFT];
        child[RIGHT] = old.child[RIGHT];
    }

    // * Copy assignment constructor
    node &operator=(const node &rhs)
    {
        if (this == &rhs)
            return *this;
        data = rhs.data;
        child[LEFT] = rhs.child[LEFT];
        child[RIGHT] = rhs.child[RIGHT];
        col = rhs.col;
        return *this;
    }
};
}   // namespace ft

#endif
