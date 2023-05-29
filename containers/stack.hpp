/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:25:38 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/29 23:57:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <cstddef>

namespace ft
{

template <class T, class Container = vector<T> > class stack
{
  public:
    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

  protected:
    container_type c;

  public:
    explicit stack(const container_type &ctnr = container_type()) : c(ctnr)
    {
    }

    bool empty(void) const
    {
        return c.empty();
    }

    size_type size(void) const
    {
        return c.size();
    }

    value_type &top()
    {
        return c.back();
    }

    const value_type &top() const
    {
        return c.back();
    }

    void push(const value_type &val)
    {
        c.push_back(val);
    }

    void pop(void)
    {
        c.pop_back();
    }

    template <class Type, class Cont>
    friend bool operator==(const stack<Type, Cont> &lhs,
                           const stack<Type, Cont> &rhs);

    template <class Type, class Cont>
    friend bool operator!=(const stack<Type, Cont> &lhs,
                           const stack<Type, Cont> &rhs);

    template <class Type, class Cont>
    friend bool operator<(const stack<Type, Cont> &lhs,
                          const stack<Type, Cont> &rhs);

    template <class Type, class Cont>
    friend bool operator<=(const stack<Type, Cont> &lhs,
                           const stack<Type, Cont> &rhs);

    template <class Type, class Cont>
    friend bool operator>(const stack<Type, Cont> &lhs,
                          const stack<Type, Cont> &rhs);

    template <class Type, class Cont>
    friend bool operator>=(const stack<Type, Cont> &lhs,
                           const stack<Type, Cont> &rhs);
};

template <class T, class Container>
bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return lhs.c != rhs.c;
}

template <class T, class Container>
bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return lhs.c <= rhs.c;
}

template <class T, class Container>
bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return lhs.c > rhs.c;
}

template <class T, class Container>
bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
{
    return lhs.c >= rhs.c;
}
}   // namespace ft
#endif
