/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/24 15:58:02 by hsarhan          ###   ########.fr       */
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
    typedef Compare compare_type;

  private:
    compare_type _comp;
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
        _alloc = rhs._alloc;
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
        // pointer to store the parent of the current node
        node_type *parent = NULL;

        // start with the root node
        node_type *curr = root;
        bool dir = LEFT;

        // search key in the BST and set its parent pointer
        // traverse the tree and search for the key
        while (curr != NULL && (_comp(curr->data.first, node->data.first) == true ||
                                _comp(node->data.first, curr->data.first) == true))
        {
            // update the parent to the current node
            parent = curr;

            // if the given key is less than the current node, go to the left subtree;
            // otherwise, go to the right subtree
            if (_comp(node->data.first, curr->data.first) == true)
            {
                curr = curr->child[LEFT];
                dir = LEFT;
            }
            else if (_comp(curr->data.first, node->data.first) == true)
            {
                curr = curr->child[RIGHT];
                dir = RIGHT;
            }
        }

        // return if the key is not found in the tree
        // This should never happen
        if (curr == NULL)
        {
            return;
        }

        // Case 1: node to be deleted has no children, i.e., it is a leaf node
        if (curr->child[LEFT] == NULL && curr->child[RIGHT] == NULL)
        {
            // if the node to be deleted is not a root node, then set its
            // parent left/right child to null
            if (curr != root)
            {
                if (parent->child[LEFT] == curr)
                {
                    parent->child[LEFT] = NULL;
                }
                else
                {
                    parent->child[RIGHT] = NULL;
                }
            }
            // if the tree has only a root node, set it to null
            else
            {
                root = NULL;
            }

            // deallocate the memory
            // free(curr);   // or delete curr;
            _alloc.destroy(curr);
            _alloc.deallocate(curr, 1);
        }

        // Case 2: node to be deleted has two children
        else if (curr->child[LEFT] && curr->child[RIGHT])
        {
            // find its inorder successor node
            node_type *successor = min_node(curr->child[RIGHT]);

            // store successor value
            typename node_type::data_type val = successor->data;

            // recursively delete the successor. Note that the successor
            // will have at most one child (right child)
            delete_node(successor);

            // copy value of the successor to the current node
            // curr->data = val;
            node_type *new_node_to_replace_curr = _alloc.allocate(1);
            _alloc.construct(new_node_to_replace_curr, node_type(val, curr->col));
            parent->child[dir] = new_node_to_replace_curr;
            _alloc.destroy(curr);
            _alloc.deallocate(curr, 1);
        }

        // Case 3: node to be deleted has only one child
        else
        {
            // choose a child node
            node_type *child = (curr->child[LEFT]) ? curr->child[LEFT] : curr->child[RIGHT];

            // if the node to be deleted is not a root node, set its parent
            // to its child
            if (curr != root)
            {
                if (curr == parent->child[LEFT])
                {
                    parent->child[LEFT] = child;
                }
                else
                {
                    parent->child[RIGHT] = child;
                }
            }

            // if the node to be deleted is a root node, then set the root to the child
            else
            {
                root = child;
            }

            // deallocate the memory
            // free(curr);
            _alloc.destroy(curr);
            _alloc.deallocate(curr, 1);
        }
    }

    // * Free the nodes from a tree
    void clear(node_type *&node)
    {
        if (node == NULL)
        {
            return;
        }
        node_type *right = node->child[RIGHT];
        node_type *left = node->child[LEFT];
        clear(left);
        // node->child[LEFT] = NULL;
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
        node = NULL;
        clear(right);
        // node->child[RIGHT] = NULL;
    }
};
}   // namespace ft

#endif
