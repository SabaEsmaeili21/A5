#ifndef __MATCH_HPP__
#define __MATCH_HPP__
#include <iostream>
#include <map>
#include "Round.hpp"
#include "MatchStatusView.hpp"

class Match{
    public:
    
    Match(std::string player1Username, std::string player2Username,
        int bullet1 = 1, int bullet2 = 1):
    player1Username_(player1Username),player2Username_(player2Username),
    player1Bullets_(bullet1), player2Bullets_(bullet2){
        rounds_.emplace(1, Round{});
    }
    void ProcessMove(Move move, std::string username);
    bool IsFinished() const;
    std::string WinnerUsername() const;
    std::string LoserUsername() const;
    MatchStatusView MatchStatus(std::string username) const;

    private:
    void ResolveRound();
    bool static CanShoot(Move move, int bulletCount);
    std::vector<std::pair<Move, Move>> RoundHistory(std::string username) const;
    std::string player1Username_;
    std::string player2Username_;
    int player1Bullets_;
    int player2Bullets_;
    std::map<int, Round> rounds_;
    int currentRound_ = 1;
    std:: string winnerUsername_;
    bool isFinished_ = false;
};

#endif
