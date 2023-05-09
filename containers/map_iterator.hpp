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

#include "iterator_traits.hpp"
#include "tree.hpp"
#include <cstddef>

namespace ft
{
template <class NodeType, class T> class map_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef value_type *pointer;
    typedef value_type &reference;
    typedef NodeType node_type;
    typedef node_type *node_pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

  private:
    // * Private attributes
    node_pointer _node_ptr;
    node_pointer _root;

  public:
    // * Constructors and destructors
    map_iterator(void)
    {
    }

    map_iterator(node_pointer ptr, node_pointer root) : _node_ptr(ptr), _root(root)
    {
    }

    template <class T2> map_iterator(const map_iterator<NodeType, T2> &old)
    {
        (void) old;
    }

    template <class T2> map_iterator &operator=(const map_iterator<NodeType, T2> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        return *this;
    }

    ~map_iterator(void)
    {
        // ??
    }

    node_pointer    base(void) const
    {
        return _node_ptr;
    }


    // * Iterator traversal
    map_iterator &operator++(void)   // pre-increment
    {
        return *this;
    }

    map_iterator &operator--(void)   // pre-decrement
    {
        return *this;
    }

    map_iterator operator++(int)   // post-increment
    {
        map_iterator temp = *this;
        ++(*this);
        return temp;
    }

    map_iterator operator--(int)   // post-decrement
    {
        map_iterator temp = *this;
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

}   // namespace ft

#endif
