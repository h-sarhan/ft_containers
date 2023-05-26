/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:41:27 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/26 22:53:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TREE_HPP
#define MAP_TREE_HPP

#include "node.hpp"
#include "pair.hpp"
#include <cstddef>

namespace ft
{
template <class Key, class Value, class KeyCompare, class NodeAllocator> class map_tree
{
  public:
    typedef ft::pair<Key, Value> node_data;
    typedef ft::map_node<Key, Value> node_type;
    typedef node_type *node_pointer;
    typedef KeyCompare key_compare;
    typedef NodeAllocator node_allocator;
    typedef Key key_type;

  private:
    node_pointer _root;
    key_compare _key_comp;
    node_allocator _alloc;

  public:
    map_tree(node_pointer root, key_compare comp, const node_allocator &alloc)
        : _root(root), _key_comp(comp), _alloc(alloc)
    {
    }

    map_tree(const map_tree &old) : _root(old._root), _key_comp(old._key_comp), _alloc(old._alloc)
    {
    }

    node_pointer root(void) const
    {
        return _root;
    }

    node_pointer search_node(key_type key) const
    {
        node_pointer node = root();

        // We start traversing from the root
        while (node != NULL)
        {
            // If the node's key matches then this is the node we are looking for so we return it
            if (_node_equal(node, key) == true)
            {
                return node;
            }
            // If the node we are looking at is bigger than the key then we have to go to a node
            // smaller than it
            else if (_node_greater(node, key) == true)
            {
                node = node->left;
            }
            // If the node we are looking at is smaller than the key then we have to go to a node
            // bigger than it
            else if (_node_less(node, key) == true)
            {
                node = node->right;
            }
        }
        return NULL;
    }

    // Returns true if the node was inserted
    bool insert_node(const node_data &data)
    {
        node_pointer new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(data));

        if (root() == NULL)
        {
            _root = new_node;
            return true;
        }

        node_pointer node = root();
        while (true)
        {
            if (_node_greater(node, new_node))
            {
                if (node->left != NULL)
                {
                    node = node->left;
                }
                else
                {
                    node->left = new_node;
                    return true;
                }
            }
            else if (_node_less(node, new_node))
            {
                if (node->right != NULL)
                {
                    node = node->right;
                }
                else
                {
                    node->right = new_node;
                    return false;
                }
            }
            else
            {
                _alloc.destroy(new_node);
                _alloc.deallocate(new_node, 1);
                return false;
            }
        }
        // In theory we will never reach this line, but in practice...
        return false;
    }

  private:
    const key_type &_get_key(const node_pointer node) const
    {
        return node->data.first;
    }

    bool _node_equal(const node_pointer node, const key_type &key) const
    {
        return _node_equal(_get_key(node), key);
    }

    bool _node_less(const node_pointer node, const key_type &key) const
    {
        return _node_less(_get_key(node), key);
    }

    bool _node_greater(const node_pointer node, const key_type &key) const
    {
        return _node_greater(_get_key(node), key);
    }

    bool _node_equal(const key_type &key, const node_pointer node) const
    {
        return _node_equal(key, _get_key(node));
    }

    bool _node_less(const key_type &key, const node_pointer node) const
    {
        return _node_less(key, _get_key(node));
    }

    bool _node_greater(const key_type &key, const node_pointer node) const
    {

        return _node_greater(key, _get_key(node));
    }

    bool _node_equal(const node_pointer node1, const node_pointer node2) const
    {
        return _node_equal(_get_key(node1), _get_key(node2));
    }

    bool _node_less(const node_pointer node1, const node_pointer node2) const
    {
        return _node_less(_get_key(node1), _get_key(node2));
    }

    bool _node_greater(const node_pointer node1, const node_pointer node2) const
    {
        return _node_greater(_get_key(node1), _get_key(node2));
    }

    bool _node_equal(const key_type &key1, const key_type &key2) const
    {
        return !_node_less(key1, key2) && !_node_greater(key1, key2);
    }

    bool _node_less(const key_type &key1, const key_type &key2) const
    {
        return _key_comp(key1, key2);
    }

    bool _node_greater(const key_type &key1, const key_type &key2) const
    {
        return _key_comp(key2, key1);
    }
};

}   // namespace ft

#endif
