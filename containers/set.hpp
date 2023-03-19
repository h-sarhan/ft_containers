/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:06:35 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/19 16:17:11 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "bst.hpp"
#include "iterator_comparison.hpp"
#include "node.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "tree_iterator.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace ft
{
template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> > class set
{
    // ** Member types
  public:
    typedef T key_type;
    typedef T value_type;
    typedef size_t size_type;

    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef typename Alloc::template rebind<node<value_type> >::other allocator_type;

    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;

    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

    typedef tree_iterator<const value_type, node<T> > iterator;
    typedef tree_iterator<const value_type, node<T> > const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename iterator_traits<iterator>::difference_type difference_type;

    // ** Private member attributes
  private:
    typedef node<value_type> node_type;

    key_compare _key_comp;
    allocator_type _alloc;
    bst<T, key_compare, allocator_type> _bst;
    size_type _size;
    node_type *_sentinel;

    // ** Constructors and destructors
  public:
    // * Default constructor
    explicit set(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
        : _key_comp(comp), _alloc(alloc), _bst(NULL, comp, alloc), _size(0),
          _sentinel(_alloc.allocate(1))
    {
        _alloc.construct(_sentinel, node_type());
    }

    // * Range-based iterator constructor
    template <class InputIterator>
    set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type())
        : _key_comp(comp), _alloc(alloc), _bst(NULL, comp, alloc), _size(0),
          _sentinel(_alloc.allocate(1))
    {
        _alloc.construct(_sentinel, node_type());
        for (InputIterator it = first; it != last; it++)
        {
            insert(*it);
        }
    }

    // * Copy constructor
    set(const set &old)
        : _key_comp(old._key_comp), _alloc(old._alloc), _bst(NULL, old._key_comp, old._alloc),
          _size(0), _sentinel(_alloc.allocate(1))
    {
        _alloc.construct(_sentinel, node_type());
        insert(old.begin(), old.end());
    }

    // * Copy assignment constructor
    set &operator=(const set &x)
    {
        if (&x == this)
        {
            return *this;
        }
        clear();
        _key_comp = x._key_comp;
        _alloc = x._alloc;
        _alloc.destroy(_sentinel);
        _alloc.deallocate(_sentinel, 1);
        _sentinel = _alloc.allocate(1);
        _alloc.construct(_sentinel, node_type());
        _bst = bst<T, key_compare, allocator_type>(NULL, _key_comp, _alloc);
        _size = 0;
        insert(x.begin(), x.end());
        return *this;
    }

    // * Destructor
    ~set(void)
    {
        _alloc.destroy(_sentinel);
        _alloc.deallocate(_sentinel, 1);
    }

    // ** Iterator functions
    iterator begin(void)
    {
        // ! Check if this is correct behaviour with std::set on linux and mac
        if (empty())
        {
            return iterator(_sentinel, _bst.root, _sentinel);
        }
        return iterator(ft::min_node(_bst.root), _bst.root, _sentinel);
    }

    const_iterator begin(void) const
    {
        // ! Check if this is correct behaviour with std::set on linux and mac. Maybe return
        // sentinel node instead??
        if (empty())
        {
            return const_iterator(_sentinel, _bst.root, _sentinel);
        }
        return const_iterator(ft::min_node(_bst.root), _bst.root, _sentinel);
    }

    iterator end(void)
    {
        // ! Check if this is correct behaviour with std::set on linux and mac. Maybe return
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

        return const_reverse_iterator(const_iterator(_sentinel, _bst.root, _sentinel));
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
        return const_reverse_iterator(
            const_iterator(ft::min_node(_bst.root), _bst.root, _sentinel));
    }

    // ** Capacity

    // * Is the set empty?
    bool empty(void) const
    {
        return _bst.root == NULL;
    }

    // * Number of elements in set
    size_type size(void) const
    {
        return _size;
    }

    // * Max number of elements in set
    size_type max_size(void) const
    {
        return _alloc.max_size();
    }

    // * Single element insert
    pair<iterator, bool> insert(const value_type &val)
    {
        ft::pair<node_type *, bool> res = _bst.set_insert(val);

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
        node_type *to_delete = _bst.set_get(k);
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
        node_type *to_delete = _bst.set_get(*position);
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

    // * Swap two sets without invalidating iterators
    void swap(set &x)
    {
        if (this == &x)
        {
            return;
        }
        key_compare temp_key_comp = x.key_comp();
        allocator_type temp_allocator = x.get_allocator();
        node_type *temp_bst_root = x._bst.root;
        size_type temp_size = x._size;
        node_type *temp_sentinel = x._sentinel;

        x._key_comp = _key_comp;
        x._alloc = _alloc;
        x._bst.root = _bst.root;
        x._size = _size;
        x._sentinel = _sentinel;

        _key_comp = temp_key_comp;
        _alloc = temp_allocator;
        _bst.root = temp_bst_root;
        _size = temp_size;
        _sentinel = temp_sentinel;
    }

    // * Erase all elements from a set
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
        return _key_comp;
    }

    // ** Operations

    // * Find a an element based on a key
    iterator find(const key_type &k)
    {
        node_type *search = _bst.set_get(k);
        if (search == NULL)
        {
            return end();
        }
        return iterator(search, _bst.root, _sentinel);
    }

    const_iterator find(const key_type &k) const
    {
        node_type *search = _bst.set_get(k);
        if (search == NULL)
        {
            return end();
        }
        return const_iterator(search, _bst.root, _sentinel);
    }

    // * Count number of elements matching key. For this container this will be 1 or 0
    size_type count(const key_type &k) const
    {
        if (_bst.set_get(k) == NULL)
        {
            return 0;
        }
        return 1;
    }

    iterator lower_bound(const key_type &k)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            if (_key_comp(k, *it) == true ||
                (_key_comp(k, *it) == false && _key_comp(*it, k) == false))
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
            if (_key_comp(k, *it) == true ||
                (_key_comp(k, *it) == false && _key_comp(*it, k) == false))
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
            if (_key_comp(k, *it) == true)
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
            if (_key_comp(k, *it) == true)
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
template <class T, class Compare, class Alloc>
bool operator==(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
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

template <class T, class Compare, class Alloc>
bool operator!=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return !(lhs == rhs);
}

template <class T, class Compare, class Alloc>
bool operator<(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
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

template <class T, class Compare, class Alloc>
bool operator<=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return lhs == rhs || lhs < rhs;
}

template <class T, class Compare, class Alloc>
bool operator>(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return rhs < lhs;
}

template <class T, class Compare, class Alloc>
bool operator>=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return rhs < lhs || lhs == rhs;
}

template <class T, class Compare, class Alloc>
void swap(set<T, Compare, Alloc> &x, set<T, Compare, Alloc> &y)
{
    x.swap(y);
}

}   // namespace ft

#endif
