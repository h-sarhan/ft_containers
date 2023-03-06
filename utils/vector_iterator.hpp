/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:24 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 06:31:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"
#include <cstddef>

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
    typedef random_access_iterator_tag iterator_category;

  private:
    // * Private attributes
    pointer _ptr;

  public:
    // * Constructors and destructors
    vector_iterator(void);
    vector_iterator(pointer ptr);

    template <class U> vector_iterator(const vector_iterator<U> &old);
    template <class U> vector_iterator &operator=(const vector_iterator<U> &rhs);
    ~vector_iterator(void);

    pointer base(void) const;

    // * Iterator traversal
    vector_iterator &operator++(void);   // pre-increment
    vector_iterator &operator--(void);   // pre-decrement
    vector_iterator operator++(int);     // post-increment
    vector_iterator operator--(int);     // post-decrement

    // * Iterator comparison
    template <class U> bool operator==(const vector_iterator<U> &rhs) const;
    template <class U> bool operator!=(const vector_iterator<U> &rhs) const;
    template <class U> bool operator<(const vector_iterator<U> &rhs) const;
    template <class U> bool operator>(const vector_iterator<U> &rhs) const;
    template <class U> bool operator<=(const vector_iterator<U> &rhs) const;
    template <class U> bool operator>=(const vector_iterator<U> &rhs) const;

    // * Iterator access
    reference operator*(void);
    pointer operator->(void);
    value_type &operator[](const difference_type b);

    // * Iterator arithmetic
    template <class U> difference_type operator-(const vector_iterator<U> &rhs) const;
    vector_iterator operator+(const difference_type rhs) const;
    vector_iterator operator-(const difference_type rhs) const;
    vector_iterator &operator+=(const difference_type b);
    vector_iterator &operator-=(const difference_type b);
};

// * Non-member Iterator comparison
template <class T>
vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n,
                             const vector_iterator<T> &it);

};   // namespace ft

template <class T> ft::vector_iterator<T>::vector_iterator(void) : _ptr(0)
{
}

template <class T> ft::vector_iterator<T>::vector_iterator(pointer ptr) : _ptr(ptr)
{
}

template <class T>
template <class U>
ft::vector_iterator<T>::vector_iterator(const vector_iterator<U> &old) : _ptr(old.base())
{
}

template <class T> typename ft::vector_iterator<T>::pointer ft::vector_iterator<T>::base(void) const
{
    return _ptr;
}

template <class T>
template <class U>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator=(const vector_iterator<U> &rhs)
{
    // _traits = rhs._traits;
    _ptr = rhs.base();
    return *this;
}

template <class T> ft::vector_iterator<T>::~vector_iterator<T>(void)
{
    // ??
}

template <class T> ft::vector_iterator<T> &ft::vector_iterator<T>::operator++(void)
{
    _ptr++;
    return *this;
}

template <class T> ft::vector_iterator<T> &ft::vector_iterator<T>::operator--(void)
{
    _ptr--;
    return *this;
}

template <class T> ft::vector_iterator<T> ft::vector_iterator<T>::operator++(int)
{
    vector_iterator<T> temp = *this;
    ++(*this);
    return temp;
}

template <class T> ft::vector_iterator<T> ft::vector_iterator<T>::operator--(int)
{
    vector_iterator<T> temp = *this;
    --(*this);
    return temp;
}

template <class T>
template <class U>
bool ft::vector_iterator<T>::operator==(const vector_iterator<U> &rhs) const
{
    return _ptr == rhs.base();
}

template <class T>
template <class U>
bool ft::vector_iterator<T>::operator!=(const vector_iterator<U> &rhs) const
{
    return _ptr != rhs.base();
}

template <class T>
template <class U>
bool ft::vector_iterator<T>::operator<(const vector_iterator<U> &rhs) const
{
    return _ptr < rhs.base();
}

template <class T>
template <class U>
bool ft::vector_iterator<T>::operator>(const vector_iterator<U> &rhs) const
{
    return _ptr > rhs.base();
}

template <class T>
template <class U>
bool ft::vector_iterator<T>::operator<=(const vector_iterator<U> &rhs) const
{
    return _ptr <= rhs.base();
}

template <class T>
template <class U>
bool ft::vector_iterator<T>::operator>=(const vector_iterator<U> &rhs) const
{
    return _ptr >= rhs.base();
}

template <class T>
typename ft::vector_iterator<T>::value_type &ft::vector_iterator<T>::operator*(void)
{
    return *_ptr;
}

template <class T>
typename ft::vector_iterator<T>::value_type *ft::vector_iterator<T>::operator->(void)
{
    return _ptr;
}

template <class T>
typename ft::vector_iterator<T>::value_type &ft::vector_iterator<T>::operator[](
    const difference_type i)
{
    return _ptr[i];
}

template <class T>
template <class U>
typename ft::vector_iterator<T>::difference_type ft::vector_iterator<T>::operator-(
    const vector_iterator<U> &rhs) const
{
    return _ptr - rhs.base();
}

template <class T>
ft::vector_iterator<T> ft::vector_iterator<T>::operator+(const difference_type rhs) const
{
    return vector_iterator<T>(_ptr + rhs);
}

template <class T>
ft::vector_iterator<T> ft::vector_iterator<T>::operator-(const difference_type rhs) const
{
    return vector_iterator<T>(_ptr - rhs);
}

template <class T>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator+=(const difference_type rhs)
{
    _ptr += rhs;
    return *this;
}

template <class T>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator-=(const difference_type rhs)
{
    _ptr -= rhs;
    return *this;
}

template <class T>
ft::vector_iterator<T> ft::operator+(typename ft::vector_iterator<T>::difference_type n,
                                     const ft::vector_iterator<T> &it)
{
    return ft::vector_iterator<T>(it.base() + n);
}

#endif
