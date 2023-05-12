/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_traversal.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:48:17 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/12 16:38:50 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_TRAVERSAL_HPP
#define NODE_TRAVERSAL_HPP

#include <cstddef>
#define LEFT  0
#define RIGHT 1
namespace ft
{

template <class NodeType> NodeType *min_node(NodeType *node)
{
    while (node->child[LEFT] != NULL)
    {
        node = node->child[LEFT];
    }
    return node;
}

template <class NodeType> NodeType *max_node(NodeType *node)
{
    while (node->child[RIGHT] != NULL)
    {
        node = node->child[RIGHT];
    }
    return node;
}

template <class NodeType, class Comp>
NodeType *successor_node(NodeType *node, NodeType *root, Comp &comp)
{
    // The node's successor will be the min node its right subtree exists
    if (node->child[RIGHT] != NULL)
    {
        return min_node(node->child[RIGHT]);
    }
    // If the node has no right subtree then we have to traverse from the root of the tree
    NodeType *succ = root;
    NodeType *traverse = root;
    while (traverse != NULL)
    {
        // The node we want is less than the current one so we go down the left child
        if (comp(node->data.first, succ->data.first) == true)
        {
            traverse = traverse->child[LEFT];
            succ = traverse;
        }
        // The node we want is greater than the current one so we go down the right child
        else if (comp(node->data.first, succ->data.first) == false)
        {
            traverse = traverse->child[RIGHT];
        }
        else
        {
            return succ;
        }
    }
    return traverse;
}

// template <class NodeType> NodeType *predecessor_node(NodeType *node)
template <class NodeType, class Comp> NodeType *predecessor_node(NodeType *node, NodeType *root, Comp &comp)
{
    // The node's predeccesor will be the max node its left subtree exists
    if (node->child[LEFT] != NULL)
    {
        return max_node(node->child[LEFT]);
    }
    NodeType *succ = root;
    NodeType *traverse = root;
    while (traverse != NULL)
    {
        // The node we want is less than the current one so we go down the left child
        if (comp(succ->data.first, node->data.first) == true)
        {
            traverse = traverse->child[RIGHT];
            succ = traverse;
        }
        // The node we want is greater than the current one so we go down the right child
        else if (comp(succ->data.first, node->data.first) == false)
        {
            traverse = traverse->child[LEFT];
        }
        else
        {
            return succ;
        }
    }
    return traverse;
}
}   // namespace ft
#endif
