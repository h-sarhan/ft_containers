/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:41:27 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/26 19:52:59 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <cstddef>

template <class T, class KeyCompare> class tree
{
  public:
    typedef node<T, KeyCompare> *node_pointer;

  private:
    node_pointer _root;
    KeyCompare _comp;

  public:
    tree(node_pointer root, KeyCompare comp) : _root(root), _comp(comp)
    {
    }

    tree(const tree &old) : _root(old._root), _comp(old._comp)
    {
    }

    node_pointer root(void) const
    {
        return _root;
    }

    template <class KeyType> node_pointer search_node(KeyType key)
    {
        node_pointer node = root();
        while (node != NULL)
        {
            if (node == key)
            {
                return node;
            }
            else if (node > key)
            {
                node = node->child[LEFT];
            }
            else if (node < key)
            {
                node = node->child[RIGHT];
            }
        }
        return NULL;
    }
};
#endif
