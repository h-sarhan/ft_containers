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
// NodeType is going to be an alias of node
template <class NodeType> class map_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef NodeType value_type;
    typedef NodeType *pointer;
    typedef NodeType &reference;
    typedef bidirectional_iterator_tag iterator_category;

  private:
    // * Private attributes
    pointer _node_ptr;

  public:
    // * Constructors and destructors
    map_iterator(void);
    map_iterator(pointer ptr);

    template <class OtherNodeType> map_iterator &operator=(const map_iterator<OtherNodeType> &rhs);
    ~map_iterator(void);

    template <class OtherNodeType> map_iterator(const map_iterator<OtherNodeType> &old);

    pointer base(void) const;

    // * Iterator traversal
    map_iterator &operator++(void);   // pre-increment
    map_iterator &operator--(void);   // pre-decrement
    map_iterator operator++(int);     // post-increment
    map_iterator operator--(int);     // post-decrement

    // * Iterator comparison
    template <class OtherNodeType> bool operator==(const map_iterator<OtherNodeType> &rhs) const;
    template <class OtherNodeType> bool operator!=(const map_iterator<OtherNodeType> &rhs) const;

    // * Iterator access
    reference operator*(void);
    pointer operator->(void);
};
}   // namespace ft

template <class NodeType> ft::map_iterator<NodeType>::map_iterator(void) : _node_ptr(0)
{
}

template <class NodeType>
ft::map_iterator<NodeType>::map_iterator(pointer ptr) : _node_ptr(ptr)
{
}

template <class NodeType>
template <class OtherNodeType>
ft::map_iterator<NodeType>::map_iterator(const map_iterator<OtherNodeType> &old)
    : _node_ptr(old.base())
{
}

template <class NodeType>
typename ft::map_iterator<NodeType>::pointer ft::map_iterator<NodeType>::base(void) const
{
    return _node_ptr;
}

template <class NodeType>
template <class OtherNodeType>
ft::map_iterator<NodeType> &ft::map_iterator<NodeType>::operator=(
    const map_iterator<OtherNodeType> &rhs)
{
    _node_ptr = rhs.base();
    return *this;
}

template <class NodeType> ft::map_iterator<NodeType>::~map_iterator<NodeType>(void)
{
    // ??
}

template <class NodeType> ft::map_iterator<NodeType> &ft::map_iterator<NodeType>::operator++(void)
{
    // * This will find the successor of the tree
    _node_ptr = ft::successor_node(_node_ptr);
    return *this;
}

template <class NodeType> ft::map_iterator<NodeType> &ft::map_iterator<NodeType>::operator--(void)
{
    _node_ptr = ft::predecessor_node(_node_ptr);
    return *this;
}

template <class NodeType> ft::map_iterator<NodeType> ft::map_iterator<NodeType>::operator++(int)
{
    map_iterator<NodeType> temp = *this;
    ++(*this);
    return temp;
}

template <class NodeType> ft::map_iterator<NodeType> ft::map_iterator<NodeType>::operator--(int)
{
    map_iterator<NodeType> temp = *this;
    --(*this);
    return temp;
}

template <class NodeType>
template <class OtherNodeType>
bool ft::map_iterator<NodeType>::operator==(const map_iterator<OtherNodeType> &rhs) const
{
    return _node_ptr == rhs.base();
}

template <class NodeType>
template <class OtherNodeType>
bool ft::map_iterator<NodeType>::operator!=(const map_iterator<OtherNodeType> &rhs) const
{
    return _node_ptr != rhs.base();
}

template <class NodeType>
typename ft::map_iterator<NodeType>::value_type &ft::map_iterator<NodeType>::operator*(void)
{
    return *_node_ptr;
}

template <class NodeType>
typename ft::map_iterator<NodeType>::value_type *ft::map_iterator<NodeType>::operator->(void)
{
    return _node_ptr;
}

#endif
