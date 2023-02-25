/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:42:21 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/25 23:54:14 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP

# include <memory>

# define VECTOR_HPP
namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class vector
	{
	public:
		typedef T									value_type;
		typedef Allocator							allocator_type;
		typedef typename Allocator::size_type		size_type;
		typedef typename Allocator::difference_type	difference_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		// typedef my_iterator_type					iterator;
		// typedef my_const_iterator_type			const_iterator;
		// typedef my_reverse_iterator_type			reverse_iterator;
		// typedef my_const_reverse_iterator_type	const_reverse_iterator;

	// private attributes
	private:
		allocator_type _alloc;
		value_type*	_array;
		size_type	_size;
		size_type	_capacity;

	public:
		// constructors
		explicit vector(const allocator_type& alloc = allocator_type());
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

		// getters
		size_type	size(void) const;
		size_type	capacity(void) const;
	};
};


// IMPLEMENTATION (Maybe put this in a .tpp)
template <class T, class Allocator >
ft::vector<T, Allocator>::vector(const allocator_type& alloc) : _alloc(alloc), _size(0), _capacity(0)
{
}

template <class T, class Allocator >
ft::vector<T, Allocator>::vector(size_type n, const value_type& val, const allocator_type& alloc) : _alloc(alloc), _size(0), _capacity(0)
{
	_array = _alloc.allocate(n * sizeof(val));
	for (size_type i = 0; i < n; i++)
	{
		_alloc.construct(&_array[i], val);
	}
}

template <class T, class Allocator >
typename ft::vector<T, Allocator>::size_type	ft::vector<T, Allocator>::size(void) const
{
	return	_size;
}

template <class T, class Allocator >
typename ft::vector<T, Allocator>::size_type	ft::vector<T, Allocator>::capacity(void) const
{
	return	_capacity;
}


#endif