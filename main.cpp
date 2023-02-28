/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:43:47 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/28 08:08:45 by hsarhan          ###   ########.fr       */
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
	std::cout << std::endl;
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
	std::cout << std::endl;
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
	std::cout << "Testing copy constructor" << std::endl;

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
	std::cout << std::endl;
}

/**
 * @brief Tests where the template type of a vector is another vector
 * 
 */
void	vectorInVectorTests(void)
{
	std::cout << "Testing vector of vectors" << std::endl;

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
	std::cout << std::endl;
}

/**
 * @brief vector.max_size() tests
 * 
 * @test Compare max_size method with ft and std vectors
 */
void	maxSizeTests(void)
{
	std::cout << "Testing vec::max_size()" << std::endl;

	std::vector<int>	stdVec;
	ft::vector<int>		ftVec;

	std::cout << "std max_size() = " << stdVec.max_size() << std::endl;
	std::cout << "ft max_size() =  " << ftVec.max_size() << std::endl;
	std::cout << std::endl;
}

/**
 * @brief vector.empty() tests
 * 
 * @test Check vec.empty() with empty and non-empty vectors
 */
void	emptyTest(void)
{
	std::cout << "Testing vec::empty()" << std::endl;

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
	std::cout << std::endl;
}

/**
 * @brief vector.at() tests
 * 
 * @test Check vec.at() when n is in or out of range
 */
void	atTests()
{
	std::cout << "Testing vec::at(i)" << std::endl;

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
	std::cout << std::endl;
}

/**
 * @brief Tests for vec::front() and vec::back() methods
 * 
 * @test Check front with filled vector
 * @test Check front with empty vector
 * @test Check back with filled vector
 * @test Check back with empty vector
 * 
 */
void	frontBackTests(void)
{
	std::cout << "Testing vec::front() and vec::back()" << std::endl;

	ft::vector<int>	ftVec(200, 10);
	ftVec[0] = 1;
	ftVec[199] = 2;
	std::cout << "ftVec.front() == " << ftVec.front() << std::endl;
	std::cout << "ftVec.back() == " << ftVec.back() << std::endl;

	std::vector<int>	stdVec(200, 10);
	stdVec[0] = 1;
	stdVec[199] = 2;
	std::cout << "stdVec.front() == " << stdVec.front() << std::endl;
	std::cout << "stdVec.back() == " << stdVec.back() << std::endl;

	// ! Invalid reads
	// ft::vector<int>	ftVecEmpty;
	// std::cout << "ftVecEmpty.front()" << ftVecEmpty.front() << std::endl;
	// std::cout << "ftVecEmpty.back()" << ftVecEmpty.back() << std::endl;

	// std::vector<int>	stdVecEmpty;
	// std::cout << "stdVecEmpty.front()" << stdVecEmpty.front() << std::endl;
	// std::cout << "stdVecEmpty.back()" << stdVecEmpty.back() << std::endl;
	std::cout << std::endl;
}

/**
 * @brief Tests for vec::data()
 *
 * @test Check data pointer with filled vector
 * @test Check data pointer with empty vector
 * 
 */
void	dataTest(void)
{
	std::cout << "Testing vec::data()" << std::endl;

	ft::vector<int>	ftVecFull(10, 10);
	int	*dataPtr = ftVecFull.data();
	std::cout << "Full data pointer == " << *dataPtr << std::endl;

	// ! invalid read
	// ft::vector<int>	ftVecEmpty;
	// int	*emptyDataPtr = ftVecEmpty.data();
	// std::cout << "Empty data pointer == " << *emptyDataPtr;
	std::cout << std::endl;
}


/**
 * @brief Tests for vec::swap()
 * 
 * @test Check with normal case
 * @test Check with different sized vectors
 * @test Check with empty vectors
 * @test Check size and capacity
 * @test Check with same vector
 * @test Check with overloaded swap
 */
void	swapTest(void)
{
	std::cout << "Testing vec::swap()" << std::endl;

	ft::vector<int>	vec1(10, 1);
	ft::vector<int>	vec2(10, 2);
	
	printVec(vec1, "vec1 before swap");
	printVec(vec2, "vec2 before swap");
	vec1.swap(vec2);
	printVec(vec1, "vec1 after swap 1");
	printVec(vec2, "vec2 after swap 1");
	vec1.swap(vec2);
	printVec(vec1, "vec1 after swap 2");
	printVec(vec2, "vec2 after swap 2");

	std::cout << "Testing vec::swap() with different sized vectors" << std::endl;
	ft::vector<ft::vector<int> > vec3(5, vec1);
	ft::vector<ft::vector<int> > vec4(10, vec2);
	printVec(vec3[4], "vec3[4] before swap");
	printVec(vec4[9], "vec3[9] before swap");
	std::cout << "vec3.capacity() == " << vec3.capacity() << std::endl;
	std::cout << "vec4.capacity() == " << vec4.capacity() << std::endl;
	vec3.swap(vec4);
	printVec(vec3[9], "vec3[9] after swap 1");
	printVec(vec4[4], "vec3[4] after swap 1");
	std::cout << "vec3.capacity() == " << vec3.capacity() << std::endl;
	std::cout << "vec4.capacity() == " << vec4.capacity() << std::endl;
	vec3.swap(vec4);
	printVec(vec3[4], "vec3[4] after swap 2");
	printVec(vec4[9], "vec3[9] after swap 2");
	std::cout << "vec3.capacity() == " << vec3.capacity() << std::endl;
	std::cout << "vec4.capacity() == " << vec4.capacity() << std::endl;

	std::cout << "Testing vec::swap() with empty vectors" << std::endl;
	ft::vector<int> vec5;
	ft::vector<int> vec6;
	vec5.swap(vec6);
	vec2.swap(vec6);
	vec1.swap(vec5);

	std::cout << "Testing vec::swap() with the same vector" << std::endl;
	vec1.swap(vec1);
	vec2.swap(vec2);
	vec3.swap(vec3);
	vec4.swap(vec4);
	vec5.swap(vec5);
	vec6.swap(vec6);

	std::cout << "Testing overloaded swap() with the different sized vectors" << std::endl;
	ft::vector<double>	vec7(4, 9.87);
	ft::vector<double>	vec8(11, 6.7);
	printVec(vec7, "vec7 before swap");
	printVec(vec8, "vec8 before swap");
	swap(vec7, vec8);
	printVec(vec7, "vec7 after swap");
	printVec(vec8, "vec8 after swap");
	std::cout << std::endl;
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
	frontBackTests();
	dataTest();
	swapTest();
	std::cout << std::endl;
}
