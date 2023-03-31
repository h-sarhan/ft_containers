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
template <class T, class NodeType, class Tree> class tree_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef NodeType *node_pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
    Tree *bst;

  private:
    // * Private attributes
    node_pointer _node_ptr;


  public:
    // * Constructors and destructors
    tree_iterator(void) :  bst(NULL), _node_ptr(NULL)
    {
    }

    tree_iterator(node_pointer ptr, Tree *bst) :  bst(bst), _node_ptr(ptr)
    {
    }

    template <class T2>
    tree_iterator(const tree_iterator<T2, NodeType, Tree> &old)
        :  bst(old.bst), _node_ptr(old.base())
    {
    }

    template <class T2> tree_iterator &operator=(const tree_iterator<T2, NodeType, Tree> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _node_ptr = rhs._node_ptr;
        bst = rhs.bst;
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

    // * Iterator traversal
    tree_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then incrementing it should give
        // you ? the first element.
        if (_node_ptr == bst->sentinel)
        {
            // ? Get the first element of the map
            _node_ptr = bst->min_node(bst->root);
            return *this;
        }
        _node_ptr = bst->successor_node(_node_ptr);
        if (_node_ptr == NULL)
        {
            _node_ptr = bst->sentinel;
        }
        return *this;
    }

    tree_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one in front of the first element then decrementing it should
        // give ? you the last element.
        if (_node_ptr == bst->sentinel)
        {
            // ? Get the last element of the map
            _node_ptr = bst->max_node(bst->root);
            return *this;
        }
        _node_ptr = bst->predecessor_node(_node_ptr);
        if (_node_ptr == NULL)
        {
            _node_ptr = bst->sentinel;
        }
        return *this;
    }

    tree_iterator operator++(int)   // post-increment
    {
        tree_iterator<T, NodeType, Tree> temp = *this;
        ++(*this);
        return temp;
    }

    tree_iterator operator--(int)   // post-decrement
    {
        tree_iterator<T, NodeType, Tree> temp = *this;
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

template <class T, class NodeType, class Tree> class const_tree_iterator
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
    const Tree *_bst;

  public:
    // * Constructors and destructors
    const_tree_iterator(void) : _node_ptr(NULL), _bst(NULL)
    {
    }
    const_tree_iterator(node_pointer ptr, const Tree *bst)
        : _node_ptr(ptr), _bst(bst)
    {
    }

    const_tree_iterator(const const_tree_iterator &old)
        : _node_ptr(old.base()), _bst(old._bst)
    {
    }

    const_tree_iterator(const tree_iterator<T, NodeType, Tree> &old)
        : _node_ptr(old.base()), _bst(old.bst)
    {
    }

    const_tree_iterator &operator=(const const_tree_iterator &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _node_ptr = rhs._node_ptr;
        _bst = rhs._bst;
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
        if (_node_ptr == _bst->sentinel)
        {
            // ? Get the first element of the map
            _node_ptr = _bst->min_node(_bst->root);
            return *this;
        }
        _node_ptr = _bst->successor_node(_node_ptr);
        if (_node_ptr == NULL)
        {
            _node_ptr = _bst->sentinel;
        }
        return *this;
    }
    const_tree_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one in front of the first element then decrementing it should
        // give ? you the last element.
        if (_node_ptr == _bst->sentinel)
        {
            // ? Get the last element of the map
            _node_ptr = _bst->max_node(_bst->root);
            return *this;
        }
        _node_ptr = _bst->predecessor_node(_node_ptr);
        if (_node_ptr == NULL)
        {
            _node_ptr = _bst->sentinel;
        }
        return *this;
    }

    const_tree_iterator operator++(int)   // post-increment
    {
        const_tree_iterator<T, NodeType, Tree> temp = *this;
        ++(*this);
        return temp;
    }
    const_tree_iterator operator--(int)   // post-decrement
    {
        const_tree_iterator<T, NodeType, Tree> temp = *this;
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
};
}   // namespace ft

#endif
