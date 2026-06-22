#include <iostream>
#include "Round.hpp"
#include "Exception.hpp"
using namespace std;

void Round::RegisterMove(Move move, PlayerSide playerSide){
    Move& registeredMove = playerSide == PlayerSide::Player1 ? player1Move_
            : player2Move_;

    if (registeredMove != Move::PENDING)
        throw PermissionDenied();

    registeredMove = move;
}

bool Round::IsComplete() const{
    return player1Move_ != Move::PENDING &&
           player2Move_ != Move::PENDING;
}

Move Round::Player2Move() const{
    return player2Move_;
}

Move Round::Player1Move() const{
    return player1Move_;
}