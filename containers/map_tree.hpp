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
// The red black tree implementation was based on
// https://www.happycoders.eu/algorithms/red-black-tree-java/
// ! WRITE BETTER COMMENTS
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

        // Traverse the tree to the left or
        // right depending on the key
        node_pointer node = _root;
        node_pointer parent = NULL;
        while (node != NULL)
        {
            parent = node;
            // if (key < node->data)
            if (_node_greater(node, new_node))
            {
                node = node->left;
            }
            // else if (key > node->data)
            else if (_node_less(node, new_node))
            {
                node = node->right;
            }
            else
            {
                _alloc.destroy(new_node);
                _alloc.deallocate(new_node, 1);
                return false;
            }
        }

        // Insert new node
        new_node->color = RED;
        if (parent == NULL)
        {
            _root = new_node;
        }
        else if (_node_greater(parent, new_node))
        {
            parent->left = new_node;
        }
        else if (_node_less(parent, new_node))
        {
            parent->right = new_node;
        }
        new_node->parent = parent;

        _balance_after_insert(new_node);
        return true;
    }

    void delete_node(key_type key)
    {
        node_pointer node = _root;

        // Find the node to be deleted
        while (node != NULL && !_node_equal(node, key))
        {
            // Traverse the tree to the left or right depending on the key
            if (_node_greater(node, key))
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        // Node not found?
        if (node == NULL)
        {
            return;
        }

        node_pointer temp = node;

        // At this point, "node" is the node to be deleted

        // In this variable, we'll store the node at which we're going to start
        // to fix the R-B properties after deleting a node
        node_pointer replacement_node;
        bool deleted_color;

        // Node has zero or one child
        if (node->left == NULL || node->right == NULL)
        {
            replacement_node = _delete_leaf_or_single_child(node);
            deleted_color = node->color;
        }

        // Node has two children
        else
        {
            // Find minimum node of right subtree ("inorder successor" of
            // current node)
            node_pointer successor = _minimum_node(node->right);

            // Copy inorder successor's data to current node (keep its color!)
            _node_data_reassign(node, node->parent, successor->data);

            // Delete inorder successor just as we would delete a node with 0 or
            // 1 child
            replacement_node = _delete_leaf_or_single_child(successor);
            deleted_color = successor->color;
        }

        if (deleted_color == BLACK)
        {
            _balance_after_delete(replacement_node);

            // Remove the temporary NIL node
            if (replacement_node->fake_node == true)
            {
                _replace_child(replacement_node->parent, replacement_node,
                               NULL);
                _alloc.destroy(replacement_node);
                _alloc.deallocate(replacement_node, 1);
            }
        }
        _alloc.destroy(temp);
        _alloc.deallocate(temp, 1);
    }

    ~map_tree(void)
    {
        _tree_pruner(_root);
        _root = NULL;
    }

  private:
    void _balance_after_delete(node_pointer to_delete)
    {
        // Case 1: Examined node is root, end of recursion
        if (to_delete == _root)
        {
            to_delete->color = BLACK;
            return;
        }

        node_pointer sibling = _get_sibling(to_delete);

        // Case 2: Red sibling
        if (sibling->color == RED)
        {
            _case_2(to_delete, sibling);
            // Get new sibling for fall-through to cases 3-6
            sibling = _get_sibling(to_delete);
        }

        // Cases 3+4: Black sibling with two black children
        if (_is_black(sibling->left) && _is_black(sibling->right))
        {
            sibling->color = RED;

            // Case 3: Black sibling with two black children + red parent
            if (to_delete->parent->color == RED)
            {
                to_delete->parent->color = BLACK;
            }

            // Case 4: Black sibling with two black children + black parent
            else
            {
                _balance_after_delete(to_delete->parent);
            }
        }

        // Case 5+6: Black sibling with at least one red child
        else
        {
            _case_5_6(to_delete, sibling);
        }
    }

    void _case_5_6(node_pointer node, node_pointer sibling)
    {
        bool is_left_child;
        if (node == node->parent->left)
        {
            is_left_child = true;
        }
        else
        {
            is_left_child = false;
        }

        // Case 5: Black sibling with at least one red child + "outer nephew" is
        // black
        // --> Recolor sibling and its child, and rotate around sibling
        if (is_left_child && _is_black(sibling->right))
        {
            sibling->left->color = BLACK;
            sibling->color = RED;
            _rotate_right(sibling);
            sibling = node->parent->right;
        }
        else if (!is_left_child && _is_black(sibling->left))
        {
            sibling->right->color = BLACK;
            sibling->color = RED;
            _rotate_left(sibling);
            sibling = node->parent->left;
        }

        // Fall-through to case 6...

        // Case 6: Black sibling with at least one red child + "outer nephew" is
        // red
        // --> Recolor sibling + parent + sibling's child, and rotate around
        // parent
        sibling->color = node->parent->color;
        node->parent->color = BLACK;
        if (is_left_child)
        {
            sibling->right->color = BLACK;
            _rotate_left(node->parent);
        }
        else
        {
            sibling->left->color = BLACK;
            _rotate_right(node->parent);
        }
    }

    bool _is_black(node_pointer node)
    {
        if (node == NULL || node->color == BLACK)
            return true;
        return false;
    }

    node_pointer _get_sibling(node_pointer node)
    {
        node_pointer parent = node->parent;
        if (node == parent->left)
        {
            return parent->right;
        }
        else
        {
            return parent->left;
        }
    }

    void _case_2(node_pointer node, node_pointer sibling)
    {
        // Recolor...
        sibling->color = BLACK;
        node->parent->color = RED;

        // ... and rotate
        if (node == node->parent->left)
        {
            _rotate_left(node->parent);
        }
        else
        {
            _rotate_right(node->parent);
        }
    }

    void _balance_after_insert(node_pointer inserted_node)
    {
        node_pointer parent = inserted_node->parent;

        // Case 1: New node is the root, the root has to be black so we
        // color it black
        if (parent == NULL)
        {
            inserted_node->color = BLACK;
            return;
        }

        // If the parent is black, then there is no violation of the red
        // black tree rules when inserting a red node
        if (parent->color == BLACK)
        {
            return;
        }
        // If the parent color is red then there is a violation and we need
        // to fix it

        // Get the grandparent and uncle these will help us fix the rest of
        // the cases
        node_pointer grandparent = parent->parent;
        node_pointer uncle = _get_uncle(parent);

        // Case 2: Parent and uncle nodes are red
        // For this case we color the parent and the uncle to black and the
        // grandparent to be red
        if (uncle != NULL && uncle->color == RED)
        {
            parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            // Coloring the grandparent red can cause more red black tree
            // violations so what we can do is recursively call this
            // function on the grandparent until all violations have been
            // fixed
            _balance_after_insert(grandparent);
        }

        // Parent is a left child
        else if (parent == grandparent->left)
        {
            // Case 3a: Parent is red, uncle is black, and the inserted_node
            // is an inner grandchild, i.e. The path from the grandparent to
            // the inserted_node forms a triangle For this case we have to
            // rotate the parent in the opposite direction of the
            // inserted_node, (so left) and then we rotate the grandparent
            // in the opposite direction of the previous rotation, (so
            // right) and finally we color the inserted_node black and the
            // original grandparent red
            if (inserted_node == parent->right)
            {
                _rotate_left(parent);
                parent = inserted_node;
            }

            // Case 4a: Parent is red, uncle is black, and the inserted_node
            // is an outer grandchild, i.e. The path from the grandparent to
            // the inserted_node forms a line. In this case we just need to
            // rotate the grandparent in the opposite direction of the
            // parent and inserted_node
            _rotate_right(grandparent);

            // Recolor original parent and grandparent
            parent->color = BLACK;
            grandparent->color = RED;
        }
        // This is the symmetrical case if the parent is a right child
        else
        {
            if (inserted_node == parent->left)
            {
                _rotate_right(parent);
                parent = inserted_node;
            }
            _rotate_left(grandparent);

            parent->color = BLACK;
            grandparent->color = RED;
        }
    }

    node_pointer _get_uncle(node_pointer parent)
    {
        node_pointer grandparent = parent->parent;

        if (grandparent->left == parent)
        {
            return grandparent->right;
        }
        else
        {
            return grandparent->left;
        }
    }

    void _rotate_right(node_pointer node)
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

    void _rotate_left(node_pointer node)
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

    node_pointer _delete_leaf_or_single_child(node_pointer to_delete)
    {
        // If the node only has a left child then replace the node by its
        // left child
        if (to_delete->left)
        {
            _replace_child(to_delete->parent, to_delete, to_delete->left);
            return to_delete->left;
        }
        // If the node only has a right child then replace the node by its
        // right child
        else if (to_delete->right)
        {
            _replace_child(to_delete->parent, to_delete, to_delete->right);
            return to_delete->right;
        }
        // Node has no children -->
        // * node is red --> just remove it
        // * node is black --> replace it by a temporary NIL node (needed to
        // fix the R-B rules)
        else
        {
            // Node newChild = node.color == BLACK ? new NilNode() : null;
            // replaceParentsChild(node.parent, node, newChild);
            node_pointer child;
            if (to_delete->color == BLACK)
            {
                child = _alloc.allocate(1);
                _alloc.construct(child, node_type());
                child->fake_node = true;
            }
            else
            {
                child = NULL;
            }
            _replace_child(to_delete->parent, to_delete, child);
            return child;
        }
    }

    // Disgusting hack to reassign a node's data, I cant do this the obvious
    // way because the data for a map is a pair and the first type of the
    // pair is const so the copy assignment operator for pair does not
    // compile 😊
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

    node_pointer _minimum_node(node_pointer node)
    {
        node_pointer min = node;
        while (min->left != NULL)
        {
            min = min->left;
        }
        return min;
    }

    node_pointer _maximum_node(node_pointer node)
    {
        node_pointer max = node;
        while (max->right != NULL)
        {
            max = max->right;
        }
        return max;
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
