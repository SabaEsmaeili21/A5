#include <iostream>
#include "MatchesManager.hpp"
#include "IdGenerator.hpp"
#include "Match.hpp"
#include "Exception.hpp"

int MatchesManager::AddMatch(Match match){
    int id = IdGenerator::GenerateMatchId();
    matches_.emplace(id, match);
    return id;
}

Match& MatchesManager::Find(int id){
    auto it = matches_.find(id);
    if(it == matches_.end())
        throw NotFound();
    return it->second;
}

