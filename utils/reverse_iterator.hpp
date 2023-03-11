/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:54:39 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/11 20:40:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
template <class Iterator> class reverse_iterator
{
  public:
    // * Member types
    typedef Iterator iterator_type;
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::pointer pointer;
    typedef typename iterator_traits<Iterator>::reference reference;

  private:
    // * Private attributes
    iterator_type _base;

  public:
    // * Constructors and destructors
    reverse_iterator(void);
    explicit reverse_iterator(iterator_type it);
    template <class Iter> reverse_iterator(const reverse_iterator<Iter> &rev_it);

    // * Base iterator
    iterator_type base(void) const;

    // * Iterator traversal
    reverse_iterator &operator++(void);   // pre-increment
    reverse_iterator &operator--(void);   // pre-decrement
    reverse_iterator operator++(int);     // post-increment
    reverse_iterator operator--(int);     // post-decrement

    // * Iterator access
    value_type &operator*(void);
    value_type *operator->(void);
    value_type &operator[](const difference_type b);

    // * Iterator arithmetic
    reverse_iterator operator+(difference_type n) const;
    reverse_iterator operator-(difference_type n) const;
    reverse_iterator &operator+=(const difference_type b);
    reverse_iterator &operator-=(const difference_type b);
};

// * Non-member Iterator comparison
template <class It1, class It2>
bool operator==(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2);

template <class It1, class It2>
bool operator!=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2);

template <class It1, class It2>
bool operator<(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2);

template <class It1, class It2>
bool operator>(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2);

template <class It1, class It2>
bool operator<=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2);

template <class It1, class It2>
bool operator>=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2);

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &rev_it);

template <class It1, class It2>
typename reverse_iterator<It1>::difference_type operator-(const reverse_iterator<It1> &lhs,
                                                          const reverse_iterator<It2> &rhs);
}   // namespace ft

template <class Iterator> ft::reverse_iterator<Iterator>::reverse_iterator(void) : _base()
{
}

template <class Iterator>
ft::reverse_iterator<Iterator>::reverse_iterator(iterator_type it) : _base(it)
{
}

template <class Iterator>
template <class Iter>
ft::reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<Iter> &rev_it)
    : _base(rev_it.base())
{
}

template <class It1, class It2>
bool ft::operator==(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() == it2.base();
}

template <class It1, class It2>
bool ft::operator!=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() != it2.base();
}

template <class It1, class It2>
bool ft::operator<(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() > it2.base();
}

template <class It1, class It2>
bool ft::operator>(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() < it2.base();
}

template <class It1, class It2>
bool ft::operator<=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() >= it2.base();
}

template <class It1, class It2>
bool ft::operator>=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() <= it2.base();
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::operator+(typename reverse_iterator<Iterator>::difference_type n,
                                             const reverse_iterator<Iterator> &rev_it)
{
    return reverse_iterator<Iterator>(rev_it.base() - n);
}

template <class It1, class It2>
typename ft::reverse_iterator<It1>::difference_type ft::operator-(const reverse_iterator<It1> &it1,
                                                                  const reverse_iterator<It2> &it2)
{
    return it2.base() - it1.base();
}

template <class Iterator>
ft::reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator++(void)
{
    _base--;
    return *this;
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator++(int)
{
    reverse_iterator<Iterator> temp = *this;
    ++(*this);
    return temp;
}

template <class Iterator>
ft::reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator--(void)
{
    _base++;
    return *this;
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator--(int)
{
    reverse_iterator<Iterator> temp = *this;
    --(*this);
    return temp;
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::value_type &ft::reverse_iterator<Iterator>::operator*(void)
{
    iterator_type temp = _base;
    temp--;
    return *temp;
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::iterator_type ft::reverse_iterator<Iterator>::base(
    void) const
{
    return _base;
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::value_type *ft::reverse_iterator<Iterator>::operator->(
    void)
{
    return &(operator*());
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::value_type &ft::reverse_iterator<Iterator>::operator[](
    const difference_type i)
{
    return base()[-i - 1];
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator+(difference_type n) const
{
    return reverse_iterator<Iterator>(base() - n);
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator-(difference_type n) const
{
    return reverse_iterator<Iterator>(base() + n);
}

template <class Iterator>
ft::reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator+=(const difference_type n)
{
    _base = _base - n;
    return (*this);
}

template <class Iterator>
ft::reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator-=(const difference_type n)
{
    _base = _base + n;
    return (*this);
}
#endif
