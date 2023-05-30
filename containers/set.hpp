/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:25:48 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/30 08:25:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "make_pair.hpp"
#include "node.hpp"
#include "pair.hpp"
#include "set_iterator.hpp"
#include "set_tree.hpp"
#include <functional>
#include <memory>

namespace ft
{
template <class T, class Compare = std::less<T>,
          class Alloc = std::allocator<T> >
class set
{
  public:
    typedef T key_type;
    typedef T value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef
        typename Alloc::template rebind<ft::set_node<const key_type> >::other
            allocator_type;
    typedef key_type &reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;
    typedef size_t size_type;

  private:
    typedef set_tree<key_type, key_compare, allocator_type> tree_type;

    typedef ft::set_node<const key_type> node_type;
    typedef node_type *node_pointer;

    size_type _size;
    allocator_type _alloc;
    key_compare _comp;
    tree_type _tree;
    tree_type *_tree_ptr;

  public:
    typedef ft::set_iterator<tree_type> iterator;
    typedef ft::const_set_iterator<tree_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef
        typename ft::iterator_traits<iterator>::difference_type difference_type;

  public:
    //** *** CONSTRUCTORS *** *//
    // empty container constructor (default constructor)
    explicit set(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
        : _size(0), _alloc(alloc), _comp(comp),
          _tree(tree_type(NULL, comp, alloc)), _tree_ptr(&_tree)
    {
    }

    // range constructor
    template <class InputIterator>
    set(InputIterator first, InputIterator last,
        const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type())
        : _size(0), _alloc(alloc), _comp(comp),
          _tree(tree_type(NULL, comp, alloc)), _tree_ptr(&_tree)
    {
        insert(first, last);
    }

    // copy constructor
    // Insert everything in old set into the new set in a for loop
    set(const set &x)
        : _size(0), _alloc(x._alloc), _comp(x._comp),
          _tree(tree_type(NULL, _comp, _alloc)), _tree_ptr(&_tree)
    {
        insert(x.begin(), x.end());
    }

    // Copy assignment constructor
    // Insert everything in old set into the new set in a for loop
    set &operator=(const set &x)
    {
        if (&x == this)
        {
            return *this;
        }
        clear();
        _comp = x._comp;
        _alloc = x._alloc;
        _size = 0;
        _tree.root = NULL;
        insert(x.begin(), x.end());
        return *this;
    }

    //** *** DESTRUCTOR *** //
    ~set(void)
    {
    }

    //** *** ITERATOR METHODS *** //
    iterator begin(void)
    {
        if (empty())
        {
            return iterator(NULL, &_tree);
        }
        return iterator(_tree.minimum_node(_tree.root), &_tree);
    }
    const_iterator begin(void) const
    {
        if (empty())
        {
            return const_iterator(NULL, &_tree);
        }
        return const_iterator(_tree.minimum_node(_tree.root), &_tree);
    }

    iterator end(void)
    {
        if (empty())
        {
            return iterator(NULL, &_tree);
        }
        return iterator(NULL, &_tree);
    }
    const_iterator end(void) const
    {

        if (empty())
        {
            return const_iterator(NULL, &_tree);
        }
        return const_iterator(NULL, &_tree);
    }

    reverse_iterator rbegin(void)
    {
        if (empty())
        {
            // idk
        }
        return reverse_iterator(iterator(NULL, &_tree));
    }
    const_reverse_iterator rbegin(void) const
    {
        if (empty())
        {
            // idk
        }
        return const_reverse_iterator(const_iterator(node_type(), &_tree));
    }

    reverse_iterator rend(void)
    {
        if (empty())
        {
            // idk
        }
        return reverse_iterator(
            iterator(_tree.minimum_node(_tree.root), &_tree));
    }
    const_reverse_iterator rend(void) const
    {
        if (empty())
        {
            // idk
        }
        return const_reverse_iterator(
            const_iterator(_tree.maximum_node(_tree.root), &_tree));
    }

    //** *** CAPACITY METHODS *** //
    bool empty(void) const
    {
        return _size == 0 || _tree.root == NULL;
    }

    size_type size(void) const
    {
        return _size;
    }

    size_type max_size(void) const
    {
        return _alloc.max_size();
    }

    //** *** MODIFIERS  *** //

    // * Single element insert
    ft::pair<iterator, bool> insert(const value_type &val)
    {
        ft::pair<node_pointer, bool> res = _tree.insert_node(val);
        if (res.second == true)
            _size += 1;
        return ft::make_pair(iterator(res.first, _tree_ptr), res.second);
    }

    // * Single element insert with hint. Hint is just ignored lol!
    iterator insert(iterator position, const value_type &val)
    {
        (void) position;
        return insert(val).first;
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        for (InputIterator it = first; it != last; it++)
        {
            insert(*it);
        }
    }

    void erase(iterator position)
    {
        if (empty() || position.base() == NULL)
            return;
        node_pointer to_delete = _tree.search_node(*position);
        if (to_delete == NULL)
            return;
        _tree.delete_node(to_delete->data);
        _size -= 1;
    }

    size_type erase(const key_type &k)
    {
        if (empty())
            return 0;
        node_pointer to_delete = _tree.search_node(k);
        if (to_delete == NULL)
            return 0;
        _tree.delete_node(to_delete->data);
        _size -= 1;
        return 1;
    }

    void erase(iterator first, iterator last)
    {
        iterator it = first;
        ft::vector<key_type> keys;
        while (it != last)
        {
            keys.push_back(*it);
            it++;
        }
        for (typename ft::vector<key_type>::iterator key_it = keys.begin();
             key_it != keys.end(); key_it++)
            erase(*key_it);
    }

    void swap(set &x)
    {
        if (this == &x)
        {
            return;
        }
        key_compare temp_comp = x.key_comp();
        size_type temp_size = x._size;
        node_pointer temp_bst_root = x._tree.root;

        x._comp = _comp;
        x._alloc = _alloc;
        x._size = _size;
        x._tree.root = _tree.root;

        _comp = temp_comp;
        _size = temp_size;
        _tree.root = temp_bst_root;
        _tree_ptr = &_tree;
        x._tree_ptr = &x._tree;
    }

    void clear(void)
    {
        if (_size != 0 || _tree.root != NULL)
        {
            erase(begin(), end());
            _size = 0;
        }
    }

    //** *** OBSERVERS  *** //
    key_compare key_comp(void) const
    {
        return _comp;
    }

    value_compare value_comp(void) const
    {
        return _comp;
    }

    //** *** OPERATIONS  *** //

    iterator find(const key_type &k)
    {
        node_pointer search = _tree.search_node(k);
        if (search == NULL)
        {
            return end();
        }
        return iterator(search, &_tree);
    }
    const_iterator find(const key_type &k) const
    {
        node_pointer search = _tree.search_node(k);
        if (search == NULL)
        {
            return end();
        }
        return const_iterator(search, &_tree);
    }

    size_type count(const key_type &k) const
    {
        if (_tree.search_node(k) == NULL)
        {
            return 0;
        }
        return 1;
    }

    iterator lower_bound(const key_type &k)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            if (_comp(*it, k) == false)
            {
                return iterator(it.base(), &_tree);
            }
        }
        return end();
    }
    const_iterator lower_bound(const key_type &k) const
    {
        for (const_iterator it = begin(); it != end(); it++)
        {
            if (_comp(*it, k) == false)
            {
                return const_iterator(it.base(), &_tree);
            }
        }
        return end();
    }

    iterator upper_bound(const key_type &k)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            if (_comp(k, *it) == true)
            {
                return iterator(it.base(), &_tree);
            }
        }
        return end();
    }
    const_iterator upper_bound(const key_type &k) const
    {
        for (const_iterator it = begin(); it != end(); it++)
        {
            if (_comp(k, *it) == true)
            {
                return const_iterator(it.base(), &_tree);
            }
        }
        return end();
    }

    ft::pair<const_iterator, const_iterator> equal_range(
        const key_type &k) const
    {
        return ft::make_pair(lower_bound(k), upper_bound(k));
    }
    ft::pair<iterator, iterator> equal_range(const key_type &k)
    {
        return ft::make_pair(lower_bound(k), upper_bound(k));
    }

    typename Alloc::template rebind<key_type>::other get_allocator(
        void) const
    {
        typename Alloc::template rebind<key_type>::other alloc;
        return alloc;
    }
};

// ** Relational operators
template <class Key, class Compare, class Alloc>
bool operator==(const set<Key, Compare, Alloc> &lhs,
                const set<Key, Compare, Alloc> &rhs)
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

template <class Key, class Compare, class Alloc>
bool operator!=(const set<Key, Compare, Alloc> &lhs,
                const set<Key, Compare, Alloc> &rhs)
{
    return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool operator<(const set<Key, Compare, Alloc> &lhs,
               const set<Key, Compare, Alloc> &rhs)
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
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                       rhs.end());
}

template <class Key, class Compare, class Alloc>
bool operator<=(const set<Key, Compare, Alloc> &lhs,
                const set<Key, Compare, Alloc> &rhs)
{
    return lhs == rhs || lhs < rhs;
}

template <class Key, class Compare, class Alloc>
bool operator>(const set<Key, Compare, Alloc> &lhs,
               const set<Key, Compare, Alloc> &rhs)
{
    return rhs < lhs;
}

template <class Key, class Compare, class Alloc>
bool operator>=(const set<Key, Compare, Alloc> &lhs,
                const set<Key, Compare, Alloc> &rhs)
{
    return rhs < lhs || lhs == rhs;
}

template <class Key, class Compare, class Alloc>
void swap(set<Key, Compare, Alloc> &x, set<Key, Compare, Alloc> &y)
{
    x.swap(y);
}

}   // namespace ft
#endif
