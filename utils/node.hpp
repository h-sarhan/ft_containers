/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:07:03 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/14 19:18:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include <cstddef>
#include "pair.hpp"

namespace ft
{
template <class DataType> struct node
{
    typedef DataType pair_type;

    DataType data;
    node<DataType> *parent;
    node<DataType> *left;
    node<DataType> *right;

    node(void) : data(), parent(NULL), left(NULL), right(NULL)
    {
    }
    node(const DataType &data) : data(data), parent(NULL), left(NULL), right(NULL)
    {
    }
    node(const node &old) : data(old.data), parent(old.parent), left(old.left), right(old.right)
    {
    }

    node &operator=(const node &rhs)
    {
        if (this == &rhs)
            return *this;
        data = rhs.data;
        parent = rhs.parent;
        left = rhs.left;
        right = rhs.right;
        return *this;
    }
};
}   // namespace ft

#endif
