/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:43:47 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/25 23:54:50 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include "vector.hpp"


int	main(void)
{
	// std::vector<int> l;
	ft::vector<int> a;
	(void)a;
	// vector<int>::size_type l;
	// std::cout << sizeof(ft::vector<int>::reference) << std::endl;
	// std::vector<int>::iterator;
	
	// default constructor tests
	std::vector<int> b;
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;

	std::cout << b.capacity() << std::endl;
	std::cout << b.size() << std::endl;
}