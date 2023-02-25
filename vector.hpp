/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:42:21 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/26 01:26:23 by hsarhan          ###   ########.fr       */
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
		// * Typedefs
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
	private:
		// * Private attributes
		allocator_type _alloc;
		value_type*	_array;
		size_type	_size;
		size_type	_capacity;


	public:
		// * Constructors
		explicit vector(const allocator_type& alloc = allocator_type());
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		vector(const vector& old);

		// * Getters
		size_type	size(void) const;
		size_type	capacity(void) const;
	
		// * Operator overloads
		reference	operator[](size_type i);
		const_reference	operator[](size_type i) const;
	};
};

// * IMPLEMENTATION (Maybe put this in a .tpp)

/**
 * @brief Default constructor for ft::vector
 * 
 * @param alloc Allocator, optional
 */
template <class T, class Allocator >
ft::vector<T, Allocator>::vector(const allocator_type& alloc) : _alloc(alloc), _array(_alloc.allocate(0)), _size(0), _capacity(0)
{
}

/**
 * @brief Copy constructor for ft::vector. The copy is a deep copy
 * 
 * @param old The vector to copy from
 */
template <class T, class Allocator >
ft::vector<T, Allocator>::vector(const vector& old) : _alloc(old._alloc), _size(old._size), _capacity(old._capacity)
{
	_array = _alloc.allocate(_capacity);
	for (size_type i = 0; i < _size; i++) {
		_array[i] = old._array[i];
	}
}

/**
 * @brief Fill constructor for ft::vector
 * 
 * @param n Initial vector size
 * @param val Default value of vector elements, optional
 * @param alloc Allocator, optional
 */
template <class T, class Allocator >
ft::vector<T, Allocator>::vector(size_type n, const value_type& val, const allocator_type& alloc)
	: _alloc(alloc), _array(_alloc.allocate(n * sizeof(val))), _size(n), _capacity(n)
{
	for (size_type i = 0; i < n; i++)
	{
		_array[i] = val;
	}
}

/**
 * @brief Returns the number of elements in the vector
 * 
 * @return Number of elements in the vector 
 */
template <class T, class Allocator >
typename ft::vector<T, Allocator>::size_type	ft::vector<T, Allocator>::size(void) const
{
	return	_size;
}

/**
 * @brief Returns the number of elements vector can hold
 * 
 * @return Number of elements the vector can hold
 */
template <class T, class Allocator >
typename ft::vector<T, Allocator>::size_type	ft::vector<T, Allocator>::capacity(void) const
{
	return	_capacity;
}

/**
 * @brief The subscript operator overload
 * 
 * @param i Index
 * @return The element at index i in the vector
 */
template <class T, class Allocator >
typename ft::vector<T, Allocator>::reference	ft::vector<T, Allocator>::operator[](size_type i)
{
	return _array[i];
}

/**
 * @brief The const subscript operator overload
 * 
 * @param i Index
 * @return The element at index i in the vector
 */
template <class T, class Allocator >
typename ft::vector<T, Allocator>::const_reference	ft::vector<T, Allocator>::operator[](size_type i) const
{
	return _array[i];
}

#endif
