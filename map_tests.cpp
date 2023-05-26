/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:57:45 by hsarhan           #+#    #+#             */
/*   Updated: 2023/05/26 22:32:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_pair.hpp"
#include "map_tree.hpp"
#include "node.hpp"
#include "pair.hpp"
#include <cassert>
#include <memory>
#include <string>

static void treeInsertTests(void)
{
    ft::map_tree<int, std::string, std::less<int>, std::allocator<ft::map_node<int, std::string> > >
        s(NULL, std::less<int>(), std::allocator<ft::map_node<int, std::string> >());

    s.insert_node(ft::make_pair(2, "two"));
    s.insert_node(ft::make_pair(5, "five"));
    s.insert_node(ft::make_pair(7, "seven"));
    s.insert_node(ft::make_pair(8, ""));
    s.insert_node(ft::make_pair(1, ""));
    s.insert_node(ft::make_pair(7, ""));
    s.insert_node(ft::make_pair(2, ""));
    s.insert_node(ft::make_pair(-165789, ""));
    s.insert_node(ft::make_pair(4, ""));

    assert(s.search_node(2) != NULL);
    assert(s.search_node(3) == NULL);
    assert(s.search_node(2)->data.first == 2);
    assert(s.search_node(2)->data.second == "two");
    assert(s.search_node(-165789)->data.first == -165789);
    assert(s.search_node(-165789)->data.second == "");
}

static void treeDeleteTests(void)
{
    ft::map_tree<int, std::string, std::less<int>, std::allocator<ft::map_node<int, std::string> > >
        s(NULL, std::less<int>(), std::allocator<ft::map_node<int, std::string> >());

    s.insert_node(ft::make_pair(6, "six"));
    s.insert_node(ft::make_pair(14, "fourteen"));
    s.insert_node(ft::make_pair(12, "twelve"));
    s.insert_node(ft::make_pair(19, "nineteen"));
    s.insert_node(ft::make_pair(10, "ten"));
    s.insert_node(ft::make_pair(3, "three"));
    s.insert_node(ft::make_pair(18, "eighteen"));
    s.insert_node(ft::make_pair(8, "eight"));
    s.insert_node(ft::make_pair(15, "fifteen"));
    s.insert_node(ft::make_pair(11, "eleven"));
    s.insert_node(ft::make_pair(4, "four"));
    s.insert_node(ft::make_pair(5, "five"));
    s.insert_node(ft::make_pair(17, "seventeen"));
    s.insert_node(ft::make_pair(16, "sixteen"));
    s.insert_node(ft::make_pair(7, "seven"));
    s.insert_node(ft::make_pair(2, "two"));
    s.insert_node(ft::make_pair(9, "nine"));
    s.insert_node(ft::make_pair(20, "twenty"));
    s.insert_node(ft::make_pair(13, "thirteen"));

    for (int i = 1; i <= 50; i++)
    {
        s.delete_node(i);
    }
    for (int i = 1; i <= 20; i++)
    {
        assert(s.search_node(i) == NULL);
    }
}

static void treeTests(void)
{
    treeInsertTests();
    treeDeleteTests();
}

void mapTests(void)
{
    treeTests();
}
