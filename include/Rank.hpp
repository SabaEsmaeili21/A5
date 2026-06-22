#ifndef __RANK_HPP__
#define __RANK_HPP__

enum class Rank {
    Bronze,
    Silver,
    Gold,
    Platinum
};

inline Rank FromRankPoint(int rankedPoint) {
    if (rankedPoint < 1400) return Rank::Bronze;
    if (rankedPoint < 1750) return Rank::Silver;
    if (rankedPoint < 2250) return Rank::Gold;
    return Rank::Platinum;
}

#endif
