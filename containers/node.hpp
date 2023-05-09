/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:07:03 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/09 18:59:33 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#include <cstddef>
#include <memory>

#define BLACK false
#define RED   true
#define LEFT  0
#define RIGHT 1

namespace ft
{
template <class T> struct node
{
    typedef bool color;
    typedef T data_type;

  public:
    data_type data;
    node<T> *child[2];
    node<T> *parent;
    color col;

    // * Default constructor
    node(void) : data(), parent(NULL), col(BLACK)
    {
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
    }

    // * Constructor
    node(const data_type &val, bool color) : data(val), parent(NULL), col(color)
    {
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
    }

    // * Copy constructor
    node(const node &old) : data(old.data), parent(old.parent), col(old.col)
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
        parent = rhs.parent;
        child[LEFT] = rhs.child[LEFT];
        child[RIGHT] = rhs.child[RIGHT];
        col = rhs.col;
        return *this;
    }

    ~node(void)
    {
    }
};
}   // namespace ft

#endif
