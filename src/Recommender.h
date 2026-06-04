#pragma once
#include <vector>
#include <string>
#include "RatingManager.h"
#include "MovieManager.h"

class Recommender {
private:
    const RatingManager& ratingMgr;

public:
    static constexpr double NO_COMMON_MOVIES_PENALTY = -2.0;
    
    Recommender(const RatingManager& rm) 
        : ratingMgr(rm) {}

    std::vector<int> recommend(int targetUserId, const MovieManager& movieMgr, const std::string& genre = "", int K = 3, int N = 3) const;

private:
    double Similaritycalculate(int userA, int userB) const;
};