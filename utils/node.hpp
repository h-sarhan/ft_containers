/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:07:03 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/03 03:19:45 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

#include "pair.hpp"

namespace ft
{
	template <class KeyType, class ValType>
	class node
	{
	public:
		KeyType					key;
		ValType					val;
		node<KeyType, ValType>	*parent;
		node<KeyType, ValType>	*left;
		node<KeyType, ValType>	*right;

		node(void)
			: key(KeyType()), val(ValType()), parent(0), left(0), right(0){}
		node(const pair<KeyType, ValType> &pair)
			: key(pair.first), val(pair.second), parent(0), left(0), right(0){}
		node(const node &old) : key(old.key), val(old.val), parent(old.parent), left(old.left), right(old.right){}
		node		&operator=(const node &rhs)
		{
			if (this == &rhs)
				return *this;
			key = rhs.key;
			val = rhs.val;
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			return *this;
		}
	};
};

#endif