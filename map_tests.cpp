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

typedef ft::map_tree<int, std::string, std::less<int>,
                     std::allocator<ft::map_node<int, std::string> > >
    intToStrTree;

static void treeInsertTests(void)
{
    intToStrTree s(NULL, std::less<int>(),
                   std::allocator<ft::map_node<int, std::string> >());

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

static void insertRandom(intToStrTree &tree)
{
    tree.insert_node(ft::make_pair(6, "six"));
    tree.insert_node(ft::make_pair(14, "fourteen"));
    tree.insert_node(ft::make_pair(12, "twelve"));
    tree.insert_node(ft::make_pair(1, "one"));
    tree.insert_node(ft::make_pair(19, "nineteen"));
    tree.insert_node(ft::make_pair(10, "ten"));
    tree.insert_node(ft::make_pair(3, "three"));
    tree.insert_node(ft::make_pair(18, "eighteen"));
    tree.insert_node(ft::make_pair(8, "eight"));
    tree.insert_node(ft::make_pair(15, "fifteen"));
    tree.insert_node(ft::make_pair(11, "eleven"));
    tree.insert_node(ft::make_pair(4, "four"));
    tree.insert_node(ft::make_pair(5, "five"));
    tree.insert_node(ft::make_pair(17, "seventeen"));
    tree.insert_node(ft::make_pair(16, "sixteen"));
    tree.insert_node(ft::make_pair(7, "seven"));
    tree.insert_node(ft::make_pair(2, "two"));
    tree.insert_node(ft::make_pair(9, "nine"));
    tree.insert_node(ft::make_pair(20, "twenty"));
    tree.insert_node(ft::make_pair(13, "thirteen"));
}

static void insertOrdered(intToStrTree &tree)
{
    tree.insert_node(ft::make_pair(1, "one"));
    tree.insert_node(ft::make_pair(2, "two"));
    tree.insert_node(ft::make_pair(3, "three"));
    tree.insert_node(ft::make_pair(4, "four"));
    tree.insert_node(ft::make_pair(5, "five"));
    tree.insert_node(ft::make_pair(6, "six"));
    tree.insert_node(ft::make_pair(7, "seven"));
    tree.insert_node(ft::make_pair(8, "eight"));
    tree.insert_node(ft::make_pair(9, "nine"));
    tree.insert_node(ft::make_pair(10, "ten"));
    tree.insert_node(ft::make_pair(11, "eleven"));
    tree.insert_node(ft::make_pair(12, "twelve"));
    tree.insert_node(ft::make_pair(13, "thirteen"));
    tree.insert_node(ft::make_pair(14, "fourteen"));
    tree.insert_node(ft::make_pair(15, "fifteen"));
    tree.insert_node(ft::make_pair(16, "sixteen"));
    tree.insert_node(ft::make_pair(17, "seventeen"));
    tree.insert_node(ft::make_pair(18, "eighteen"));
    tree.insert_node(ft::make_pair(19, "nineteen"));
    tree.insert_node(ft::make_pair(20, "twenty"));
}

static void treeDeleteTests(void)
{
    intToStrTree s(NULL, std::less<int>(),
                   std::allocator<ft::map_node<int, std::string> >());

    insertRandom(s);

    for (int i = 1; i <= 50; i++)
    {
        s.delete_node(i);
    }
    for (int i = 1; i <= 20; i++)
    {
        assert(s.search_node(i) == NULL);
    }

    insertOrdered(s);
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
