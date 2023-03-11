/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:57:45 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/11 20:33:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_pair.hpp"
#include "map.hpp"
#include "vector.hpp"
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

    a.erase("d");

    // ft::map<std::string, int> b;
    // ft::map<std::string, int>::iterator c = b.begin();
    // a.printTree();
    // std::cout << a["d"] << std::endl;
    a.printTree();
}

void mapIterators(void)
{
    // ft::vector<int> intVec;
    // intVec.reserve(5);
    // intVec.push_back(0);
    // intVec.push_back(1);
    // intVec.push_back(2);
    // intVec.push_back(3);
    // intVec.push_back(4);
    // for (ft::vector<int>::reverse_iterator it = intVec.rbegin(); it != intVec.rend(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    ft::map<int, std::string> strToInt;
    strToInt.insert(ft::make_pair(1, "one"));
    strToInt.insert(ft::make_pair(2, "two"));
    strToInt.insert(ft::make_pair(3, "three"));
    strToInt.insert(ft::make_pair(4, "four"));
    for (ft::map<int, std::string>::reverse_iterator it = strToInt.rbegin(); it != strToInt.rend(); it++)
    {
        std::cout << "Key " << it->first << std::endl;
        std::cout << "Value " << it->second << std::endl;
    }
}

void mapTests(void)
{
    // mapSingleInsertReplace();
    mapIterators();
    std::cout << std::endl;
}
