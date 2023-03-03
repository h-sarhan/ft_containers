/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/03 14:08:35 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
# define BST_HPP

# include <cstddef>
# include <memory>
# include <iostream>
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
		void								traverse(void) const;
		void								traverse(node<value_type> *node) const;
	};
};

template <class KeyType, class ValType, class Compare, class Alloc >
void							ft::bst<KeyType, ValType, Compare, Alloc>::insert(const value_type &val)
{
	node<value_type>	*new_node = _alloc.allocate(1);
	_alloc.construct(new_node, node<value_type>(val));


	node<value_type>	*end = root;
	node<value_type>	*end_parent = NULL;
	while (end != NULL)
	{
		end_parent = end;
		if (_comp(new_node->data.first, end->data.first))
		{
			end = end->left;
		}
		else
		{
			end = end->right;
		}
	}
	new_node->parent = end_parent;
	if (end_parent == NULL)
	{
		root = new_node;
	}
	else if (_comp(new_node->data.first, end_parent->data.first))
	{
		end_parent->left = new_node;
	}
	else
	{
		end_parent->right = new_node;
	}
}

template <class KeyType, class ValType, class Compare, class Alloc>
void						ft::bst<KeyType, ValType, Compare, Alloc>::traverse(node<value_type> *node) const
{
	if (node != NULL)
	{
		traverse(node->left);
		std::cout << node->data.second << std::endl;
		traverse(node->right);
	}
}



#endif
