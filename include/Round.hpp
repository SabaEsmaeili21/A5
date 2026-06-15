#ifndef __ROUND_HPP__
#define __ROUND_HPP__
#include <iostream>
#include <vector>
#include "Move.hpp"
#include "PlayerSide.hpp"
#include "RoundOutcome.hpp"

class Round{
    public:
    Round() = default;
    void RegisterMove(Move move, PlayerSide player);
    bool IsComplete() const;
    RoundOutcome Outcome() const;
    Move Player1Move() const;
    Move Player2Move() const;
    private:
    Move player1Move_ = Move::PENDING;
    Move player2Move_ = Move::PENDING;
};
#endif