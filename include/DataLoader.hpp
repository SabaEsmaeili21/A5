#ifndef __DATALOADER_HPP__
#define __DATALOADER_HPP__
#include <iostream>
#include <map>
#include "Player.hpp"
#include "Admin.hpp"

class DataLoader{
    public: 
    std::map<std::string, Player> static LoadPlayers(std::string playersFileName);
    std::map<std::string, Admin> static LoadAdmins(std::string adminsFileName);
};
#endif