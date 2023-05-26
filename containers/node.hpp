/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:10:18 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/26 19:52:58 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#define LEFT  0
#define RIGHT 1
#include <cstddef>

// * T will be a key value pair for map
// * T will be a key for set
template <class T, class KeyCompare> class node
{
  protected:
    KeyCompare _key_comp;

  public:
    T *data;
    node *child[2];
    node *parent;

    node(const T *data, KeyCompare comp) : data(data), parent(NULL), _key_comp(comp)
    {
        child[LEFT] = NULL;
        child[RIGHT] = NULL;
    }
    bool operator<(const node *node) const = 0;
    bool operator>(const node *node) const = 0;
    bool operator==(const node *node) const = 0;
};

template <class KeyValuePair> class map_node
{
  public:
    typedef typename KeyValuePair::first_type key;

    bool operator<(const map_node *node) const
    {
        return _key_comp(this->data->first, node->data->first);
    }

    bool operator>(const map_node *node) const
    {
        return _key_comp(node->data->first, this->data->first);
    }

    bool operator==(const map_node *node) const
    {
        return _key_comp(node->data->first, this->data->first) == false &&
               _key_comp(this->data->first, node->data->first) == false;
    }

    bool operator<(const key &key) const
    {
        return _key_comp(this->data->first, key);
    }

    bool operator>(const key &key) const
    {
        return _key_comp(this->data->first, key);
    }

    bool operator==(const key &key) const
    {
        return _key_comp(key, this->data->first) == false &&
               _key_comp(this->data->first, key) == false;
    }
};

template <class Key> class set_node
{
  public:
    typedef Key key;

    bool operator<(const key *node) const
    {
        return _key_comp(this->data, node->data);
    }

    bool operator>(const key *node) const
    {
        return _key_comp(node->data, this->data);
    }

    bool operator==(const key *node) const
    {
        return _key_comp(node->data, this->data) == false &&
               _key_comp(this->data, node->data) == false;
    }

    bool operator<(const key &key) const
    {
        return _key_comp(this->data, key);
    }

    bool operator>(const key &key) const
    {
        return _key_comp(this->data, key);
    }

    bool operator==(const key &key) const
    {
        return _key_comp(key, this->data) == false && _key_comp(this->data, key) == false;
    }
};

#endif
