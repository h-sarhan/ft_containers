/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:42:21 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/30 05:50:33 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP

#define VECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_comparison.hpp"
#include "iterator_validation.hpp"
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"

// ! Check all reallocs
// ! Run the testers again
namespace ft
{
template <class T, class Alloc = std::allocator<T> > class vector
{
  public:
    // * Public member types
    typedef T value_type;
    typedef Alloc allocator_type;

    typedef typename Alloc::size_type size_type;
    typedef typename Alloc::difference_type difference_type;

    typedef value_type &reference;
    typedef const value_type &const_reference;

    typedef typename Alloc::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;

    typedef ft::vector_iterator<T> iterator;
    typedef ft::vector_iterator<const T> const_iterator;

    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  private:
    // * Private attributes
    allocator_type _alloc;
    value_type *_array;
    size_type _size;
    size_type _capacity;

  public:
    // * Constructors and destructors

    // * Default constructor
    explicit vector(const allocator_type &alloc = allocator_type())
        : _alloc(alloc), _array(NULL), _size(0), _capacity(0)
    {
    }

    // * Fill constructor
    explicit vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type())
        : _alloc(alloc), _size(n), _capacity(n)
    {
        if (n >= max_size())
            throw std::length_error("big");
        try
        {
            _array = _alloc.allocate(n);
            for (size_type i = 0; i < n; i++)
            {
                _alloc.construct(&_array[i], val);
            }
        }
        catch (const std::bad_alloc &)
        {

            throw std::length_error("big");
        }
    }

    // * Iterator range constructor
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
           const allocator_type &alloc = allocator_type(),
           typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
               * = 0)
        : _alloc(alloc), _array(NULL), _size(0), _capacity(0)
    {
        if (is_one_way(first))
        {
            _realloc(100);
            size_type i = 0;
            for (InputIterator it = first; it != last; it++)
            {
                if (i >= _capacity)
                    _realloc((_capacity + 1) * 2);
                _alloc.construct(&_array[i], *it);
                _size++;
                i++;
            }
            return;
        }
        if (validate_iterators(first, last, max_size()) == false)
        {
            throw std::length_error("Invalid iterator 😔");
        }
        _realloc(std::distance(first, last));
        size_type i = 0;
        for (InputIterator it = first; it != last; it++)
        {
            _alloc.construct(&_array[i], *it);
            _size++;
            i++;
        }
    }

    // * Copy constructor
    vector(const vector &old)
        : _alloc(old._alloc), _size(old._size), _capacity(old._capacity)
    {
        _array = _alloc.allocate(old._capacity);
        for (size_type i = 0; i < _size; i++)
        {
            _alloc.construct(&_array[i], old._array[i]);
        }
    }

    // * Copy assignment constructor
    vector &operator=(const vector &x)
    {
        if (this == &x)
        {
            return (*this);
        }
        for (size_type i = 0; i < _size; i++)
        {
            _alloc.destroy(&_array[i]);
        }
        if (_array != NULL)
            _alloc.deallocate(_array, _capacity);
        _capacity = x.capacity();
        _size = x.size();
        _array = _alloc.allocate(_capacity);
        for (size_type i = 0; i < _size; i++)
        {
            _alloc.construct(&_array[i], x._array[i]);
        }
        return (*this);
    }

    // * Destructor
    ~vector(void)
    {
        if (_array == NULL)
            return;
        for (size_type i = 0; i < _size; i++)
        {
            _alloc.destroy(&_array[i]);
        }
        _alloc.deallocate(_array, _capacity);
    }

    // * Iterators

    // * Iterator to first element
    iterator begin(void)
    {
        return iterator(&_array[0]);
    }

    // * Const iterator to first element
    const_iterator begin(void) const
    {
        return const_iterator(&_array[0]);
    }

    // * Iterator to last element
    iterator end(void)
    {
        return iterator(&_array[_size]);
    }

    // * Const iterator to last element
    const_iterator end(void) const
    {
        return const_iterator(&_array[_size]);
    }

    // * Reverse iterator to last element
    reverse_iterator rbegin(void)
    {
        return reverse_iterator(iterator(&_array[_size]));
    }

    // * Const reverse iterator to last element
    const_reverse_iterator rbegin(void) const
    {
        return const_reverse_iterator(const_iterator(&_array[_size]));
    }

    // * Reverse iterator to first element
    reverse_iterator rend(void)
    {
        return reverse_iterator(iterator(&_array[0]));
    }

    // * Const reverse iterator to first element
    const_reverse_iterator rend(void) const
    {
        return const_reverse_iterator(const_iterator(&_array[0]));
    }

    // * Capacity

    // * Number of elements in the vector
    size_type size(void) const
    {
        return _size;
    }

    // * Max number of elements the vector can hold
    size_type max_size(void) const
    {
        return std::min<size_type>(_alloc.max_size(),
                                   std::numeric_limits<difference_type>::max());
    }

    // * Resize the vector, adding extra elements if the new size is greater
    // than the old size
    // * Deletes elements if the new size is lower than the old one
    void resize(size_type n, value_type val = value_type())
    {
        if (n >= max_size())
        {
            throw std::length_error("too big 😳");
        }
        if (n > _capacity)
        {
            _realloc(n);
        }
        if (n >= _size)
        {
            for (size_type i = _size; i < n; i++)
            {
                _alloc.construct(&_array[i], val);
            }
        }
        else if (n < _size)
        {
            for (size_type i = n; i < _size; i++)
            {
                _alloc.destroy(&_array[i]);
            }
        }
        _size = n;
    }

    // * Returns the capacity of the underlying array
    size_type capacity(void) const
    {
        return _capacity;
    }

    // * Is the vector empty?
    bool empty(void) const
    {
        return _size == 0;
    }

    // * Change the capacity of the vector
    void reserve(size_type n)
    {
        if (n >= max_size())
        {
            throw std::length_error("too big 😳");
        }
        if (n > _capacity)
        {
            _realloc(n);
        }
    }

    // * Element access

    // * Subscript overloads
    reference operator[](size_type i)
    {
        return _array[i];
    }
    const_reference operator[](size_type i) const
    {
        return _array[i];
    }

    // * Get element at index n of the vector, throws exception if n is out of
    // range
    reference at(size_type n)
    {
        if (n >= _size)
            throw std::out_of_range("Index is out of range 😭");
        return (_array[n]);
    }
    const_reference at(size_type n) const
    {
        if (n >= _size)
            throw std::out_of_range("Index is out of range 😭");
        return (_array[n]);
    }

    // * Returns first element of the vector
    reference front(void)
    {
        return _array[0];
    }
    const_reference front(void) const
    {
        return _array[0];
    }

    // * Returns last element of the vector
    reference back(void)
    {
        return _array[_size - 1];
    }
    const_reference back(void) const
    {
        return _array[_size - 1];
    }

    // * Returns pointer to underlying array
    value_type *data(void)
    {
        return _array;
    }
    const value_type *data(void) const
    {
        return _array;
    }

    // * Modifiers

    // * Iterator-based range assign
    template <class InputIterator>
    void assign(
        InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
            0)
    {
        if (is_one_way(first))
        {
            for (size_type i = 0; i < _size; i++)
            {
                _alloc.destroy(&_array[i]);
            }
            size_type i;
            _size = 0;
            for (i = 0; first != last; i++)
            {
                if (i >= _capacity)
                {
                    _realloc((_capacity + 1) * 2);
                }
                if (i >= _size)
                    _alloc.construct(&_array[i], *first);
                else
                    _array[i] = *first;
                first++;
                _size++;
            }
            return;
        }
        if (validate_iterators(first, last, max_size()) == false)
            return;
        const size_type dist = std::distance(first, last);
        if (dist > _capacity)
            _realloc(dist);
        for (size_type i = 0; first != last; i++)
        {
            if (i >= _size)
                _alloc.construct(&_array[i], *first);
            else
                _array[i] = *first;
            first++;
        }
        for (size_type i = dist; i < _size; i++)
        {
            _alloc.destroy(&_array[i]);
        }
        _size = dist;
    }

    // * Fill assign
    void assign(size_type n, const value_type &val)
    {
        if (n > _capacity)
        {
            _realloc(n);
        }
        for (size_type i = 0; i < _size; i++)
        {
            _alloc.destroy(&_array[i]);
        }
        for (size_type i = 0; i < n; i++)
        {
            _alloc.construct(&_array[i], val);
        }
        _size = n;
    }

    // * Adds elements to the end of the array
    void push_back(const value_type &val)
    {
        value_type val_copy = val;
        if (_size + 1 > _capacity)
        {
            reserve((_capacity + 1) * 2);
        }
        _alloc.construct(&_array[_size], val_copy);
        _size += 1;
    }

    // * Removes elements from the end of the vector
    void pop_back(void)
    {
        if (empty())
        {
            return;
        }
        _alloc.destroy(&_array[_size - 1]);
        _size -= 1;
    }

    // * Inserts an element at the position specified by the vector
    iterator insert(iterator position, const value_type &val)
    {
        const size_type insert_idx = position - begin();
        if (_size + 1 > _capacity)
        {
            _realloc((_capacity + 1) * 2);
        }
        if (_size == 0)
            _alloc.construct(&_array[0], value_type());
        else
            _alloc.construct(&_array[_size], _array[_size - 1]);
        for (size_type i = _size; i > insert_idx; i--)
        {
            _array[i] = _array[i - 1];
        }
        _alloc.destroy(&_array[insert_idx]);
        _alloc.construct(&_array[insert_idx], val);
        _size += 1;
        return iterator(&_array[insert_idx]);
    }

    // * Inserts n elements at the position specified by the vector
    void insert(iterator position, size_type n, const value_type &val)
    {
        if (n == 0)
        {
            return;
        }
        if (n >= max_size())
        {
            throw std::length_error("Too big 😳");
        }
        const size_type insert_idx = position - begin();
        if (_size + n > _capacity)
        {
            _realloc((_size + n) * 2);
        }
        if (empty() == false)
        {
            for (size_type i = _size - 1; i >= insert_idx; i--)
            {
                if (i + n >= _size)
                    _alloc.construct(&_array[i + n], _array[i]);
                else
                    _array[i + n] = _array[i];
                if (i == 0)
                    break;
            }
        }
        (void) val;
        for (size_type i = 0; i < n; i++)
        {
            if (i + insert_idx >= _size)
                _alloc.construct(&_array[i + insert_idx], val);
            else
                _array[i + insert_idx] = val;
        }
        _size += n;
    }

    // * Inserts elements between first and last into the position specified by
    // the given iterator
    template <class InputIterator>
    void insert(
        iterator position, InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
            0)
    {
        if (is_one_way(first) && first != last)
        {
            // ! REPLACE
            const size_type insert_idx = position - begin();
            vector<value_type> temp(first, last);
            if (_size + temp.size() > _capacity)
            {
                _realloc((_size + temp.size()) * 2);
            }
            if (empty() == false)
            {
                for (size_type i = _size - 1; i >= insert_idx; i--)
                {
                    if (i + temp.size() < _size)
                        _alloc.destroy(&_array[i + temp.size()]);
                    _alloc.construct(&_array[i + temp.size()], _array[i]);
                    if (i == 0)
                        break;
                }
            }
            for (size_type i = 0; i < temp.size(); i++)
            {
                if (i + insert_idx < _size)
                    _alloc.destroy(&_array[i + insert_idx]);
                _alloc.construct(&_array[i + insert_idx], temp[i]);
            }
            _size += temp.size();
            return;
        }
        const size_type dist = std::distance(first, last);
        if (dist < 0 || dist >= max_size())
        {
            return;
        }

        // ! REPLACE
        const size_type insert_idx = position - begin();
        if (_size + dist > _capacity)
        {
            _realloc((_size + dist) * 4);
        }
        if (empty() == false)
        {
            for (size_type i = _size - 1; i >= insert_idx; i--)
            {
                if (i + dist >= _size)
                {
                    _alloc.construct(&_array[i + dist], _array[i]);
                }
                else
                    _array[i + dist] = _array[i];
                if (i == 0)
                    break;
            }
        }
        for (size_type i = 0; i < dist; i++)
        {
            if (i + insert_idx >= _size)
            {
                _alloc.construct(&_array[i + insert_idx], *first);
            }
            else
                _array[i + insert_idx] = *first;
            first++;
        }
        _size += dist;
    }

    // * Erases element at position pointed to by iterator
    iterator erase(iterator position)
    {
        const size_type erase_idx = position - begin();

        if (_size == 1)
        {
            _alloc.destroy(&_array[_size - 1]);
            _size = 0;
            return iterator(&_array[0]);
        }
        if (_size > 1)
        {
            // if (erase_idx < _size)
            for (size_type i = erase_idx; i < _size - 1; i++)
            {
                _alloc.destroy(&_array[i]);
                _alloc.construct(&_array[i], _array[i + 1]);
            }
            _alloc.destroy(&_array[_size - 1]);
        }
        if (_size > 0)
        {
            _size -= 1;
        }
        if (erase_idx >= _size)
            return iterator(&_array[_size]);
        return iterator(&_array[erase_idx]);
    }

    // * Erases elements between the two given iterators
    iterator erase(iterator first, iterator last)
    {
        if (first == last)
        {
            return first;
        }
        for (iterator it = first; it != last; it++)
        {
            _alloc.destroy(it.base());
        }
        if (_size > 1)
        {
            iterator replace = first;
            for (iterator it = last; it != end(); it++)
            {
                _alloc.construct(replace.base(), *it);
                _alloc.destroy(it.base());
                replace++;
            }
        }
        if (_size == 1)
        {
            _alloc.destroy(&_array[0]);
            _size = 0;
            return iterator(&_array[0]);
        }
        if (_size > 0)
        {
            _size -= (last - first);
        }
        return iterator(&_array[first - begin()]);
    }

    // * Swaps two vectors without invalidating any iterators
    void swap(vector &x)
    {
        if (this == &x)
            return;
        pointer temp_arr = x.data();
        allocator_type temp_alloc = x.get_allocator();
        size_type temp_size = x.size();
        size_type temp_capacity = x.capacity();

        x._array = data();
        x._alloc = get_allocator();
        x._size = size();
        x._capacity = capacity();

        _array = temp_arr;
        _alloc = temp_alloc;
        _size = temp_size;
        _capacity = temp_capacity;
    }

    // * Clears all elements in the vector
    void clear(void)
    {
        if (_array != NULL)
        {
            for (size_type i = 0; i < _size; i++)
            {
                _alloc.destroy(&_array[i]);
            }
            _alloc.deallocate(_array, _capacity);
            _array = NULL;
        }
        _capacity = 0;
        _size = 0;
    }

    // * Allocators

    // * Returns allocator
    allocator_type get_allocator(void) const
    {
        return allocator_type();
    }

  private:
    // * Private helper methods

    // * Rellocates the underlying array of elements
    void _realloc(size_type new_capacity)
    {
        if (new_capacity >= max_size())
            throw std::length_error("too big 😳");
        value_type *new_array = _alloc.allocate(new_capacity);

        for (size_type i = 0; i < _size; i++)
        {
            _alloc.construct(&new_array[i], _array[i]);
            _alloc.destroy(&_array[i]);
        }
        if (_array != NULL)
            _alloc.deallocate(_array, _capacity);
        _capacity = new_capacity;
        _array = new_array;
    }
};

// * Relational operators
template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
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

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
    return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
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

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
    return lhs < rhs || lhs == rhs;
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
    return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
    return rhs < lhs || rhs == lhs;
}

// * Non-member functions
template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
{
    x.swap(y);
}
}   // namespace ft

#endif
