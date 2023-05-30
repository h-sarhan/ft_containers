/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:41:27 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/30 08:02:03 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_TREE_HPP
#define SET_TREE_HPP

#include "make_pair.hpp"
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
template <class Key, class KeyCompare, class NodeAllocator> class set_tree
{
  public:
    typedef const Key node_data;
    typedef ft::set_node<const Key> node_type;
    typedef node_type *node_pointer;
    typedef KeyCompare key_compare;
    typedef NodeAllocator node_allocator;
    typedef Key key_type;

    node_pointer root;

  private:
    key_compare _key_comp;
    node_allocator _alloc;

  public:
    set_tree(node_pointer root, key_compare comp, const node_allocator &alloc)
        : root(root), _key_comp(comp), _alloc(alloc)
    {
    }

    set_tree(const set_tree &old)
        : root(old.root), _key_comp(old._key_comp), _alloc(old._alloc)
    {
    }

    node_pointer search_node(key_type key) const
    {
        node_pointer node = root;

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
    ft::pair<node_pointer, bool> insert_node(const node_data &data)
    {
        node_pointer new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(data));

        if (root == NULL)
        {
            root = new_node;
            return ft::make_pair(root, true);
        }

        // Traverse the tree to the left or
        // right depending on the key
        node_pointer node = root;
        node_pointer parent = NULL;
        while (node != NULL)
        {
            parent = node;
            if (_node_greater(node, new_node))
            {
                node = node->left;
            }
            else if (_node_less(node, new_node))
            {
                node = node->right;
            }
            else
            {
                _alloc.destroy(new_node);
                _alloc.deallocate(new_node, 1);
                return ft::make_pair(node, false);
            }
        }

        // Insert new node
        new_node->color = RED;
        if (parent == NULL)
        {
            root = new_node;
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
        return ft::make_pair(new_node, true);
    }

    void delete_node(key_type key)
    {
        node_pointer node = root;

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

        // At this point, "node" is the node to be deleted

        // replacement_node is where a red black tree violation could occur
        node_pointer replacement_node;
        // color of the deleted node
        bool deleted_color;

        // Node has zero or one child
        if (node->left == NULL || node->right == NULL)
        {
            deleted_color = node->color;
            replacement_node = _delete_leaf_or_single_child(node);
        }
        // Node has two children
        else
        {
            // 1. find successor
            // 2. copy successor data into the node
            // 3. Delete successor
            node_pointer successor = minimum_node(node->right);

            node = _node_data_reassign(node, node->parent, successor->data);

            deleted_color = successor->color;
            replacement_node = _delete_leaf_or_single_child(successor);
        }
        // if the node we deleted was black in color then there was a violation,
        // if it was red then there was no violation
        if (deleted_color == BLACK)
        {
            // fix red black violations
            _balance_after_delete(replacement_node);

            // remove temporary node
            if (replacement_node->nil_node == true)
            {
                _replace_child(replacement_node->parent, replacement_node,
                               NULL);
                _alloc.destroy(replacement_node);
                _alloc.deallocate(replacement_node, 1);
            }
        }
    }

    ~set_tree(void)
    {
        _tree_pruner(root);
        root = NULL;
    }

    // successor node
    node_pointer next_node(node_pointer node) const
    {
        if (node == NULL)
            return NULL;

        // if the node has a right subtree then the successor is the smallest
        // node in that tree
        if (node->right != NULL)
        {
            return minimum_node(node->right);
        }
        else
        {
            // otherwise we just have to traverse up the tree to find the first
            // parent that is a left child
            node_pointer parent = node->parent;
            while (parent != NULL && node == parent->right)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
    }

    node_pointer previous_node(node_pointer node) const
    {
        if (node == NULL)
            return NULL;

        // if the node has a left subtree then the predecessor is the largest
        // node in that tree
        if (node->left != NULL)
        {
            return maximum_node(node->left);
        }
        else
        {
            // otherwise we just have to traverse up the tree to find the first
            // parent that is a right child
            node_pointer parent = node->parent;
            while (parent != NULL && node == parent->left)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
    }

    // find the smallest node in the test
    node_pointer minimum_node(node_pointer node) const
    {
        node_pointer min = node;
        while (min->left != NULL)
        {
            min = min->left;
        }
        return min;
    }

    // find the largest node in the test
    node_pointer maximum_node(node_pointer node) const
    {
        node_pointer max = node;
        while (max->right != NULL)
        {
            max = max->right;
        }
        return max;
    }

  private:
    void _balance_after_delete(node_pointer to_delete)
    {
        // Case 1. If the node is root then we just color it black
        if (to_delete == root)
        {
            to_delete->color = BLACK;
            return;
        }

        // Get the sibling node cuz it is used a lot in fixing the violations
        node_pointer sibling = _get_sibling(to_delete);

        // Case 2. Red sibling
        if (sibling->color == RED)
        {
            _case_2(to_delete, sibling);
            // Get new sibling for fall-through to cases 3-6
            sibling = _get_sibling(to_delete);

            // After fixing case 2 which involves some recolors and a rotation
            // we will end up in one of cases 3 to 6
        }

        // Case 3/4. Two black children
        if (_is_black(sibling->left) && _is_black(sibling->right))
        {
            // color the sibling red
            sibling->color = RED;

            // Case 3. Two black children with a red parent
            if (to_delete->parent->color == RED)
            {
                // Recolor the parent black
                to_delete->parent->color = BLACK;
            }

            // Case 4. Two black children and a black parent
            else
            {
                // Recursively fix violations at the parent of the node we are
                // deleting
                _balance_after_delete(to_delete->parent);
            }
        }
        // Case 5/6 Black sibling with a red child
        else
        {
            _case_5_6(to_delete, sibling);
        }
    }

    // Fixing case 2 of the red black violation
    void _case_2(node_pointer node, node_pointer sibling)
    {
        sibling->color = BLACK;
        node->parent->color = RED;

        if (node == node->parent->left)
        {
            _rotate_left(node->parent);
        }
        else
        {
            _rotate_right(node->parent);
        }
    }

    // Fixing case 5 and 6 of potential violations after deleting a node
    void _case_5_6(node_pointer node, node_pointer sibling)
    {
        // We check if the node we are deleting is a left child
        bool is_left_child;
        if (node == node->parent->left)
        {
            is_left_child = true;
        }
        else
        {
            is_left_child = false;
        }

        // Case 5. "outer nephew is black" case
        // to fix this we recolor the sibling node and its child
        // and we rotate the sibling in the opposite direction of the node we
        // want to delete
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

        // Case 6. "outer nephew is red" case
        // to fix this we recolor the sibling, parent, sibling's child and we
        // rotate the parent in the same direction of as the node
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

    // returns whether the node is black
    bool _is_black(const node_pointer node) const
    {
        if (node == NULL || node->color == BLACK)
            return true;
        return false;
    }

    // Get the opposite sibling node
    node_pointer _get_sibling(const node_pointer node) const
    {
        node_pointer parent = node->parent;
        if (node == parent->left)
        {
            return parent->right;
        }
        else if (node == parent->right)
        {
            return parent->left;
        }
        else
        {
            throw std::runtime_error("bad");
        }
    }

    // Fixing red black tree violations after inserting
    void _balance_after_insert(node_pointer inserted_node)
    {
        node_pointer parent = inserted_node->parent;

        // if the parent is NULL then we are inserting the root node
        // we color it black to satisfy the red black tree rules
        if (parent == NULL)
        {
            inserted_node->color = BLACK;
            return;
        }

        // there are no possible violations after inserting a red node whose
        // parent is black
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

        // Case 2. Parent and uncle nodes are red
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

    // get the uncle node
    node_pointer _get_uncle(const node_pointer parent) const
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

    // Perform a right rotation, which changes the positions of the nodes at a
    // specific subtree without changing their order lexicographically
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

    // Perform a left rotation, which changes the positions of the nodes at a
    // specific subtree without changing their order lexicographically
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

    // replace a node while setting its parent pointers correctly
    void _replace_child(node_pointer parent, node_pointer old_child,
                        node_pointer new_child)
    {
        if (parent == NULL)
        {
            root = new_child;
        }
        else if (parent->left == old_child)
        {
            parent->left = new_child;
        }
        else
        {
            parent->right = new_child;
        }

        if (new_child != NULL)
        {
            new_child->parent = parent;
        }
    }

    // delete a node that has 0 or 1 child
    node_pointer _delete_leaf_or_single_child(node_pointer to_delete)
    {
        if (to_delete->left != NULL)
        {
            node_pointer temp = to_delete->left;
            _replace_child(to_delete->parent, to_delete, to_delete->left);
            _alloc.destroy(to_delete);
            _alloc.deallocate(to_delete, 1);
            return temp;
        }
        else if (to_delete->right != NULL)
        {
            node_pointer temp = to_delete->right;
            _replace_child(to_delete->parent, to_delete, to_delete->right);
            _alloc.destroy(to_delete);
            _alloc.deallocate(to_delete, 1);
            return temp;
        }
        else
        {
            node_pointer child;
            if (to_delete->color == BLACK)
            {
                child = _alloc.allocate(1);
                _alloc.construct(child, set_node_nil<const key_type>());
                child->nil_node = true;
                child->color = BLACK;
            }
            else
            {
                child = NULL;
            }
            _replace_child(to_delete->parent, to_delete, child);
            _alloc.destroy(to_delete);
            _alloc.deallocate(to_delete, 1);
            return child;
        }
    }

    // Disgusting hack to reassign a node's data, I cant do this the obvious
    // way because the data for a set is a pair and the first type of the
    // pair is const so the copy assignment operator for pair does not
    // compile 😊
    node_pointer _node_data_reassign(node_pointer node, node_pointer parent,
                                     const node_data &data)
    {
        node_pointer new_node = _alloc.allocate(1);
        _alloc.construct(new_node, node_type(data));

        new_node->left = node->left;
        new_node->right = node->right;
        new_node->parent = node->parent;
        new_node->color = node->color;
        if (node->left != NULL)
            node->left->parent = new_node;
        if (node->right != NULL)
            node->right->parent = new_node;
        if (node == root)
        {
            root = new_node;
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
        return new_node;
    }

    // recursice function to delete the nodes of the tree
    // this is used in the destructor
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

    // the rest are helper functions to compare nodes

    const key_type &_get_key(const node_pointer node) const
    {
        return node->data;
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
