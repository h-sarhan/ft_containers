/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:10:18 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/30 05:27:58 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#include <cstddef>

#define BLACK false
#define RED   true

namespace ft
{

template <class Key, class Value> struct map_node
{
    typedef ft::pair<Key, Value> node_data;

    node_data data;
    map_node *left;
    map_node *right;
    map_node *parent;
    bool color;
    bool nil_node;


    map_node(const node_data &data = node_data())
        : data(data), left(NULL), right(NULL), parent(NULL), color(BLACK),
          nil_node(false)
    {
    }
    map_node(const map_node &old)
        : data(old.data), left(old.left), right(old.right), parent(old.parent),
          color(old.color), nil_node(old.nil_node)
    {
    }
};

template <class Key, class Value>
struct map_node_nil : public map_node<Key, Value>
{
    map_node_nil() : map_node<Key, Value>()
    {
        this->nil_node = true;
    }
    map_node_nil(const map_node_nil &old) : map_node<Key, Value>(old)
    {
        this->nil_node = true;
    }
};

}   // namespace ft
#endif
