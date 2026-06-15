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
/*
inline here is mainly because the function is written inside a header file.
inline means It is okay if this function definition appears in
multiple translation units, as long as they are the same function.
*/

#endif
