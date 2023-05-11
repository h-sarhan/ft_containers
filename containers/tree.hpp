/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/11 03:36:04 by hsarhan          ###   ########.fr       */
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

    // ! Explain the cases here
    void delete_node(node_type *node)
    {
       (void)node;
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
