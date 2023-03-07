/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:57:45 by hsarhan           #+#    #+#             */
/*   Updated: 2023/03/07 08:59:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <iostream>
#include "make_pair.hpp"

void mapDefaultConstructor(void)
{
    ft::map<std::string, int> a;
    ft::map<std::string, int> b(a);
}

void mapSingleInsert(void)
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
    // mapSingleErase();
    // ft::map<std::string, int> a;
    // std::cout << a.max_size() << std::endl;
    // std::map<std::string, int> b;
    // std::cout << b.max_size() << std::endl;
    // reverseIteratorTests();
    std::cout << std::endl;
}
