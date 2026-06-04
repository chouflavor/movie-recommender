#include "Recommender.h"
#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

double Recommender::Similaritycalculate(int userA, int userB) const {
    map<int, double> ratingsA;
    map<int, double> ratingsB;

    for (const Rating& r : ratingMgr.getRatings()) {
        if (r.getUid() == userA) ratingsA[r.getMid()] = r.getScore();
        if (r.getUid() == userB) ratingsB[r.getMid()] = r.getScore();
    }

    double dotProduct = 0.0;
    double normA = 0.0;
    double normB = 0.0;

    // 벡터 A의 크기 제곱 및 내적 계산
    for (const auto& pairA : ratingsA) {
        int movieId = pairA.first;
        double scoreA = pairA.second;
        
        normA += scoreA * scoreA;

        if (ratingsB.count(movieId) > 0) {
            dotProduct += scoreA * ratingsB[movieId]; 
        }
    }

    if (dotProduct == 0.0) return NO_COMMON_MOVIES_PENALTY;

    for (const auto& pairB : ratingsB) {
        normB += pairB.second * pairB.second;
    }

    if (normA == 0.0 || normB == 0.0) return NO_COMMON_MOVIES_PENALTY;

    return dotProduct / (sqrt(normA) * sqrt(normB));
}


std::vector<int> Recommender::recommend(int targetUserId, const MovieManager& movieMgr, const std::string& genre, int K, int N) const {
    
    std::vector<int> candidateIds;
    if (!genre.empty()) {
        std::vector<Movie> filteredMovies = movieMgr.filterByGenre(genre);
        for (const auto& m : filteredMovies) {
            candidateIds.push_back(m.getId());
        }
    }

    std::map<int, double> targetRatings;
    std::set<int> allUsers;
    
    for (const Rating& r : ratingMgr.getRatings()) {
        allUsers.insert(r.getUid());
        if (r.getUid() == targetUserId) {
            targetRatings[r.getMid()] = r.getScore();
        }
    }

    std::vector<std::pair<double, int>> similarities; 
    for (int otherUser : allUsers) {
        if (otherUser != targetUserId) {
            double sim = Similaritycalculate(targetUserId, otherUser);
            similarities.push_back({sim, otherUser});
        }
    }

    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) {
            return a.first > b.first; 
        }
        return a.second < b.second;
    });

    std::map<int, double> recommendedMovies; 
    
    int limit = std::min(K, static_cast<int>(similarities.size())); 
    for (int i = 0; i < limit; i++) {
        int similarUser = similarities[i].second;
        
        for (const Rating& r : ratingMgr.getRatings()) {
            if (r.getUid() == similarUser) {
                int movieId = r.getMid();
                
                if (targetRatings.count(movieId) == 0) {
                    
                    if (!genre.empty() && std::find(candidateIds.begin(), candidateIds.end(), movieId) == candidateIds.end()) {
                        continue;
                    }
                    
                    recommendedMovies[movieId] += r.getScore(); 
                }
            }
        }
    }

    std::vector<std::pair<double, int>> finalCandidates; 
    for (const auto& pair : recommendedMovies) {
        finalCandidates.push_back({pair.second, pair.first});
    }

    std::sort(finalCandidates.begin(), finalCandidates.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second < b.second;
    });

    std::vector<int> result;
    int finalLimit = std::min(N, static_cast<int>(finalCandidates.size()));
    for (int i = 0; i < finalLimit; i++) {
        result.push_back(finalCandidates[i].second);
    }

    return result;
}