/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/12 12:19:01 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "make_pair.hpp"
#include "node.hpp"
#include "node_traversal.hpp"
#include "pair.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

#define BST_MAX_HEIGHT 64

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
        node_type *current;
        node_type *parent;
        bool dir;
        node_type *new_node;

        parent = NULL;
        current = this->root;
        while (current != NULL)
        {
            const bool less = _comp(val.data.first, current->data.first);
            const bool greater = _comp(current->data.first, val.data.first);
            if (!less && !greater)
                return ft::make_pair(current, false);
            if (less)
                dir = LEFT;
            else
                dir = RIGHT;
            parent = current;
            current = current->child[dir];
        }

        // n = tree->bst_alloc->libavl_malloc(tree->bst_alloc, sizeof *p);
        // if (n == NULL)
        //     return NULL;
        new_node = _alloc.allocate(1);
        _alloc.construct(new_node, val);

        new_node->child[RIGHT] = NULL;
        new_node->child[LEFT] = NULL;
        if (parent != NULL)
            parent->child[dir] = new_node;
        else
            this->root = new_node;

        return ft::make_pair(new_node, true);
    }

    // * Print the elements of a tree
    void traverse(node_type *node) const
    {
        if (node == NULL)
        {
            return;
        }
        traverse(node->child[LEFT]);
        std::cout << "Key: " << node->data.first << " | Value: " << node->data.second << std::endl;
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
        node_type *search;
        node_type *parent;
        bool dir;

        if (node == NULL)
            return;
        search = this->root;
        // Find the parent of the node we want to delete
        while (true)
        {
            if (_comp(search->data.first, node->data.first) == true)
                dir = RIGHT;
            else if (_comp(node->data.first, search->data.first) == true)
                dir = LEFT;
            else
                break;
            parent = search;
            search = search->child[dir];
            if (search == NULL)
                return;
        }
        // If the node has no right child, then replace the node by its left child
        if (node->child[RIGHT] == NULL)
        {
            // Replace node by its left child
            parent->child[dir] = node->child[LEFT];
        }
        // If the node has no right child, then replace the node by its left child
        else
        {
            node_type *right_child = node->child[RIGHT];
            // If the node's right child has no left child then we move the node's right child into
            // the node's place
            if (right_child->child[LEFT] == NULL)
            {
                // The right child's left child is now the left child of the node to be deleted
                right_child->child[LEFT] = node->child[LEFT];
                // Replace node by its right child
                parent->child[dir] = right_child;
            }
            // If the node's right child has a left child then we have to replace the node by its
            // successor
            else
            {
                // Find the successor node
                // The successor node is the smallest node greater than the current node
                // It is found in the leftmost leaf of the right subtree
                node_type *successor = node;
                while (true)
                {
                    successor = right_child->child[LEFT];
                    if (successor->child[LEFT] == NULL)
                        break;
                    right_child = successor;
                }
                // Replace successor with 
                right_child->child[LEFT] = successor->child[RIGHT];
                successor->child[LEFT] = node->child[LEFT];
                successor->child[RIGHT] = node->child[RIGHT];
                parent->child[dir] = successor;
            }
        }
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
    }

    // * Free the nodes from a tree
    void clear(node_type *&node)
    {
        if (node == NULL)
        {
            return;
        }
        clear(node->child[LEFT]);
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
        clear(node->child[RIGHT]);
    }
};
}   // namespace ft

#endif
