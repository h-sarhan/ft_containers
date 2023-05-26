/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:10:18 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/26 22:32:56 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#include <cstddef>

namespace ft
{

template <class Key, class Value> struct map_node
{
    typedef ft::pair<Key, Value> node_data;

    node_data data;
    map_node *left;
    map_node *right;
    map_node *parent;

    map_node(const node_data &data) : data(data), left(NULL), right(NULL), parent(NULL)
    {
    }
};

}   // namespace ft
#endif
