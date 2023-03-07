/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:57:45 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/07 13:02:53 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <cstdio>
#include <iostream>
#include "make_pair.hpp"
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

void    mapIterators(void)
{
    
}

void    mapSingleInsertReplace(void)
{
    ft::map<std::string, int> a; 
    a.insert(ft::make_pair("a", 4));
    // ft::map<int, int>::iterator mapIt = a.begin();
    a.insert(ft::make_pair("a", 0));
    a.insert(ft::make_pair("a", 0));
    a.insert(ft::make_pair("a", 0));
    a.insert(ft::make_pair("a", 0));
    a.insert(ft::make_pair("a", 0));
    a.insert(ft::make_pair("a", 0));
    a.printTree();
}

void mapTests(void)
{
    mapSingleInsertReplace();
    std::cout << std::endl;
}
