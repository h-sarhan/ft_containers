/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/29 02:44:01 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
#define BST_HPP

#include "make_pair.hpp"
#include "node.hpp"
#include "pair.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

// ! add node_compare function
namespace ft
{
template <class T, class Compare, class Alloc> class bst
{
  public:
    typedef node<T> node_type;
    node_type *root;

  private:
    Compare _comp;
    Alloc _alloc;

  private:

  public:
    // * Constructor
    bst(node_type *root, Compare comp, Alloc allocator) : root(root), _comp(comp), _alloc(allocator)
    {
    }

    bst(const bst &old) : root(old.root), _comp(old._comp), _alloc(old._alloc)
    {
    }

    // * Destructor
    ~bst(void)
    {
        if (root == NULL)
        {
            return;
        }
        clear(root);
    }

    // * Copy assignment constructor
    bst &operator=(const bst &rhs)
    {
        if (this == &rhs)
            return *this;
        root = rhs.root;
        _comp = rhs._comp;
        _alloc = rhs._alloc;
        return *this;
    }

    // * Insert into a map
    // ! Make this use a node compare function
    ft::pair<node_type *, bool> insert(const T &val)
    {
        // Is the key already in the tree?
        node_type *res = map_get(val.first);
        if (res != NULL)
        {
            return ft::make_pair(res, false);
        }
        node_type *new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(val, RED));



        return ft::make_pair(new_node, true);
    }

    // * Print the elements of a tree
    void traverse(node_type *node) const
    {
        if (node != NULL)
        {
            traverse(node->left);
            std::cout << "key == " << node->data.first << " value == " << node->data.second
                      << std::endl;
            traverse(node->right);
        }
    }

    // * Get an element from a map
    // ! Make this use a node compare function
    template <class KeyType> node_type *get(const KeyType &key) const
    {
        if (root == NULL)
        {
            return NULL;
        }
        node_type *search = root;
        while (search != NULL && (_comp(key, search->data.first) || _comp(search->data.first, key)))
        {
            if (_comp(key, search->data.first))
            {
                search = search->left;
            }
            else
            {
                search = search->right;
            }
        }
        return search;
    }

    // * Delete a node from the tree
    void delete_node(node_type *node)
    {
        node_type *temp = node;



        _alloc.destroy(temp);
        _alloc.deallocate(temp, 1);
    }

    // * Free the nodes from a tree
    void clear(node_type *node)
    {
        if (node != NULL)
        {
            clear(node->left);
            node_type *temp = node->right;
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
            clear(temp);
        }
    }
};

// ** Public helper functions

// * Get the next node in sorted order
template <class NodeType> NodeType *successor_node(NodeType *node)
{
    if (node->right != NULL)
    {
        // return smallest (left-most) node in right subtree
        return min_node(node->right);
    }
    // traverse upwards through the tree till you find an ancestor of node
    // whose left child is also an ancestor of node
    NodeType *up = node->parent;
    while (up != NULL && node != up->left)
    {
        node = up;
        up = up->parent;
    }
    return up;
}

// * Get the previous node in sorted order
template <class NodeType> NodeType *predecessor_node(NodeType *node)
{
    if (node->left != NULL)
    {
        // return largest (right-most) node in left subtree
        return max_node(node->left);
    }
    // traverse upwards through the tree till you find an ancestor of node
    // whose right child is also an ancestor of node
    NodeType *up = node->parent;
    while (up != NULL && node != up->right)
    {
        node = up;
        up = up->parent;
    }
    return up;
}

// * Get the minimum node
template <class NodeType> NodeType *min_node(NodeType *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

// * Get the maximum node
template <class NodeType> NodeType *max_node(NodeType *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}
}   // namespace ft

#endif
