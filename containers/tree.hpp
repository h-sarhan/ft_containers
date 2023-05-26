/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:41:27 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/26 22:53:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <cstddef>

namespace ft
{

template <class NodeType, class NodeCompare, class NodeAllocator> class tree
{
  public:
    typedef NodeType *node_pointer;

  private:
    node_pointer _root;
    NodeCompare _key_comp;
    NodeAllocator _alloc;

  public:
    tree(node_pointer root, NodeCompare comp, const NodeAllocator &alloc)
        : _root(root), _key_comp(comp), _alloc(alloc)
    {
    }

    tree(const tree &old) : _root(old._root), _key_comp(old._key_comp), _alloc(old._alloc)
    {
    }

    node_pointer root(void) const
    {
        return _root;
    }

    template <class KeyType> node_pointer &search_node(KeyType key)
    {
        node_pointer node = root();

        // We start traversing from the root
        while (node != NULL)
        {
            // If the node's key matches then this is the node we are looking for so we return it
            // ! REIMPLEMENT WITH NodeCompare
            if (node == key)
            {
                return node;
            }
            // If the node we are looking at is bigger than the key then we have to go to a node
            // smaller than it
            // ! REIMPLEMENT WITH NodeCompare
            else if (node > key)
            {
                node = node->left;
            }
            // If the node we are looking at is smaller than the key then we have to go to a node
            // bigger than it
            // ! REIMPLEMENT WITH NodeCompare
            else if (node < key)
            {
                node = node->right;
            }
        }
        return NULL;
    }

    // Returns true if the node was inserted
    bool insert_node(const NodeData &data)
    {
        node_pointer *new_node;

        if (root() == NULL)
        {
            _root = new_node;
            return true;
        }

        node_pointer node = root();
        while (true)
        {
            // Traverse the tree to the left or right depending on the key
            if (key < node.data)
            {
                if (node.left != null)
                {
                    // Left sub-tree exists --> follow
                    node = node.left;
                }
                else
                {
                    // Left sub-tree does not exist --> insert new node as left child
                    node.left = newNode;
                    return;
                }
            }
            else if (key > node.data)
            {
                if (node.right != null)
                {
                    // Right sub-tree exists --> follow
                    node = node.right;
                }
                else
                {
                    // Right sub-tree does not exist --> insert new node as right child
                    node.right = newNode;
                    return;
                }
            }
            else
            {
                throw new IllegalArgumentException("BST already contains a node with key " + key);
            }
        }
    }
};

}   // namespace ft

#endif
