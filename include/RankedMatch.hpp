#ifndef __RANKEDMATCH_HPP__
#define __RANKEDMATCH_HPP__
#include "Match.hpp"
#include "PlayerMatchStartState.hpp"

class RankedMatch : public Match{
    public:
    RankedMatch(
    std::string player1Username,
    std::string player2Username,
    PlayerMatchStartState player1State,
    PlayerMatchStartState player2State)
    : Match(player1Username,player2Username,
    player1State.bullets, player2State.bullets),
    player1Health_(player1State.health),
    player2Health_(player2State.health){}

    MatchType Type() const override;
    int GetHealthBonus() const override;

    private:
    RoundOutcome ResolveOutcome(const Round& round) override;

    int player1Health_ = 3;
    int player2Health_ = 3;

};


#endif