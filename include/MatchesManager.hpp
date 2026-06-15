#ifndef __MATCHESMANAGER_HPP__
#define __MATCHESMANAGER_HPP__
#include <iostream>
#include <map>
#include "Match.hpp"

class MatchesManager{
    public:
    MatchesManager() = default;
    int AddMatch(Match match);
    Match& Find(int id);
    private:
    std::map<int, Match> matches_;
};

#endif