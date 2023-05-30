/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:57:45 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/30 05:20:37 by hsarhan          ###   ########.fr       */
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
#include <set>
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
}

void mapSingleErase(void)
{
    ft::map<std::string, int> a;
    a.insert(ft::make_pair("d", 4));
    a.insert(ft::make_pair("b", 2));
    a.insert(ft::make_pair("e", 5));
    a.insert(ft::make_pair("c", 3));
    a.insert(ft::make_pair("a", 1));

    // assert(a.begin()->first == "a");
    // a.erase("d");
    a.erase(a.begin());
    // a.erase(a.begin());
    // assert(a.begin()->first == "c");
}

void mapIterators(void)
{
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(2, "two"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    for (ft::map<int, std::string>::reverse_iterator it = strToInt.rbegin();
         it != strToInt.rend(); it++)
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
    // strToInt.printTree();
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
    // strToInt.printTree();
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
    ft::map<int, std::string>::iterator it =
        strToInt.insert(lastIt, ft::make_pair(7, "seven"));
    lastIt = strToInt.end();
    lastIt--;
    assert(it == lastIt);
    // strToInt.printTree();
}

void mapLowerBound(void)
{
    std::map<int, std::string> strToIntStd;
    strToIntStd.insert(std::make_pair(1, "one"));
    strToIntStd.insert(std::make_pair(3, "three"));
    strToIntStd.insert(std::make_pair(4, "four"));
    std::map<int, std::string>::iterator itStd = strToIntStd.lower_bound(4);
    // it = strToInt.end();
    std::cout << "std lower_bound == " << itStd->first << std::endl;

    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    ft::map<int, std::string>::iterator it = strToInt.lower_bound(4);
    // it = strToInt.end();
    std::cout << "lower_bound == " << it->first << std::endl;

    // std::map<int, std::string> strToInt2;
    // strToInt2.insert(std::make_pair(1, "one"));
    // strToInt2.insert(std::make_pair(3, "three"));
    // strToInt2.insert(std::make_pair(4, "four"));
    // std::map<int, std::string>::iterator it2 = strToInt2.lower_bound(5);
    // // it = strToInt.end();
    // std::cout << "lower_bound == " << it2->first << std::endl;
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

#include "mli/srcs/map/common.hpp"

#include <list>

#define T1 char
#define T2 int
typedef ft::pair<const T1, T2> T3;

int rite_map(void)
{
    std::list<T3> lst;
    unsigned int lst_size = 5;
    for (unsigned int i = 0; i < lst_size; ++i)
        lst.push_back(T3('a' + i, (i + 1) * 7));

    TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
    TESTED_NAMESPACE::map<T1, T2>::iterator it_ = mp.begin();
    TESTED_NAMESPACE::map<T1, T2>::reverse_iterator it(it_), ite;
    printSize(mp);

    std::cout << (it_ == it.base()) << std::endl;
    std::cout << (it_ == dec(it, 3).base()) << std::endl;

    printPair(it.base());
    printPair(inc(it.base(), 1));

    std::cout << "TEST OFFSET" << std::endl;
    --it;
    printPair(it);
    printPair(it.base());

    it = mp.rbegin();
    ite = mp.rend();
    while (it != ite)
        std::cout << "[rev] " << printPair(it++, false) << std::endl;
    printReverse(mp);

    return (0);
}

void mapTests(void)
{
    rite_map();
    // mapDefaultConstructor();
    // mapSingleInsertNew();
    // mapCount();
    // mapIterators();
    // mapSingleErase();
    // mapRangeErase();
    // mapClear();
    // mapSwap();
    // mapRangeBasedConstructor();
    // mapInsertWithReturnedIterator();
    // mapLowerBound();
    // mapUpperBound();
}
