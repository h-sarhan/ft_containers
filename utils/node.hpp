/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:07:03 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/31 12:15:09 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#include <cstddef>
#include <memory>

#define BLACK false
#define RED   true
#define LEFT  0
#define RIGHT 1

namespace ft
{
template <class DataType> struct node
{
    typedef bool color;
    typedef DataType data_type;
    typedef std::allocator<DataType> allocator_type;

  private:
    allocator_type _alloc;

  public:
    data_type *data;
    node<DataType> *child[2];
    color col;

    // * Default constructor
    node(void) : _alloc(allocator_type()), data(_alloc.allocate(1)), col(BLACK)
    {
        _alloc.construct(data, data_type());
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
    }

    // * Constructor
    node(const data_type &val, bool color)
        : _alloc(allocator_type()), data(_alloc.allocate(1)), col(color)
    {
        _alloc.construct(data, val);
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
    }

    // * Copy constructor
    node(const node &old) : _alloc(old._alloc), data(_alloc.allocate(1)), col(old.col)
    {
        _alloc.construct(data, *old.data);
        child[LEFT] = old.child[LEFT];
        child[RIGHT] = old.child[RIGHT];
    }

    // * Copy assignment constructor
    node &operator=(const node &rhs)
    {
        if (this == &rhs)
            return *this;
        node *old_data = data;
        _alloc.allocate(data, 1);
        _alloc.construct(data, *rhs.data);
        _alloc.destroy(old_data);
        _alloc.deallocate(old_data, 1);
        child[LEFT] = rhs.child[LEFT];
        child[RIGHT] = rhs.child[RIGHT];
        col = rhs.col;
        return *this;
    }

    void    replace_data(data_type &new_data)
    {
        _alloc.destroy(data);
        _alloc.deallocate(data, 1);
        data = _alloc.allocate(1);
        _alloc.construct(data, new_data);
    }

    ~node(void)
    {
        _alloc.destroy(data);
        _alloc.deallocate(data, 1);
    }
};
}   // namespace ft

#endif
