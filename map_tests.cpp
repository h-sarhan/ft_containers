/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:57:45 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/13 04:43:21 by hsarhan          ###   ########.fr       */
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
    strToInt.insert(ft::make_pair(5, "four"));
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
    strToInt.insert(ft::make_pair(5, "four"));
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

void mapTests(void)
{
    // mapSingleInsertReplace();
    // mapIterators();
    // mapCount();
    // mapSingleErase();
    // mapRangeErase();
    // mapClear();
    mapSwap();
    std::map<int, std::string> strToInt;
    strToInt.swap(strToInt);
    std::cout << std::endl;
}
