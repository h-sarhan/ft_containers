/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:56:58 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/30 01:01:58 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "map_tree.hpp"
#include <cstddef>
#include <iterator>

namespace ft
{

// ! IMPLEMENT THESE
template <class MapTree> class map_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef typename MapTree::node_data value_type;
    typedef value_type *pointer;
    typedef value_type &reference;
    typedef typename MapTree::node_type node_type;
    typedef node_type *node_pointer;
    typedef MapTree tree_type;
    typedef std::bidirectional_iterator_tag iterator_category;

  private:
    node_pointer _ptr;
    const tree_type *_tree;

  public:
    map_iterator(void) : _ptr(NULL), _tree(NULL)
    {
    }

    map_iterator(node_pointer ptr, const tree_type *tree) : _ptr(ptr), _tree(tree)
    {
    }

    template <class T2>
    map_iterator(const map_iterator<T2> &old) : _ptr(old._ptr), _tree(old._tree)
    {
    }

    template <class T2> map_iterator &operator=(const map_iterator<T2> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _ptr = rhs._ptr;
        _tree = rhs._tree;
        return *this;
    }

    ~map_iterator(void)
    {
        // ??
    }

    node_pointer base(void) const
    {
        return _ptr;
    }

    // * Iterator traversal
    map_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then
        // incrementing it should give ? you the first element.
        if (_ptr == NULL)
        {
            // ? Get the first element of the map
            _ptr = _tree->minimum_node(_tree->root);
            return *this;
        }
        _ptr = _tree->next_node(_ptr);
        return *this;
    }

    map_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one after the first element then
        // incrementing it should give ? you the last element.
        if (_ptr == NULL)
        {
            // ? Get the last element of the map
            _ptr = _tree->maximum_node(_tree->root);
            return *this;
        }
        _ptr = _tree->previous_node(_ptr);
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
        return _ptr == rhs.base();
    }
    template <class It> bool operator!=(const It &rhs) const
    {
        return _ptr != rhs.base();
    }

    // * Iterator access
    reference operator*(void)
    {
        return _ptr->data;
    }

    pointer operator->(void)
    {
        return &_ptr->data;
    }
    reference operator*(void) const
    {
        return _ptr->data;
    }
    pointer operator->(void) const
    {
        return &_ptr->data;
    }
};
}   // namespace ft

#endif
