#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <iostream>
#include <set>
#include "OpponentView.hpp"
#include "User.hpp"
#include "ProfileView.hpp"
#include "Rank.hpp"
#include "Penalty.hpp"
#include "PlayerMatchStartState.hpp"

class Player : public User{
    public:
    Player(std::string username, std::string password, int xp = 500, int rp = 1200) 
    : User(username, password), xp_(xp), rp_(rp){}

    void SetCasualMatchReady(bool status);
    bool IsReadyForCasualMatch()const;
    OpponentView GetCasualOpponentInfo()const;
    bool IsInGame() const;
    void StartMatch(int matchId);
    int CurrentMatchId()const;
    void ApplyCasualWin(int deltaXp);
    void ApplyCasualLoss(int deltaXp);
    int Xp() const;
    void FinishMatch();
    ProfileView GetProfile() const;
    Rank GetRank() const;
    bool IsRank(Rank rank) const;
    void ApplyRankedWin(int deltaRp, int healthBonus);
    void ApplyRankedLoss(int deltaRp);
    int CalculateRpChange() const;
    void Block(std::string username);
    void Unblock(std::string username);
    bool HasBlocked(std::string username) const;
    void ApplyHealthPenalty(int amount, int numOfMatches);
    void ApplyBulletPenalty(int amount, int numOfMatches);
    PlayerMatchStartState GetRankedMatchStartState() const;
    void ConsumeRankedMatchPenalties();
    
    private:
    int winCount_ = 0;
    int lossCount_ = 0;
    int xp_;
    int rp_;

    bool readyForCasualMatch_ = false;
    bool inGame_ = false;

    int currentMatchId_ = -1;

    std::set<std::string> blockedUsernames_;

    Penalty healthPenalty_;
    Penalty bulletPenalty_;
};

#endif