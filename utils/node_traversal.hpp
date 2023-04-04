/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_traversal.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:07:09 by hsarhan           #+#    #+#             */
/*   Updated: 2023/04/04 16:38:24 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_TRAVERSAL_HPP
#define NODE_TRAVERSAL_HPP

#include "node_comparison.hpp"
#include <cstddef>
#define LEFT  0
#define RIGHT 1

// * Get the minimum node
template <class NodeType> NodeType *min_node(NodeType *node)
{
    while (node->child[LEFT] != NULL)
    {
        node = node->child[LEFT];
    }
    return node;
}

// * Get the maximum node
template <class NodeType> NodeType *max_node(NodeType *node)
{
    while (node->child[RIGHT] != NULL)
    {
        node = node->child[RIGHT];
    }
    return node;
}

// * Get the next node in sorted order
template <class NodeType, class Compare>
NodeType *successor_node(NodeType *root, NodeType *node, const Compare &comp)
{
    NodeType *successor;

    if (node->child[RIGHT] != NULL)
    {
        // Successor is just the min node of the right subtree
        return min_node(node->child[RIGHT]);
    }
    else
    {
        // If the node doesn't have a right sub tree then its successor is above it in the tree
        // Since we do not have an easy way to go up the tree we need to start searching for a
        // potential successor from the root
        successor = NULL;
        NodeType *search = root;
        // the search terminates at a leaf node or when we reach the node itself
        while (search != NULL || search == node)
        {
            if (node_greater(search, node, comp) == true)
            {
                // the search node is greater so it could be a successor
                successor = search;
                // we assign search to its left child to see if there are any potential
                // successors smaller than it
                search = search->child[LEFT];
            }
            else
            {
                // the search node is smaller than the node so it can not be a successor
                // so we reassign search to be its right child to look for nodes greater than it
                // that could be a successor
                search = search->child[RIGHT];
            }
        }
        if (search == node)
            return NULL;
    }
    return (successor);
}

// * Get the previous node in sorted order
template <class NodeType, class Compare>
NodeType *predecessor_node(NodeType *root, NodeType *node, const Compare &comp)
{
    NodeType *predecessor;

    if (node->child[LEFT] != NULL)
    {
        // Predecessor is just the max node of the left subtree
        return max_node(node->child[LEFT]);
    }
    else
    {
        // If the node doesn't have a left sub tree then its predecessor is above it in the tree
        // Since we do not have an easy way to go up the tree we need to start searching for a
        // potential predecessor from the root
        predecessor = NULL;
        NodeType *search = root;
        // the search terminates at a leaf node or when we reach the node itself
        while (search != NULL || search == node)
        {
            if (node_less(search, node, comp) == true)
            {
                // the search node is less than the node so it could be a predecessor
                predecessor = search;
                // we assign search to its right child to see if there are any potential
                // predecessors greater than it
                search = search->child[RIGHT];
            }
            else
            {
                // the search node is greater than the node so it can not be a predecessor
                // so we reassign search to be its left child to look for nodes less than it
                // that could be a predecessor
                search = search->child[LEFT];
            }
        }
    }
    return (predecessor);
}

#endif
