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

  public:
    // * Constructors and destructors
    map_iterator(void);
    map_iterator(node_pointer ptr);

    template <class T2> map_iterator &operator=(const map_iterator<T2, NodeType> &rhs);
    ~map_iterator(void);

    template <class T2> map_iterator(const map_iterator<T2, NodeType> &old);

    node_pointer base(void) const;

    // * Iterator traversal
    map_iterator &operator++(void);   // pre-increment
    map_iterator &operator--(void);   // pre-decrement
    map_iterator operator++(int);     // post-increment
    map_iterator operator--(int);     // post-decrement

    // * Iterator comparison
    template <class T2> bool operator==(const map_iterator<T2, NodeType> &rhs) const;
    template <class T2> bool operator!=(const map_iterator<T2, NodeType> &rhs) const;

    // * Iterator access
    reference operator*(void);
    pointer operator->(void);
};
};   // namespace ft

template <class T, class NodeType> ft::map_iterator<T, NodeType>::map_iterator(void) : _node_ptr(0)
{
}

template <class T, class NodeType>
ft::map_iterator<T, NodeType>::map_iterator(node_pointer ptr) : _node_ptr(ptr)
{
}

template <class T, class NodeType>
template <class T2>
ft::map_iterator<T, NodeType>::map_iterator(const map_iterator<T2, NodeType> &old)
    : _node_ptr(old.base())
{
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::node_pointer ft::map_iterator<T, NodeType>::base(void) const
{
    return _node_ptr;
}

template <class T, class NodeType>
template <class T2>
ft::map_iterator<T, NodeType> &ft::map_iterator<T, NodeType>::operator=(
    const map_iterator<T2, NodeType> &rhs)
{
    _node_ptr = rhs.base();
    return *this;
}

template <class T, class NodeType> ft::map_iterator<T, NodeType>::~map_iterator<T, NodeType>(void)
{
    // ??
}

template <class T, class NodeType>
ft::map_iterator<T, NodeType> &ft::map_iterator<T, NodeType>::operator++(void)
{
    // * This will find the successor of the tree
    _node_ptr = ft::successor_node(_node_ptr);
    return *this;
}

template <class T, class NodeType>
ft::map_iterator<T, NodeType> &ft::map_iterator<T, NodeType>::operator--(void)
{
    _node_ptr = ft::predecessor_node(_node_ptr);
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
template <class T2>
bool ft::map_iterator<T, NodeType>::operator==(const map_iterator<T2, NodeType> &rhs) const
{
    return _node_ptr == rhs.base();
}

template <class T, class NodeType>
template <class T2>
bool ft::map_iterator<T, NodeType>::operator!=(const map_iterator<T2, NodeType> &rhs) const
{
    return _node_ptr != rhs.base();
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::value_type &ft::map_iterator<T, NodeType>::operator*(void)
{
    return (*_node_ptr).data;
}

template <class T, class NodeType>
typename ft::map_iterator<T, NodeType>::value_type *ft::map_iterator<T, NodeType>::operator->(void)
{
    return &_node_ptr->data;
}

#endif
