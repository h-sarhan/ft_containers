/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:06:35 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/10 11:36:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "iterator_comparison.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "tree.hpp"
#include "map_iterator.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

// ! Everything has issues
namespace ft
{
template <class K, class V, class Compare = std::less<K>,
          class Alloc = std::allocator<node<ft::pair<const K, V> > > >
class map
{
    // ** Member types
  public:
    typedef K key_type;
    typedef V mapped_type;
    typedef ft::pair<const key_type, mapped_type> value_type;
    typedef size_t size_type;

    typedef Compare key_compare;
    typedef typename Alloc::template rebind<node<value_type> >::other allocator_type;

    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;

  private:
    typedef node<value_type> node_type;

    typedef tree<node_type, Compare, Alloc> tree_type;

  public:
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef map_iterator<node_type, value_type> iterator;
    // typedef const_map_iterator<node_type, value_type> const_iterator;
    typedef map_iterator<node_type, value_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

    // ** Nested value_compare class
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

  private:
    key_compare _key_comp;
    value_compare _val_comp;
    allocator_type _alloc;
    tree_type _tree;
    size_type _size;

    // ** Constructors and destructors
  public:
    // * Default constructor
    explicit map(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
        : _key_comp(comp), _val_comp(comp), _alloc(alloc), _tree(), _size(0)
    {
    }

    // * Range-based iterator constructor
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type())
        : _key_comp(comp), _val_comp(comp), _alloc(alloc), _tree(), _size(0)
    {
        for (InputIterator it = first; it != last; it++)
        {
            insert(*it);
        }
    }

    // * Copy constructor
    map(const map &old)
        : _key_comp(old._key_comp), _val_comp(old._val_comp), _alloc(old._alloc), _tree(), _size(0)
    {
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
        _size = 0;
        insert(x.begin(), x.end());
        return *this;
    }

    // * Destructor
    ~map(void)
    {
    }

    // ** Iterator functions

    // * Begin iterator
    iterator begin(void)
    {
        // ! Check if this is correct behaviour with std::map on linux and mac
        if (empty())
        {
            return iterator(NULL, _tree.root);
        }
        return iterator(min_node(_tree.root), _tree.root);
        // return iterator(NULL, _tree.root);
    }
    const_iterator begin(void) const
    {
        // ! Check if this is correct behaviour with std::map on linux and mac. Maybe return
        // sentinel node instead??
        if (empty())
        {
            return const_iterator(NULL, _tree.root);
        }
        return const_iterator(min_node(_tree.root), _tree.root);
        // return const_iterator(NULL, _tree.root);
    }

    // * End iterator
    iterator end(void)
    {
        // ! Check if this is correct behaviour with std::map on linux and mac. Maybe return
        // sentinel node instead??
        if (empty())
        {
            return begin();
        }
        return iterator(NULL, _tree.root);
    }
    const_iterator end(void) const
    {
        if (empty())
        {
            return begin();
        }
        return const_iterator(NULL, _tree.root);
    }

    // * Reverse begin iterator
    reverse_iterator rbegin(void)
    {
        if (empty())
        {
            // idk
        }

        return reverse_iterator(iterator(NULL, _tree.root));
    }
    const_reverse_iterator rbegin(void) const
    {
        if (empty())
        {
            // idk
        }

        return const_reverse_iterator(iterator(NULL, _tree.root));
    }

    // * Reverse end iterator
    reverse_iterator rend(void)
    {
        if (empty())
        {
            // idk
        }
        return reverse_iterator(iterator(min_node(_tree.root), _tree.root));
    }
    const_reverse_iterator rend(void) const
    {
        if (empty())
        {
            // idk
        }
        return const_reverse_iterator(iterator(min_node(_tree.root), _tree.root));
    }

    // ** Capacity

    // * Is the map empty?
    bool empty(void) const
    {
        return _tree.root == NULL;
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
        node_type *res = _tree.get(key);
        if (res == NULL)
        {
            iterator ret = insert(ft::make_pair(key, mapped_type())).first;
            return ret->second;
        }
        return res->data.second;
    }

    // ** Modifiers

    // * Single element insert
    ft::pair<iterator, bool> insert(const value_type &val)
    {
        ft::pair<node_type *, bool> res = _tree.insert(node<value_type>(val, BLACK));

        if (res.second == true)
        {
            _size += 1;
            return ft::make_pair(iterator(res.first, _tree.root), true);
        }
        return ft::make_pair(iterator(res.first, _tree.root), false);
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
        node_type *to_delete = _tree.get(k);
        if (to_delete == NULL)
        {
            return 0;
        }
        _tree.delete_node(to_delete);
        _size -= 1;
        return 1;
    }

    // * Single element insert based on iterator
    void erase(iterator position)
    {
        if (_size == 0 || _tree.root == NULL)
            return;
        node_type *to_delete = _tree.get(position->first);
        if (to_delete == NULL)
        {
            return;
        }
        _tree.delete_node(to_delete);
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
        // size_type _size;
        key_compare temp_key_comp = x.key_comp();
        value_compare temp_val_comp = x.value_comp();
        allocator_type temp_allocator = x.get_allocator();
        size_type temp_size = x._size;
        tree_type temp_bst = x._tree;

        x._key_comp = _key_comp;
        x._val_comp = _val_comp;
        x._alloc = _alloc;
        x._size = _size;
        x._tree = _tree;

        _key_comp = temp_key_comp;
        _val_comp = temp_val_comp;
        _alloc = temp_allocator;
        _size = temp_size;
        _tree = temp_bst;
    }

    // * Erase all elements from a map
    void clear(void)
    {
        if (_size != 0 || _tree.root != NULL)
        {
            erase(begin(), end());
            _tree.root = NULL;
            _size = 0;
        }
    }

    // * Return key comp
    key_compare key_comp(void) const
    {
        return _key_comp;
    }

    // * Return value comp
    value_compare value_comp(void) const
    {
        return _val_comp;
    }

    // ** Operations

    // * Find a an element based on a key
    iterator find(const key_type &k)
    {
        node_type *search = _tree.get(k);
        if (search == NULL)
        {
            return end();
        }
        return iterator(search, _tree.root);
    }
    const_iterator find(const key_type &k) const
    {
        node_type *search = _tree.get(k);
        if (search == NULL)
        {
            return end();
        }
        return const_iterator(search, _tree.root);
    }

    // * Count number of elements matching key. For this container this will be 1 or 0
    size_type count(const key_type &k) const
    {
        if (_tree.get(k) == NULL)
        {
            return 0;
        }
        return 1;
    }

    // * Return lower bound
    iterator lower_bound(const key_type &k)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            if (_key_comp(it->first, k) == false)
            {
                return iterator(it.base(), _tree.root);
            }
        }
        return end();
    }
    const_iterator lower_bound(const key_type &k) const
    {
        for (const_iterator it = begin(); it != end(); it++)
        {
            if (_key_comp(it->first, k) == false)
            {
                return const_iterator(it.base(), _tree.root);
            }
        }
        return end();
    }

    // * Return upper bound
    iterator upper_bound(const key_type &k)
    {
        for (iterator it = begin(); it != end(); it++)
        {
            if (_key_comp(k, it->first) == true)
            {
                return iterator(it.base(), _tree.root);
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
                return const_iterator(it.base(), _tree.root);
            }
        }
        return end();
    }

    // * Return pair of upper and lower bound
    ft::pair<iterator, iterator> equal_range(const key_type &k)
    {
        return ft::make_pair(lower_bound(k), upper_bound(k));
    }
    ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
    {
        return ft::make_pair(lower_bound(k), upper_bound(k));
    }

    // ** Allocators
    allocator_type get_allocator(void) const
    {
        return _alloc;
    }

    // ? For debugging
    void printTree(void) const
    {
        _tree.traverse(_tree.root);
    }
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
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
