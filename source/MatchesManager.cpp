#include <iostream>
#include "MatchesManager.hpp"
#include "IdGenerator.hpp"
#include "CasualMatch.hpp"
#include "RankedMatch.hpp"
#include "Exception.hpp"
using namespace std;

int MatchesManager::AddCasualMatch(string player1Username, string player2Username){
    int id = IdGenerator::GenerateMatchId();
    matches_.emplace(id, make_unique<CasualMatch>(player1Username, player2Username));
    return id;
}

int MatchesManager::AddRankedMatch(string player1Username, string player2Username,
    PlayerMatchStartState player1State, PlayerMatchStartState player2State){

    int id = IdGenerator::GenerateMatchId();
    matches_.emplace(id,make_unique<RankedMatch>(player1Username, player2Username,
        player1State, player2State));
    return id;
}

Match& MatchesManager::Find(int id){
    auto it = matches_.find(id);
    if(it == matches_.end())
        throw NotFound();
    return *(it->second);
}

const Match& MatchesManager::Find(int id)const{
    auto it = matches_.find(id);
    if(it == matches_.end())
        throw NotFound();
    return *(it->second);
}

