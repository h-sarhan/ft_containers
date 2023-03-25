/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:24 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/23 18:02:27 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"
#include <cstddef>
#include <iterator>

namespace ft
{
template <class T> class vector_iterator
{
  public:
    // * Types
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef std::random_access_iterator_tag iterator_category;

  private:
    // * Private attributes
    pointer _ptr;

  public:
    // * Constructors and destructors
    vector_iterator(void) : _ptr(NULL)
    {
    }

    vector_iterator(pointer ptr) : _ptr(ptr)
    {
    }

    template <class U> vector_iterator(const vector_iterator<U> &old) : _ptr(old.base())
    {
    }
    template <class U> vector_iterator &operator=(const vector_iterator<U> &rhs)
    {
        _ptr = rhs.base();
        return *this;
    }
    ~vector_iterator(void)
    {
        // ??
    }

    pointer base(void) const
    {
        return _ptr;
    }

    // * Iterator traversal
    vector_iterator &operator++(void)   // pre-increment
    {
        _ptr++;
        return *this;
    }

    vector_iterator &operator--(void)   // pre-decrement
    {
        _ptr--;
        return *this;
    }
    vector_iterator operator++(int)   // post-increment
    {
        vector_iterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    vector_iterator operator--(int)   // post-decrement
    {
        vector_iterator<T> temp = *this;
        --(*this);
        return temp;
    }

    // * Iterator comparison
    template <class U> bool operator==(const vector_iterator<U> &rhs) const
    {
        return _ptr == rhs.base();
    }

    template <class U> bool operator!=(const vector_iterator<U> &rhs) const
    {
        return _ptr != rhs.base();
    }

    template <class U> bool operator<(const vector_iterator<U> &rhs) const
    {
        return _ptr < rhs.base();
    }

    template <class U> bool operator>(const vector_iterator<U> &rhs) const
    {
        return _ptr > rhs.base();
    }

    template <class U> bool operator<=(const vector_iterator<U> &rhs) const
    {
        return _ptr <= rhs.base();
    }

    template <class U> bool operator>=(const vector_iterator<U> &rhs) const
    {
        return _ptr >= rhs.base();
    }

    // * Iterator access
    reference operator*(void)
    {
        return *_ptr;
    }

    pointer operator->(void)
    {
        return _ptr;
    }

    value_type &operator[](const difference_type i)
    {
        return _ptr[i];
    }

    // * Iterator arithmetic
    template <class U> difference_type operator-(const vector_iterator<U> &rhs) const
    {
        return _ptr - rhs.base();
    }

    vector_iterator operator+(const difference_type rhs) const
    {
        return vector_iterator<T>(_ptr + rhs);
    }

    vector_iterator operator-(const difference_type rhs) const
    {
        return vector_iterator<T>(_ptr - rhs);
    }

    vector_iterator &operator+=(const difference_type rhs)
    {
        _ptr += rhs;
        return *this;
    }
    vector_iterator &operator-=(const difference_type rhs)
    {
        _ptr -= rhs;
        return *this;
    }
};

// * Non-member Iterator operator
template <class T>
vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n,
                             const vector_iterator<T> &it)
{
    return ft::vector_iterator<T>(it.base() + n);
}

}   // namespace ft

#endif
