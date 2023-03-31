/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/31 07:01:51 by hsarhan          ###   ########.fr       */
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
    bool _node_equal(const node_type *node1, const node_type *node2) const
    {
        return _comp(node1, node2) == false && _comp(node2, node1) == false;
    }

    bool _node_less(const node_type *node1, const node_type *node2) const
    {
        return _comp(node1, node2) == true;
    }

    bool _node_greater(const node_type *node1, const node_type *node2) const
    {
        return _comp(node2, node1) == true;
    }

    template <class KeyType> bool _key_equal(const KeyType &key, const node_type *node) const
    {
        return _comp(node, key) == false && _comp(key, node) == false;
    }

    template <class KeyType> bool _key_less(const KeyType &key, const node_type *node) const
    {
        return _comp(node, key) == true;
    }

    template <class KeyType> bool _key_greater(const KeyType &key, const node_type *node) const
    {
        return _comp(key, node) == true;
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
    ft::pair<node_type *, bool> insert(const T &val)
    {
        // Is the key already in the tree?
        node_type *res = get(val.first);
        if (res != NULL)
        {
            return ft::make_pair(res, false);
        }
        node_type *new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(val, RED));
        if (root == NULL)
        {
            root = new_node;
        }
        else
        {
            node_type *it = root;

            bool dir;
            while (1)
            {

                dir = !_node_less(new_node, it);
                // if dir == true then we go to the left node
                // if dir == false then we go to the left node
                if (it->child[dir] == NULL)
                {
                    break;
                }
                it = it->child[dir];
            }
            it->child[dir] = new_node;
        }
        return ft::make_pair(new_node, true);
    }

    // * Print the elements of a tree
    void traverse(node_type *node) const
    {
        if (node != NULL)
        {
            traverse(node->child[LEFT]);
            std::cout << "key == " << node->data.first << " value == " << node->data.second
                      << std::endl;
            traverse(node->child[RIGHT]);
        }
    }

    // * Get an element from a map
    // ! Make this use a node compare function
    // ! This should use a temporary node to be able to use the node compare function
    template <class KeyType> node_type *get(const KeyType &key) const
    {
        node_type *it = root;

        // creating temp node to compare with
        while (it != NULL)
        {
            if (_key_equal(key, it))
            {
                return it;
            }
            else
            {
                bool dir = !_key_less(key, it);
                // if dir == true then we go to the left node
                // if dir == false then we go to the left node
                it = it->child[dir];
            }
        }
        return (NULL);
    }

    // * Delete a node from the tree
    void delete_node(node_type *node)
    {
        if (root == NULL)
            return;
        // node_type *to_free = node;
        node_type *parent = NULL;
        node_type *successor;
        node_type *it = root;
        bool dir;

        while (1)
        {
            if (it == NULL)
                return;
            else if (_node_equal(it, node))
                break;
            dir = !_node_less(it, node);
            parent = it;
            it = it->child[dir];
        }

        if (it->child[LEFT] != NULL && it->child[RIGHT] != NULL)
        {
            parent = it;
            successor = it->child[RIGHT];

            while (successor->child[LEFT] != NULL)
            {
                parent = successor;
                successor = successor->child[LEFT];
            }

            it->data = successor->data;
            parent->child[parent->child[RIGHT] == successor] = successor->child[RIGHT];

        }
        else
        {
            dir = it->child[LEFT] == NULL;

            if (parent == NULL)
                root = it->child[dir];
            else
                parent->child[parent->child[RIGHT] == it] = it->child[dir];
        }
        // _alloc.destroy(to_free);
        // _alloc.deallocate(to_free, 1);
    }

    // * Free the nodes from a tree
    void clear(node_type *node)
    {
        if (node != NULL)
        {
            clear(node->child[LEFT]);
            node_type *temp = node->child[RIGHT];
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
    // ! find some other way to implement this without using parent pointers lol
    (void) node;
    return (NULL);
}

// * Get the previous node in sorted order
template <class NodeType> NodeType *predecessor_node(NodeType *node)
{
    // ! find some other way to implement this without using parent pointers lol
    (void) node;
    return (NULL);
}

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
}   // namespace ft

#endif
