/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/26 02:31:30 by hsarhan          ###   ########.fr       */
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
    void _move_subtree(node_type *tree1, node_type *tree2)
    {

        if (tree1->parent == NULL)
        {
            // node 1 is root
            root = tree2;
        }
        else if (tree1 == tree1->parent->left)
        {
            // node 1 is a left child of its parent
            tree1->parent->left = tree2;
        }
        else if (tree1 == tree1->parent->right)
        {
            // node 1 is a right child of its parent
            tree1->parent->right = tree2;
        }
        if (tree2 != NULL)
        {
            // update node 2's parent
            tree2->parent = tree1->parent;
        }
    }

    void _left_rotate(node_type *x)
    {
        node_type *y = x->right;
        x->right = y->left;
        if (y->left != NULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void _right_rotate(node_type *x)
    {
        node_type *y = x->left;
        x->left = y->right;
        if (y->right != NULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void _insert_fixup(node_type *node)
    {
        // while there is a red node whose parent is a red node
        while (node->parent != NULL && node->parent->color == RED)
        {
            // if node's parent is a left child
            if (node->parent == node->parent->parent->left)
            {
                // get the node's uncle which will be its grandparent's right child
                node_type *uncle = node->parent->parent->right;
                // if the uncle's color is red
                if (uncle != NULL && uncle->color == RED)
                {
                    // case 1: involves only recoloring
                    // recolor parent and uncle to black
                    node->parent->color = BLACK;
                    uncle->color = BLACK;

                    // recolor grandparent to red
                    node->parent->parent->color = RED;
                    // traverse up the tree
                    node = node->parent->parent;
                }
                else
                {
                    // if node is a right child
                    if (node == node->parent->right)
                    {
                        // case 2
                        // just left rotate it to become a left child
                        node = node->parent;
                        _left_rotate(node);
                    }
                    // case 3
                    // recolor and right rotate to fix the violation
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    _right_rotate(node->parent->parent);
                }
            }
            else
            {
                node_type *uncle = node->parent->parent->left;
                if (uncle != NULL && uncle->color == RED)
                {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->left)
                    {
                        node = node->parent;
                        _right_rotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    _left_rotate(node->parent->parent);
                }
            }
        }
        // root of a red black tree has to be black
        root->color = BLACK;
    }

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
    ft::pair<node_type *, bool> map_insert(const T &val)
    {
        // Is the key already in the tree?
        node_type *res = map_get(val.first);
        if (res != NULL)
        {
            return ft::make_pair(res, false);
        }
        node_type *new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(val, RED));

        node_type *end = root;
        node_type *end_parent = NULL;
        while (end != NULL)
        {
            end_parent = end;
            if (_comp(new_node->data.first, end->data.first))
            {
                // less than
                end = end->left;
            }
            else
            {
                // greater tahn
                end = end->right;
            }
        }
        new_node->parent = end_parent;
        if (end_parent == NULL)
        {
            root = new_node;
        }
        else if (_comp(new_node->data.first, end_parent->data.first))
        {
            end_parent->left = new_node;
        }
        else
        {
            end_parent->right = new_node;
        }
        new_node->left = NULL;
        new_node->right = NULL;
        _insert_fixup(new_node);
        return ft::make_pair(new_node, true);
    }

    // * Insert into a set
    ft::pair<node_type *, bool> set_insert(const T &val)
    {
        // Is the key already in the tree?
        node_type *res = set_get(val);
        if (res != NULL)
        {
            return ft::make_pair(res, false);
        }
        node_type *new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(val, RED));

        node_type *end = root;
        node_type *end_parent = NULL;
        while (end != NULL)
        {
            end_parent = end;
            if (_comp(new_node->data, end->data))
            {
                // less than
                end = end->left;
            }
            else
            {
                // greater tahn
                end = end->right;
            }
        }
        new_node->parent = end_parent;
        if (end_parent == NULL)
        {
            root = new_node;
        }
        else if (_comp(new_node->data, end_parent->data))
        {
            end_parent->left = new_node;
        }
        else
        {
            end_parent->right = new_node;
        }
        new_node->left = NULL;
        new_node->right = NULL;
        _insert_fixup(new_node);
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
    template <class KeyType> node_type *map_get(const KeyType &key) const
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

    // * Get an element from a set
    template <class KeyType> node_type *set_get(const KeyType &key) const
    {
        if (root == NULL)
        {
            return NULL;
        }
        node_type *search = root;
        while (search != NULL && (_comp(key, search->data) || _comp(search->data, key)))
        {
            if (_comp(key, search->data))
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
        if (node->left == NULL)
        {
            // if node only has a right child replace it by its right child
            _move_subtree(node, node->right);
        }
        else if (node->right == NULL)
        {
            // if node only has a left child replace it by its left child
            _move_subtree(node, node->left);
        }
        else
        {
            // find node's successor and replace node by it
            node_type *successor = min_node(node->right);
            if (successor != node->right)
            {
                // node's successor is not its right child
                //                                               node
                //                                           l1         r
                //                                                  suc
                //                                                      x

                // 1. Replace node's successor by its right child (repalace suc with x)
                //                                                node
                //                                           l1                                  r
                //                                                                           x
                //                                                                               suc
                _move_subtree(successor, successor->right);

                // 2. Set suc to be r's parent
                //                                                node
                //                                           l1                              suc
                //                                                                               r
                //                                                                           x
                successor->right = node->right;
                successor->right->parent = successor;

                // 3. Replace suc with node
                //                                                suc
                //                                            l1       r
                //                                                  x
                _move_subtree(node, successor);
                successor->left = node->left;
                successor->left->parent = successor;
            }
            else
            {
                // node's successor is its right child
                //                                               node
                //                                           l1        suc
                //                                                          x

                // 1. Replace suc with node
                //                                                suc
                //                                            l1       x
                _move_subtree(node, successor);
                successor->left = node->left;
                successor->left->parent = successor;
            }
        }
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
