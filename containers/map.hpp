/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:25:48 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/26 19:52:58 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include <functional>
#include <memory>

namespace ft
{
template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<ft::pair<const Key, T> > >
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
    // typedef map_iterator iterator;
    // typedef map_iterator const_iterator;
    // typedef reverse_iterator<iterator> reverse_iterator;
    // typedef reverse_iterator<const_iterator> const_reverse_iterator;
    // typedef iterator_traits<iterator>::difference_type difference_type;
    typedef size_t size_type;

    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;

      protected:
        Compare _comp;
        value_compare(Compare c) : _comp(c)
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
    size_type _size;
    allocator_type _alloc;

  public:
    //** *** CONSTRUCTORS *** *//
    // empty container constructor (default constructor)
    explicit map(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type());

    // range constructor
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type());

    // copy constructor
    map(const map &x);

    // Copy assignment constructor
    map &operator=(const map &x);

    //** *** DESTRUCTOR *** //
    ~map(void);

    //** *** ITERATOR METHODS *** //
    // iterator begin();
    // const_iterator begin() const;

    // iterator end();
    // const_iterator end() const;

    // reverse_iterator rbegin();
    // const_reverse_iterator rbegin() const;

    //  reverse_iterator rend();
    // const_reverse_iterator rend() const;

    //** *** CAPACITY METHODS *** //
    bool empty(void) const;

    size_type size(void) const;

    size_type max_size(void) const;

    //** *** ELEMENT ACCESS  *** //
    mapped_type &operator[](const key_type &k);

    //** *** MODIFIERS  *** //
    // pair<iterator, bool> insert (const value_type& val);

    // iterator insert (iterator position, const value_type& val);

    template <class InputIterator> void insert(InputIterator first, InputIterator last);

    // void erase(iterator position);

    size_type erase(const key_type &k);

    // void erase(iterator first, iterator last);

    void swap(map &x);

    void clear(void);

    //** *** OBSERVERS  *** //
    key_compare key_comp(void) const;

    value_compare value_comp(void) const;

    //** *** OPERATIONS  *** //

    // iterator find(const key_type &k);
    // const_iterator find(const key_type &k) const;

    size_type count(const key_type &k) const;

    // iterator lower_bound(const key_type &k);
    // const_iterator lower_bound(const key_type &k) const;

    // iterator upper_bound(const key_type &k);
    // const_iterator upper_bound(const key_type &k) const;

    // pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
    // pair<iterator, iterator> equal_range(const key_type &k);

    allocator_type get_allocator(void) const;
};
}   // namespace ft
#endif
