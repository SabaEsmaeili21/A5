#ifndef __MATCHESMANAGER_HPP__
#define __MATCHESMANAGER_HPP__
#include <iostream>
#include <map>
#include <memory>
#include "Match.hpp"
#include "PlayerMatchStartState.hpp"

class MatchesManager{
    public:
    MatchesManager() = default;
    int AddCasualMatch(std::string player1Username, std::string player2Username);
    int AddRankedMatch(std::string player1Username, std::string player2Username,
        PlayerMatchStartState player1State, PlayerMatchStartState player2State);

    Match& Find(int id);
    const Match& Find(int id) const;
    private:
    std::map<int, std::unique_ptr<Match>> matches_;
};

#endif