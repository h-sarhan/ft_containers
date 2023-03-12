/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:06:35 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/12 23:03:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "bst.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include <cstddef>
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
    typedef map_iterator<const value_type, node_type> const_iterator;
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
    explicit map(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type());
    // template <class InputIterator>
    // map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const
    // allocator_type &alloc = allocator_type());
    map(const map &x);
    // ~map(void);
    // map												&operator=(const map &x);

    // ** Iterator functions
    iterator begin(void);
    const_iterator begin(void) const;
    iterator end(void);
    const_iterator end(void) const;
    reverse_iterator rbegin(void);
    const_reverse_iterator rbegin(void) const;
    reverse_iterator rend(void);
    const_reverse_iterator rend(void) const;

    // ** Capacity
    bool empty(void) const;

    size_type size(void) const;

    size_type max_size(void) const;

    // ** Element access
    mapped_type &operator[](const key_type &k);

    // ! THESE ONES ARE FOR TESTING PLEASE REMOVE
    void insert(const value_type &val);
    void printTree(void) const;

    // ** Modifiers
    // pair<iterator,bool> insert(const value_type &val);
    // iterator insert(iterator position, const value_type &val);
    // template <class InputIterator> void insert(InputIterator first, InputIterator last);
    size_type erase(const key_type &k);
    // void erase(iterator position);
    // void erase(iterator first, iterator last);
    // void swap(map &x);
    // void clear(void);

    // ** Observers
    key_compare key_comp(void) const;
    value_compare value_comp(void) const;

    // ** Operations
    // iterator find(const key_type &k);
    // const_iterator find(const key_type &k) const;
    size_type count(const key_type &k) const;
    // iterator lower_bound(const key_type &k);
    // const_iterator lower_bound(const key_type &k) const;
    // iterator upper_bound(const key_type &k);
    // const_iterator upper_bound(const key_type &k) const;
    // pair<iterator, iterator> equal_range(const key_type &k);
    // pair<const_iterator, const_iterator> equal_range(const key_type &k) const;

    // ** Allocators
    allocator_type get_allocator(void) const;
};
}   // namespace ft

template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::map(const key_compare &comp, const allocator_type &alloc)
    : _key_comp(comp), _val_comp(comp), _alloc(alloc), _bst(NULL, comp, alloc), _size(0),
      _sentinel(_alloc.allocate(1))
{
    _alloc.construct(_sentinel, node_type());
}

template <class Key, class T, class Compare, class Alloc>
ft::map<Key, T, Compare, Alloc>::map(const map &old)
    : _key_comp(old._key_comp), _val_comp(old._val_comp), _alloc(old._alloc), _bst(old._bst),
      _size(old._size), _sentinel(old._sentinel)
{
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator ft::map<Key, T, Compare, Alloc>::begin(void)
{
    // ! Check if this is correct behaviour with std::map on linux and mac. Maybe return sentinel
    // node instead??
    if (empty())
    {
        return iterator();
    }
    return iterator(ft::min_node(_bst.root), _bst.root, _sentinel);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_iterator ft::map<Key, T, Compare, Alloc>::begin(
    void) const
{
    // ! Check if this is correct behaviour with std::map on linux and mac. Maybe return sentinel
    // node instead??
    if (empty())
    {
        return iterator();
    }
    return iterator(ft::min_node(_bst.root), _bst.root, _sentinel);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::iterator ft::map<Key, T, Compare, Alloc>::end(void)
{
    // ! Check if this is correct behaviour with std::map on linux and mac. Maybe return sentinel
    // node instead??
    if (empty())
    {
        return begin();
    }
    // ! probably wrong i'll come back to this when the tester fails me
    return iterator(_sentinel, _bst.root, _sentinel);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_iterator ft::map<Key, T, Compare, Alloc>::end(
    void) const
{
    if (empty())
    {
        return begin();
    }
    return iterator(_sentinel, _bst.root, _sentinel);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::reverse_iterator ft::map<Key, T, Compare, Alloc>::rbegin(
    void)
{
    if (empty())
    {
        // idk
    }

    return reverse_iterator(iterator(_sentinel, _bst.root, _sentinel));
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator ft::map<Key, T, Compare,
                                                                         Alloc>::rbegin(void) const
{
    if (empty())
    {
        // idk
    }
    return reverse_iterator(iterator(_sentinel, _bst.root, _sentinel));
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::reverse_iterator ft::map<Key, T, Compare, Alloc>::rend(
    void)
{
    if (empty())
    {
        // idk
    }
    return reverse_iterator(iterator(ft::min_node(_bst.root), _bst.root, _sentinel));
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::const_reverse_iterator ft::map<Key, T, Compare,
                                                                         Alloc>::rend(void) const
{
    if (empty())
    {
        // idk
    }
    return reverse_iterator(iterator(ft::min_node(_bst.root), _bst.root, _sentinel));
}

template <class Key, class T, class Compare, class Alloc>
bool ft::map<Key, T, Compare, Alloc>::empty(void) const
{
    return _bst.root == NULL;
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type ft::map<Key, T, Compare, Alloc>::count(const key_type &k) const
{
    if (_bst.get(k) == NULL)
    {
        return 0;
    }
    return 1;
}


template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type ft::map<Key, T, Compare, Alloc>::size() const
{
    return _size;
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type ft::map<Key, T, Compare, Alloc>::max_size()
    const
{
    return _alloc.max_size();
}

template <class Key, class T, class Compare, class Alloc>
void ft::map<Key, T, Compare, Alloc>::insert(const value_type &val)
{
    // ft::pair<iterator, bool> res;

    if (_bst.insert(val) == true)
    {
        _size += 1;
    }
}

template <class Key, class T, class Compare, class Alloc>
void ft::map<Key, T, Compare, Alloc>::printTree(void) const
{
    _bst.traverse(_bst.root);
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::mapped_type &ft::map<Key, T, Compare, Alloc>::operator[](
    const key_type &key)
{
    node_type *res = _bst.get(key);
    if (res == NULL)
    {
        // ! You should create an element with a value of mapped_type()
        throw std::out_of_range("key not in map");   // ! Replace this by returning a reference to
                                                     // the value that was just added
    }
    return res->data.second;
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::allocator_type ft::map<Key, T, Compare,
                                                                 Alloc>::get_allocator(void) const
{
    return _alloc;
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::size_type ft::map<Key, T, Compare, Alloc>::erase(
    const key_type &k)
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

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::key_compare ft::map<Key, T, Compare, Alloc>::key_comp(
    void) const
{
    return _key_comp;
}

template <class Key, class T, class Compare, class Alloc>
typename ft::map<Key, T, Compare, Alloc>::value_compare ft::map<Key, T, Compare, Alloc>::value_comp(
    void) const
{
    return _val_comp;
}

#endif
