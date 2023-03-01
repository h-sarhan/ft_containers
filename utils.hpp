/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:46:06 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/01 13:47:18 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP

# define UTILS_HPP

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2);

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2);
};

/**
 * @brief Checks if the elements in both iterators are equal
 * 
 * @param first1 First iterator
 * @param last1 End of first iterator
 * @param first2 Second iterator
 * @return true if equal, false if not equal
 */
template <class InputIterator1, class InputIterator2>
bool		ft::equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1)
	{
		if (*first1 != *first2)
		{
			return false;
		}
		first1++;
		first2++;
	}
	return true;
}

/**
 * @brief Compares the two sequences lexicographically
 * 
 * @param first1 First iterator
 * @param last1 End of first iterator
 * @param first2 Second iterator
 * @param first2 End of second iterator
 * @return true if equal, false if not equal
 */
template <class InputIterator1, class InputIterator2>
bool	ft::lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
		{
			return false;
		}
		else if (*first1 < *first2)
		{
			return true;
		}
		first1++;
		first2++;
	}
	return (first2 != last2);
}

#endif
