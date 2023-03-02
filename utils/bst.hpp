/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 03:04:59 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/03 03:22:13 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
# define BST_HPP

# include "node.hpp"

namespace ft
{
	template <class KeyType, class ValType>
	class bst
	{
	public:
		node<KeyType, ValType>		*root;

		bst(void) : root(0) {}
		bst(const node<KeyType, ValType> *root) : root(root){}
		bst(const bst &old) : root(old.root) {}
		bst		&operator=(const bst &rhs)
		{
			if (this == &rhs)
				return *this;
			root = rhs.root;
			return *this;
		}
	};
};
#endif