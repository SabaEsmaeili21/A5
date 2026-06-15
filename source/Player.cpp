#include <iostream>
#include "Player.hpp"
#include "OpponentView.hpp"
using namespace std;

void Player::SetCasualMatchReady(bool status){
    readyForCasualMatch_ = status;
}

bool Player::IsReadyForCasualMatch()const{
    return readyForCasualMatch_;
}

OpponentView Player::GetCasualOpponentInfo()const{
    return {username_, xp_};
}

bool Player::IsInGame() const{
    return inGame_;
}

void Player::StartMatch(int matchId){
    currentMatchId_ = matchId;
    inGame_ = true;
}

int Player::CurrentMatchId()const{
    return currentMatchId_;
}

void Player::ApplyCasualWin(int deltaXp){
    xp_ += deltaXp;
    winCount_ ++;
}
void Player::ApplyCasualLoss(int deltaXp){
    xp_ -= deltaXp;
    lossCount_++;
}

void Player::FinishMatch(){
    inGame_ = false;
    currentMatchId_ = -1;
}

int Player::Xp() const{
    return xp_;
}

ProfileView Player::GetProfile() const{
    return ProfileView {username_, xp_, winCount_, lossCount_};
}

Rank Player::GetRank() const{
    return FromRankPoint(rp_);
}

bool Player::IsRank(Rank rank) const{
    return (FromRankPoint(rp_) == rank);
}

void Player::ApplyRankedWin(int deltaRp, int healthBonus){
    rp_ += deltaRp + healthBonus;
    winCount_ ++;
}

void Player::ApplyRankedLoss(int deltaRp){
    rp_ -= deltaRp;
    lossCount_ ++;
}

int Player::CalculateRpChange() const{
    switch(FromRankPoint(rp_)){
        case(Rank::Bronze):
            return 75;
        case(Rank::Silver):
            return 100;
        case(Rank::Gold):
            return 125;
        case(Rank::Platinum):
            return 150;
    }
}
