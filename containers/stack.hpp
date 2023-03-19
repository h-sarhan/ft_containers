/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:25:38 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/19 16:53:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <cstddef>

namespace ft
{

template <class T, class Container = vector<T> > class stack
{
  public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

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
    friend bool operator==(const stack<Type, Cont> &lhs, const stack<Type, Cont> &rhs);

    template <class Type, class Cont>
    friend bool operator!=(const stack<Type, Cont> &lhs, const stack<Type, Cont> &rhs);
    
    template <class Type, class Cont>
    friend bool operator<(const stack<Type, Cont> &lhs, const stack<Type, Cont> &rhs);

    template <class Type, class Cont>
    friend bool operator<=(const stack<Type, Cont> &lhs, const stack<Type, Cont> &rhs);

    template <class Type, class Cont>
    friend bool operator>(const stack<Type, Cont> &lhs, const stack<Type, Cont> &rhs);
    
    template <class Type, class Cont>
    friend bool operator>=(const stack<Type, Cont> &lhs, const stack<Type, Cont> &rhs);
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
