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

User* UsersManager::FindUser(string username) const{
    auto playerIt = players_.find(username);
    auto adminIt = admins_.find(username);
    if(playerIt == players_.end()){
        if(adminIt == admins_.end())
            throw NotFound();
        else    
            return &(*adminIt->second);
    }
    else
        return &(*playerIt->second);
}

vector<OpponentView> UsersManager::CasualMatchOpponents(std::string requesterUsername) const{
    
    vector<OpponentView> casualOpponent;

    for(const auto& [username, player] : players_){
        if(player->IsReadyForCasualMatch() && player->Username() != requesterUsername)
            casualOpponent.push_back(player->GetCasualOpponentInfo());
    }
    if(casualOpponent.empty())
        throw Empty();

    return casualOpponent;
}

Player& UsersManager::FindPlayer(std::string username)const{
    auto playerIt = players_.find(username);
    
    if(playerIt == players_.end())
        throw NotFound();
        
    return (*playerIt->second);
}
Admin& UsersManager::FindAdmin(std::string username) const{
    auto adminIt = admins_.find(username);
    
    if(adminIt == admins_.end())
            throw NotFound();
        
    return (*adminIt->second);
}

bool UsersManager::UsernameExists(std::string username) const{
    auto playerIt = players_.find(username);
    auto adminIt = admins_.find(username);
    if(playerIt == players_.end()){
        if(adminIt == admins_.end())
            return false;
        else    
            return true;
    }
    else
        return true;
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
    vector<OpponentView> rankedOpponent;

    for(const auto& [username, player] : players_){
        if(player->IsRank(rank) && player->Username() != requesterUsername)
            rankedOpponent.push_back(player->GetCasualOpponentInfo());
    }
    if(rankedOpponent.empty())
        throw Empty();

    return rankedOpponent;
}
