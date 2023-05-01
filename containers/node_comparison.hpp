/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_comparison.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:01:03 by hsarhan           #+#    #+#             */
/*   Updated: 2023/04/04 11:12:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_COMPARISON_HPP
#define NODE_COMPARISON_HPP

template <class NodeType, class Compare>
bool node_equal(const NodeType *node1, const NodeType *node2, const Compare &comp)
{
    return comp(node1, node2) == false && comp(node2, node1) == false;
}

template <class NodeType, class Compare>
bool node_less(const NodeType *node1, const NodeType *node2, const Compare &comp)
{
    return comp(node1, node2) == true;
}

template <class NodeType, class Compare>
bool node_greater(const NodeType *node1, const NodeType *node2, const Compare &comp)
{
    return comp(node2, node1) == true;
}

template <class NodeType, class KeyType, class Compare>
bool key_equal(const KeyType &key, const NodeType *node, const Compare &comp)
{
    return comp(node, key) == false && comp(key, node) == false;
}

template <class NodeType, class KeyType, class Compare>
bool key_less(const KeyType &key, const NodeType *node, const Compare &comp)
{
    return comp(key, node) == true;
}

template <class NodeType, class KeyType, class Compare>
bool key_greater(const KeyType &key, const NodeType *node, const Compare &comp)
{
    return comp(node, key) == true;
}
#endif
