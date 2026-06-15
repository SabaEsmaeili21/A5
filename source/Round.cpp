#include <iostream>
#include "Round.hpp"
#include "Exception.hpp"
using namespace std;

void Round::RegisterMove(Move move, PlayerSide player){
    if(player == PlayerSide::Player1){
        if(player1Move_ == Move::PENDING)
            player1Move_ = move;
        else    
            throw PermissionDenied();
    }

    else if(player == PlayerSide::Player2){
        if(player2Move_ == Move::PENDING)
            player2Move_ = move;
        else    
            throw PermissionDenied();
    }
}

bool Round::IsComplete() const{
    return player1Move_ != Move::PENDING &&
           player2Move_ != Move::PENDING;
}

RoundOutcome Round::Outcome() const{
    if(player1Move_ == Move::SHOOT && player2Move_ == Move::RELOAD)
        return RoundOutcome::Player1Wins;

    if(player2Move_ == Move::SHOOT && player1Move_ == Move::RELOAD)
        return RoundOutcome::Player2Wins;
    
    return RoundOutcome::NoWinner;        
}

Move Round::Player1Move() const{
    return player1Move_;
}

Move Round::Player2Move() const{
    return player2Move_;
}