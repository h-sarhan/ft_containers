/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:42:21 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/19 13:13:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP

#define VECTOR_HPP

#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_comparison.hpp"
#include "iterator_distance.hpp"
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"

// ! Check iterator ranges: if first == last || last < first
// ! Check if size == 0
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
        : _alloc(alloc), _array(_alloc.allocate(0)), _size(0), _capacity(0)
    {
    }

    // * Fill constructor
    explicit vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type())
        : _alloc(alloc), _size(n), _capacity(n)
    {
        _array = _alloc.allocate(n);
        for (size_type i = 0; i < n; i++)
        {
            _alloc.construct(&_array[i], val);
        }
    }

    // * Iterator range constructor
    template <class InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
           typename enable_if<!is_integral<InputIterator>::value>::type * = 0)
        : _alloc(alloc), _array(_alloc.allocate(iterator_distance(first, last))),
          _size(iterator_distance(first, last)), _capacity(_size)
    {
        size_type i = 0;
        for (InputIterator it = first; it != last; it++)
        {
            _alloc.construct(&_array[i], *it);
            i++;
        }
    }

    // * Copy constructor
    vector(const vector &old)
        : _alloc(old._alloc), _array(_alloc.allocate(old._capacity)), _size(old._size),
          _capacity(old._capacity)
    {
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
        return reverse_iterator(end());
    }

    // * Const reverse iterator to last element
    const_reverse_iterator rbegin(void) const
    {
        return const_reverse_iterator(end());
    }

    // * Reverse iterator to first element
    reverse_iterator rend(void)
    {
        return reverse_iterator(begin());
    }

    // * Const reverse iterator to first element
    const_reverse_iterator rend(void) const
    {
        return const_reverse_iterator(begin());
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
        return _alloc.max_size();
    }

    // * Resize the vector, adding extra elements if the new size is greater than the old size
    // * Deletes elements if the new size is lower than the old one
    void resize(size_type n, value_type val = value_type())
    {
        if (n >= max_size())
        {
            throw std::logic_error("Too big");
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
            throw std::logic_error("Too big");
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

    // * Get element at index n of the vector, throws exception if n is out of range
    reference at(size_type n)
    {
        if (n >= _size)
            throw std::out_of_range("Index is out of range");
        return (_array[n]);
    }
    const_reference at(size_type n) const
    {
        if (n >= _size)
            throw std::out_of_range("Index is out of range");
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
    void assign(InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value>::type * = 0)
    {
        const size_type count = iterator_distance(first, last);
        if (count > _capacity)
        {
            _realloc(count);
        }
        for (size_type i = 0; i < count; i++)
        {
            if (i < _size)
            {
                _alloc.destroy(&_array[i]);
            }
            _alloc.construct(&_array[i], *first);
            first++;
        }
        _size = count;
    }

    // * Fill assign
    void assign(size_type n, const value_type &val)
    {
        if (n > _capacity)
        {
            _realloc(n);
        }
        for (size_type i = 0; i < n; i++)
        {
            if (i < _size)
            {
                _alloc.destroy(&_array[i]);
            }
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
    // ! CAN BE PROTECTED
    iterator insert(iterator position, const value_type &val)
    {
        const size_type insert_idx = position - begin();
        if (_size + 1 > _capacity)
        {
            _realloc((_capacity + 1) * 2);
        }
        for (size_type i = _size; i > insert_idx; i--)
        {
            _alloc.construct(&_array[i], _array[i - 1]);
            _alloc.destroy(&_array[i - 1]);
        }
        _alloc.construct(&_array[insert_idx], val);
        _size += 1;
        return iterator(&_array[insert_idx]);
    }

    // * Inserts n elements at the position specified by the vector
    // ! CAN BE PROTECTED
    void insert(iterator position, size_type n, const value_type &val)
    {
        if (n == 0)
        {
            return;
        }
        const size_type insert_idx = position - begin();
        if (_size + n > _capacity)
        {
            _realloc(_size + n);
        }
        if (empty() == false)
        {
            for (size_type i = _size - 1; i >= insert_idx; i--)
            {
                _alloc.construct(&_array[i + n], _array[i]);
                _alloc.destroy(&_array[i]);
                if (i == 0)
                    break;
            }
        }
        for (size_type i = 0; i < n; i++)
        {
            _alloc.construct(&_array[i + insert_idx], val);
        }
        _size += n;
    }

    // * Inserts elements between first and last into the position specified by the given iterator
    // ! CAN BE PROTECTED

    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value>::type * = 0)
    {
        const size_type insert_idx = position - begin();
        const size_type n = iterator_distance(first, last);

        if (n == 0)
        {
            return;
        }
        if (_size + n > _capacity)
        {
            _realloc(_size + n);
        }
        if (empty() == false)
        {
            for (size_type i = _size - 1; i >= insert_idx; i--)
            {
                _alloc.construct(&_array[i + n], _array[i]);
                _alloc.destroy(&_array[i]);
                if (i == 0)
                    break;
            }
        }
        for (size_type i = 0; i < n; i++)
        {
            _alloc.construct(&_array[i + insert_idx], *first);
            first++;
        }
        _size += n;
    }

    // * Erases element at position pointed to by iterator
    // ! CAN BE PROTECTED
    iterator erase(iterator position)
    {
        const size_type erase_idx = position - begin();

        _alloc.destroy(&_array[erase_idx]);
        if (_size > 1)
        {
            for (size_type i = erase_idx; i < _size - 1; i++)
            {
                _alloc.construct(&_array[i], _array[i + 1]);
                _alloc.destroy(&_array[i + 1]);
            }
        }
        if (_size > 0)
        {
            _size -= 1;
        }
        return iterator(&_array[erase_idx]);
    }

    // * Erases elements between the two given iterators
    // ! CAN BE PROTECTED
    // ! TEST THIS FUNCTION WHEN LAST - FIRST == 1
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
        for (size_type i = 0; i < _size; i++)
        {
            _alloc.destroy(&_array[i]);
        }
        _alloc.deallocate(_array, _capacity);
        _array = _alloc.allocate(0);
        _capacity = 0;
        _size = 0;
    }

    // * Allocators

    // * Returns allocator
    allocator_type get_allocator(void) const
    {
        return _alloc;
    }

  private:
    // * Private helper methods

    // * Rellocates the underlying array of elements
    void _realloc(size_type new_capacity)
    {
        value_type *new_array = _alloc.allocate(new_capacity);
        for (size_type i = 0; i < _size; i++)
        {
            _alloc.construct(&new_array[i], _array[i]);
            _alloc.destroy(&_array[i]);
        }
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
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
template <class T, class Alloc> void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
{
    x.swap(y);
}
}   // namespace ft

#endif
