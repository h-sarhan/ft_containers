/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:25:48 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/30 04:46:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "make_pair.hpp"
#include "map_iterator.hpp"
#include "map_tree.hpp"
#include "node.hpp"
#include "pair.hpp"
#include <functional>
#include <memory>

namespace ft
{
template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<ft::map_node<const Key, T> > >
class map
{
  public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef size_t size_type;

    class value_compare
        : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;

      protected:
        key_compare _comp;
        value_compare(key_compare c) : _comp(c)
        {
        }   // constructed with map's comparison object
      public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;
        bool operator()(const value_type &x, const value_type &y) const
        {
            return _comp(x.first, y.first);
        }
    };

  private:
    typedef map_tree<key_type, mapped_type, key_compare, allocator_type>
        tree_type;

    typedef ft::map_node<const key_type, mapped_type> node_type;
    typedef node_type *node_pointer;

    size_type _size;
    allocator_type _alloc;
    key_compare _comp;
    tree_type _tree;
    tree_type *_tree_ptr;
    value_compare _val_comp;

  public:
    typedef ft::map_iterator<tree_type> iterator;
    typedef ft::map_iterator<tree_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef
        typename ft::iterator_traits<iterator>::difference_type difference_type;

  public:
    //** *** CONSTRUCTORS *** *//
    // empty container constructor (default constructor)
    explicit map(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
        : _size(0), _alloc(alloc), _comp(comp),
          _tree(tree_type(NULL, comp, alloc)), _tree_ptr(&_tree),
          _val_comp(_comp)
    {
    }

    // range constructor
    template <class InputIterator>
    map(InputIterator first, InputIterator last,
        const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type())
        : _size(0), _alloc(alloc), _comp(comp),
          _tree(tree_type(NULL, comp, alloc)), _tree_ptr(&_tree),
          _val_comp(_comp)
    {
        insert(first, last);
    }

    // copy constructor
    // Insert everything in old map into the new map in a for loop
    map(const map &x)
        : _size(0), _alloc(x._alloc), _comp(x._comp),
          _tree(tree_type(NULL, _comp, _alloc)), _tree_ptr(&_tree),
          _val_comp(x._val_comp)
    {
        insert(x.begin(), x.end());
    }

    // Copy assignment constructor
    // Insert everything in old map into the new map in a for loop
    map &operator=(const map &x)
    {
        if (&x == this)
        {
            return *this;
        }
        clear();
        _comp = x._comp;
        _val_comp = x._val_comp;
        _alloc = x._alloc;
        _size = 0;
        _tree.root = NULL;
        insert(x.begin(), x.end());
        return *this;
    }

    //** *** DESTRUCTOR *** //
    ~map(void)
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
        return reverse_iterator(
            iterator(_tree.maximum_node(_tree.root), &_tree));
    }
    const_reverse_iterator rbegin(void) const
    {
        if (empty())
        {
            // idk
        }
        return const_reverse_iterator(
            const_iterator(_tree.maximum_node(_tree.root), &_tree));
    }

    reverse_iterator rend(void)
    {
        if (empty())
        {
            // idk
        }
        return reverse_iterator(iterator(NULL, &_tree));
    }
    const_reverse_iterator rend(void) const
    {
        if (empty())
        {
            // idk
        }
        return const_reverse_iterator(const_iterator(NULL, &_tree));
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

    //** *** ELEMENT ACCESS  *** //
    mapped_type &operator[](const key_type &k)
    {
        node_pointer res = _tree.search_node(k);
        if (res == NULL)
        {
            iterator ret = insert(ft::make_pair(k, mapped_type())).first;
            return ret->second;
        }
        return res->data.second;
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
        node_pointer to_delete = _tree.search_node(position->first);
        if (to_delete == NULL)
            return;
        _tree.delete_node(to_delete->data.first);
        _size -= 1;
    }

    size_type erase(const key_type &k)
    {
        if (empty())
            return 0;
        node_pointer to_delete = _tree.search_node(k);
        if (to_delete == NULL)
            return 0;
        _tree.delete_node(to_delete->data.first);
        _size -= 1;
        return 1;
    }

    void erase(iterator first, iterator last)
    {
        iterator it = first;
        ft::vector<key_type> keys;
        while (it != last)
        {
            keys.push_back(it->first);
            it++;
        }
        for (typename ft::vector<key_type>::iterator key_it = keys.begin();
             key_it != keys.end(); key_it++)
            erase(*key_it);
    }

    void swap(map &x)
    {
        if (this == &x)
        {
            return;
        }
        key_compare temp_comp = x.key_comp();
        allocator_type temp_allocator = x.get_allocator();
        size_type temp_size = x._size;
        node_pointer temp_bst_root = x._tree.root;
        // tree_type *temp_tree_ptr = x._tree_ptr;

        x._comp = _comp;
        x._alloc = _alloc;
        x._size = _size;
        x._tree.root = _tree.root;
        // x._tree_ptr = _tree_ptr;

        _comp = temp_comp;
        _alloc = temp_allocator;
        _size = temp_size;
        _tree.root = temp_bst_root;
        // _tree_ptr = temp_tree_ptr;
        _tree_ptr = &_tree;
        x._tree_ptr = &x._tree;
    }

    void clear(void)
    {
        if (_size != 0 || _tree.root != NULL)
        {
            erase(begin(), end());
            // _tree.root = NULL;
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
        return _val_comp;
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
            if (_comp(it->first, k) == false)
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
            if (_comp(it->first, k) == false)
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
            if (_comp(k, it->first) == true)
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
            if (_comp(k, it->first) == true)
            {
                return const_iterator(it.base(), &_tree);
            }
        }
        return end();
    }

    pair<const_iterator, const_iterator> equal_range(const key_type &k) const
    {
        return ft::make_pair(lower_bound(k), upper_bound(k));
    }
    pair<iterator, iterator> equal_range(const key_type &k)
    {
        return ft::make_pair(lower_bound(k), upper_bound(k));
    }

    typename Alloc::template rebind<
        ft::pair<const key_type, mapped_type> >::other
    get_allocator(void) const
    {
        typename Alloc::template rebind<
            ft::pair<const key_type, mapped_type> >::other alloc;
        return alloc;
    }
};

// ** Relational operators
template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs)
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
bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs)
{
    return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &lhs,
               const map<Key, T, Compare, Alloc> &rhs)
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

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs)
{
    return lhs == rhs || lhs < rhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &lhs,
               const map<Key, T, Compare, Alloc> &rhs)
{
    return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
                const map<Key, T, Compare, Alloc> &rhs)
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
