#pragma once
#include <vector>
#include "RatingManager.h"

class Recommender {
private:
    const RatingManager& ratingMgr;

public:
    Recommender(const RatingManager& rm) 
        : ratingMgr(rm) {}

    std::vector<int> recommend(int targetUserId, int K = 3, int N = 3) const;

private:
    int Similaritycalculate(int userA, int userB) const;
};