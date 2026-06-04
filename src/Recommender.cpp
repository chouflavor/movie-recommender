#include "Recommender.h"
#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>

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


std::vector<int> Recommender::recommend(int targetUserId, const MovieManager& movieMgr, const std::string& genre, int K, int N) const {
    
    // 1. 장르 필터가 지정된 경우, 해당 장르에 속하는 영화 ID 목록 추출
    std::vector<int> candidateIds;
    if (!genre.empty()) {
        std::vector<Movie> filteredMovies = movieMgr.filterByGenre(genre);
        for (const auto& m : filteredMovies) {
            candidateIds.push_back(m.getId());
        }
    }

    // 2. 타겟 유저가 이미 평가한 영화 목록 수집 및 유저 목록 구성
    std::map<int, double> targetRatings;
    std::set<int> allUsers;
    
    for (const Rating& r : ratingMgr.getRatings()) {
        allUsers.insert(r.getUid());
        if (r.getUid() == targetUserId) {
            targetRatings[r.getMid()] = r.getScore();
        }
    }

    // 3. 타겟 유저와 다른 유저들 간의 유사도 계산
    std::vector<std::pair<int, int>> similarities; // <유사도 점수, 유저 ID>
    for (int otherUser : allUsers) {
        if (otherUser != targetUserId) {
            int sim = Similaritycalculate(targetUserId, otherUser);
            similarities.push_back({sim, otherUser});
        }
    }

    // 유사도 기준 내림차순 정렬 (유사도가 같으면 유저 ID 오름차순)
    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second < b.second;
    });

    // 4. 유사한 상위 K명의 유저가 본 영화를 바탕으로 추천 점수 누적
    std::map<int, double> recommendedMovies; // <영화 ID, 누적 점수>
    
    int limit = std::min(K, static_cast<int>(similarities.size())); 
    for (int i = 0; i < limit; i++) {
        int similarUser = similarities[i].second;
        
        for (const Rating& r : ratingMgr.getRatings()) {
            if (r.getUid() == similarUser) {
                int movieId = r.getMid();
                
                // 타겟 유저가 아직 보지 않은 영화인 경우에만 추천 후보로 등록
                if (targetRatings.count(movieId) == 0) {
                    
                    // [장르 필터 처리] 장르가 입력되었고, 해당 영화가 장르 후보군(candidateIds)에 없다면 제외
                    if (!genre.empty() && std::find(candidateIds.begin(), candidateIds.end(), movieId) == candidateIds.end()) {
                        continue;
                    }
                    
                    recommendedMovies[movieId] += r.getScore(); 
                }
            }
        }
    }

    // 5. 추천 점수 기반 정렬을 위해 vector로 변환
    std::vector<std::pair<double, int>> finalCandidates; // <누적 점수, 영화 ID>
    for (const auto& pair : recommendedMovies) {
        finalCandidates.push_back({pair.second, pair.first});
    }

    // 점수 높은 순으로 정렬 (점수가 같으면 영화 ID 오름차순)
    std::sort(finalCandidates.begin(), finalCandidates.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second < b.second;
    });

    // 6. 최종 상위 N개의 영화 ID 추출 후 반환
    std::vector<int> result;
    int finalLimit = std::min(N, static_cast<int>(finalCandidates.size()));
    for (int i = 0; i < finalLimit; i++) {
        result.push_back(finalCandidates[i].second);
    }

    return result;
}