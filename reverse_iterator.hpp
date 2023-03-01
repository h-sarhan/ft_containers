/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:54:39 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/01 15:13:34 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	public:
		// * Member types
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
	
	private:
		// * Private attributes
		iterator_type		_base;

	public:
		// * Constructors and destructors
		reverse_iterator(void);
		explicit reverse_iterator(iterator_type it);
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it);

		// * Base iterator
		iterator_type			base(void) const;

		// * Iterator traversal
		reverse_iterator	&operator++(void); // pre-increment
		reverse_iterator	&operator--(void); // pre-decrement
		reverse_iterator	operator++(int); // post-increment
		reverse_iterator	operator--(int); // post-decrement


		// * Iterator access
		value_type			&operator*(void);
		value_type			*operator->(void);
		value_type			&operator[](const difference_type b);
		
		// * Iterator arithmetic
		reverse_iterator		operator+(difference_type n) const;
		reverse_iterator		operator-(difference_type n) const;
		reverse_iterator		&operator+=(const difference_type b);
		reverse_iterator		&operator-=(const difference_type b);

	};

	// * Non-member Iterator comparison
	template <class Iterator>
	bool													operator==(const reverse_iterator<Iterator> &it1, const reverse_iterator<Iterator> &it2);

	template <class Iterator>
	bool													operator!=(const reverse_iterator<Iterator> &it1, const reverse_iterator<Iterator> &it2);

	template <class Iterator>
	bool													operator<(const reverse_iterator<Iterator> &it1, const reverse_iterator<Iterator> &it2);

	template <class Iterator>
	bool													operator>(const reverse_iterator<Iterator> &it1, const reverse_iterator<Iterator> &it2);

	template <class Iterator>
	bool													operator<=(const reverse_iterator<Iterator> &it1, const reverse_iterator<Iterator> &it2);

	template <class Iterator>
	bool													operator>=(const reverse_iterator<Iterator> &it1, const reverse_iterator<Iterator> &it2);

	template <class Iterator>
	reverse_iterator<Iterator>								operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it);
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
};

	template <class Iterator>
	bool													ft::operator==(const ft::reverse_iterator<Iterator> &it1, const ft::reverse_iterator<Iterator> &it2)
	{
		return it1.base() == it2.base();
	}

	template <class Iterator>
	bool													ft::operator!=(const ft::reverse_iterator<Iterator> &it1, const ft::reverse_iterator<Iterator> &it2)
	{
		return it1.base() != it2.base();
	}

	template <class Iterator>
	bool													ft::operator<(const ft::reverse_iterator<Iterator> &it1, const ft::reverse_iterator<Iterator> &it2)
	{
		return it1.base() < it2.base();
	}

	template <class Iterator>
	bool													ft::operator>(const ft::reverse_iterator<Iterator> &it1, const ft::reverse_iterator<Iterator> &it2)
	{
		return it1.base() > it2.base();
	}

	template <class Iterator>
	bool													ft::operator<=(const ft::reverse_iterator<Iterator> &it1, const ft::reverse_iterator<Iterator> &it2)
	{
		return it1.base() <= it2.base();
	}

	template <class Iterator>
	bool													ft::operator>=(const ft::reverse_iterator<Iterator> &it1, const ft::reverse_iterator<Iterator> &it2)
	{
		return it1.base() >= it2.base();
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>								ft::operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it)
	{
		return rev_it + n;
	}

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type	ft::operator-(const ft::reverse_iterator<Iterator>& it1, const ft::reverse_iterator<Iterator>& it2)
	{
		return it2.base() - it1.base();
	}
	template <class Iterator>
	ft::reverse_iterator<Iterator>::reverse_iterator(void) : _base()
	{
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>::reverse_iterator(iterator_type it) : _base(it)
	{
	}

	template <class Iterator>
	template <class Iter>
	ft::reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base(rev_it._base)
	{
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>							&ft::reverse_iterator<Iterator>::operator++(void)
	{
		--_base;
		return *this;
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>							&ft::reverse_iterator<Iterator>::operator--(void)
	{
		++_base;
		return *this;
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>							ft::reverse_iterator<Iterator>::operator++(int)
	{
		iterator_type temp = _base;
		--_base;
		return reverse_iterator(temp);
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>							ft::reverse_iterator<Iterator>::operator--(int)
	{
		iterator_type temp = _base;
		++_base;
		return reverse_iterator(temp);
	}

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::value_type		&ft::reverse_iterator<Iterator>::operator*(void)
	{
		return *_base;
	}

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::iterator_type	ft::reverse_iterator<Iterator>::base(void) const
	{
		return _base;
	}

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::value_type		*ft::reverse_iterator<Iterator>::operator->(void)
	{
		return _base.operator->();
	}

	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::value_type		&ft::reverse_iterator<Iterator>::operator[](const difference_type i)
	{
		return _base[i];
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>		ft::reverse_iterator<Iterator>::operator+(difference_type n) const
	{
		return reverse_iterator(_base - n);
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>		ft::reverse_iterator<Iterator>::operator-(difference_type n) const
	{
		return reverse_iterator(_base + n);
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>		&ft::reverse_iterator<Iterator>::operator+=(const difference_type n)
	{
		*this = reverse_iterator(_base - n);
		return *this;
	}

	template <class Iterator>
	ft::reverse_iterator<Iterator>		&ft::reverse_iterator<Iterator>::operator-=(const difference_type n)
	{
		*this = reverse_iterator(_base + n);
		return *this;
	}
#endif