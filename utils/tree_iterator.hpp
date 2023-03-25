/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:24 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 06:31:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "bst.hpp"
#include "iterator_traits.hpp"
#include <cstddef>

namespace ft
{
template <class T, class NodeType> class tree_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef NodeType *node_pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

  private:
    // * Private attributes
    node_pointer _node_ptr;
    node_pointer _bst_root;
    node_pointer _sentinel;

  public:
    // * Constructors and destructors
    tree_iterator(void) : _node_ptr(NULL), _bst_root(NULL), _sentinel(NULL)
    {
    }

    tree_iterator(node_pointer ptr, node_pointer bst_root, node_pointer sentinel)
        : _node_ptr(ptr), _bst_root(bst_root), _sentinel(sentinel)
    {
    }

    template <class T2>
    tree_iterator(const tree_iterator<T2, NodeType> &old)
        : _node_ptr(old.base()), _bst_root(old.bst_root()), _sentinel(old.sentinel())
    {
    }

    template <class T2> tree_iterator &operator=(const tree_iterator<T2, NodeType> &rhs)
    {
        _node_ptr = rhs.base();
        _bst_root = rhs.bst_root();
        _sentinel = rhs.sentinel();
        return *this;
    }

    ~tree_iterator(void)
    {
        // ??
    }

    node_pointer base(void) const
    {
        return _node_ptr;
    }

    node_pointer bst_root(void) const
    {
        return _bst_root;
    }

    node_pointer sentinel(void) const
    {
        return _sentinel;
    }

    // * Iterator traversal
    tree_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then incrementing it should give
        // you ? the first element.
        if (_node_ptr == _sentinel)
        {
            // ? Get the first element of the map
            _node_ptr = ft::min_node(_bst_root);
            return *this;
        }
        _node_ptr = ft::successor_node(_node_ptr);
        if (_node_ptr == NULL)
        {
            _node_ptr = _sentinel;
        }
        return *this;
    }

    tree_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one in front of the first element then decrementing it should
        // give ? you the last element.
        if (_node_ptr == _sentinel)
        {
            // ? Get the last element of the map
            _node_ptr = ft::max_node(_bst_root);
            return *this;
        }
        _node_ptr = ft::predecessor_node(_node_ptr);
        if (_node_ptr == NULL)
        {
            _node_ptr = _sentinel;
        }
        return *this;
    }

    tree_iterator operator++(int)   // post-increment
    {
        tree_iterator<T, NodeType> temp = *this;
        ++(*this);
        return temp;
    }

    tree_iterator operator--(int)   // post-decrement
    {
        tree_iterator<T, NodeType> temp = *this;
        --(*this);
        return temp;
    }

    // * Iterator comparison
    template <class It> bool operator==(const It &rhs) const
    {
        return _node_ptr == rhs.base();
    }
    template <class It> bool operator!=(const It &rhs) const
    {
        return _node_ptr != rhs.base();
    }

    // * Iterator access
    reference operator*(void)
    {
        return _node_ptr->data;
    }

    pointer operator->(void)
    {
        return &_node_ptr->data;
    }
    reference operator*(void) const
    {
        return _node_ptr->data;
    }
    pointer operator->(void) const
    {
        return &_node_ptr->data;
    }
};

template <class T, class NodeType> class const_tree_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef const T value_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef const NodeType *node_pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

  private:
    // * Private attributes
    node_pointer _node_ptr;
    node_pointer _bst_root;
    node_pointer _sentinel;

  public:
    // * Constructors and destructors
    const_tree_iterator(void) : _node_ptr(NULL), _bst_root(NULL), _sentinel(NULL)
    {
    }
    const_tree_iterator(node_pointer ptr, node_pointer bst_root, node_pointer sentinel)
        : _node_ptr(ptr), _bst_root(bst_root), _sentinel(sentinel)
    {
    }

    const_tree_iterator(const const_tree_iterator &old)
        : _node_ptr(old.base()), _bst_root(old.bst_root()), _sentinel(old.sentinel())
    {
    }

    const_tree_iterator(const tree_iterator<T, NodeType> &old)
        : _node_ptr(old.base()), _bst_root(old.bst_root()), _sentinel(old.sentinel())
    {
    }

    const_tree_iterator &operator=(const const_tree_iterator &rhs)
    {
        _node_ptr = rhs.base();
        _bst_root = rhs.bst_root();
        _sentinel = rhs.sentinel();
        return *this;
    }

    ~const_tree_iterator(void)
    {
    }

    node_pointer base(void) const
    {
        return _node_ptr;
    }

    node_pointer bst_root(void) const
    {
        return _bst_root;
    }

    node_pointer sentinel(void) const
    {
        return _sentinel;
    }

    // * Iterator traversal
    const_tree_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then incrementing it should give
        // you ? the first element.
        if (_node_ptr == _sentinel)
        {
            // ? Get the first element of the map
            _node_ptr = ft::min_node(_bst_root);
            return *this;
        }
        _node_ptr = ft::successor_node(_node_ptr);
        if (_node_ptr == NULL)
        {
            _node_ptr = _sentinel;
        }
        return *this;
    }
    const_tree_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one in front of the first element then decrementing it should
        // give ? you the last element.
        if (_node_ptr == _sentinel)
        {
            // ? Get the last element of the map
            _node_ptr = ft::max_node(_bst_root);
            return *this;
        }
        _node_ptr = ft::predecessor_node(_node_ptr);
        if (_node_ptr == NULL)
        {
            _node_ptr = _sentinel;
        }
        return *this;
    }

    const_tree_iterator operator++(int)   // post-increment
    {
        const_tree_iterator<T, NodeType> temp = *this;
        ++(*this);
        return temp;
    }
    const_tree_iterator operator--(int)   // post-decrement
    {
        const_tree_iterator<T, NodeType> temp = *this;
        --(*this);
        return temp;
    }

    // * Iterator comparison
    template <class It> bool operator==(const It &rhs) const
    {
        return _node_ptr == rhs.base();
    }
    template <class It> bool operator!=(const It &rhs) const
    {
        return _node_ptr != rhs.base();
    }

    // * Iterator access
    reference operator*(void) const
    {
        return _node_ptr->data;
    }
    pointer operator->(void) const
    {
        return &_node_ptr->data;
    }
};
}   // namespace ft

#endif
