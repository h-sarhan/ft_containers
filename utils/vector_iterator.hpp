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

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

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
    vector_iterator &operator=(const vector_iterator &rhs);
    ~vector_iterator(void);

    template <class U> vector_iterator(const vector_iterator<U> &old);

    pointer base(void) const;

    // * Iterator traversal
    vector_iterator &operator++(void);   // pre-increment
    vector_iterator &operator--(void);   // pre-decrement
    vector_iterator operator++(int);     // post-increment
    vector_iterator operator--(int);     // post-decrement

    // * Iterator comparison
    bool operator==(const vector_iterator &rhs) const;
    bool operator!=(const vector_iterator &rhs) const;
    bool operator<(const vector_iterator &rhs) const;
    bool operator>(const vector_iterator &rhs) const;
    bool operator<=(const vector_iterator &rhs) const;
    bool operator>=(const vector_iterator &rhs) const;

    // * Iterator access
    reference operator*(void);
    pointer operator->(void);
    value_type &operator[](const difference_type b);

    // * Iterator arithmetic
    difference_type operator-(const vector_iterator &rhs) const;
    vector_iterator operator+(const difference_type rhs) const;
    vector_iterator operator-(const difference_type rhs) const;
    vector_iterator &operator+=(const difference_type b);
    vector_iterator &operator-=(const difference_type b);
};

// * Non-member Iterator comparison
template <class T1, class T2>
bool operator==(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2);

template <class T>
bool operator==(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2);

template <class T1, class T2>
bool operator!=(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2);

template <class T>
bool operator!=(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2);

template <class T1, class T2>
bool operator<(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2);

template <class T>
bool operator<(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2);

template <class T1, class T2>
bool operator>(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2);

template <class T>
bool operator>(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2);

template <class T1, class T2>
bool operator<=(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2);

template <class T>
bool operator<=(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2);

template <class T1, class T2>
bool operator>=(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2);

template <class T>
bool operator>=(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2);

template <class T>
ft::vector_iterator<T> operator+(typename ft::vector_iterator<T>::difference_type n,
                                 const ft::vector_iterator<T> &it);

template <class T>
typename ft::vector_iterator<T>::difference_type operator-(const ft::vector_iterator<T> &lhs,
                                                           const ft::vector_iterator<T> &rhs);
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
ft::vector_iterator<T> &ft::vector_iterator<T>::operator=(const vector_iterator &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    // _traits = rhs._traits;
    _ptr = rhs._ptr;
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

template <class T> bool ft::vector_iterator<T>::operator==(const vector_iterator &rhs) const
{
    return _ptr == rhs._ptr;
}

template <class T> bool ft::vector_iterator<T>::operator!=(const vector_iterator &rhs) const
{
    return _ptr != rhs._ptr;
}

template <class T> bool ft::vector_iterator<T>::operator<(const vector_iterator &rhs) const
{
    return _ptr < rhs._ptr;
}

template <class T> bool ft::vector_iterator<T>::operator>(const vector_iterator &rhs) const
{
    return _ptr > rhs._ptr;
}

template <class T> bool ft::vector_iterator<T>::operator<=(const vector_iterator &rhs) const
{
    return _ptr <= rhs._ptr;
}

template <class T> bool ft::vector_iterator<T>::operator>=(const vector_iterator &rhs) const
{
    return _ptr >= rhs._ptr;
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
typename ft::vector_iterator<T>::difference_type ft::vector_iterator<T>::operator-(
    const vector_iterator &rhs) const
{
    return _ptr - rhs._ptr;
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

template <class T1, class T2>
bool ft::operator==(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2)
{
    return it1.base() == it2.base();
}

template <class T>
bool ft::operator==(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2)
{
    return it1.base() == it2.base();
}

template <class T1, class T2>
bool ft::operator!=(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2)
{
    return !(it1 == it2);
}

template <class T>
bool ft::operator!=(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2)
{
    return !(it1 == it2);
}

template <class T1, class T2>
bool ft::operator<(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2)
{
    return it1.base() < it2.base();
}

template <class T>
bool ft::operator<(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2)
{
    return it1.base() < it2.base();
}

template <class T1, class T2>
bool ft::operator>(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2)
{
    return it2 < it1;
}

template <class T>
bool ft::operator>(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2)
{
    return it2 < it1;
}

template <class T1, class T2>
bool ft::operator<=(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2)
{
    return it1 < it2 || it1 == it2;
}

template <class T>
bool ft::operator<=(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2)
{
    return it1 < it2 || it1 == it2;
}

template <class T1, class T2>
bool ft::operator>=(const ft::vector_iterator<T1> &it1, const ft::vector_iterator<T2> &it2)
{
    return it1 > it2 || it1 == it2;
}

template <class T>
bool ft::operator>=(const ft::vector_iterator<T> &it1, const ft::vector_iterator<T> &it2)
{
    return it1 > it2 || it1 == it2;
}

template <class T>
ft::vector_iterator<T> ft::operator+(typename ft::vector_iterator<T>::difference_type n,
                                     const ft::vector_iterator<T> &it)
{
    return ft::vector_iterator<T>(it.base() + n);
}

template <class T>
typename ft::vector_iterator<T>::difference_type ft::operator-(const ft::vector_iterator<T> &lhs,
                                                               const ft::vector_iterator<T> &rhs)
{
    return lhs.base() - rhs.base();
}

#endif
