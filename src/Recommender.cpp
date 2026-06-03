#include "Recommender.h"
#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

int Recommender::Similaritycalculate(int userA, int userB) const {
    map<int, double> ratingsA;
    map<int, double> ratingsB;

    for (const Rating& r : ratingMgr.getRatings()) {
        if (r.getUid() == userA) ratingsA[r.getMid()] = r.getScore();
        if (r.getUid() == userB) ratingsB[r.getMid()] = r.getScore();
    }

    int commonCount = 0;
    double diffSum = 0.0;

    for (const auto& pairA : ratingsA) {
        int movieId = pairA.first;
        double scoreA = pairA.second;

        if (ratingsB.count(movieId) > 0) {
            commonCount++;
            diffSum += abs(scoreA - ratingsB[movieId]); 
        }
    }

    if (commonCount == 0) return NO_COMMON_MOVIES_PENALTY;

    return (commonCount * COMMON_MOVIE_WEIGHT) - static_cast<int>(diffSum);
}


vector<int> Recommender::recommend(int targetUserId, int K, int N) const {
    
    map<int, double> targetRatings;
    vector<int> allUsers; 

    for (const Rating& r : ratingMgr.getRatings()) {
        if (r.getUid() == targetUserId) {
            targetRatings[r.getMid()] = r.getScore();
        }
        
        if (find(allUsers.begin(), allUsers.end(), r.getUid()) == allUsers.end()) {
            allUsers.push_back(r.getUid());
        }
    }

    if (targetRatings.empty()) {
        return vector<int>();
    }

    
    vector<pair<int, int>> similarities;
    for (int otherUser : allUsers) {
        if (otherUser == targetUserId) continue; 
        
        int simScore = Similaritycalculate(targetUserId, otherUser);
        if (simScore > NO_COMMON_MOVIES_PENALTY) { 
            similarities.push_back({simScore, otherUser});
        }
    }

    sort(similarities.begin(), similarities.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first; 
    });

 
    map<int, double> recommendedMovies; 
    
    int limit = min(K, (int)similarities.size()); 
    for (int i = 0; i < limit; i++) {
        int similarUser = similarities[i].second;
        
       
        for (const Rating& r : ratingMgr.getRatings()) {
            if (r.getUid() == similarUser) {
                int movieId = r.getMid();
                
                
                if (targetRatings.count(movieId) == 0) {
                    recommendedMovies[movieId] += r.getScore(); 
                }
            }
        }
    }

    vector<pair<double, int>> finalCandidates;
    for (const auto& rm : recommendedMovies) {
        finalCandidates.push_back({rm.second, rm.first});
    }

    sort(finalCandidates.rbegin(), finalCandidates.rend());

    vector<int> result; 
    int resultLimit = min(N, (int)finalCandidates.size());
    for (int i = 0; i < resultLimit; i++) {
        result.push_back(finalCandidates[i].second);
    }

    return result;
}