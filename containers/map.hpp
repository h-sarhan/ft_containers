/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:06:35 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/19 13:50:05 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "bst.hpp"
#include "iterator_comparison.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace ft
{
template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, T> > >
class map
{
    // ** Member types
  public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const key_type, mapped_type> value_type;
    typedef node<value_type> node_type;
    typedef size_t size_type;

    typedef Compare key_compare;
    typedef typename Alloc::template rebind<node_type>::other allocator_type;

    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;

    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

    typedef map_iterator<value_type, node_type> iterator;
    typedef const_map_iterator<value_type, node_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename iterator_traits<iterator>::difference_type difference_type;

    // ** Nested value_compare class
  public:
    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;

      protected:
        key_compare comp;
        value_compare(key_compare c) : comp(c)
        {
        }

      public:
        bool operator()(const value_type &x, const value_type &y) const
        {
            return comp(x.first, y.first);
        }
    };

    // ** Private member attributes
  private:
    key_compare _key_comp;
    value_compare _val_comp;
    allocator_type _alloc;
    bst<key_type, mapped_type, key_compare, allocator_type> _bst;
    size_type _size;
    node_type *_sentinel;

    // ** Constructors and destructors
  public:
    // * Default constructor
    explicit map(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
        : _key_comp(comp), _val_comp(comp), _alloc(alloc), _bst(NULL, comp, alloc), _size(0),
          _sentinel(_alloc.allocate(1))
    {
        _alloc.construct(_sentinel, node_type());
    }

    // * Rnage-based iterator constructor
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type())
        : _key_comp(comp), _val_comp(comp), _alloc(alloc), _bst(NULL, comp, alloc), _size(0),
          _sentinel(_alloc.allocate(1))
    {
        _alloc.construct(_sentinel, node_type());
        for (InputIterator it = first; it != last; it++)
        {
            insert(*it);
        }
    }

    // * Copy constructor
    map(const map &old)
        : _key_comp(old._key_comp), _val_comp(old._val_comp), _alloc(old._alloc),
          _bst(NULL, old._key_comp, old._alloc), _size(0), _sentinel(_alloc.allocate(1))
    {
        _alloc.construct(_sentinel, node_type());
        insert(old.begin(), old.end());
    }

    // * Copy assignment constructor
    map &operator=(const map &x)
    {
        if (&x == this)
        {
            return *this;
        }
        clear();
        _key_comp = x._key_comp;
        _val_comp = x._val_comp;
        _alloc = x._alloc;
        _alloc.destroy(_sentinel);
        _alloc.deallocate(_sentinel, 1);
        _sentinel = _alloc.allocate(1);
        _alloc.construct(_sentinel, node_type());
        _bst = bst<key_type, mapped_type, key_compare, allocator_type>(NULL, _key_comp, _alloc);
        _size = 0;
        insert(x.begin(), x.end());
        return *this;
    }

    // * Destructor
    ~map(void)
    {
        _alloc.destroy(_sentinel);
        _alloc.deallocate(_sentinel, 1);
    }

    // ** Iterator functions
    iterator begin(void)
    {
        // ! Check if this is correct behaviour with std::map on linux and mac
        if (empty())
        {
            return iterator(_sentinel, _bst.root, _sentinel);
        }
        return iterator(ft::min_node(_bst.root), _bst.root, _sentinel);
    }
    const_iterator begin(void) const
    {
        // ! Check if this is correct behaviour with std::map on linux and mac. Maybe return
        // sentinel node instead??
        if (empty())
        {
            return const_iterator(_sentinel, _bst.root, _sentinel);
        }
        return const_iterator(ft::min_node(_bst.root), _bst.root, _sentinel);
    }

    iterator end(void)
    {
        // ! Check if this is correct behaviour with std::map on linux and mac. Maybe return
        // sentinel node instead??
        if (empty())
        {
            return begin();
        }
        return iterator(_sentinel, _bst.root, _sentinel);
    }
    const_iterator end(void) const
    {
        if (empty())
        {
            return begin();
        }
        return const_iterator(_sentinel, _bst.root, _sentinel);
    }

    reverse_iterator rbegin(void)
    {
        if (empty())
        {
            // idk
        }

        return reverse_iterator(iterator(_sentinel, _bst.root, _sentinel));
    }
    const_reverse_iterator rbegin(void) const
    {
        if (empty())
        {
            // idk
        }

        return const_reverse_iterator(iterator(_sentinel, _bst.root, _sentinel));
    }

    reverse_iterator rend(void)
    {
        if (empty())
        {
            // idk
        }
        return reverse_iterator(iterator(ft::min_node(_bst.root), _bst.root, _sentinel));
    }
    const_reverse_iterator rend(void) const
    {
        if (empty())
        {
            // idk
        }
        return const_reverse_iterator(iterator(ft::min_node(_bst.root), _bst.root, _sentinel));
    }

    // ** Capacity

    // * Is the map empty?
    bool empty(void) const
    {
        return _bst.root == NULL;
    }

    // * Number of elements in map
    size_type size(void) const
    {
        return _size;
    }

    // * Max number of elements in map
    size_type max_size(void) const
    {
        return _alloc.max_size();
    }

    // ** Element access

    // * Subscript operator overload
    mapped_type &operator[](const key_type &key)
    {
        node_type *res = _bst.get(key);
        if (res == NULL)
        {
            iterator ret = insert(ft::make_pair(key, mapped_type())).first;
            return ret->second;
        }
        return res->data.second;
    }

    // ** Modifiers

    // * Single element insert
    pair<iterator, bool> insert(const value_type &val)
    {
        ft::pair<node_type *, bool> res = _bst.insert(val);

        if (res.second == true)
        {
            _size += 1;
            return ft::make_pair(iterator(res.first, _bst.root, _sentinel), true);
        }
        return ft::make_pair(iterator(res.first, _bst.root, _sentinel), false);
    }

    // * Single element insert with hint. Hint is just ignored lol!
    iterator insert(iterator hint, const value_type &val)
    {
        (void) hint;
        return insert(val).first;
    }

    // * Range-based iterator insert
    template <class InputIterator> void insert(InputIterator first, InputIterator last)
    {

        for (InputIterator it = first; it != last; it++)
        {
            insert(*it);
        }
    }

    // * Single element insert based on key
    size_type erase(const key_type &k)
    {
        node_type *to_delete = _bst.get(k);
        if (to_delete == NULL)
        {
            return 0;
        }
        _bst.delete_node(to_delete);
        _size -= 1;
        return 1;
    }

    // * Single element insert based on iterator
    void erase(iterator position)
    {
        node_type *to_delete = _bst.get(position->first);
        if (to_delete == NULL)
        {
            return;
        }
        _bst.delete_node(to_delete);
        _size -= 1;
    }

    // * Range-based iterator erase
    void erase(iterator first, iterator last)
    {
        iterator it = first;
        while (it != last)
        {
            iterator next = it;
            next++;
            erase(it);
            it = next;
        }
    }

    // * Swap two maps without invalidating iterators
    void swap(map &x)
    {
        if (this == &x)
        {
            return;
        }
        key_compare temp_key_comp = x.key_comp();
        value_compare temp_val_comp = x.value_comp();
        allocator_type temp_allocator = x.get_allocator();
        node_type *temp_bst_root = x._bst.root;
        size_type temp_size = x._size;
        node_type *temp_sentinel = x._sentinel;

        x._key_comp = _key_comp;
        x._val_comp = _val_comp;
        x._alloc = _alloc;
        x._bst.root = _bst.root;
        x._size = _size;
        x._sentinel = _sentinel;

        _key_comp = temp_key_comp;
        _val_comp = temp_val_comp;
        _alloc = temp_allocator;
        _bst.root = temp_bst_root;
        _size = temp_size;
        _sentinel = temp_sentinel;
    }

    // * Erase all elements from a map
    void clear(void)
    {
        erase(begin(), end());
    }

    key_compare key_comp(void) const
    {
        return _key_comp;
    }
    value_compare value_comp(void) const
    {
        return _val_comp;
    }

    // ** Operations

    // * Find a an element based on a key
    iterator find(const key_type &k)
    {
        node_type *search = _bst.get(k);
        if (search == NULL)
        {
            return end();
        }
        return iterator(search, _bst.root, _sentinel);
    }

    const_iterator find(const key_type &k) const
    {
        node_type *search = _bst.get(k);
        if (search == NULL)
        {
            return end();
        }
        return const_iterator(search, _bst.root, _sentinel);
    }

    // * Count number of elements matching key. For this container this will be 1 or 0
    size_type count(const key_type &k) const
    {
        if (_bst.get(k) == NULL)
        {
            return 0;
        }
        return 1;
    }

    iterator lower_bound(const key_type &k)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            if (_key_comp(k, it->first) == true ||
                (_key_comp(k, it->first) == false && _key_comp(it->first, k) == false))
            {
                return iterator(it.base(), _bst.root, _sentinel);
            }
        }
        return end();
    }

    const_iterator lower_bound(const key_type &k) const
    {
        for (const_iterator it = begin(); it != end(); it++)
        {
            if (_key_comp(k, it->first) == true ||
                (_key_comp(k, it->first) == false && _key_comp(it->first, k) == false))
            {
                return const_iterator(it.base(), _bst.root, _sentinel);
            }
        }
        return end();
    }

    iterator upper_bound(const key_type &k)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            if (_key_comp(k, it->first) == true)
            {
                return iterator(it.base(), _bst.root, _sentinel);
            }
        }
        return end();
    }

    const_iterator upper_bound(const key_type &k) const
    {
        for (const_iterator it = begin(); it != end(); it++)
        {
            if (_key_comp(k, it->first) == true)
            {
                return const_iterator(it.base(), _bst.root, _sentinel);
            }
        }
        return end();
    }

    pair<iterator, iterator> equal_range(const key_type &k)
    {
        return ft::make_pair(lower_bound(k), upper_bound(k));
    }
    pair<const_iterator, const_iterator> equal_range(const key_type &k) const
    {
        return ft::make_pair(lower_bound(k), upper_bound(k));
    }

    // ** Allocators
    allocator_type get_allocator(void) const
    {
        return _alloc;
    }

    // ? For debugging
    // void printTree(void) const
    // {
    //     _bst.traverse(_bst.root);
    // }
};

// ** Relational operators
template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
    if (lhs.size() == 0 && rhs.size() == 0)
    {
        return true;
    }
    if (lhs.size() != rhs.size())
    {
        return false;
    }
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
    return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
    if (lhs.size() == 0 && rhs.size() == 0)
    {
        return false;
    }
    if (lhs.size() == 0 && rhs.size() != 0)
    {
        return true;
    }
    if (lhs.size() != 0 && rhs.size() == 0)
    {
        return false;
    }
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
    return lhs == rhs || lhs < rhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
    return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
{
    return rhs < lhs || lhs == rhs;
}

template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
{
    x.swap(y);
}

}   // namespace ft

#endif
