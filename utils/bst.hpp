/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/03 06:02:32 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
# define BST_HPP

# include <cstddef>
#include <memory>
# include "node.hpp"

namespace ft
{
	template <class KeyType, class ValType, class Compare, class Alloc >
	class bst
	{
	public:
		typedef pair<const KeyType, ValType>		value_type;

		node<value_type>				*root;
	private:
		Compare							_comp;
		Alloc							_alloc;

	public:
		bst(node<value_type> *root, Compare comp, Alloc allocator)
			: root(root), _comp(comp), _alloc(allocator) {}
		bst(const bst &old)
			: root(old.root), _comp(old._comp), _alloc(old._alloc) {}
		bst		&operator=(const bst &rhs)
		{
			if (this == &rhs)
				return *this;
			root = rhs.root;
			_comp = rhs._comp;
			_alloc = rhs._alloc;
			return *this;
		}
		void								insert(const value_type &val);
	};
};

template <class KeyType, class ValType, class Compare, class Alloc >
void							ft::bst<KeyType, ValType, Compare, Alloc>::insert(const value_type &val)
{

	node<value_type>	*new_node = _alloc.allocate(1);
	_alloc.construct(new_node, node<value_type>(val));

	node<value_type>	*x = root;
	node<value_type>	*y = NULL;
	while (x != NULL)
	{
		y = x;
		if (_comp(new_node->data.first, x->data.first))
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	new_node->parent = y;
	if (y == NULL)
	{
		root = new_node;
	}
	else if (_comp(new_node->data.first, y->data.first))
	{
		y->left = new_node;
	}
	else
	{
		y->right = new_node;
	}
}

#endif