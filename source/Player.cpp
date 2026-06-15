#include <iostream>
#include "Player.hpp"
#include "CasualOpponent.hpp"
using namespace std;

void Player::SetCasualMatchReady(bool status){
    readyForCasualMatch_ = status;
}

bool Player::IsReadyForCasualMatch()const{
    return readyForCasualMatch_;
}

CasualOpponent Player::GetCasualOpponentInfo()const{
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

void Player::ApplyWin(int deltaXp){
    xp_ += deltaXp;
    winCount_ ++;
}
void Player::ApplyLoss(int deltaXp){
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
