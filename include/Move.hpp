#ifndef __MOVE_HPP__
#define __MOVE_HPP__
#include <iostream>
#include <map>

enum class Move{
    DEFEND,
    SHOOT,
    RELOAD,
    PENDING
};

const std::map<std::string, Move> GetMove{
    {"shoot", Move::SHOOT},
    {"defend", Move::DEFEND},
    {"reload", Move::RELOAD}
};

#endif