/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:42:21 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 06:27:36 by hsarhan          ###   ########.fr       */
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
// ! Check range insert
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
    explicit vector(const allocator_type &alloc = allocator_type());

    explicit vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type());

    template <class InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
           typename enable_if<!is_integral<InputIterator>::value>::type * = 0);

    vector(const vector &old);

    vector &operator=(const vector &x);

    ~vector(void);

    // * Iterators
    iterator begin(void);
    const_iterator begin(void) const;

    iterator end(void);
    const_iterator end(void) const;

    reverse_iterator rbegin(void);
    const_reverse_iterator rbegin(void) const;

    reverse_iterator rend(void);
    const_reverse_iterator rend(void) const;

    // * Capacity
    size_type size(void) const;

    size_type max_size(void) const;

    void resize(size_type n, value_type val = value_type());

    size_type capacity(void) const;

    bool empty(void) const;

    void reserve(size_type n);

    // * Element access
    reference operator[](size_type i);
    const_reference operator[](size_type i) const;

    reference at(size_type n);
    const_reference at(size_type n) const;

    reference front(void);
    const_reference front(void) const;

    reference back(void);
    const_reference back(void) const;

    value_type *data(void);
    const value_type *data(void) const;

    // * Modifiers
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value>::type * = 0);
    void assign(size_type n, const value_type &val);

    void push_back(const value_type &val);

    void pop_back(void);

    iterator insert(iterator position, const value_type &val);
    void insert(iterator position, size_type n, const value_type &val);
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value>::type * = 0);

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);

    void swap(vector &x);

    void clear(void);

    // * Allocators
    allocator_type get_allocator(void) const;

  private:
    // * Private helper methods
    void _realloc(size_type new_capacity);
};

// * Relational operators
template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

// * Non-member functions
template <class T, class Alloc> void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);
};   // namespace ft

// * IMPLEMENTATION (Maybe put this in a .tpp)

// ** Constructors and destructors
/**
 * @brief Default constructor for ft::vector
 *
 * @param alloc Allocator object, optional
 */
template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type &alloc)
    : _alloc(alloc), _array(_alloc.allocate(0)), _size(0), _capacity(0)
{
}

/**
 * @brief Fill constructor for ft::vector
 *
 * @param n Initial vector size
 * @param val Default value of vector elements, optional
 * @param alloc Allocator object, optional
 */
template <class T, class Alloc>
ft::vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc)
    : _alloc(alloc), _size(n), _capacity(n)
{
    _array = _alloc.allocate(n);
    for (size_type i = 0; i < n; i++)
    {
        _alloc.construct(&_array[i], val);
    }
}

/**
 * @brief Range constructor for ft::vector
 * Generates a new vector with contents from the two iterators
 *
 * @param first Iterator pointing to the beginning of the content
 * @param last Iterator pointing to the end of the content
 * @param alloc Allocator object, optional
 */
template <class T, class Alloc>
template <class InputIterator>
ft::vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc,
                             typename enable_if<!is_integral<InputIterator>::value>::type *)
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

/**
 * @brief Copy constructor for ft::vector. The copy is a deep copy
 *
 * @param old The vector to copy from
 */
template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const vector &old)
    : _alloc(old._alloc), _array(_alloc.allocate(old._capacity)), _size(old._size),
      _capacity(old._capacity)
{
    for (size_type i = 0; i < _size; i++)
    {
        _alloc.construct(&_array[i], old._array[i]);
    }
}

/**
 * @brief Destructor for ft::vector. Destroys the container elements and frees the memory
 * allocated for the underlying array
 *
 */
template <class T, class Alloc> ft::vector<T, Alloc>::~vector(void)
{
    for (size_type i = 0; i < _size; i++)
    {
        _alloc.destroy(&_array[i]);
    }
    _alloc.deallocate(_array, _capacity);
}

/**
 * @brief Copy assignment constructor for ft::vector. The copy is a deep copy
 *
 * @param rhs Vector to copy from
 * @return Reference to itself
 */
template <class T, class Alloc>
ft::vector<T, Alloc> &ft::vector<T, Alloc>::operator=(const vector<T, Alloc> &rhs)
{
    if (this == &rhs)
    {
        return (*this);
    }
    for (size_type i = 0; i < _size; i++)
    {
        _alloc.destroy(&_array[i]);
    }
    _alloc.deallocate(_array, _capacity);
    _capacity = rhs.capacity();
    _size = rhs.size();
    _array = _alloc.allocate(_capacity);
    for (size_type i = 0; i < _size; i++)
    {
        _alloc.construct(&_array[i], rhs._array[i]);
    }
    return (*this);
}

// ** Iterators

/**
 * @brief Returns an iterator to the first element of the vector
 *
 * @return Iterator to the first element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::begin(void)
{
    return iterator(&_array[0]);
}

/**
 * @brief Returns a const iterator to the first element of the vector
 *
 * @return Const iterator to the first element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator ft::vector<T, Alloc>::begin(void) const
{
    return const_iterator(&_array[0]);
}

/**
 * @brief Returns an iterator to the last element of the vector
 *
 * @return Iterator to the last element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::end(void)
{
    return iterator(&_array[_size]);
}

/**
 * @brief Returns a const iterator to the last element of the vector
 *
 * @return Const iterator to the last element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator ft::vector<T, Alloc>::end(void) const
{
    return const_iterator(&_array[_size]);
}

/**
 * @brief Returns a reverse iterator to the first element of the vector
 *
 * @return Reverse iterator to the first element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator ft::vector<T, Alloc>::rbegin(void)
{
    return reverse_iterator(end());
}

/**
 * @brief Returns a const reverse iterator to the first element of the vector
 *
 * @return Const reverse iterator to the first element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator ft::vector<T, Alloc>::rbegin(void) const
{
    return const_reverse_iterator(end());
}

/**
 * @brief Returns a reverse iterator to the last element of the vector
 *
 * @return Reverse iterator to the last element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator ft::vector<T, Alloc>::rend(void)
{
    return reverse_iterator(begin());
}

/**
 * @brief Returns a const reverse iterator to the last element of the vector
 *
 * @return Const reverse iterator to the last element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator ft::vector<T, Alloc>::rend(void) const
{
    return const_reverse_iterator(begin());
}

// ** Capacity

/**
 * @brief Returns the number of elements in the vector
 *
 * @return Number of elements in the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::size(void) const
{
    return _size;
}

/**
 * @brief Returns the maximum amount of elements that can be held by this vector
 *
 * @return Max number of elements
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::max_size(void) const
{
    return _alloc.max_size();
}

/**
 * @brief Resizes the vector so that it fits n elements
 * Fills in extra elements if n > size
 * Truncates the vector if n < size
 * Reallocates if necessaary. n > capacity
 *
 * @param n New size of the array
 * @param val, optional Value of newly created objects
 */
template <class T, class Alloc> void ft::vector<T, Alloc>::resize(size_type n, value_type val)
{
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

/**
 * @brief Returns the number of elements vector can hold
 *
 * @return Number of elements the vector can hold
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::capacity(void) const
{
    return _capacity;
}

/**
 * @brief Tests whether the vector is empty
 *
 * @return true if the vector is empty, false otherwise
 */
template <class T, class Alloc> bool ft::vector<T, Alloc>::empty(void) const
{
    return _size == 0;
}

/**
 * @brief Increases vector capacity if it is less than n
 *
 * @param n New vector capacity
 */
template <class T, class Alloc> void ft::vector<T, Alloc>::reserve(size_type n)
{
    if (n > _capacity)
    {
        _realloc(n);
    }
}

// ** Element access

/**
 * @brief Subscript operator overload
 *
 * @param i Index
 * @return The element at index i in the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::operator[](size_type i)
{
    return _array[i];
}

/**
 * @brief Const subscript operator overload
 *
 * @param i Index
 * @return The element at index i in the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::operator[](size_type i) const
{
    return _array[i];
}

/**
 * @brief Returns a reference to the vector element at index n.
 * Similar to subscript operator but throws an exception when n is out of range
 *
 * @param n Index
 * @return The element at index n in the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::at(size_type n)
{
    if (n >= _size)
        throw std::out_of_range("Index is out of range");
    return (_array[n]);
}

/**
 * @brief Returns a const reference to the vector element at index n.
 * Similar to subscript operator but throws an exception when n is out of range
 *
 * @param n Index
 * @return The element at index n in the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::at(size_type n) const
{
    if (n >= _size)
        throw std::out_of_range("Index is out of range");
    return (_array[n]);
}

/**
 * @brief Returns a reference to the first element of the vector.
 * Behaviour is undefined when the vector is empty
 *
 * @return The first element of the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::front(void)
{
    return _array[0];
}

/**
 * @brief Returns a const reference to the first element of the vector.
 * Behaviour is undefined when the vector is empty
 *
 * @return The first element of the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::front(void) const
{
    return _array[0];
}

/**
 * @brief Returns a reference to the last element of the vector.
 * Behaviour is undefined when the vector is empty
 *
 * @return The last element of the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::back(void)
{
    return _array[_size - 1];
}

/**
 * @brief Returns a const reference to the last element of the vector.
 * Behaviour is undefined when the vector is empty
 *
 * @return The last element of the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::back(void) const
{
    return _array[_size - 1];
}

/**
 * @brief Returns a pointer to the underlying array
 *
 * @return Pointer to the underlying array
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::value_type *ft::vector<T, Alloc>::data(void)
{
    return _array;
}

/**
 * @brief Returns a const pointer to the underlying array
 *
 * @return Const pointer to the underlying array
 */
template <class T, class Alloc>
const typename ft::vector<T, Alloc>::value_type *ft::vector<T, Alloc>::data(void) const
{
    return _array;
}

// ** Modifiers

/**
 * @brief Replaces the vector's contents with the elements between the last and first iterators
 *        A reallocation takes place if the number of elements to add is greater than the capacity
 * of the vector
 *
 * @param first Beginning iterator
 * @param last End iterator
 */
template <class T, class Alloc>
template <class InputIterator>
void ft::vector<T, Alloc>::assign(InputIterator first, InputIterator last,
                                  typename enable_if<!is_integral<InputIterator>::value>::type *)
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

/**
 * @brief Replaces the vector's contents with n elements of value val.
 * If n is greater than the capcity of the vector then a reallocation takes place
 *
 * @param n Number of elements
 * @param val Default value of elements
 */
template <class T, class Alloc>
void ft::vector<T, Alloc>::assign(size_type n, const value_type &val)
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

/**
 * @brief Adds an element at the end of the vector. Reallocates if necessary
 *
 * @param val Element to add
 */
template <class T, class Alloc> void ft::vector<T, Alloc>::push_back(const value_type &val)
{
    value_type val_copy = val;
    if (_size + 1 > _capacity)
    {
        reserve((_capacity + 1) * 2);
    }
    _alloc.construct(&_array[_size], val_copy);
    _size += 1;
}

/**
 * @brief Removes an element from the end of the vector.
 *
 */
template <class T, class Alloc> void ft::vector<T, Alloc>::pop_back(void)
{
    _alloc.destroy(&_array[_size - 1]);
    _size -= 1;
}

/**
 * @brief Inserts a single element at the position specified.
 *
 * @param position Position to place the new element
 * @param val The element to place
 * @return An iterator to the new element
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::insert(iterator position,
                                                                     const value_type &val)
{
    const size_type insert_idx = position - begin();
    if (_size + 1 > _capacity)
    {
        _realloc((_capacity + 1) * 2);
    }
    for (size_type i = _size; i > insert_idx; i--)
    {
        _alloc.construct(&_array[i], _array[i - 1]);
    }
    _alloc.construct(&_array[insert_idx], val);
    _size += 1;
    return iterator(&_array[insert_idx]);
}

/**
 * @brief Inserts n elements at the position specified
 *
 * @param position Position to place the new elements
 * @param n Number of elements to place
 * @param val The value of the elements
 */
template <class T, class Alloc>
void ft::vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val)
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

/**
 * @brief Inserts elements into the vector based from the iterators passed to it.
 *
 * @param position Where to place the elements
 * @param first Beginning of the iterator
 * @param last End of the iterator
 */
template <class T, class Alloc>
template <class InputIterator>
void ft::vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last,
                                  typename enable_if<!is_integral<InputIterator>::value>::type *)
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

/**
 * @brief Erases the element pointed to by the iterator
 *
 * @param position Iterator pointing to the element being erased
 * @return Iterator to the element that is now at the erased element's place
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::erase(iterator position)
{
    const size_type erase_idx = position - begin();

    _alloc.destroy(&_array[erase_idx]);
    if (_size > 1)
    {
        for (size_type i = erase_idx; i < _size - 1; i++)
        {
            _alloc.construct(&_array[i], _array[i + 1]);
        }
    }
    if (_size > 0)
    {
        _size -= 1;
    }
    return iterator(&_array[erase_idx]);
}

/**
 * @brief Erases the elements pointed to by the iterators
 *
 * @param first An iterator pointing to where to start erasing
 * @param last An iterator pointing to where to stop erasing
 * @return Iterator to the element that is now at the erased element's place
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::erase(iterator first, iterator last)
{
    const size_type erase_idx = first - begin();
    const size_type n = iterator_distance(first, last);

    if (n == 0)
    {
        return first;
    }
    for (size_type i = erase_idx; i < n; i++)
    {
        _alloc.destroy(&_array[i]);
    }
    if (_size > 1)
    {
        for (size_type i = erase_idx; i < _size - 1; i++)
        {
            _alloc.construct(&_array[i], _array[i + n]);
        }
    }
    if (_size > 0)
    {
        _size -= n;
    }
    return iterator(&_array[erase_idx]);
}

/**
 * @brief Swaps contents of current vector with the one passed as an argument.
 * Swap is performed using a temporary vector.
 *
 * @param x Vector to swap contents with
 */
template <class T, class Alloc> void ft::vector<T, Alloc>::swap(vector<T, Alloc> &x)
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

/**
 * @brief Clears the contents of the vector, deallocates the memory associated
 * with it and sets size and capacity to zero
 *
 */
template <class T, class Alloc> void ft::vector<T, Alloc>::clear(void)
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

// ** Allocators

/**
 * @brief Returns the allocator object that is used by the vector class
 *
 * @return ft::vector<T, Alloc>::allocator_type
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::allocator_type ft::vector<T, Alloc>::get_allocator(void) const
{
    return _alloc;
}

// * Private helper methods

/**
 * @brief Reallocates the vector's underlying array by allocating a new array,
 * copying all the values from the old array to the new one, and destroying the old array
 * Also changes the vector's capacity
 *
 * @param new_capacity The vector's new capacity
 */
template <class T, class Alloc> void ft::vector<T, Alloc>::_realloc(size_type new_capacity)
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

// ** Relational operators

/**
 * @brief Equality operator overload method
 *
 * @param lhs Left-handside vector
 * @param rhs Right-handside vector
 * @return true if the two vectors are equal, false otherwise
 */
template <class T, class Alloc>
bool ft::operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
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

/**
 * @brief Not equals operator overload method
 *
 * @param lhs Left-handside vector
 * @param rhs Right-handside vector
 * @return true if the two vectors are not equal, false otherwise
 */
template <class T, class Alloc>
bool ft::operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief Less than operator overload method
 *
 * @param lhs Left-handside vector
 * @param rhs Right-handside vector
 * @return true if the left vector is less than the right one
 */
template <class T, class Alloc>
bool ft::operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
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

/**
 * @brief Less than or equal operator overload method
 *
 * @param lhs Left-handside vector
 * @param rhs Right-handside vector
 * @return true if the left vector is less than or equal to the right one
 */
template <class T, class Alloc>
bool ft::operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
    return lhs < rhs || lhs == rhs;
}

/**
 * @brief Greater than operator overload method
 *
 * @param lhs Left-handside vector
 * @param rhs Right-handside vector
 * @return true if the left vector is greater than  the right one
 */
template <class T, class Alloc>
bool ft::operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
    return rhs < lhs;
}

/**
 * @brief Greater than or equal operator overload method
 *
 * @param lhs Left-handside vector
 * @param rhs Right-handside vector
 * @return true if the left vector is greater than or equal to the right one
 */
template <class T, class Alloc>
bool ft::operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
    return rhs < lhs || rhs == lhs;
}

// ** Non-member functions
/**
 * @brief Swaps the contents of the two vectors provided as arguments
 *
 * @param x Vector 1
 * @param y Vector 2
 */
template <class T, class Alloc> void ft::swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
{
    x.swap(y);
}

#endif
