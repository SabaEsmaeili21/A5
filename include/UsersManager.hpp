#ifndef __USERSMANAGER_HPP__
#define __USERSMANAGER_HPP__
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "OpponentView.hpp"
#include "Player.hpp"
#include "Admin.hpp"

class UsersManager{
    public:
    UsersManager(std::map<std::string, Player> players, std::map<std::string, Admin> admins);
    Player& RegisterPlayer(std::string username, std::string password);
    const Player& FindPlayer(std::string username) const;
    const Admin& FindAdmin(std::string username) const;
    Player& FindPlayer(std::string username);
    Admin& FindAdmin(std::string username);
    std::vector<OpponentView> CasualMatchOpponents(std::string requesterUsername) const;
    bool UsernameExists(std::string username) const;
    std::vector<OpponentView> RankedMatchOpponents(std::string requesterUsername, Rank rank) const;
    bool PlayerExists(std::string username) const;
    bool AdminExists(std::string username) const;

    private:
    std::map<std::string, std::unique_ptr<Player>> players_;
    std::map<std::string, std::unique_ptr<Admin>> admins_;

};

#endif