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
#include "node_traversal.hpp"
#include <cstddef>

namespace ft
{
template <class T, class NodeType, class Compare> class tree_iterator
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
    node_pointer *_root;
    node_pointer _node_ptr;
    Compare _comp;

  public:
    // * Constructors and destructors
    tree_iterator(void) : _root(NULL), _node_ptr(NULL), _comp()
    {
    }

    tree_iterator(node_pointer ptr, node_pointer *root, const Compare &comp)
        : _root(root), _node_ptr(ptr), _comp(comp)
    {
    }

    template <class T2>
    tree_iterator(const tree_iterator<T2, NodeType, Compare> &old)
        : _root(old._root), _node_ptr(old._node_ptr), _comp(old._comp)
    {
    }

    template <class T2> tree_iterator &operator=(const tree_iterator<T2, NodeType, Compare> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _node_ptr = rhs._node_ptr;
        _root = rhs._root;
        _comp = rhs._comp;
        return *this;
    }

    ~tree_iterator(void)
    {
        // ??
    }

    node_pointer *root(void) const
    {
        return _root;
    }

    Compare comp(void) const
    {
        return _comp;
    }

    node_pointer base(void) const
    {
        return _node_ptr;
    }

    // * Iterator traversal
    tree_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then incrementing it should give
        // you ? the first element.
        if (_node_ptr == NULL)
        {
            // ? Get the first element of the map
            _node_ptr = min_node(*_root);
            return *this;
        }
        _node_ptr = successor_node(*_root, _node_ptr, _comp);
        return *this;
    }

    tree_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one in front of the first element then decrementing it should
        // give ? you the last element.
        if (_node_ptr == NULL)
        {
            // ? Get the last element of the map
            _node_ptr = max_node(*_root);
            return *this;
        }
        _node_ptr = predecessor_node(*_root, _node_ptr, _comp);
        return *this;
    }

    tree_iterator operator++(int)   // post-increment
    {
        tree_iterator<T, NodeType, Compare> temp = *this;
        ++(*this);
        return temp;
    }

    tree_iterator operator--(int)   // post-decrement
    {
        tree_iterator<T, NodeType, Compare> temp = *this;
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
        return *_node_ptr->data;
    }

    pointer operator->(void)
    {
        return _node_ptr->data;
    }
    reference operator*(void) const
    {
        return *_node_ptr->data;
    }
    pointer operator->(void) const
    {
        return _node_ptr->data;
    }
};

template <class T, class NodeType, class Compare> class const_tree_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef const T value_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef NodeType *node_pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

  private:
    // * Private attributes
    node_pointer _node_ptr;
    const node_pointer *_root;
    Compare _comp;

  public:
    // * Constructors and destructors
    const_tree_iterator(void) : _node_ptr(NULL), _root(NULL), _comp()
    {
    }
    const_tree_iterator(node_pointer ptr, const node_pointer *root, const Compare &comp)
        : _node_ptr(ptr), _root(root), _comp(comp)
    {
    }

    const_tree_iterator(const const_tree_iterator &old)
        : _node_ptr(old.base()), _root(old.root()), _comp(old.comp())
    {
    }

    const_tree_iterator(const tree_iterator<T, NodeType, Compare> &old)
        : _node_ptr(old.base()), _root(old.root()), _comp(old.comp())
    {
    }

    const_tree_iterator &operator=(const const_tree_iterator &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _node_ptr = rhs._node_ptr;
        _root = rhs._root;
        _comp = rhs._comp;
        return *this;
    }

    ~const_tree_iterator(void)
    {
    }

    node_pointer base(void) const
    {
        return _node_ptr;
    }

    // * Iterator traversal
    const_tree_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then incrementing it should give
        // you ? the first element.
        if (_node_ptr == NULL)
        {
            // ? Get the first element of the map
            _node_ptr = min_node(*_root);
            return *this;
        }
        _node_ptr = successor_node(*_root, _node_ptr, _comp);
        return *this;
    }
    const_tree_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one in front of the first element then decrementing it should
        // give ? you the last element.
        if (_node_ptr == NULL)
        {
            // ? Get the last element of the map
            _node_ptr = max_node(*_root);
            return *this;
        }
        _node_ptr = predecessor_node(*_root, _node_ptr, _comp);
        return *this;
    }

    const_tree_iterator operator++(int)   // post-increment
    {
        const_tree_iterator<T, NodeType, Compare> temp = *this;
        ++(*this);
        return temp;
    }
    const_tree_iterator operator--(int)   // post-decrement
    {
        const_tree_iterator<T, NodeType, Compare> temp = *this;
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
        return *_node_ptr->data;
    }
    pointer operator->(void) const
    {
        return _node_ptr->data;
    }

    const node_pointer *root(void) const
    {
        return _root;
    }

    Compare comp(void) const
    {
        return _comp;
    }
};
}   // namespace ft

#endif
