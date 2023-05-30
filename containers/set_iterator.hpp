/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:56:58 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/30 08:17:29 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_ITERATOR_HPP
#define SET_ITERATOR_HPP

#include "set_tree.hpp"
#include <cstddef>
#include <iterator>

namespace ft
{
template <class SetTree>
class const_set_iterator;
template <class SetTree> class set_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef typename SetTree::node_data value_type;
    typedef value_type *pointer;
    typedef value_type &reference;
    typedef typename SetTree::node_type node_type;
    typedef node_type *node_pointer;
    typedef SetTree tree_type;
    typedef std::bidirectional_iterator_tag iterator_category;

  private:
    node_pointer _ptr;
    const tree_type *_tree;

  public:
    set_iterator(void) : _ptr(NULL), _tree(NULL)
    {
    }

    set_iterator(node_pointer ptr, const tree_type *tree) : _ptr(ptr), _tree(tree)
    {
    }

    template <class T2>
    set_iterator(const set_iterator<T2> &old) : _ptr(old._ptr), _tree(old._tree)
    {
    }


    set_iterator(const const_set_iterator<SetTree> &old) : _ptr(old.base()), _tree(old.tree())
    {
    }

    template <class T2> set_iterator &operator=(const set_iterator<T2> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _ptr = rhs._ptr;
        _tree = rhs._tree;
        return *this;
    }

    ~set_iterator(void)
    {
        // ??
    }

    node_pointer base(void) const
    {
        return _ptr;
    }

    // * Iterator traversal
    set_iterator &operator++(void)   // pre-increment
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

    set_iterator &operator--(void)   // pre-decrement
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

    set_iterator operator++(int)   // post-increment
    {
        set_iterator temp = *this;
        ++(*this);
        return temp;
    }

    set_iterator operator--(int)   // post-decrement
    {
        set_iterator temp = *this;
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

    const tree_type *tree(void) const
    {
        return _tree;
    }
};

template <class SetTree> class const_set_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef typename SetTree::node_data value_type;
    typedef value_type *pointer;
    typedef value_type &reference;
    typedef typename SetTree::node_type node_type;
    typedef node_type *node_pointer;
    typedef SetTree tree_type;
    typedef std::bidirectional_iterator_tag iterator_category;

  private:
    node_pointer _ptr;
    const tree_type *_tree;

  public:
    const_set_iterator(void) : _ptr(NULL), _tree(NULL)
    {
    }

    const_set_iterator(node_pointer ptr, const tree_type *tree) : _ptr(ptr), _tree(tree)
    {
    }

    template <class T2>
    const_set_iterator(const set_iterator<T2> &old) : _ptr(old.base()), _tree(old.tree())
    {
    }

    template <class T2> const_set_iterator &operator=(const const_set_iterator<T2> &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        _ptr = rhs._ptr;
        _tree = rhs._tree;
        return *this;
    }

    ~const_set_iterator(void)
    {
        // ??
    }

    node_pointer base(void) const
    {
        return _ptr;
    }

    // * Iterator traversal
    const_set_iterator &operator++(void)   // pre-increment
    {
        // ? If the passed node was one behind the first element then
        // incrementing it should give ? you the first element.
        if (_ptr == NULL)
        {
            // ? Get the first element of the set
            _ptr = _tree->minimum_node(_tree->root);
            return *this;
        }
        _ptr = _tree->next_node(_ptr);
        return *this;
    }

    const_set_iterator &operator--(void)   // pre-decrement
    {
        // ? If the passed node was one after the first element then
        // incrementing it should give ? you the last element.
        if (_ptr == NULL)
        {
            // ? Get the last element of the set
            _ptr = _tree->maximum_node(_tree->root);
            return *this;
        }
        _ptr = _tree->previous_node(_ptr);
        return *this;
    }

    const_set_iterator operator++(int)   // post-increment
    {
        const_set_iterator temp = *this;
        ++(*this);
        return temp;
    }

    const_set_iterator operator--(int)   // post-decrement
    {
        const_set_iterator temp = *this;
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

    reference operator*(void) const
    {
        return _ptr->data;
    }
    pointer operator->(void) const
    {
        return &_ptr->data;
    }
    const tree_type *tree(void) const
    {
        return _tree;
    }
};
}   // namespace ft

#endif
