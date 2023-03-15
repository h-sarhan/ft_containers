/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                :+:      :+:    :+:   */
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
template <class T, class NodeType> class map_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef NodeType *node_pointer;
    typedef bidirectional_iterator_tag iterator_category;

  private:
    // * Private attributes
    node_pointer _node_ptr;
    node_pointer _bst_root;
    node_pointer _sentinel;

  public:
    // * Constructors and destructors
    map_iterator(void);
    map_iterator(node_pointer ptr, node_pointer bst_root, node_pointer sentinel);

    template <class T2> map_iterator(const map_iterator<T2, NodeType> &old);
    template <class T2> map_iterator &operator=(const map_iterator<T2, NodeType> &rhs);
    ~map_iterator(void);

    node_pointer base(void) const;
    node_pointer bst_root(void) const;
    node_pointer sentinel(void) const;

    // * Iterator traversal
    map_iterator &operator++(void);   // pre-increment
    map_iterator &operator--(void);   // pre-decrement
    map_iterator operator++(int);     // post-increment
    map_iterator operator--(int);     // post-decrement

    // * Iterator comparison
    template <class It> bool operator==(const It &rhs) const;
    template <class It> bool operator!=(const It &rhs) const;

    // * Iterator access
    reference operator*(void);
    pointer operator->(void);
    reference operator*(void) const;
    pointer operator->(void) const;
};

template <class T, class NodeType> class const_map_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef NodeType *node_pointer;
    typedef bidirectional_iterator_tag iterator_category;

  private:
    // * Private attributes
    node_pointer _node_ptr;
    node_pointer _bst_root;
    node_pointer _sentinel;

  public:
    // * Constructors and destructors
    const_map_iterator(void);
    const_map_iterator(node_pointer ptr, node_pointer bst_root, node_pointer sentinel);

    const_map_iterator(const const_map_iterator &old);
    const_map_iterator(const map_iterator<T, NodeType> &old);
    const_map_iterator &operator=(const const_map_iterator &rhs);
    ~const_map_iterator(void);

    node_pointer base(void) const;
    node_pointer bst_root(void) const;
    node_pointer sentinel(void) const;

    // * Iterator traversal
    const_map_iterator &operator++(void);   // pre-increment
    const_map_iterator &operator--(void);   // pre-decrement
    const_map_iterator operator++(int);     // post-increment
    const_map_iterator operator--(int);     // post-decrement

    // * Iterator comparison
    template <class It> bool operator==(const It &rhs) const;
    template <class It> bool operator!=(const It &rhs) const;

    // * Iterator access
    reference operator*(void);
    pointer operator->(void);
    reference operator*(void) const;
    pointer operator->(void) const;
};
}   // namespace ft

template <class T, class NodeType>
ft::map_iterator<T, NodeType>::map_iterator(void)
    : _node_ptr(NULL), _bst_root(NULL), _sentinel(NULL)
{
}

template <class T, class NodeType>
ft::map_iterator<T, NodeType>::map_iterator(node_pointer ptr, node_pointer bst_root,
                                            node_pointer sentinel)
    : _node_ptr(ptr), _bst_root(bst_root), _sentinel(sentinel)
{
}

template <class T, class NodeType>
template <class T2>
ft::map_iterator<T, NodeType>::map_iterator(const map_iterator<T2, NodeType> &old)
    : _node_ptr(old.base()), _bst_root(old.bst_root()), _sentinel(old.sentinel())
{
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::node_pointer ft::map_iterator<T, NodeType>::base(void) const
{
    return _node_ptr;
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::node_pointer ft::map_iterator<T, NodeType>::bst_root(
    void) const
{
    return _bst_root;
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::node_pointer ft::map_iterator<T, NodeType>::sentinel(
    void) const
{
    return _sentinel;
}

template <class T, class NodeType>
template <class T2>
ft::map_iterator<T, NodeType> &ft::map_iterator<T, NodeType>::operator=(
    const map_iterator<T2, NodeType> &rhs)
{
    _node_ptr = rhs.base();
    _bst_root = rhs.bst_root();
    _sentinel = rhs.sentinel();
    return *this;
}

template <class T, class NodeType> ft::map_iterator<T, NodeType>::~map_iterator<T, NodeType>(void)
{
    // ??
}

template <class T, class NodeType>
ft::map_iterator<T, NodeType> &ft::map_iterator<T, NodeType>::operator++(void)
{
    // ? If the passed node was one behind the first element then incrementing it should give you
    // ? the first element.
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

template <class T, class NodeType>
ft::map_iterator<T, NodeType> &ft::map_iterator<T, NodeType>::operator--(void)
{
    // ? If the passed node was one in front of the first element then decrementing it should give
    // ? you the last element.
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

template <class T, class NodeType>
ft::map_iterator<T, NodeType> ft::map_iterator<T, NodeType>::operator++(int)
{
    map_iterator<T, NodeType> temp = *this;
    ++(*this);
    return temp;
}

template <class T, class NodeType>
ft::map_iterator<T, NodeType> ft::map_iterator<T, NodeType>::operator--(int)
{
    map_iterator<T, NodeType> temp = *this;
    --(*this);
    return temp;
}

template <class T, class NodeType>
template <class It>
bool ft::map_iterator<T, NodeType>::operator==(const It &rhs) const
{
    return _node_ptr == rhs.base();
}

template <class T, class NodeType>
template <class It>
bool ft::map_iterator<T, NodeType>::operator!=(const It &rhs) const
{
    return _node_ptr != rhs.base();
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::value_type &ft::map_iterator<T, NodeType>::operator*(void)
{
    return _node_ptr->data;
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::value_type &ft::map_iterator<T, NodeType>::operator*(
    void) const
{
    return _node_ptr->data;
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::value_type *ft::map_iterator<T, NodeType>::operator->(void)
{
    return &_node_ptr->data;
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::pointer ft::map_iterator<T, NodeType>::operator->(
    void) const
{
    return &_node_ptr->data;
}

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType>::const_map_iterator(void)
    : _node_ptr(NULL), _bst_root(NULL), _sentinel(NULL)
{
}

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType>::const_map_iterator(node_pointer ptr, node_pointer bst_root,
                                                        node_pointer sentinel)
    : _node_ptr(ptr), _bst_root(bst_root), _sentinel(sentinel)
{
}

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType>::const_map_iterator(const const_map_iterator &old)
    : _node_ptr(old.base()), _bst_root(old.bst_root()), _sentinel(old.sentinel())
{
}

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType>::const_map_iterator(const map_iterator<T, NodeType> &old)
    : _node_ptr(old.base()), _bst_root(old.bst_root()), _sentinel(old.sentinel())
{
}

template <class T, class NodeType>
typename ft::const_map_iterator<T, NodeType>::node_pointer ft::const_map_iterator<
    T, NodeType>::base(void) const
{
    return _node_ptr;
}

template <class T, class NodeType>
typename ft::const_map_iterator<T, NodeType>::node_pointer ft::const_map_iterator<
    T, NodeType>::bst_root(void) const
{
    return _bst_root;
}

template <class T, class NodeType>
typename ft::const_map_iterator<T, NodeType>::node_pointer ft::const_map_iterator<
    T, NodeType>::sentinel(void) const
{
    return _sentinel;
}

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType> &ft::const_map_iterator<T, NodeType>::operator=(
    const const_map_iterator &rhs)
{
    _node_ptr = rhs.base();
    _bst_root = rhs.bst_root();
    _sentinel = rhs.sentinel();
    return *this;
}

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType>::~const_map_iterator<T, NodeType>(void)
{
    // ??
}

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType> &ft::const_map_iterator<T, NodeType>::operator++(void)
{
    // ? If the passed node was one behind the first element then incrementing it should give you
    // ? the first element.
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

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType> &ft::const_map_iterator<T, NodeType>::operator--(void)
{
    // ? If the passed node was one in front of the first element then decrementing it should give
    // ? you the last element.
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

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType> ft::const_map_iterator<T, NodeType>::operator++(int)
{
    const_map_iterator<T, NodeType> temp = *this;
    ++(*this);
    return temp;
}

template <class T, class NodeType>
ft::const_map_iterator<T, NodeType> ft::const_map_iterator<T, NodeType>::operator--(int)
{
    const_map_iterator<T, NodeType> temp = *this;
    --(*this);
    return temp;
}

template <class T, class NodeType>
template <class It>
bool ft::const_map_iterator<T, NodeType>::operator==(const It &rhs) const
{
    return _node_ptr == rhs.base();
}

template <class T, class NodeType>
template <class It>
bool ft::const_map_iterator<T, NodeType>::operator!=(const It &rhs) const
{
    return _node_ptr != rhs.base();
}

template <class T, class NodeType>
typename ft::const_map_iterator<T, NodeType>::reference ft::const_map_iterator<
    T, NodeType>::operator*(void)
{
    return _node_ptr->data;
}

template <class T, class NodeType>
typename ft::const_map_iterator<T, NodeType>::reference ft::const_map_iterator<
    T, NodeType>::operator*(void) const
{
    return _node_ptr->data;
}

template <class T, class NodeType>
typename ft::const_map_iterator<T, NodeType>::pointer ft::const_map_iterator<
    T, NodeType>::operator->(void)
{
    return &_node_ptr->data;
}

template <class T, class NodeType>
typename ft::const_map_iterator<T, NodeType>::pointer ft::const_map_iterator<
    T, NodeType>::operator->(void) const
{
    return &_node_ptr->data;
}

#endif
