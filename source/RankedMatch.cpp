#include "RankedMatch.hpp"

RoundOutcome RankedMatch::ResolveOutcome(const Round& round){
    Move player1Move = round.Player1Move();
    Move player2Move = round.Player2Move();

    if(player1Move == Move::SHOOT && player2Move == Move::RELOAD)
        player2Health_--;

    if(player2Move == Move::SHOOT && player1Move == Move::RELOAD)
        player1Health_--;
    
    if(player1Health_ == 0)
        return RoundOutcome::Player2Wins;
    if(player2Health_ == 0)
        return RoundOutcome::Player1Wins;
    return RoundOutcome::NoWinner;
}

MatchType RankedMatch::Type() const {
    return MatchType::RANKED;
}

int RankedMatch::GetHealthBonus() const{
    if(player1Health_ != 0)
        return player1Health_ * 25;
    if(player2Health_ != 0)
        return player2Health_ * 25;
    return 0;
}