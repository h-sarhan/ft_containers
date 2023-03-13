/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/13 21:29:37 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
#define BST_HPP

#include "make_pair.hpp"
#include "node.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

// ! Implement sentinel nodes, because you are segfaulting whenever you increment end()
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

  public:
    bst(node_type *root, Compare comp, Alloc allocator) : root(root), _comp(comp), _alloc(allocator)
    {
    }
    bst(const bst &old) : root(old.root), _comp(old._comp), _alloc(old._alloc)
    {
    }
    ~bst(void);
    bst &operator=(const bst &rhs)
    {
        if (this == &rhs)
            return *this;
        root = rhs.root;
        _comp = rhs._comp;
        _alloc = rhs._alloc;
        return *this;
    }
    ft::pair<node_type *, bool> insert(const value_type &val);
    void traverse(node_type *node) const;
    node_type *get(const KeyType &key) const;
    void delete_node(node_type *key);
    void free_nodes(node_type *node);
};

// * Public helper functions
template <class NodeType> NodeType *successor_node(NodeType *node);

template <class NodeType> NodeType *predecessor_node(NodeType *node);

template <class NodeType> NodeType *min_node(NodeType *node);

template <class NodeType> NodeType *max_node(NodeType *node);
}   // namespace ft

template <class KeyType, class ValType, class Compare, class Alloc>
ft::bst<KeyType, ValType, Compare, Alloc>::~bst<KeyType, ValType, Compare, Alloc>(void)
{
    free_nodes(root);
}

template <class KeyType, class ValType, class Compare, class Alloc>
void ft::bst<KeyType, ValType, Compare, Alloc>::free_nodes(node_type *node)
{
    if (node != NULL)
    {
        free_nodes(node->left);
        node_type *temp = node->right;
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
        free_nodes(temp);
    }
}

template <class KeyType, class ValType, class Compare, class Alloc>
ft::pair<typename ft::bst<KeyType, ValType, Compare, Alloc>::node_type *, bool> ft::bst<
    KeyType, ValType, Compare, Alloc>::insert(const value_type &val)
{
    // Is the key already in the tree?
    node_type *res = get(val.first);
    if (res != NULL)
    {
        return ft::make_pair(res, false);
    }
    node_type *new_node = _alloc.allocate(1);
    _alloc.construct(new_node, node_type(val));

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
        std::cout << "updating root " << std::endl;
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
    // return true;
    return ft::make_pair(new_node, true);
}

template <class KeyType, class ValType, class Compare, class Alloc>
typename ft::bst<KeyType, ValType, Compare, Alloc>::node_type *ft::bst<
    KeyType, ValType, Compare, Alloc>::get(const KeyType &key) const
{
    if (root == NULL)
    {
        return NULL;
    }
    node_type *search = root;
    // std::cout << "in bst::get() root"
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
        std::cout << "key == " << node->data.first << " value == " << node->data.second
                  << std::endl;
        traverse(node->right);
    }
}

template <class KeyType, class ValType, class Compare, class Alloc>
void ft::bst<KeyType, ValType, Compare, Alloc>::_move_subtree(node_type *tree1, node_type *tree2)
{
    // ! This should destroy and fee

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
}

template <class NodeType> NodeType *ft::min_node(NodeType *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

template <class NodeType> NodeType *ft::max_node(NodeType *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

template <class NodeType> NodeType *ft::successor_node(NodeType *node)
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

template <class NodeType> NodeType *ft::predecessor_node(NodeType *node)
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

#endif
