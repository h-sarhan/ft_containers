/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/09 17:09:48 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "make_pair.hpp"
#include "node.hpp"
#include "pair.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

namespace ft
{
template <class T, class Compare, class Alloc> class tree
{
  public:
    typedef T node_type;
    node_type *root;

  private:
    Compare _comp;
    Alloc _alloc;

  public:
    // * Constructor
    tree(void) : root(NULL), _comp(), _alloc()
    {
    }
    tree(node_type *root) : root(root), _comp(), _alloc()
    {
    }

    tree(const tree &old) : root(old.root), _comp(old._comp), _alloc(old._alloc)
    {
    }

    // * Destructor
    ~tree(void)
    {
    }

    // * Copy assignment constructor
    tree &operator=(const tree &rhs)
    {
        if (this == &rhs)
            return *this;
        root = rhs.root;
        _comp = rhs._comp;
        return *this;
    }

    // * Insert into a map
    ft::pair<node_type *, bool> insert(const T &val)
    {
        // Create node
        node_type *new_node = _alloc.allocate(1);
        _alloc.construct(new_node, val);

        // If tree is empty then the root is just the new node
        if (root == NULL)
        {
            root = new_node;
            return ft::make_pair(new_node, true);
        }

        // If the tree is not empty then just traverse through the tree to figure out
        // where to add the node
        node_type *node = root;
        while (true)
        {
            // If the new node is smaller than the current one then we go down
            // its left child
            if (_comp(new_node->data.first, node->data.first))
            {
                if (node->child[LEFT] != NULL)
                {
                    node = node->child[LEFT];
                }
                // If its left child is empty then this is where we place the node
                else
                {
                    node->child[LEFT] = new_node;
                    return ft::make_pair(new_node, true);
                }
            }
            // If the new node is larger than the current one then we go down
            // its right child
            else if (_comp(node->data.first, new_node->data.first))
            {
                if (node->child[RIGHT] != NULL)
                {
                    node = node->child[RIGHT];
                }
                // If its right child is empty then this is where we place the node
                else
                {
                    node->child[RIGHT] = new_node;
                    return ft::make_pair(new_node, true);
                }
            }
            else
            {
                // This key is already in the tree so we dont add it
                _alloc.destroy(new_node);
                _alloc.deallocate(new_node, 1);
                return ft::make_pair(node, false);
            }
        }
        // we will never reach this line
        return ft::make_pair(node, false);
    }

    // * Print the elements of a tree
    void traverse(node_type *node) const
    {
        if (node == NULL)
        {
            return;
        }
        traverse(node->child[LEFT]);
        std::cout << "Key: " << node->data.first << "\nValue: " << node->data.second << std::endl;
        traverse(node->child[RIGHT]);
    }

    // * Get an element from a map
    template <class KeyType> node_type *get(const KeyType &key) const
    {
        node_type *node = root;
        while (node != NULL)
        {
            if (_comp(key, node->data.first))
            {
                node = node->child[LEFT];
            }
            else if (_comp(node->data.first, key))
            {
                node = node->child[RIGHT];
            }
            else
            {
                return node;
            }
        }
        return NULL;
    }

    void delete_node(node_type *node)
    {
        (void) node;
    }

    // * Free the nodes from a tree
    void clear(node_type *node)
    {
        (void) node;
    }
};
}   // namespace ft

#endif
