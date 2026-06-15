#ifndef __CASUALMATCH_HPP__
#define __CASUALMATCH_HPP__
#include "Match.hpp"

class CasualMatch : public Match{
    public:
    CasualMatch(std::string player1Username, std::string player2Username)
    :Match(player1Username, player2Username, 1, 1){}

    MatchType Type() const override;

    private:
    RoundOutcome ResolveOutcome(const Round& round) override;
};

#endif