/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 12:39:40 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
#define BST_HPP

#include "node.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

namespace ft
{
template <class KeyType, class ValType, class Compare, class Alloc> class bst
{
  public:
    typedef pair<const KeyType, ValType> value_type;
    typedef node<value_type> node_type;

    node_type *root;

  private:
    Compare _comp;
    Alloc _alloc;

  private:
    void _move_subtree(node_type *node_1, node_type *node_2);
    static node_type *_bst_min(node_type *node);
    static node_type *_bst_max(node_type *node);
    static node_type *_bst_successor(node_type *node);
    static node_type *_bst_predecessor(node_type *node);

  public:
    bst(node_type *root, Compare comp, Alloc allocator) : root(root), _comp(comp), _alloc(allocator)
    {
    }
    bst(const bst &old) : root(old.root), _comp(old._comp), _alloc(old._alloc)
    {
    }
    bst &operator=(const bst &rhs)
    {
        if (this == &rhs)
            return *this;
        root = rhs.root;
        _comp = rhs._comp;
        _alloc = rhs._alloc;
        return *this;
    }
    void insert(const value_type &val);
    void traverse(node_type *node) const;
    node_type *get(const KeyType &key);
    void delete_node(node_type *key);
};
};   // namespace ft

template <class KeyType, class ValType, class Compare, class Alloc>
void ft::bst<KeyType, ValType, Compare, Alloc>::insert(const value_type &val)
{
    node_type *new_node = _alloc.allocate(1);
    _alloc.construct(new_node, node_type(val));

    node_type *end = root;
    node_type *end_parent = NULL;
    while (end != NULL)
    {
        end_parent = end;
        if (_comp(new_node->data.first, end->data.first))
        {
            end = end->left;
        }
        else
        {
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
}

template <class KeyType, class ValType, class Compare, class Alloc>
typename ft::bst<KeyType, ValType, Compare, Alloc>::node_type *ft::bst<
    KeyType, ValType, Compare, Alloc>::get(const KeyType &key)
{
    node_type *search = root;
    while (search != NULL && search->data.first != key)
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

template <class KeyType, class ValType, class Compare, class Alloc>
void ft::bst<KeyType, ValType, Compare, Alloc>::traverse(node_type *node) const
{
    if (node != NULL)
    {
        traverse(node->left);
        std::cout << "key == " << node->data.first << " value == " << node->data.second << std::endl;
        traverse(node->right);
    }
}

template <class KeyType, class ValType, class Compare, class Alloc>
void ft::bst<KeyType, ValType, Compare, Alloc>::_move_subtree(node_type *tree1, node_type *tree2)
{
    // ! This should destroy and tree1

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

template <class KeyType, class ValType, class Compare, class Alloc>
void ft::bst<KeyType, ValType, Compare, Alloc>::delete_node(node_type *node)
{
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
        node_type *successor = _bst_min(node->right);
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
}

template <class KeyType, class ValType, class Compare, class Alloc>
typename ft::bst<KeyType, ValType, Compare, Alloc>::node_type *ft::bst<
    KeyType, ValType, Compare, Alloc>::_bst_min(node_type *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

template <class KeyType, class ValType, class Compare, class Alloc>
typename ft::bst<KeyType, ValType, Compare, Alloc>::node_type *ft::bst<
    KeyType, ValType, Compare, Alloc>::_bst_max(node_type *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

template <class KeyType, class ValType, class Compare, class Alloc>
typename ft::bst<KeyType, ValType, Compare, Alloc>::node_type *ft::bst<
    KeyType, ValType, Compare, Alloc>::_bst_successor(node_type *node)
{
    if (node->right != NULL)
    {
        // return left-most node in right subtree
        return _bst_min(node->right);
    }
    // traverse upwards through the tree till you find an ancestor of node
    // whose left child is also an ancestor of node
    node_type *up = node->parent;
    while (up != NULL && node != up->left)
    {
        node = up;
        up = up->parent;
    }
    return up;
}

template <class KeyType, class ValType, class Compare, class Alloc>
typename ft::bst<KeyType, ValType, Compare, Alloc>::node_type *ft::bst<
    KeyType, ValType, Compare, Alloc>::_bst_predecessor(node_type *node)
{
    if (node->left != NULL)
    {
        // return right-most node in left subtree
        return _bst_max(node->left);
    }
    // traverse upwards through the tree till you find an ancestor of node
    // whose right child is also an ancestor of node
    node_type *up = node->parent;
    while (up != NULL && node != up->right)
    {
        node = up;
        up = up->parent;
    }
    return up;
}

#endif
