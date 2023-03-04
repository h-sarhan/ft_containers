/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:16:13 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 06:30:49 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
template <class T1, class T2> struct pair
{
    // * Member types
    typedef T1 first_type;
    typedef T2 second_type;

    // * Public member attributes
    first_type first;
    second_type second;

    // * Constructors
    pair(void);
    template <class U, class V> pair(const pair<U, V> &old);
    pair(const first_type &a, const second_type &b);

    // * Copy assignment
    pair &operator=(const pair &pr);
};

// * Relational operators
template <class T1, class T2> bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
template <class T1, class T2> bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
template <class T1, class T2> bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
template <class T1, class T2> bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
template <class T1, class T2> bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
template <class T1, class T2> bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);
};   // namespace ft

template <class T1, class T2> ft::pair<T1, T2>::pair(void) : first(T1()), second(T2())
{
}

template <class T1, class T2>
template <class U, class V>
ft::pair<T1, T2>::pair(const ft::pair<U, V> &old) : first(old.first), second(old.second)
{
}

template <class T1, class T2>
ft::pair<T1, T2>::pair(const first_type &a, const second_type &b) : first(a), second(b)
{
}

template <class T1, class T2> ft::pair<T1, T2> &ft::pair<T1, T2>::operator=(const pair &pr)
{
    first = pr.first;
    second = pr.second;
}

template <class T1, class T2> bool ft::operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2> bool ft::operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
    return !(lhs == rhs);
}

template <class T1, class T2> bool ft::operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2> bool ft::operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
    return !(rhs < lhs);
}

template <class T1, class T2> bool ft::operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
    return rhs < lhs;
}

template <class T1, class T2> bool ft::operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
    return !(lhs < rhs);
}

#endif
