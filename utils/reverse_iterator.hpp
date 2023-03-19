/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:54:39 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/19 12:49:13 by hsarhan          ###   ########.fr       */
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
    reverse_iterator(void) : _base()
    {
    }
    explicit reverse_iterator(iterator_type it) : _base(it)
    {
    }

    template <class Iter>
    reverse_iterator(const reverse_iterator<Iter> &rev_it) : _base(rev_it.base())
    {
    }

    // * Base iterator
    iterator_type base(void) const
    {
        return _base;
    }

    // * Iterator traversal

    // * pre-increment
    reverse_iterator &operator++(void)
    {
        _base--;
        return *this;
    }

    // * pre-decrement
    reverse_iterator &operator--(void)
    {
        _base++;
        return *this;
    }

    // * post-increment
    reverse_iterator operator++(int)
    {
        reverse_iterator<Iterator> temp = *this;
        ++(*this);
        return temp;
    }
    //* post-decrement
    reverse_iterator operator--(int)
    {
        reverse_iterator<Iterator> temp = *this;
        --(*this);
        return temp;
    }

    // * Iterator access
    reference operator*(void) const
    {
        iterator_type temp = _base;
        temp--;
        return *temp;
    }
    pointer operator->(void) const
    {
        return &(operator*());
    }
    reference operator[](const difference_type i) const
    {
        return base()[-i - 1];
    }

    // * Iterator arithmetic
    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator<Iterator>(base() - n);
    }
    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator<Iterator>(base() + n);
    }
    reverse_iterator &operator+=(const difference_type n)
    {
        _base = _base - n;
        return (*this);
    }
    reverse_iterator &operator-=(const difference_type n)
    {
        _base = _base + n;
        return (*this);
    }
};

// * Non-member Iterator comparison
template <class It1, class It2>
bool operator==(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() == it2.base();
}

template <class It1, class It2>
bool operator!=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() != it2.base();
}

template <class It1, class It2>
bool operator<(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() > it2.base();
}

template <class It1, class It2>
bool operator>(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() < it2.base();
}

template <class It1, class It2>
bool operator<=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() >= it2.base();
}

template <class It1, class It2>
bool operator>=(const reverse_iterator<It1> &it1, const reverse_iterator<It2> &it2)
{
    return it1.base() <= it2.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &rev_it)
{
    return reverse_iterator<Iterator>(rev_it.base() - n);
}

template <class It1, class It2>
typename reverse_iterator<It1>::difference_type operator-(const reverse_iterator<It1> &it1,
                                                          const reverse_iterator<It2> &it2)
{
    return it2.base() - it1.base();
}

}   // namespace ft

#endif
