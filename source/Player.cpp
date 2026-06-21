#include <iostream>
#include "Player.hpp"
#include "OpponentView.hpp"
#include "Exception.hpp"

using namespace std;

const int MIN_PENALTY_AMOUNT = 1;
const int MAX_HEALTH_PENALTY_AMOUNT = 2;
const int MAX_BULLET_PENALTY_AMOUNT = 3;
const int MIN_PENALTY_MATCHES = 1;
const int DEFAULT_RANKED_BULLETS = 3;
const int DEFAULT_RANKED_HEALTH = 3;

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

void Player::Block(std::string username){
    blockedUsernames_.insert(username);
}
void Player::Unblock(std::string username){
    blockedUsernames_.erase(username);
}

bool Player::HasBlocked(std::string username) const{
    return blockedUsernames_.count(username);
}

void Player::ApplyHealthPenalty(int amount, int numberOfMatches){

     if (amount < MIN_PENALTY_AMOUNT || amount > MAX_HEALTH_PENALTY_AMOUNT)
        throw BadRequest();

    if (numberOfMatches < MIN_PENALTY_MATCHES)
        throw BadRequest();

    healthPenalty_ = Penalty{amount, numberOfMatches};
}
void Player::ApplyBulletPenalty(int amount, int numberOfMatches){

    if (amount < MIN_PENALTY_AMOUNT || amount > MAX_BULLET_PENALTY_AMOUNT)
        throw BadRequest();

    if (numberOfMatches < MIN_PENALTY_MATCHES)
        throw BadRequest();

    bulletPenalty_ = Penalty{amount, numberOfMatches};
}

PlayerMatchStartState Player::GetRankedMatchStartState() const
{
    int startingBullets = DEFAULT_RANKED_BULLETS;
    int startingHealth = DEFAULT_RANKED_HEALTH;

    if (bulletPenalty_.remainingMatches > 0) {
        startingBullets -= bulletPenalty_.amount;
    }

    if (healthPenalty_.remainingMatches > 0) {
        startingHealth -= healthPenalty_.amount;
    }

    return PlayerMatchStartState{
        .bullets = startingBullets,
        .health = startingHealth
    };
}

void Player::ConsumeRankedMatchPenalties()
{
    if (bulletPenalty_.remainingMatches > 0) {
        bulletPenalty_.remainingMatches--;

        if (bulletPenalty_.remainingMatches == 0)
            bulletPenalty_.amount = 0;
    }

    if (healthPenalty_.remainingMatches > 0) {
        healthPenalty_.remainingMatches--;

        if (healthPenalty_.remainingMatches == 0)
            healthPenalty_.amount = 0;
    }
}