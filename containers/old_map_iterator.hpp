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
#include "map_tree.hpp"
#include <cstddef>

namespace ft
{
template <class Tree> class map_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef typename Tree::node_type::data_type value_type;
    typedef value_type *pointer;
    typedef value_type &reference;
    typedef typename Tree::node_type node_type;
    typedef node_type *node_pointer;
    typedef Tree tree_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef typename Tree::compare_type compare_type;

  private:
    // * Private attributes
    node_pointer _node_ptr;
    tree_type *_tree;
    compare_type _comp;

  public:
    // * Constructors and destructors
    map_iterator(void) : _node_ptr(NULL), _tree(NULL), _comp()
    {
    }

    map_iterator(node_pointer ptr, tree_type *tree) : _node_ptr(ptr), _tree(tree), _comp()
    {
    }

    template <class T2>
    map_iterator(const map_iterator<T2> &old)
        : _node_ptr(old._node_ptr), _tree(old._tree), _comp(old._comp)
    {
    }

    template <class T2> map_iterator &operator=(const map_iterator<T2> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _node_ptr = rhs._node_ptr;
        _tree = rhs._tree;
        _comp = rhs._comp;
        return *this;
    }

    ~map_iterator(void)
    {
        // ??
    }

    node_pointer base(void) const
    {
        return _node_ptr;
    }

    // * Iterator traversal
    map_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then incrementing it should give
        // ? you the first element.
        if (_node_ptr == NULL)
        {
            // ? Get the first element of the map
            // _node_ptr = min_node(get_root());
            return *this;
        }
        _node_ptr = successor_node(_node_ptr, _tree->root, _comp);
        return *this;
    }

    map_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one after the first element then incrementing it should give
        // ? you the last element.
        if (_node_ptr == NULL)
        {
            // ? Get the last element of the map
            // _node_ptr = max_node(get_root());
            return *this;
        }
        _node_ptr = ft::predecessor_node(_node_ptr, _tree->root, _comp);
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

template <class Tree> class const_map_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef typename Tree::node_type::data_type value_type;
    typedef const value_type *pointer;
    typedef const value_type &reference;
    typedef typename Tree::node_type node_type;
    typedef node_type *node_pointer;
    typedef const Tree tree_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef typename Tree::compare_type compare_type;

  private:
    // * Private attributes
    node_pointer _node_ptr;
    tree_type *_tree;
    compare_type _comp;

  public:
    // * Constructors and destructors
    const_map_iterator(void) : _node_ptr(NULL), _tree(NULL), _comp()
    {
    }

    const_map_iterator(node_pointer ptr, tree_type *tree) : _node_ptr(ptr), _tree(tree), _comp()
    {
    }

    const_map_iterator &operator=(const const_map_iterator &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _node_ptr = rhs._node_ptr;
        _tree = rhs._tree;
        _comp = rhs._comp;
        return *this;
    }

    ~const_map_iterator(void)
    {
        // ??
    }

    node_pointer base(void) const
    {
        return _node_ptr;
    }

    // * Iterator traversal
    const_map_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then incrementing it should give
        // ? you the first element.
        if (_node_ptr == NULL)
        {
            // ? Get the first element of the map
            // _node_ptr = min_node(get_root());
            return *this;
        }
        _node_ptr = successor_node(_node_ptr, _tree->root, _comp);
        return *this;
    }

    const_map_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one after the first element then incrementing it should give
        // ? you the last element.
        if (_node_ptr == NULL)
        {
            // ? Get the last element of the map
            // _node_ptr = max_node(get_root());
            return *this;
        }
        _node_ptr = ft::predecessor_node(_node_ptr, _tree->root, _comp);
        return *this;
    }

    const_map_iterator operator++(int)   // post-increment
    {
        const_map_iterator temp = *this;
        ++(*this);
        return temp;
    }

    const_map_iterator operator--(int)   // post-decrement
    {
        const_map_iterator temp = *this;
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