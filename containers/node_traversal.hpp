/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_traversal.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:48:17 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/11 03:54:42 by hsarhan          ###   ########.fr       */
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

template <class NodeType> NodeType *successor_node(NodeType *node)
{
    // The node's successor will be the min node its right subtree exists
    if (node->child[RIGHT] != NULL)
    {
        return min_node(node->child[RIGHT]);
    }
    // If the node has no right subtree then we have to go up the tree to find the
    // parent of an ancestor who is a left child
    // So we save a pointer to the parent of the current node and we keep going up the tree
    // until we reach a node whose parent is a left child, then we return that parent
    // or NULL
    // NodeType *parent = node->parent;
    // while (parent != NULL && node == parent->child[RIGHT])
    // {
    //     node = parent;
    //     parent = parent->parent;
    // }
    // return parent;
    return NULL;
}

template <class NodeType> NodeType *predecessor_node(NodeType *node)
{
    // The node's predeccesor will be the max node its left subtree exists
    if (node->child[LEFT] != NULL)
    {
        return max_node(node->child[LEFT]);
    }
    // If the node has no left subtree then we have to go up the tree to find the
    // parent of an ancestor who is a right child
    // So we save a pointer to the parent of the current node and we keep going up the tree
    // until we reach a node whose parent is a right child, then we return that parent
    // or NULL
    // NodeType *parent = node->parent;
    // while (parent != NULL && node == parent->child[LEFT])
    // {
    //     node = parent;
    //     parent = parent->parent;
    // }
    // return parent;
    return NULL;
}
}   // namespace ft
#endif
