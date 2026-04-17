#include "RatingManager.h"
#include <iostream>

using namespace std;

Rating RatingManager::addRating() {
    
    cout << "\n--- [ 평점 입력 ] ---\n";
    
    int uId, mId;
    double rating;

    cout << "유저 아이디: ";
    cin >> uId;

    cout << "영화 아이디: ";
    cin >> mId;

    cout << "평점(0~5점): ";
    cin >> rating;

    Rating newRating(uId, mId, rating);
    ratings.push_back(newRating);

    cout << "평점 추가 완료! " << endl;
}

void RatingManager::printRatingsByMovie() const{
    cout << "\n--- [ 영화별 평점 목록 ] ---\n";

    if (ratings.empty()) {
        cout << "등록된 평점이 없습니다." << endl;
        return;
    }

    for (const Rating& r : ratings) {
        r.display();
    }

    cout << "총 " << ratings.size() << "건" << endl;
}