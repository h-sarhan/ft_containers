/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:57:45 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/17 13:09:53 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_pair.hpp"
#include "map.hpp"
#include "vector.hpp"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

void mapDefaultConstructor(void)
{
    ft::map<std::string, int> a;
    ft::map<std::string, int> b(a);
}

void mapSingleInsertNew(void)
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

void mapSingleErase(void)
{
    ft::map<std::string, int> a;
    a.insert(ft::make_pair("d", 4));
    a.insert(ft::make_pair("b", 2));
    a.insert(ft::make_pair("e", 5));
    a.insert(ft::make_pair("c", 3));
    a.insert(ft::make_pair("a", 1));

    // a.erase("d");
    // a.printTree();
    a.erase(a.begin());
    a.erase(a.begin());
    a.printTree();
}

void mapIterators(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(2, "two"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    for (ft::map<int, std::string>::reverse_iterator it = strToInt.rbegin(); it != strToInt.rend();
         it++)
    {
        std::cout << "Key " << it->first << std::endl;
        std::cout << "Value " << it->second << std::endl;
    }
}

void mapCount(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(2, "two"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    assert(strToInt.count(1) == 1);
    assert(strToInt.count(5) == 0);
}

void mapRangeErase(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(2, "two"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    ft::map<int, std::string>::iterator first = strToInt.begin();
    ft::map<int, std::string>::iterator last = first;
    last++;
    last++;
    strToInt.erase(first, last);
    assert(strToInt.count(1) == 0);
    assert(strToInt.count(2) == 0);
    assert(strToInt.count(3) == 1);
    assert(strToInt.count(4) == 1);
    strToInt.printTree();
}

void mapClear(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(2, "two"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    strToInt.insert(ft::make_pair(5, "five"));
    strToInt.clear();
    assert(strToInt.empty() == true);
    assert(strToInt.size() == 0);
    strToInt.printTree();
}

void mapSwap(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(2, "two"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    strToInt.insert(ft::make_pair(5, "five"));
    ft::map<int, std::string> strToInt2;
    strToInt2.insert(ft::make_pair(6, "six"));
    strToInt2.insert(ft::make_pair(7, "seven"));
    strToInt2.insert(ft::make_pair(8, "eight"));
    strToInt2.insert(ft::make_pair(9, "nine"));
    strToInt2.insert(ft::make_pair(10, "ten"));

    strToInt2.swap(strToInt);
    assert(strToInt.count(6) == 1);
    assert(strToInt2.count(6) == 0);
    assert(strToInt2.count(1) == 1);
    assert(strToInt.count(1) == 0);
}

void mapRangeBasedConstructor(void)
{
    ft::vector<ft::pair<int, std::string> > vec;
    vec.insert(vec.end(), ft::make_pair(3, "three"));
    vec.insert(vec.end(), ft::make_pair(4, "four"));
    vec.insert(vec.end(), ft::make_pair(1, "one"));
    vec.insert(vec.end(), ft::make_pair(5, "five"));
    vec.insert(vec.end(), ft::make_pair(2, "two"));
    ft::map<int, std::string> strToInt(vec.begin(), vec.end());
    strToInt.printTree();
    assert(strToInt.size() == 5);
}

void mapInsertWithReturnedIterator(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(2, "two"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    ft::pair<ft::map<int, std::string>::iterator, bool> res =
        strToInt.insert(ft::make_pair(5, "five"));
    ft::map<int, std::string>::iterator lastIt = strToInt.end();
    lastIt--;
    assert(res.second == true);
    assert(lastIt == res.first);
    ft::pair<ft::map<int, std::string>::iterator, bool> res2 =
        strToInt.insert(ft::make_pair(4, "four"));
    assert(res2.second == false);
    lastIt--;
    assert(lastIt == res2.first);
    ft::map<int, std::string>::iterator it = strToInt.insert(lastIt, ft::make_pair(7, "seven"));
    lastIt = strToInt.end();
    lastIt--;
    assert(it == lastIt);
    strToInt.printTree();
}

void mapLowerBound(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    ft::map<int, std::string>::iterator it = strToInt.lower_bound(5);
    // it = strToInt.end();
    std::cout << "lower_bound == " << it->first << std::endl;

    std::map<int, std::string> strToInt2;
    strToInt2.insert(std::make_pair(1, "one"));
    strToInt2.insert(std::make_pair(3, "three"));
    strToInt2.insert(std::make_pair(4, "four"));
    std::map<int, std::string>::iterator it2 = strToInt2.lower_bound(5);
    // it = strToInt.end();
    std::cout << "lower_bound == " << it2->first << std::endl;
}

void mapUpperBound(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    ft::map<int, std::string>::iterator it = strToInt.upper_bound(3);
    // it = strToInt.end();
    std::cout << "upper_bound == " << it->first << std::endl;

    std::map<int, std::string> strToInt2;
    strToInt2.insert(std::make_pair(1, "one"));
    strToInt2.insert(std::make_pair(3, "three"));
    strToInt2.insert(std::make_pair(4, "four"));
    std::map<int, std::string>::iterator it2 = strToInt2.upper_bound(3);
    // it = strToInt.end();
    std::cout << "upper_bound == " << it2->first << std::endl;
}

void mapFind(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    // strToInt.insert(ft::make_pair(3, "three"));
    // strToInt.insert(ft::make_pair(3, "three"));
    // strToInt.insert(ft::make_pair(3, "three"));
    // strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(345534, "three"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(31212, "three"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(321, "three"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(5, "three"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    ft::map<int, std::string>::iterator it = strToInt.find(5);
    std::cout << "Key == " << it->first << std::endl;
}

#include "./containers_test/srcs/map/common.hpp"

#ifdef TESTED_NAMESPACE
#undef TESTED_NAMESPACE
#define TESTED_NAMESPACE ft
// #define TESTED_NAMESPACE std
#endif

#include <list>

#define T1 int
#define T2 int
typedef _pair<const T1, T2> T3;

void copyConstruct(void)
{
    std::list<T3> lst;
    unsigned int lst_size = 7;
    for (unsigned int i = 0; i < lst_size; ++i)
        lst.push_back(T3(lst_size - i, i));

    TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
    TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();

    TESTED_NAMESPACE::map<T1, T2> mp_range(it, --(--ite));
    for (int i = 0; it != ite; ++it)
        it->second = ++i * 5;

    it = mp.begin();
    ite = --(--mp.end());
    TESTED_NAMESPACE::map<T1, T2> mp_copy(mp);
    for (int i = 0; it != ite; ++it)
        it->second = ++i * 7;

    std::cout << "\t-- PART ONE --" << std::endl;
    printSize(mp);
    printSize(mp_range);
    printSize(mp_copy);

    mp = mp_copy;
    mp_copy = mp_range;
    mp_range.clear();

    std::cout << "\t-- PART TWO --" << std::endl;
    printSize(mp);
    printSize(mp_range);
    printSize(mp_copy);
}

#undef T1
#define T1 char

#undef T2
#define T2 int

typedef _pair<const T1, T2> T4;

void mapSwap2(void)
{
    std::list<T4> lst;

    unsigned int lst_size = 7;
    for (unsigned int i = 0; i < lst_size; ++i)
        lst.push_back(T4('a' + i, lst_size - i));
    TESTED_NAMESPACE::map<T1, T2> foo(lst.begin(), lst.end());

    lst.clear();
    lst_size = 4;
    for (unsigned int i = 0; i < lst_size; ++i)
        lst.push_back(T4('z' - i, i * 5));
    TESTED_NAMESPACE::map<T1, T2> bar(lst.begin(), lst.end());

    TESTED_NAMESPACE::map<T1, T2>::const_iterator it_foo = foo.begin();
    TESTED_NAMESPACE::map<T1, T2>::const_iterator it_bar = bar.begin();

    std::cout << "BEFORE SWAP" << std::endl;

    std::cout << "foo contains:" << std::endl;
    printSize(foo);
    std::cout << "bar contains:" << std::endl;
    printSize(bar);

    foo.swap(bar);

    std::cout << "AFTER SWAP" << std::endl;

    std::cout << "foo contains:" << std::endl;
    printSize(foo);
    std::cout << "bar contains:" << std::endl;
    printSize(bar);

    std::cout << "Iterator validity:" << std::endl;
    std::cout << (it_foo == bar.begin()) << std::endl;
    std::cout << (it_bar == foo.begin()) << std::endl;
}

void mapTests(void)
{
    // mapSingleInsertReplace();
    // mapIterators();
    // mapCount();
    // mapSingleErase();
    // mapRangeErase();
    // mapClear();
    // mapSwap();
    // mapRangeBasedConstructor();
    // mapInsertWithReturnedIterator();
    // mapLowerBound();
    // mapUpperBound();
    // mapFind();
    // copyConstruct();
    // TESTED_NAMESPACE::map<T1, T2> const mp;
    // TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin(); // <-- error expected
    // (void)it;

    mapSwap();
    mapSwap2();
    std::cout << std::endl;
}
