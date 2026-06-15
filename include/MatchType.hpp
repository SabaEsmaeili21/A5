#ifndef __MATCHTYPE_HPP__
#define __MATCHTYPE_HPP__

#include <iostream>
#include <map>

enum class MatchType{
    CASUAL
};

const std::map<std::string, MatchType> GetMatchType{
    {"casual", MatchType::CASUAL}
};


#endif