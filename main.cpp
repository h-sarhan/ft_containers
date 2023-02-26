/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:43:47 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/26 14:50:57 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <vector>
#include <iostream>
#include "vector.hpp"


/**
 * @brief Prints the contents of a std::vector or ft::vector
 * 
 * @tparam Vec std or ft vector
 * @param vec The vector that you want to print the contents of
 * @param message Message to print before printing the contents of the vector
 */
template <typename Vec>
void	printVec(const Vec& vec, const std::string& message)
{
	std::cout << message << std::endl;
	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
	}
}

/**
 * @brief Tests for default constructor
 * 
 * @test Check size and capacity with empty vector
 * @test Check subscript operator with empty vector
 * 
 */
void	defaultConstructorTests(void)
{
	std::cout << "Testing default constructor" << std::endl;
	
	ft::vector<int> ftVec;
	std::vector<int> stdVec;
	std::cout << "STDLIB Vector" << std::endl;
	std::cout << "Capacity = " << stdVec.capacity() << std::endl;
	std::cout << "Size = " << stdVec.size() << std::endl;

	std::cout << "FT Vector" << std::endl;
	std::cout << "Capacity = " << ftVec.capacity() << std::endl;
	std::cout << "Size = " << ftVec.size() << std::endl;

	// ! int j = stdVec[0]; // a seg fault / invalid read
	// std::cout << "????? = " << j << std::endl;

	// ! int k = ftVec[0]; // a seg fault / invalid read
	// std::cout << "????? = " << k << std::endl;
}

/**
 * @brief Tests for fill constructor
 * 
 * @test Check size and capacity with filled vector
 * @test Check contents of vector initialized with fill constructor with 
 * and without optional value
 * 
 */
void	fillConstructorTests(void)
{
	std::cout << "Testing fill constructor" << std::endl;

	std::vector<int>	stdVecDef(10);

	printVec(stdVecDef, "std::vector after fill constructor with default value");
	std::cout << "STDLIB Vector" << std::endl;
	std::cout << "Capacity = " << stdVecDef.capacity() << std::endl;
	std::cout << "Size = " << stdVecDef.size() << std::endl;

	ft::vector<int>	ftVecDef(10);

	printVec(ftVecDef, "ft::vector after fill constructor with default value");
	std::cout << "FT Vector" << std::endl;
	std::cout << "Capacity = " << ftVecDef.capacity() << std::endl;
	std::cout << "Size = " << ftVecDef.size() << std::endl;

	std::vector<int>	stdVecFill(10, 20);

	printVec(stdVecFill, "std::vector after fill constructor with optional value");
	std::cout << "STDLIB Vector" << std::endl;
	std::cout << "Capacity = " << stdVecFill.capacity() << std::endl;
	std::cout << "Size = " << stdVecFill.size() << std::endl;

	ft::vector<int>	ftVecFill(10, 20);

	printVec(ftVecFill, "ft::vector after fill constructor with optional value");
	std::cout << "FT Vector" << std::endl;
	std::cout << "Capacity = " << ftVecFill.capacity() << std::endl;
	std::cout << "Size = " << ftVecFill.size() << std::endl;
}

/**
 * @brief Copy constructor tests
 * 
 * 
 * @test Check size and capacity after using copy constructor
 * @test Check copy constructor with empty and non-empty vectors
 */
void	copyConstructorTests(void)
{
	ft::vector<int>	vec1(10, 34);
	ft::vector<int>	vec2(vec1);
	
	std::cout << "Vec2 size and capacity" << std::endl;
	std::cout << vec2.size() << std::endl;
	std::cout << vec2.capacity() << std::endl;

	vec1[0] = 9;
	printVec(vec1, "Printing vec1");
	printVec(vec2, "Printing vec2");
	
	ft::vector<int> vec3;
	ft::vector<int>	vec4(vec3);
	
	std::cout << "Vec4 size and capacity" << std::endl;
	std::cout << vec4.size() << std::endl;
	std::cout << vec4.capacity() << std::endl;

	printVec(vec4, "Printing vec4 (should be empty)");
}

/**
 * @brief Tests where the template type of a vector is another vector
 * 
 */
void	vectorInVectorTests(void)
{
	ft::vector<std::vector<int> > a(10);
	a[0] = std::vector<int>(10, 9);
	a[1] = std::vector<int>(10, 9);
	a[2] = std::vector<int>(10, 9);

	ft::vector<ft::vector<int> > b(10);
	b[0] = ft::vector<int>(10, 9);
	b[1] = ft::vector<int>(10, 9);
	b[2] = ft::vector<int>(10, 9);

	ft::vector<ft::vector<int> > c(0);
	ft::vector<std::vector<int> > d(100);

	std::vector<ft::vector<int> > e(100);
	e[10] = ft::vector<int>(8);
}

/**
 * @brief vector.max_size() tests
 * 
 * @test Compare max_size method with ft and std vectors
 */
void	maxSizeTests(void)
{
	std::vector<int>	stdVec;
	ft::vector<int>		ftVec;

	std::cout << "std max_size() = " << stdVec.max_size() << std::endl;
	std::cout << "ft max_size() =  " << ftVec.max_size() << std::endl;
}

/**
 * @brief vector.empty() tests
 * 
 * @test Check vec.empty() with empty and non-empty vectors
 */
void	emptyTest(void)
{
	ft::vector<int>		ftVec;
	std::vector<int>	stdVec;
	if (stdVec.empty() && ftVec.empty())
	{
		std::cout << "Both vectors are empty: √" << std::endl;
	}

	ft::vector<int>		ftVec2(10);
	std::vector<int>	stdVec2(10);
	if (!stdVec2.empty() && !ftVec2.empty())
	{
		std::cout << "Both vectors are not empty: √" << std::endl;
	}
}

/**
 * @brief vector.at() tests
 * 
 * @test Check vec.at() when n is in or out of range
 */
void	atTests()
{
	try
	{
		std::vector<int> a(10, 3);
		std::cout << a.at(10) << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		ft::vector<int> a(10, 3);
		std::cout << a.at(10) << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		std::vector<int> a(10, 3);
		std::cout << a.at(9) << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		ft::vector<int> a(10, 3);
		std::cout << a.at(9) << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}
}

int	main(void)
{
	defaultConstructorTests();
	fillConstructorTests();
	copyConstructorTests();
	vectorInVectorTests();
	maxSizeTests();
	emptyTest();
	atTests();
}
