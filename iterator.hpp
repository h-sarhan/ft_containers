/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:44:24 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/28 21:19:21 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "iterator_traits.hpp"

namespace ft
{
	template <class T>
	class vector_iterator
	{
	public:
		// * Types
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T								*pointer;
		typedef T								&reference;
		typedef random_access_iterator_tag		iterator_category;

	private:
		// * Private attributes
		iterator_traits<vector_iterator<T> >	_traits;
		pointer									_ptr;

	public:
		// * Constructors and destructors
		vector_iterator(void);
		vector_iterator(pointer ptr);
		vector_iterator(const vector_iterator &old);
		vector_iterator	&operator=(const vector_iterator &rhs);
		~vector_iterator(void);

		// * Iterator traversal
		vector_iterator	&operator++(void); // pre-increment
		vector_iterator	&operator--(void); // pre-decrement
		vector_iterator	operator++(int); // post-increment
		vector_iterator	operator--(int); // post-decrement

		// * Iterator comparison
		bool				operator==(const vector_iterator &rhs) const;
		bool				operator!=(const vector_iterator &rhs) const;
		bool				operator<(const vector_iterator &rhs) const;
		bool				operator>(const vector_iterator &rhs) const;
		bool				operator<=(const vector_iterator &rhs) const;
		bool				operator>=(const vector_iterator &rhs) const;

		// * Iterator access
		value_type			&operator*(void);
		value_type			*operator->(void);
		value_type			&operator[](const difference_type b);
		
		// * Iterator arithmetic
		vector_iterator		operator-(const vector_iterator &rhs) const;
		vector_iterator		operator+(const difference_type rhs) const;
		vector_iterator		operator-(const difference_type rhs) const;
		vector_iterator		&operator+=(const difference_type b);
		vector_iterator		&operator-=(const difference_type b);

	};
};

template <class T>
ft::vector_iterator<T>::vector_iterator(void): _traits(), _ptr(0)
{}

template <class T>
ft::vector_iterator<T>::vector_iterator(pointer ptr): _traits(), _ptr(ptr)
{}

template <class T>
ft::vector_iterator<T>::vector_iterator(const vector_iterator &old): _traits(old._traits), _ptr(old._ptr)
{}

template <class T>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator=(const vector_iterator &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	_traits = rhs._traits;
	_ptr = rhs._ptr;
	return *this;
}

template <class T>
ft::vector_iterator<T>::~vector_iterator<T>(void)
{
	// ??
}

template <class T>
ft::vector_iterator<T>	&ft::vector_iterator<T>::operator++(void)
{
	_ptr++;
	return *this;
}

template <class T>
ft::vector_iterator<T>	&ft::vector_iterator<T>::operator--(void)
{
	_ptr--;
	return *this;
}

template <class T>
ft::vector_iterator<T>	ft::vector_iterator<T>::operator++(int)
{
	vector_iterator<T> temp = *this;
	++*this;
	return temp;
}

template <class T>
ft::vector_iterator<T>	ft::vector_iterator<T>::operator--(int)
{
	vector_iterator<T> temp = *this;
	--*this;
	return temp;
}

template <class T>
bool	ft::vector_iterator<T>::operator==(const vector_iterator &rhs) const
{
	return _ptr == rhs._ptr;
}

template <class T>
bool	ft::vector_iterator<T>::operator!=(const vector_iterator &rhs) const
{
	return _ptr != rhs._ptr;
}

template <class T>
bool	ft::vector_iterator<T>::operator<(const vector_iterator &rhs) const
{
	return _ptr < rhs._ptr;
}

template <class T>
bool	ft::vector_iterator<T>::operator>(const vector_iterator &rhs) const
{
	return _ptr > rhs._ptr;
}

template <class T>
bool	ft::vector_iterator<T>::operator<=(const vector_iterator &rhs) const
{
	return _ptr <= rhs._ptr;
}

template <class T>
bool	ft::vector_iterator<T>::operator>=(const vector_iterator &rhs) const
{
	return _ptr >= rhs._ptr;
}

template <class T>
typename ft::vector_iterator<T>::value_type			&ft::vector_iterator<T>::operator*(void)
{
	return *_ptr;
}

template <class T>
typename ft::vector_iterator<T>::value_type			*ft::vector_iterator<T>::operator->(void)
{
	return _ptr;
}

template <class T>
typename ft::vector_iterator<T>::value_type			&ft::vector_iterator<T>::operator[](const difference_type i)
{
	return _ptr[i];
}

template <class T>
ft::vector_iterator<T>								ft::vector_iterator<T>::operator-(const vector_iterator &rhs) const
{
	return vector_iterator<T>(_ptr - rhs._ptr);	
}

template <class T>
ft::vector_iterator<T>								ft::vector_iterator<T>::operator+(const difference_type rhs) const
{
	return vector_iterator<T>(_ptr + rhs);	
}

template <class T>
ft::vector_iterator<T>		ft::vector_iterator<T>::operator-(const difference_type rhs) const
{
	return vector_iterator<T>(_ptr - rhs);	
}

template <class T>
ft::vector_iterator<T>		&ft::vector_iterator<T>::operator+=(const difference_type rhs)
{
	_ptr += rhs;
	return *this;
}

template <class T>
ft::vector_iterator<T>		&ft::vector_iterator<T>::operator-=(const difference_type rhs)
{
	_ptr -= rhs;
	return *this;
}

#endif
