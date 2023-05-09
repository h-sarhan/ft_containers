/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:57:45 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/09 19:15:47 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_pair.hpp"
#include "map.hpp"
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

    a.printTree();
}

// void mapSingleErase(void)
// {
//     ft::map<std::string, int> a;
//     a.insert(ft::make_pair("d", 4));
//     a.insert(ft::make_pair("b", 2));
//     a.insert(ft::make_pair("e", 5));
//     a.insert(ft::make_pair("c", 3));
//     a.insert(ft::make_pair("a", 1));

//     // assert(a.begin()->first == "a");
//     // a.erase("d");
//     a.printTree();
//     std::cout << std::endl;
//     a.erase(a.begin());
//     // a.erase(a.begin());
//     // assert(a.begin()->first == "c");
//     a.printTree();
// }

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

// void mapRangeErase(void)
// {
//     ft::map<int, std::string> strToInt;
//     strToInt.insert(ft::make_pair(1, "one"));
//     strToInt.insert(ft::make_pair(2, "two"));
//     strToInt.insert(ft::make_pair(3, "three"));
//     strToInt.insert(ft::make_pair(4, "four"));
//     ft::map<int, std::string>::iterator first = strToInt.begin();
//     ft::map<int, std::string>::iterator last = first;
//     last++;
//     last++;
//     strToInt.erase(first, last);
//     assert(strToInt.count(1) == 0);
//     assert(strToInt.count(2) == 0);
//     assert(strToInt.count(3) == 1);
//     assert(strToInt.count(4) == 1);
//     // strToInt.printTree();
// }

// void mapClear(void)
// {
//     ft::map<int, std::string> strToInt;
//     strToInt.insert(ft::make_pair(1, "one"));
//     strToInt.insert(ft::make_pair(2, "two"));
//     strToInt.insert(ft::make_pair(3, "three"));
//     strToInt.insert(ft::make_pair(4, "four"));
//     strToInt.insert(ft::make_pair(5, "five"));
//     strToInt.clear();
//     assert(strToInt.empty() == true);
//     assert(strToInt.size() == 0);
//     // strToInt.printTree();
// }

// void mapSwap(void)
// {
//     ft::map<int, std::string> strToInt;
//     strToInt.insert(ft::make_pair(1, "one"));
//     strToInt.insert(ft::make_pair(2, "two"));
//     strToInt.insert(ft::make_pair(3, "three"));
//     strToInt.insert(ft::make_pair(4, "four"));
//     strToInt.insert(ft::make_pair(5, "five"));
//     ft::map<int, std::string> strToInt2;
//     strToInt2.insert(ft::make_pair(6, "six"));
//     strToInt2.insert(ft::make_pair(7, "seven"));
//     strToInt2.insert(ft::make_pair(8, "eight"));
//     strToInt2.insert(ft::make_pair(9, "nine"));
//     strToInt2.insert(ft::make_pair(10, "ten"));

//     strToInt2.swap(strToInt);
//     assert(strToInt.count(6) == 1);
//     assert(strToInt2.count(6) == 0);
//     assert(strToInt2.count(1) == 1);
//     assert(strToInt.count(1) == 0);
// }

// void mapRangeBasedConstructor(void)
// {
//     ft::vector<ft::pair<int, std::string> > vec;
//     vec.insert(vec.end(), ft::make_pair(3, "three"));
//     vec.insert(vec.end(), ft::make_pair(4, "four"));
//     vec.insert(vec.end(), ft::make_pair(1, "one"));
//     vec.insert(vec.end(), ft::make_pair(5, "five"));
//     vec.insert(vec.end(), ft::make_pair(2, "two"));
//     ft::map<int, std::string> strToInt(vec.begin(), vec.end());
//     // strToInt.printTree();
//     assert(strToInt.size() == 5);
// }

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
    std::cout << lastIt->first << std::endl;
    std::cout << res.first->first << std::endl;
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
    // strToInt.printTree();
}

// void mapLowerBound(void)
// {
//     std::map<int, std::string> strToIntStd;
//     strToIntStd.insert(std::make_pair(1, "one"));
//     strToIntStd.insert(std::make_pair(3, "three"));
//     strToIntStd.insert(std::make_pair(4, "four"));
//     std::map<int, std::string>::iterator itStd = strToIntStd.lower_bound(4);
//     // it = strToInt.end();
//     std::cout << "std lower_bound == " << itStd->first << std::endl;

//     ft::map<int, std::string> strToInt;
//     strToInt.insert(ft::make_pair(1, "one"));
//     strToInt.insert(ft::make_pair(3, "three"));
//     strToInt.insert(ft::make_pair(4, "four"));
//     ft::map<int, std::string>::iterator it = strToInt.lower_bound(4);
//     // it = strToInt.end();
//     std::cout << "lower_bound == " << it->first << std::endl;

//     // std::map<int, std::string> strToInt2;
//     // strToInt2.insert(std::make_pair(1, "one"));
//     // strToInt2.insert(std::make_pair(3, "three"));
//     // strToInt2.insert(std::make_pair(4, "four"));
//     // std::map<int, std::string>::iterator it2 = strToInt2.lower_bound(5);
//     // // it = strToInt.end();
//     // std::cout << "lower_bound == " << it2->first << std::endl;
// }

// void mapUpperBound(void)
// {
//     ft::map<int, std::string> strToInt;
//     strToInt.insert(ft::make_pair(1, "one"));
//     strToInt.insert(ft::make_pair(3, "three"));
//     strToInt.insert(ft::make_pair(4, "four"));
//     ft::map<int, std::string>::iterator it = strToInt.upper_bound(3);
//     // it = strToInt.end();
//     std::cout << "upper_bound == " << it->first << std::endl;

//     std::map<int, std::string> strToInt2;
//     strToInt2.insert(std::make_pair(1, "one"));
//     strToInt2.insert(std::make_pair(3, "three"));
//     strToInt2.insert(std::make_pair(4, "four"));
//     std::map<int, std::string>::iterator it2 = strToInt2.upper_bound(3);
//     // it = strToInt.end();
//     std::cout << "upper_bound == " << it2->first << std::endl;
// }

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

// #define NAMESPACE ft
// #include "gerard/include/map_templates.hpp"

// void gerardSwap(void)
// {
//     timeval exec_time;
//     gettimeofday(&exec_time, NULL);
//     double start = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;

//     // member function swap
//     {
//         NAMESPACE::map<int, int> map_1;
//         NAMESPACE::map<int, int>::iterator it_begin_1 = map_1.begin();
//         NAMESPACE::map<int, int>::iterator it_end_1 = map_1.end();
//         insertRandomValues(map_1, 15);
//         printContent(map_1);

//         NAMESPACE::map<int, int> map_2;
//         NAMESPACE::map<int, int>::iterator it_begin_2 = map_2.begin();
//         NAMESPACE::map<int, int>::iterator it_end_2 = map_2.end();
//         insertRandomValues(map_2, 8);
//         printContent(map_2);

//         std::cout << std::boolalpha << "Is map_1.begin() == it_begin_1? "
//                   << (map_1.begin() == it_begin_1) << std::endl
//                   << "Is map_1.end() == it_end_1? " << (map_1.end() == it_end_1) << std::endl
//                   << "Is map_2.begin() == it_begin_2? " << (map_2.begin() == it_begin_2)
//                   << std::endl
//                   << "Is map_2.end() == it_end_2? " << (map_2.end() == it_end_2) << std::endl;

//         it_begin_1 = map_1.begin();
//         it_end_1 = map_1.end();
//         it_begin_2 = map_2.begin();
//         it_end_2 = map_2.end();

//         map_1.swap(map_2);
//         printByIterator(map_1, it_begin_2, map_1.end());
//         printByIterator(map_2, it_begin_1, map_2.end());

//         std::cout << "Is map_1.begin() == it_begin_1? " << (map_1.begin() == it_begin_1)
//                   << std::endl
//                   << "Is map_1.begin() == it_begin_2? " << (map_1.begin() == it_begin_2)
//                   << std::endl
//                   << "Is map_2.begin() == it_begin_1? " << (map_2.begin() == it_begin_1)
//                   << std::endl
//                   << "Is map_2.begin() == it_begin_2? " << (map_2.begin() == it_begin_2)
//                   << std::endl;

//         NAMESPACE::map<int, int> map_3(map_2);
//         NAMESPACE::map<int, int>::iterator it_begin_3 = map_3.begin();

//         std::cout << "Is map_3.begin() == it_begin_1? " << (map_3.begin() == it_begin_1)
//                   << std::endl
//                   << "Is map_3.begin() == it_begin_2? " << (map_3.begin() == it_begin_2)
//                   << std::endl;

//         map_3.swap(map_1);
//         printByIterator(map_1, it_begin_3, map_1.end());
//         printByIterator(map_3, it_begin_2, map_3.end());

//         map_3.swap(map_2);
//         printByIterator(map_2, it_begin_2, map_2.end());
//         printByIterator(map_3, it_begin_1, map_3.end());

//         map_3.clear();
//         printContent(map_1);
//         printContent(map_2);
//         printContent(map_3);
//     }

//     // non-member function swap
//     {
//         NAMESPACE::map<char, std::string> map_1;
//         NAMESPACE::map<char, std::string>::iterator it_begin_1 = map_1.begin();
//         NAMESPACE::map<char, std::string>::iterator it_end_1 = map_1.end();
//         insertValue(map_1, INSERT_BY_MAKE_PAIR, 'b',
//                     "I admire your courage but I don't admire your singing ability.");
//         insertValue(map_1, INSERT_BY_MAKE_PAIR, '0', "There was a big earthquake last night.");
//         insertValue(map_1, INSERT_BY_MAKE_PAIR, ' ',
//                     "Tom can't remember all his passwords, so he keeps them in a list disguised as "
//                     "phone numbers.");
//         insertValue(map_1, INSERT_BY_MAKE_PAIR, '!',
//                     "Let's all just take a moment to breathe, please!");
//         insertValue(map_1, INSERT_BY_MAKE_PAIR, '\\',
//                     "It's fascinating that you know all the planets.");
//         insertValue(map_1, INSERT_BY_MAKE_PAIR, 'q',
//                     " Your reputation as an eccentric will rapidly grow in the neighborhood if "
//                     "you're seen walking a pet ostrich on a leash every morning.");
//         insertValue(map_1, INSERT_BY_MAKE_PAIR, '^', "Have you heard the news?");

//         NAMESPACE::map<char, std::string> map_2;
//         NAMESPACE::map<char, std::string>::iterator it_begin_2 = map_2.begin();
//         NAMESPACE::map<char, std::string>::iterator it_end_2 = map_2.end();
//         insertValue(map_2, INSERT_BY_MAKE_PAIR, 'G', "Lorem ipsum dolor sit amet");
//         insertValue(map_2, INSERT_BY_MAKE_PAIR, '@', "");
//         insertValue(map_2, INSERT_BY_MAKE_PAIR, '\'',
//                     "The quick brown fox jumps over the lazy dog");

//         std::cout << "Is map_1.begin() == it_begin_1? " << (map_1.begin() == it_begin_1)
//                   << std::endl
//                   << "Is map_1.end() == it_end_1? " << (map_1.end() == it_end_1) << std::endl
//                   << "Is map_2.begin() == it_begin_2? " << (map_2.begin() == it_begin_2)
//                   << std::endl
//                   << "Is map_2.end() == it_end_2? " << (map_2.end() == it_end_2) << std::endl;

//         it_begin_1 = map_1.begin();
//         it_end_1 = map_1.end();
//         it_begin_2 = map_2.begin();
//         it_end_2 = map_2.end();

//         NAMESPACE::swap(map_1, map_2);
//         printByIterator(map_1, it_begin_2, map_1.end());
//         printByIterator(map_2, it_begin_1, map_2.end());

//         std::cout << "Is map_1.begin() == it_begin_1? " << (map_1.begin() == it_begin_1)
//                   << std::endl
//                   << "Is map_1.begin() == it_begin_2? " << (map_1.begin() == it_begin_2)
//                   << std::endl
//                   << "Is map_2.begin() == it_begin_1? " << (map_2.begin() == it_begin_1)
//                   << std::endl
//                   << "Is map_2.begin() == it_begin_2? " << (map_2.begin() == it_begin_2)
//                   << std::endl;

//         NAMESPACE::map<char, std::string> map_3(map_1);
//         NAMESPACE::map<char, std::string>::iterator it_begin_3 = map_3.begin();

//         std::cout << "Is map_3.begin() == it_begin_1? " << (map_3.begin() == it_begin_1)
//                   << std::endl
//                   << "Is map_3.begin() == it_begin_2? " << (map_3.begin() == it_begin_2)
//                   << std::endl;

//         NAMESPACE::swap(map_3, map_2);
//         printByIterator(map_2, it_begin_3, map_2.end());
//         printByIterator(map_3, it_begin_1, map_3.end());

//         map_3.clear();
//         printContent(map_1);
//         printContent(map_2);
//         printContent(map_3);
//     }

//     gettimeofday(&exec_time, NULL);
//     double end = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;
//     std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
// }

// void gerardErase(void)
// {
//     // timeval exec_time;
//     // gettimeofday(&exec_time, NULL);
//     // double start = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;

//     NAMESPACE::map<int, int> test;
//     insertRandomValues(test, 30);
//     // printContent(test);

//     NAMESPACE::map<int, int> clone(test);
//     // printContent(clone);

//     clone.erase(1234);
//     clone.erase(2339);
//     clone.erase(9876);
//     clone.erase(3919);
//     // printContent(clone);

//     clone.erase(clone.begin(), clone.begin());
//     clone.erase(clone.end(), clone.end());
//     // printContent(clone);

//     clone.swap(test);
//     // printContent(test);
//     // printContent(clone);

//     clone.erase(++(++(clone.begin())));
//     clone.erase(++(clone.begin()));
//     clone.erase(--clone.end());
//     // printContent(clone);

//     clone.erase(++(++clone.begin()), clone.end());
//     // printContent(clone);

//     test.erase(test.begin(), test.end());
//     // printContent(test);

//     // gettimeofday(&exec_time, NULL);
//     // double end = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;
//     // std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" <<
//     // std::endl;
// }

// void hassanErase(void)
// {
//     NAMESPACE::map<int, int> test;

//     for (int i = 1; i <= 30; i++)
//     {
//         test.insert(NAMESPACE::make_pair(rand(), 0));
//     }

//     NAMESPACE::map<int, int> clone(test);

//     clone.erase(20);
//     clone.erase(10);
//     clone.erase(5);
//     clone.erase(15);

//     clone.erase(clone.begin(), clone.begin());
//     clone.erase(clone.end(), clone.end());

//     clone.swap(test);

//     clone.erase(++(++(clone.begin())));
//     clone.erase(++(clone.begin()));
//     clone.erase(--clone.end());

//     for (NAMESPACE::map<int, int>::iterator it = test.begin(); it != test.end(); it++)
//     {
//         std::cout << it->first << std::endl;
//     }
//     clone.erase((clone.begin()), clone.end());
//     clone.erase(++(clone.begin()));
//     clone.erase(++((clone.begin())), ((clone.end())));

//     test.erase(test.begin(), test.end());
// }

void mapTests(void)
{
    mapDefaultConstructor();
    mapSingleInsertNew();
    mapCount();
    // hassanErase();
    // gerardErase();
    mapIterators();
    // mapSingleErase();
    // mapRangeErase();
    // mapClear();
    // mapSwap();
    // mapRangeBasedConstructor();
    mapInsertWithReturnedIterator();
    // mapLowerBound();
    // mapUpperBound();
    mapFind();
    // mapSwap();
    // gerardSwap();
    // std::cout << std::endl;
    // ft::map<int, std::string> strToInt;
    // strToInt.insert(ft::make_pair(1, "one"));
    // strToInt.insert(ft::make_pair(2, "two"));
    // strToInt.insert(ft::make_pair(3, "three"));
    // strToInt.insert(ft::make_pair(4, "four"));
    // strToInt.insert(ft::make_pair(5, "five"));
    // for (ft::map<int, std::string>::iterator it = strToInt.begin(); it != strToInt.end(); it++)
    // {
    //     std::cout << "Node == " << it->second << std::endl;
    // }
    // strToInt.clear();
    // std::cout << std::endl;
    // // strToInt.erase(strToInt.begin());
    // for (ft::map<int, std::string>::iterator it = strToInt.begin(); it != strToInt.end(); it++)
    // {
    //     std::cout << "Node == " << it->second << std::endl;
    // }
}
