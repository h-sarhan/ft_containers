/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/09 14:48:04 by hsarhan          ###   ########.fr       */
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
template <class T> class tree
{
  private:
    typedef T node_type;

  public:
    node_type *root;

    // * Constructor
    tree(void) : root(NULL)
    {
    }
    tree(node_type *root) : root(root)
    {
    }

    tree(const tree &old) : root(old.root)
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
        return *this;
    }

    // * Insert into a map
    ft::pair<node_type *, bool> insert(const T &val)
    {
        (void) val;
    }

    // * Print the elements of a tree
    void traverse(node_type *node) const
    {
        (void) node;
    }

    // * Get an element from a map
    template <class KeyType> node_type *get(const KeyType &key) const
    {
        (void) key;
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
