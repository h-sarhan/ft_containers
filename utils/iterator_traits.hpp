/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:48:10 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/07 09:03:52 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
struct input_iterator_tag
{
};

struct output_iterator_tag
{
};

struct forward_iterator_tag
{
};

struct bidirectional_iterator_tag
{
};

struct random_access_iterator_tag
{
};

template <class Iterator> class iterator_traits
{
  public:
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};
}   // namespace ft

#endif
