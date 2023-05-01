/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/04/06 16:14:28 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
#define BST_HPP

#include "make_pair.hpp"
#include "node.hpp"
#include "node_comparison.hpp"
#include "pair.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

namespace ft
{
template <class T> class bst
{
  private:
    typedef node<T> node_type;

    Alloc _alloc;

  public:
    node_type *root;

    // * Constructor
    bst(void) : _alloc(), root(NULL)
    {
    }
    bst(node_type *root) : _alloc(), root(root)
    {
    }

    bst(const bst &old) : _alloc(old._alloc), root(old.root)
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
    // ! LOOK INTO THIS AGAIN
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
                // ! REWRITE THIS
                dir = !node_less<node_type, Compare>(new_node, it, _comp);
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
            std::cout << "key == " << node->data->first << " value == " << node->data->second
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

        while (it != NULL)
        {
            if (key_equal(key, it, _comp))
            {
                return it;
            }
            else
            {
                // ! REWRITE THIS
                bool dir = !key_less(key, it, _comp);
                // if dir == true then we go to the left node
                // if dir == false then we go to the left node
                it = it->child[dir];
            }
        }
        return (NULL);
    }

    // * Delete a node from the tree
    void delete_node2(node_type *node)
    {
        if (root != NULL)
        {
            node_type head;
            node_type *it = &head;
            node_type *p = NULL;
            node_type  *f = NULL;
            bool dir = RIGHT;

            it->child[RIGHT] = root;

            while (it->child[dir] != NULL)
            {
                p = it;
                it = it->child[dir];
                if (node_less(it, node, _comp) || node_equal(it, node, _comp))
                {
                    dir = RIGHT;
                }
                else
                {
                    dir = LEFT;
                }

                if (node_equal(it, node, _comp))
                    f = it;
            }

            if (f != NULL)
            {
                // f->data = it->data;
                f->replace(*it->data);
                p->child[p->child[RIGHT] == it] = it->child[it->child[LEFT] == NULL];
                // free(it);
                // _alloc.destroy(it);
                _alloc.deallocate(it, 1);
            }
            root = head.child[RIGHT];
        }
    }
    void delete_node(node_type *node)
    {
        if (root == NULL)
        {
            return;
        }
        node_type *parent = NULL;
        node_type *successor;
        node_type *it = root;
        bool dir;

        // go through tree till we find node to delete
        while (1)
        {
            if (it == NULL)
                return;
            else if (node_equal(it, node, _comp))
                break;
            if (node_less(node, it, _comp) == true)
            {
                dir = LEFT;
            }
            else
            {
                dir = RIGHT;
            }
            parent = it;
            it = it->child[dir];
        }
        // at this point `it` is the node we want to delete
        // `parent` is `it`'s parent

        // if the node we want to delete has two children, we need to find the successor
        if (it->child[LEFT] != NULL && it->child[RIGHT] != NULL)
        {
            parent = it;

            // we find the successor by getting the left-most node in the right child of the node we
            // want to delete
            successor = it->child[RIGHT];
            while (successor->child[LEFT] != NULL)
            {
                parent = successor;
                successor = successor->child[LEFT];
            }
            // now we have the successor

            // we want to replace the successor's data with the node we want to delete and then
            // delete the successor
            it->replace(*successor->data);

            // if the successor is a right child?
            if (successor == parent->child[RIGHT])
            {
                // then dir is right
                dir = RIGHT;
            }
            else
            {
                // then dir is left
                dir = LEFT;
            }
            // successor's parent now points to successor's child since the successor has been
            // removed
            parent->child[dir] = successor->child[RIGHT];

            // std::cout << "DELETING NODE1 " << successor->data->first << std::endl;
            //  delete successor here
            _alloc.destroy(successor);
            _alloc.deallocate(successor, 1);
            traverse(root);
        }
        else
        {
            // if the node we want to delete has one child

            // if the node we want to delete has a right child
            if (it->child[RIGHT] != NULL)
            {
                // then dir is right
                dir = RIGHT;
            }
            else
            {
                // then dir is left
                dir = LEFT;
            }
            // Special case: we are deleting the root
            if (parent == NULL)
            {
                // does the node have a right child?
                // in this case the new root is it's child and we delete `it`
                root = it->child[dir];
            }
            else
            {
                // if `it` is a right child?
                if (it == parent->child[RIGHT])
                {
                    // then dir is right
                    // `it`'s parent now points to `it`'s child since `it` has been removed
                    parent->child[RIGHT] = it->child[dir];
                }
                else
                {
                    // then dir is left
                    // `it`'s parent now points to `it`'s child since `it` has been removed
                    parent->child[LEFT] = it->child[dir];
                }
            }
            // std::cout << "DELETING NODE2 " << it->data->first << std::endl;
            _alloc.destroy(it);
            _alloc.deallocate(it, 1);
        }
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
}   // namespace ft

#endif
