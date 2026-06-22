#ifndef __MATCHSTATUSVIEW_HPP__
#define __MATCHSTATUSVIEW_HPP__

#include <iostream>
#include <vector>
#include <optional>
#include "Move.hpp"

struct MatchStatusView{
    int turnNum;
    Move yourMove;
    bool opponentHasPlayed;
    std::vector<std::pair<Move, Move>> history;
    int yourRemainingBullets;
    std::optional<int> yourRemainingHealth;
};
#endif