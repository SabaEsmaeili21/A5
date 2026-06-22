#include <iostream>
#include <map>
#include <memory>
#include <UsersManager.hpp>
#include "Exception.hpp"
using namespace std;

UsersManager::UsersManager(map<string, Player> players, map<string, Admin> admins){
    for(auto&[username, player] : players){
        players_.emplace(username, make_unique<Player>(player));
    }

    for(auto&[username, admin] : admins){
        admins_.emplace(username, make_unique<Admin>(admin));
    }
}

Player& UsersManager::RegisterPlayer(string username, string password){
    if (UsernameExists(username))
        throw BadRequest();
    auto [it, inserted] = players_.emplace(username, make_unique<Player>(username, password));
    return (*it->second);
}


vector<OpponentView> UsersManager::CasualMatchOpponents(std::string requesterUsername) const{
    
    vector<OpponentView> casualOpponents;

    for(const auto& [username, player] : players_){
        if(player->IsReadyForCasualMatch() && player->Username() != requesterUsername)
            casualOpponents.push_back(player->GetCasualOpponentInfo());
    }
    if(casualOpponents.empty())
        throw Empty();

    return casualOpponents;
}

const Player& UsersManager::FindPlayer(std::string username)const{
    auto playerIt = players_.find(username);
    
    if(playerIt == players_.end())
        throw NotFound();
        
    return (*playerIt->second);
}
const Admin& UsersManager::FindAdmin(std::string username) const{
    auto adminIt = admins_.find(username);
    
    if(adminIt == admins_.end())
            throw NotFound();
        
    return (*adminIt->second);
}

Player& UsersManager::FindPlayer(std::string username){
    auto playerIt = players_.find(username);
    
    if(playerIt == players_.end())
        throw NotFound();
        
    return (*playerIt->second);
}

Admin& UsersManager::FindAdmin(std::string username){
    auto adminIt = admins_.find(username);
    
    if(adminIt == admins_.end())
            throw NotFound();
        
    return (*adminIt->second);
}

bool UsersManager::UsernameExists(std::string username) const{
    return PlayerExists(username) ||
           AdminExists(username);
}


bool UsersManager::PlayerExists(std::string username) const{
    auto playerIt = players_.find(username);
    return !(playerIt == players_.end());
}


bool UsersManager::AdminExists(std::string username) const{
    auto adminIt = admins_.find(username);
    return !(adminIt == admins_.end());
}

std::vector<OpponentView> UsersManager::RankedMatchOpponents(std::string requesterUsername, Rank rank) const{
    vector<OpponentView> rankedOpponents;

    for(const auto& [username, player] : players_){
        if(player->IsRank(rank) && player->Username() != requesterUsername)
            rankedOpponents.push_back(player->GetRankedOpponentInfo());
    }
    if(rankedOpponents.empty())
        throw Empty();

    return rankedOpponents;
}
