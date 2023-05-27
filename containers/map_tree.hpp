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
#include "vector.hpp"
#include <cstddef>

namespace ft
{

// Red black tree rules
// 1. Each node is either red or black.
// 2. (The root is black.)
// 3. All NIL leaves are black.
// 4. A red node must not have red children.
// 5. All paths from a node to the leaves below contain the same number of black
// nodes.
template <class Key, class Value, class KeyCompare, class NodeAllocator>
class map_tree
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

    map_tree(const map_tree &old)
        : _root(old._root), _key_comp(old._key_comp), _alloc(old._alloc)
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
            // If the node's key matches then this is the node we are looking
            // for so we return it
            if (_node_equal(node, key) == true)
            {
                return node;
            }
            // If the node we are looking at is bigger than the key then we have
            // to go to a node smaller than it
            else if (_node_greater(node, key) == true)
            {
                node = node->left;
            }
            // If the node we are looking at is smaller than the key then we
            // have to go to a node bigger than it
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

    void delete_node(key_type key)
    {
        node_pointer node = _root;
        node_pointer parent = NULL;

        while (node != NULL && !_node_equal(node, key))
        {
            parent = node;
            if (_node_greater(node, key))
            {
                node = node->left;
            }
            else if (_node_less(node, key))
            {
                node = node->right;
            }
        }

        if (node == NULL)
        {
            return;
        }

        if (node->left == NULL && node->right == NULL)
        {
            _delete_leaf_node(node, parent);
        }
        else if (node->left == NULL || node->right == NULL)
        {
            _delete_single_child(node, parent);
        }
        else
        {
            _delete_two_childs(node, parent);
        }
    }

    ~map_tree(void)
    {
        _tree_pruner(_root);
        _root = NULL;
    }

  private:
    void _right_rotate(node_pointer node)
    {
        node_pointer parent = node->parent;
        node_pointer left = node->left;

        node->left = left->right;
        if (left->right != NULL)
        {
            left->right->parent = node;
        }

        left->right = node;
        node->parent = left;

        _replace_child(parent, node, left);
    }

    void _left_rotate(node_pointer node)
    {
        node_pointer parent = node->parent;
        node_pointer right = node->right;

        node->right = right->left;
        if (right->left != NULL)
        {
            right->left->parent = node;
        }

        right->left = node;
        node->parent = right;

        _replace_child(parent, node, right);
    }

    void _replace_child(node_pointer parent, node_pointer old_child,
                        node_pointer new_child)
    {
        if (parent == NULL)
        {
            _root = new_child;
        }
        else if (parent->left == old_child)
        {
            parent->left = new_child;
        }
        else if (parent->right == old_child)
        {
            parent->right = new_child;
        }

        if (new_child != NULL)
        {
            new_child->parent = parent;
        }
    }

    void _delete_leaf_node(node_pointer to_delete, node_pointer parent)
    {
        // special case if the node we want to delete is the root
        if (to_delete == root())
        {
            _root = NULL;
        }
        // if the parent node is smaller than the node we want to delete then
        // the parent's right child is the node we want to delete
        else if (_node_less(parent, to_delete))
        {
            parent->right = NULL;
        }
        else
            parent->left = NULL;
        _alloc.destroy(to_delete);
        _alloc.deallocate(to_delete, 1);
    }

    void _delete_single_child(node_pointer to_delete, node_pointer parent)
    {
        node_pointer child;
        if (to_delete->right == NULL)
        {
            child = to_delete->left;
        }
        else
        {
            child = to_delete->right;
        }
        // special case if the node we want to delete is the root
        if (to_delete == root())
        {
            _root = child;
        }
        // if the parent node is smaller than the node we want to delete then
        // the parent's right child is the node we want to delete
        else if (_node_less(parent, to_delete))
        {
            parent->right = child;
        }
        else
        {
            parent->left = child;
        }
        _alloc.destroy(to_delete);
        _alloc.deallocate(to_delete, 1);
    }

    void _delete_two_childs(node_pointer to_delete, node_pointer parent)
    {
        // Find minimum node of right subtree ("inorder successor" of current
        // node)
        node_pointer succ;
        node_pointer succ_parent;

        succ = to_delete->right;
        succ_parent = to_delete;

        while (succ->left != NULL)
        {
            succ_parent = succ;
            succ = succ->left;
        }
        _node_data_reassign(to_delete, parent, succ->data);

        // Case a) Inorder successor is the deleted node's right child
        if (succ == to_delete->right)
        {
            // --> Replace right child with inorder successor's right child
            to_delete->right = succ->right;
        }

        // Case b) Inorder successor is further down, meaning, it's a left child
        else
        {
            // --> Replace inorder successor's parent's left child
            //     with inorder successor's right child
            succ_parent->left = succ->right;
        }
    }

    // disgusting hack to reassign a node's data, I cant do this the obvious way
    // because the data for a map is a pair and the first type of the pair is
    // const so the copy assignment operator for pair does not compile 😊
    void _node_data_reassign(node_pointer node, node_pointer parent,
                             const node_data &data)
    {
        node_pointer new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(data));

        new_node->left = node->left;
        new_node->right = node->right;
        new_node->parent = node->parent;
        if (node == _root)
        {
            _root = new_node;
        }
        else if (_node_less(node, parent))
        {
            parent->left = new_node;
        }
        else
        {
            parent->right = new_node;
        }
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
    }

    void _tree_pruner(node_pointer &node)
    {
        if (node == NULL)
            return;
        node_pointer left = node->left;
        node_pointer right = node->right;
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
        node = NULL;
        _tree_pruner(left);
        _tree_pruner(right);
    }

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
