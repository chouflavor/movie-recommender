#pragma once
#include <vector>
#include "MovieManager.h"
#include "RatingManager.h"

class Recommender {
private:
    const MovieManager& movieMgr;
    const RatingManager& ratingMgr;

public:
    Recommender(const MovieManager& mm, const RatingManager& rm) 
        : movieMgr(mm), ratingMgr(rm) {}

    std::vector<int> recommend(int targetUserId, int K = 3, int N = 3) const;

private:
    int calculateSimilarity(int userA, int userB) const;
};