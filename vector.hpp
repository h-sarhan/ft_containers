/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:42:21 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/28 08:06:18 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP

# include <memory>
# include <stdexcept>

# define VECTOR_HPP
namespace ft
{
	template <class T, class Alloc = std::allocator<T> > class vector
	{
	public:
		// * Typedefs
		typedef T								value_type;
		typedef Alloc							allocator_type;
		typedef typename Alloc::size_type		size_type;
		typedef typename Alloc::difference_type	difference_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;
		// typedef my_iterator_type					iterator;
		// typedef my_const_iterator_type			const_iterator;
		// typedef my_reverse_iterator_type			reverse_iterator;
		// typedef my_const_reverse_iterator_type	const_reverse_iterator;

	private:
		// * Private attributes
		allocator_type	_alloc;
		value_type		*_array;
		size_type		_size;
		size_type		_capacity;

	public:
		// * Constructors and destructors
		explicit vector(const allocator_type& alloc = allocator_type());
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		vector(const vector& old);
		~vector(void);
		vector				&operator=(const vector &x);

		// * Iterators
		// iterator			begin();
		// const_iterator		begin() const;
		// iterator			end();
		// const_iterator		end() const;
		// reverse_iterator				rbegin();
		// const_reverse_iterator		rbegin() const;
		// reverse_iterator				rend();
		// const_reverse_iterator		rend() const;
		
		// * Capacity
		size_type			size(void) const;
		size_type			max_size(void) const;
		// void				resize (size_type n, value_type val = value_type());
		size_type			capacity(void) const;
		bool				empty(void) const;
		// void				reserve (size_type n);

		// * Element access
		reference			operator[](size_type i);
		const_reference		operator[](size_type i) const;
		reference			at(size_type n);
		const_reference		at(size_type n) const;
		reference			front(void);
		const_reference		front(void) const;
		reference			back(void);
		const_reference		back(void) const;
		value_type*			data(void);
		const value_type*	data(void) const;

		// * Modifiers
		// template <class InputIterator>
		// void				assign(InputIterator first, InputIterator last);
		// void				assign(size_type n, const value_type& val);
		// void				push_back(const value_type& val);
		// void				pop_back(void);
		// iterator			insert(iterator position, const value_type& val);
		// void				insert(iterator position, size_type n, const value_type& val);
		// template <class InputIterator>
		// void				insert(iterator position, InputIterator first, InputIterator last);
		// iterator			erase(iterator position);
		// iterator			erase(iterator first, iterator last);
		void				swap(vector& x);
		// ? void				clear(void);

		// * Allocators
		// ? allocator_type	get_allocator() const;
	};
	// * Relational operators
	// template <class T, class Alloc>
	// ? bool								operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// ? bool								operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// ? bool								operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// ? bool								operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// ? bool								operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	// template <class T, class Alloc>
	// ? bool								operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// * Non-member functions
	// template <class T, class Alloc>
	// ? void								swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
};

// * IMPLEMENTATION (Maybe put this in a .tpp)

// ** Constructors and destructors 
/**
 * @brief Default constructor for ft::vector
 * 
 * @param alloc Alloc, optional
 */
template <class T, class Alloc >
ft::vector<T, Alloc>::vector(const allocator_type& alloc) : _alloc(alloc), _array(_alloc.allocate(0)), _size(0), _capacity(0)
{
}

/**
 * @brief Fill constructor for ft::vector
 * 
 * @param n Initial vector size
 * @param val Default value of vector elements, optional
 * @param alloc Alloc, optional
 */
template <class T, class Alloc >
ft::vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc)
	: _alloc(alloc), _array(_alloc.allocate(n * sizeof(val))), _size(n), _capacity(n)
{
	for (size_type i = 0; i < n; i++)
	{
		_alloc.construct(&_array[i], val);
	}
}

/**
 * @brief Copy constructor for ft::vector. The copy is a deep copy
 * 
 * @param old The vector to copy from
 */
template <class T, class Alloc >
ft::vector<T, Alloc>::vector(const vector& old)
	: _alloc(old._alloc), _array(_alloc.allocate(old._capacity)), _size(old._size), _capacity(old._capacity)
{
	for (size_type i = 0; i < _size; i++)
	{
		_alloc.construct(&_array[i], old._array[i]);
	}
}

/**
 * @brief Destructor for ft::vector. Destroys the container elements and frees the memory
 * allocated for the underlying array
 * 
 */
template <class T, class Alloc>
ft::vector<T, Alloc>::~vector(void)
{
	for (size_type i = 0; i < _size; i++)
	{
		_alloc.destroy(&_array[i]);
	}
	_alloc.deallocate(_array, _capacity);
}

/**
 * @brief Copy assignment constructor for ft::vector. The copy is a deep copy
 * 
 * @param rhs Vector to copy from
 * @return Reference to itself
 */
template <class T, class Alloc>
ft::vector<T, Alloc>&								ft::vector<T, Alloc>::operator=(const ft::vector<T, Alloc>& rhs)
{
	if (this == &rhs)
	{
		return (*this);
	}
	for (size_type i = 0; i < _size; i++)
	{
		_alloc.destroy(&_array[i]);
	}
	_alloc.deallocate(_array, _capacity);
	_capacity = rhs.capacity();
	_size = rhs.size();
	_array = _alloc.allocate(_capacity * sizeof(value_type));
	for (size_type i = 0; i < _size; i++)
	{
		_alloc.construct(&_array[i], rhs._array[i]);
	}
	return (*this);
}

// ** Capacity

/**
 * @brief Returns the number of elements in the vector
 * 
 * @return Number of elements in the vector 
 */
template <class T, class Alloc >
typename ft::vector<T, Alloc>::size_type			ft::vector<T, Alloc>::size(void) const
{
	return	_size;
}

/**
 * @brief Returns the maximum amount of elements that can be held by this vector
 * 
 * @return Max number of elements
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type			ft::vector<T, Alloc>::max_size() const
{
	return _alloc.max_size();
}

/**
 * @brief Returns the number of elements vector can hold
 * 
 * @return Number of elements the vector can hold
 */
template <class T, class Alloc >
typename ft::vector<T, Alloc>::size_type			ft::vector<T, Alloc>::capacity(void) const
{
	return	_capacity;
}

/**
 * @brief Tests whether the vector is empty
 * 
 * @return true if the vector is empty, false otherwise
 */
template <class T, class Alloc>
bool	ft::vector<T, Alloc>::empty() const
{
	return _size == 0;
}

// ** Element access

/**
 * @brief Subscript operator overload
 * 
 * @param i Index
 * @return The element at index i in the vector
 */
template <class T, class Alloc >
typename ft::vector<T, Alloc>::reference			ft::vector<T, Alloc>::operator[](size_type i)
{
	return _array[i];
}

/**
 * @brief Const subscript operator overload
 * 
 * @param i Index
 * @return The element at index i in the vector
 */
template <class T, class Alloc >
typename ft::vector<T, Alloc>::const_reference		ft::vector<T, Alloc>::operator[](size_type i) const
{
	return _array[i];
}

/**
 * @brief Returns a reference to the vector element at index n.
 * Similar to subscript operator but throws an exception when n is out of range
 * 
 * @param n Index
 * @return The element at index n in the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference			ft::vector<T, Alloc>::at(size_type n)
{
	if (n >= _size)
		throw std::out_of_range("Index is out of range");
	return (_array[n]);
}

/**
 * @brief Returns a const reference to the vector element at index n.
 * Similar to subscript operator but throws an exception when n is out of range
 * 
 * @param n Index
 * @return The element at index n in the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference		ft::vector<T, Alloc>::at(size_type n) const
{
	if (n >= _size)
		throw std::out_of_range("Index is out of range");
	return (_array[n]);
}

/**
 * @brief Returns a reference to the first element of the vector.
 * Behaviour is undefined when the vector is empty
 * 
 * @return The first element of the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference			ft::vector<T, Alloc>::front(void)
{
	return _array[0];
}

/**
 * @brief Returns a const reference to the first element of the vector.
 * Behaviour is undefined when the vector is empty
 * 
 * @return The first element of the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference		ft::vector<T, Alloc>::front(void) const
{
	return _array[0];
}

/**
 * @brief Returns a reference to the last element of the vector.
 * Behaviour is undefined when the vector is empty
 * 
 * @return The last element of the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::reference			ft::vector<T, Alloc>::back(void)
{
	return _array[_size - 1];
}

/**
 * @brief Returns a const reference to the last element of the vector.
 * Behaviour is undefined when the vector is empty
 * 
 * @return The last element of the vector
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reference		ft::vector<T, Alloc>::back(void) const
{
	return _array[_size - 1];
}

/**
 * @brief Returns a pointer to the underlying array
 * 
 * @return Pointer to the underlying array
 */
template <class T, class Alloc>
typename ft::vector<T, Alloc>::value_type*			ft::vector<T, Alloc>::data(void)
{
	return _array;
}

/**
 * @brief Returns a const pointer to the underlying array
 * 
 * @return Const pointer to the underlying array
 */
template <class T, class Alloc>
const typename ft::vector<T, Alloc>::value_type*	ft::vector<T, Alloc>::data(void) const
{
	return _array;
}

// ** Modifiers

/**
 * @brief Swaps contents of current vector with the one passed as an argument.
 * Swap is performed using a temporary vector.
 * 
 * @param x Vector to swap contents with
 */
template <class T, class Alloc>
void											ft::vector<T, Alloc>::swap(ft::vector<T, Alloc> &x)
{
	if (this == &x)
		return ;
	ft::vector<T>	temp(x);
	x = *this;
	*this = temp;
}


// ** Non-member functions
/**
 * @brief Swaps the contents of the two vectors provided as arguments
 * 
 * @param x Vector 1
 * @param y Vector 2
 */
template <class T, class Alloc>
void											swap(ft::vector<T,Alloc> &x, ft::vector<T,Alloc> &y)
{
	x.swap(y);
}

#endif
