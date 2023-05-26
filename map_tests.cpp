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
    // s.insert_node(ft::make_pair(2, "two"));
    // s.insert_node(ft::make_pair(2, "two"));
    // s.insert_node(ft::make_pair(2, "two"));
    // s.insert_node(ft::make_pair(2, "two"));
    // s.insert_node(ft::make_pair(2, "two"));
    // s.insert_node(ft::make_pair(2, "two"));
    // s.insert_node(ft::make_pair(2, "two"));

    assert(s.search_node(2) != NULL);
    assert(s.search_node(3) == NULL);
    assert(s.search_node(2)->data.first == 2);
    assert(s.search_node(2)->data.second == "two");
    assert(s.search_node(-165789)->data.first == -165789);
    assert(s.search_node(-165789)->data.second == "");
}

static void treeTests(void)
{
    treeInsertTests();
}

void mapTests(void)
{
    treeTests();
}
