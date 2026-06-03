#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

    return newRating;
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

void RatingManager::loadFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string uidStr, midStr, scoreStr;
        getline(ss, uidStr, ',');
        getline(ss, midStr, ',');
        getline(ss, scoreStr, ',');
        
        try {
            ratings.push_back(Rating(stoi(uidStr), stoi(midStr), stod(scoreStr)));
        } catch (const std::exception& e) {
            cout << "경고: 평점 데이터 로드 중 형식 오류 발생. (해당 줄 건너뜀) -> " << line << endl;
        }
    }
    fin.close();
    cout << "평점 데이터 로드 완료 (" << ratings.size() << "건)\n";
}

void RatingManager::saveToFile(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) return;
    for (const Rating& r : ratings) {
        fout << r.getUid() << "," << r.getMid() << "," << r.getScore() << "\n";
    }
    fout.close();
}