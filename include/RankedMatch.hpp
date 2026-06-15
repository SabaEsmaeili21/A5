#ifndef __RANKEDMATCH_HPP__
#define __RANKEDMATCH_HPP__
#include "Match.hpp"

class RankedMatch : public Match{
    public:
    RankedMatch(std::string player1Username, std::string player2Username)
    : Match(std::move(player1Username), std::move(player2Username), 3, 3),
    player1Health_(3), player2Health_(3) {}

    MatchType Type() const override;
    int GetHealthBonus() const override;

    private:
    RoundOutcome ResolveOutcome(const Round& round) override;

    int player1Health_ = 3;
    int player2Health_ = 3;

};


#endif