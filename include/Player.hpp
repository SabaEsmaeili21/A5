#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <iostream>
#include "CasualOpponent.hpp"
#include "User.hpp"
#include "ProfileView.hpp"

class Player : public User{
    public:
    Player(std::string username, std::string password, int xp = 500) 
    : User(username, password), xp_(xp){}

    void SetCasualMatchReady(bool status);
    bool IsReadyForCasualMatch()const;
    CasualOpponent GetCasualOpponentInfo()const;
    bool IsInGame() const;
    void StartMatch(int matchId);
    int CurrentMatchId()const;
    void ApplyWin(int deltaXp);
    void ApplyLoss(int deltaXp);
    int Xp() const;
    void FinishMatch();
    ProfileView GetProfile() const;


    private:
    int xp_;
    int winCount_ = 0;
    int lossCount_ = 0;

    bool readyForCasualMatch_ = false;
    bool inGame_ = false;

    int currentMatchId_ = -1;
};

#endif