/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:43:47 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/04 12:23:49 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is_integral.hpp"
#include "make_pair.hpp"
#include "map.hpp"
#include "vector.hpp"
#include <cassert>
#include <map>
#include <string>
#include <vector>

/**
 * @brief Prints the contents of a std::vector or ft::vector
 *
 * @tparam Vec std or ft vector
 * @param vec The vector that you want to print the contents of
 * @param message Message to print before printing the contents of the vector
 */
template <typename Vec> void printVec(const Vec &vec, const std::string &message)
{
    std::cout << message << std::endl;
    for (size_t i = 0; i < vec.size(); i++)
    {
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
void defaultConstructorTests(void)
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
    assert((ftVec.size() == stdVec.size()));
    assert((ftVec.capacity() == stdVec.capacity()));
}

/**
 * @brief Tests for fill constructor
 *
 * @test Check size and capacity with filled vector
 * @test Check contents of vector initialized with fill constructor with
 * and without optional value
 *
 */
void fillConstructorTests(void)
{
    std::cout << "Testing fill constructor" << std::endl;

    std::vector<int> stdVecDef(10);

    printVec(stdVecDef, "std::vector after fill constructor with default value");
    std::cout << "STDLIB Vector" << std::endl;
    std::cout << "Capacity = " << stdVecDef.capacity() << std::endl;
    std::cout << "Size = " << stdVecDef.size() << std::endl;

    ft::vector<int> ftVecDef(10);

    printVec(ftVecDef, "ft::vector after fill constructor with default value");
    std::cout << "FT Vector" << std::endl;
    std::cout << "Capacity = " << ftVecDef.capacity() << std::endl;
    std::cout << "Size = " << ftVecDef.size() << std::endl;

    std::vector<int> stdVecFill(10, 20);

    printVec(stdVecFill, "std::vector after fill constructor with optional value");
    std::cout << "STDLIB Vector" << std::endl;
    std::cout << "Capacity = " << stdVecFill.capacity() << std::endl;
    std::cout << "Size = " << stdVecFill.size() << std::endl;

    ft::vector<int> ftVecFill(10, 20);

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
void copyConstructorTests(void)
{
    std::cout << "Testing copy constructor" << std::endl;

    ft::vector<int> vec1(10, 34);
    ft::vector<int> vec2(vec1);

    std::cout << "Vec2 size and capacity" << std::endl;
    std::cout << vec2.size() << std::endl;
    std::cout << vec2.capacity() << std::endl;

    vec1[0] = 9;
    printVec(vec1, "Printing vec1");
    printVec(vec2, "Printing vec2");

    ft::vector<int> vec3;
    ft::vector<int> vec4(vec3);

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
void vectorInVectorTests(void)
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
void maxSizeTests(void)
{
    std::cout << "Testing vec::max_size()" << std::endl;

    std::vector<int> stdVec;
    ft::vector<int> ftVec;

    std::cout << "std max_size() = " << stdVec.max_size() << std::endl;
    std::cout << "ft max_size() =  " << ftVec.max_size() << std::endl;
    std::cout << std::endl;
}

/**
 * @brief vector.empty() tests
 *
 * @test Check vec.empty() with empty and non-empty vectors
 */
void emptyTest(void)
{
    std::cout << "Testing vec::empty()" << std::endl;

    ft::vector<int> ftVec;
    std::vector<int> stdVec;
    if (stdVec.empty() && ftVec.empty())
    {
        std::cout << "Both vectors are empty: √" << std::endl;
    }

    ft::vector<int> ftVec2(10);
    std::vector<int> stdVec2(10);
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
void atTests()
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
void frontBackTests(void)
{
    std::cout << "Testing vec::front() and vec::back()" << std::endl;

    ft::vector<int> ftVec(200, 10);
    ftVec[0] = 1;
    ftVec[199] = 2;
    std::cout << "ftVec.front() == " << ftVec.front() << std::endl;
    std::cout << "ftVec.back() == " << ftVec.back() << std::endl;

    std::vector<int> stdVec(200, 10);
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
void dataTest(void)
{
    std::cout << "Testing vec::data()" << std::endl;

    ft::vector<int> ftVecFull(10, 10);
    int *dataPtr = ftVecFull.data();
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
void swapTest(void)
{
    std::cout << "Testing vec::swap()" << std::endl;

    ft::vector<int> vec1(10, 1);
    ft::vector<int> vec2(10, 2);

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
    ft::vector<double> vec7(4, 9.87);
    ft::vector<double> vec8(11, 6.7);
    printVec(vec7, "vec7 before swap");
    printVec(vec8, "vec8 before swap");
    swap(vec7, vec8);
    printVec(vec7, "vec7 after swap");
    printVec(vec8, "vec8 after swap");
    std::cout << std::endl;
}

/**
 * @brief Tests for vec::clear()
 *
 * @test Check with normal vector
 * @test Check with empty vector
 *
 */
void clearTests(void)
{
    std::cout << "Testing vec::clear()" << std::endl;
    ft::vector<int> normalVec(10, 10);

    normalVec.clear();
    assert(normalVec.size() == 0);
    assert(normalVec.capacity() == 0);
    assert(normalVec.empty() == true);
    ft::vector<int> emptyVec;

    emptyVec.clear();
    assert(emptyVec.size() == 0);
    assert(emptyVec.capacity() == 0);
    assert(emptyVec.empty() == true);
    ft::vector<int> intenseVec(19832, 198732);
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    intenseVec.clear();
    assert(intenseVec.size() == 0);
    assert(intenseVec.capacity() == 0);
    assert(intenseVec.empty() == true);
    ft::vector<int> replaceVec(1902, 198732);
    intenseVec = replaceVec;
    assert(intenseVec.size() == 1902);
    assert(intenseVec.capacity() >= 1902);
    assert(intenseVec.empty() == false);
    intenseVec.clear();
    assert(intenseVec.size() == 0);
    assert(intenseVec.capacity() == 0);
    assert(intenseVec.empty() == true);
    std::cout << std::endl;
}

/**
 * @brief Tests for vec::resize()
 *
 * @test New size > old && New size < capacity
 * @test New size < old && New size < capacity
 * @test New size == old && New size < capacity
 * @test New size > old && New size > capacity
 * @test New size == old && New size == capacity
 * @test Tests with empty vectors
 * @test Tests with optional arguments
 * @test Tests with vector of vectors
 * @test Tests n == 0
 */
void resizeTests(void)
{
    std::cout << "Testing vec::resize()" << std::endl;

    ft::vector<int> vec1(5, 5);   // size = 5 capacity = 5

    vec1.resize(6);   // New size > old && new size > capacity
    printVec(vec1, "");
    // size == 6 capacity == 6
    vec1.resize(3);
    printVec(vec1, "");
    // size == 3 capacity == 6
    vec1.resize(4);
    printVec(vec1, "");
    // size == 4 capacity == 6
    vec1.resize(4);
    printVec(vec1, "");
    vec1.resize(6);
    printVec(vec1, "");
    vec1.resize(6);
    printVec(vec1, "");

    ft::vector<int> empty;
    empty.resize(1);
    empty.resize(1);
    empty.resize(1);
    printVec(empty, "");
    empty.resize(0);
    printVec(empty, "");
    empty.resize(6);
    printVec(empty, "");
    empty.resize(10, 1);
    printVec(empty, "");
    empty.resize(0);
    printVec(empty, "");

    ft::vector<int> filler(909, 100);
    ft::vector<ft::vector<int> > no;
    no.resize(0);
    no.resize(90);
    no.resize(100, filler);
    no.resize(80, filler);
    no.resize(1000);
    no.resize(10000, filler);
    std::cout << std::endl;
}

/**
 * @brief Tests for vec::reserve()
 *
 */
void reserveTests(void)
{
    ft::vector<int> vec;

    vec.reserve(100);
    vec.reserve(0);
    vec.reserve(1);
    assert(vec.capacity() == 100);
    vec.reserve(2000);
    assert(vec.capacity() == 2000);
    std::cout << std::endl;
}

void vectorIteratorTests(void)
{
    ft::vector<int> vec(10, 10);

    ft::vector<int>::iterator beg = vec.begin();

    vec[5] = 9;
    for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}

void vectorRelational(void)
{
    ft::vector<int> empty1;
    ft::vector<int> empty2;

    if (empty1 == empty2)
    {
        std::cout << "equal" << std::endl;
    }
    if (empty1 < empty2)
    {
        std::cout << "less than" << std::endl;
    }
    ft::vector<int> vec1(10, 10);
    ft::vector<int> vec2(10, 10);
    if (vec1 == vec2)
    {
        std::cout << "equal" << std::endl;
    }
    if (vec1 == empty1)
    {
        std::cout << "equal" << std::endl;
    }
    if (vec1 < vec2)
    {
        std::cout << "less than" << std::endl;
    }
    if (vec1 < empty1)
    {
        std::cout << "less than" << std::endl;
    }
    ft::vector<int> vec3(10, 9);
    ft::vector<int> vec4(10, 10);
    if (vec3 == vec4)
    {
        std::cout << "equal" << std::endl;
    }
    if (vec3 < vec4)
    {
        std::cout << "less than" << std::endl;
    }
    std::cout << std::endl;
}

void vectorReverseIteratorTests(void)
{
    ft::vector<int> vec(10, 10);

    for (ft::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); it++)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}

void rangeConstructorTests(void)
{
    ft::vector<int> v1(10, 100);
    ft::vector<int> v2(10, 100);
    ft::vector<int> v3(10, 100);
    ft::vector<ft::vector<int> > vecOfVecs(3);
    vecOfVecs[0] = v1;
    vecOfVecs[1] = v2;
    vecOfVecs[2] = v3;
    ft::vector<ft::vector<int> > vecOfVecs2(vecOfVecs.begin(), vecOfVecs.end());

    // std::vector<int> o(10, 10);
    // ft::vector<double> k(o.begin(), o.end());
    printVec(vecOfVecs2[0], "");
    // std::vector<int>
}

void assignTests(void)
{
    ft::vector<int> a;

    a.assign(1000, 4);
    a.assign(1000, 4);
    a.assign(1000, 4);
    a.assign(1000, 4);
    a.assign(1000, 4);
    a.assign(1, 4);
    printVec(a, "");

    ft::vector<int> b(10, 290);
    a.assign(b.begin(), b.begin());
    printVec(a, "");
}

void pushBackTests(void)
{
    ft::vector<ft::vector<int> > a(1);
    // a.reserve(1);
    a[0] = ft::vector<int>(908, 10);
    a.push_back(a[0]);
    ft::vector<int> q(100, 45);
    a.push_back(q);
    // printVec(a[1], "");
    // std::cout << a[0][0] << std::endl;
}

void popBackTests(void)
{
    ft::vector<ft::vector<int> > a(100);
    a[98] = ft::vector<int>(2, 3);
    a[99] = ft::vector<int>(2, 2);
    a.pop_back();
    printVec(a[98], "");
}

void insertTests(void)
{
    ft::vector<int> vec1;
    vec1.insert(vec1.begin(), 1);
    vec1.insert(vec1.begin(), 1);
    vec1.insert(vec1.begin(), 13);
    vec1.insert(vec1.begin(), 1);
    vec1.insert(vec1.begin(), 2);
    vec1.insert(vec1.begin(), 8);

    ft::vector<int> vec2;
    vec2.insert(vec2.end(), 2, 6);
    // printVec(vec2, "");
    ft::vector<int> vec3(1);
    ft::vector<int> vec4(8, 4);
    vec4[0] = 1;
    vec4[1] = 2;
    vec4[2] = 3;
    vec4[3] = 9;
    vec3.insert(vec3.begin(), vec4.begin(), vec4.end());
    printVec(vec3, "");
}

void eraseTests(void)
{
    ft::vector<int> a(5);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;
    a.erase(a.begin() + 1);
    // printVec(a, "");

    ft::vector<int> b(1, 5);
    b.erase(b.begin(), b.begin() + 1);
    printVec(b, "");
}

void reverseIteratorTests(void)
{
    ft::vector<int> a(5);

    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    a[4] = 4;

    // std::cout << *a.rbegin() << std::endl;
    std::cout << *a.rend() << std::endl;

    std::vector<int> b(5);

    // b[0] = 0;
    // b[1] = 1;
    // b[2] = 2;
    // b[3] = 3;
    // b[4] = 4;

    // std::cout << *b.rbegin() << std::endl;
    std::cout << *b.rend() << std::endl;
}

void mapDefaultConstructor(void)
{
    ft::map<std::string, int> a;
    ft::map<std::string, int> b(a);
}

void mapSingleInsert()
{
    ft::map<std::string, int> a;
    a.insert(ft::make_pair("d", 4));
    a.insert(ft::make_pair("b", 2));
    a.insert(ft::make_pair("e", 5));
    a.insert(ft::make_pair("c", 3));
    a.insert(ft::make_pair("a", 1));

    // a.printTree();
    std::cout << a["b"] << std::endl;
}

void mapSingleErase()
{
    ft::map<std::string, int> a;
    a.insert(ft::make_pair("d", 4));
    a.insert(ft::make_pair("b", 2));
    a.insert(ft::make_pair("e", 5));
    a.insert(ft::make_pair("c", 3));
    a.insert(ft::make_pair("a", 1));

    a.erase("d");

    // ft::map<std::string, int> b;
    // ft::map<std::string, int>::iterator c = b.begin();
    // a.printTree();
    // std::cout << a["d"] << std::endl;
    a.printTree();
}

int main(void)
{
    // defaultConstructorTests();
    // fillConstructorTests();
    // copyConstructorTests();
    // vectorInVectorTests();
    // maxSizeTests();
    // emptyTest();
    // atTests();
    // frontBackTests();
    // dataTest();
    // swapTest();
    // clearTests();
    // resizeTests();
    // reserveTests();
    // beginTests();
    // vectorIteratorTests();
    // vectorReverseIteratorTests();
    // vectorRelational();
    // rangeConstructorTests();
    // assignTests();
    // pushBackTests();
    // popBackTests();
    // insertTests();
    // eraseTests();
    // copyTests();
    // fillConstructor();
    // rangeConstructor();
    // defaultConstructor();
    // mapDefaultConstructor();
    // mapSingleInsert();
    mapSingleErase();
    // ft::map<std::string, int> a;
    // std::cout << a.max_size() << std::endl;
    // std::map<std::string, int> b;
    // std::cout << b.max_size() << std::endl;
    // reverseIteratorTests();
    std::cout << std::endl;
}
