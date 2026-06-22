#ifndef __PROFILEVIEW_HPP__
#define __PROFILEVIEW_HPP__
#include <iostream>
#include "Rank.hpp"
struct ProfileView{
    std::string username;
    Rank rank;
    int rp;
    int xp;
    int totalWins;
    int totalLosses;
};
#endif