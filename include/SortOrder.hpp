#ifndef __SORTORDER_HPP__
#define __SORTORDER_HPP__
#include <iostream>
#include <map>

enum class SortOrder{
    ASC,
    DESC
};

const std::map<std::string, SortOrder> getSortOrder {
    {"asc", SortOrder::ASC},
    {"desc", SortOrder::DESC}};

#endif