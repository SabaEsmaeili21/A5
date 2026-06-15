#include "CasualMatch.hpp"

RoundOutcome CasualMatch::ResolveOutcome(const Round& round){
    Move player1Move = round.Player1Move();
    Move player2Move = round.Player2Move();
    if(player1Move == Move::SHOOT && player2Move == Move::RELOAD)
        return RoundOutcome::Player1Wins;

    if(player2Move == Move::SHOOT && player1Move == Move::RELOAD)
        return RoundOutcome::Player2Wins;
    
    return RoundOutcome::NoWinner;    
}

MatchType CasualMatch::Type() const {
    return MatchType::CASUAL;
}