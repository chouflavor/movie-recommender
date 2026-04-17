#include "MovieManager.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void MovieManager::addMovie(){
    cout << "\n--- [ 영화 추가 ]---\n";
    
    int year;
    string title, genre;

    cin.ignore();

    cout << "제목: ";
    getline(cin, title);

    cout << "장르: ";
    getline(cin, genre);

    cout << "출시 연도: ";
    cin >> year;

    int mId = movies.size() + 1;

    Movie newMovie(mId, title, genre, year);
    movies.push_back(newMovie);

    cout << "영화 추가 완료! " << endl;
}

void MovieManager::printAllMovies() const{
    if(movies.empty()){
        cout << "등록된 영화가 없습니다." << endl;
        return;
    }
    for(const Movie& x : movies){
            x.display();
        }
    cout << "총 " << movies.size() << "편" << endl;
}

void MovieManager::searchByTitle() const{
    cout << "\n--- [ 제목으로 검색 ] ---\n";

    if(movies.empty()) {
        cout << "등록된 영화가 없습니다." << endl;
        return;
    }

    string keyword;
    cin.ignore();
    cout << "검색할 정확한 제목 입력: ";
    getline(cin, keyword);

    bool found = false;

    for (const Movie& m : movies) {
        if (m.getTitle() == keyword) { 
            m.display();
            found = true;
            break; 
        }
    }

    if (!found) {
        cout << "검색 결과가 없습니다." << endl;
    }
}

void MovieManager::printSortedByRating() const {
    cout << "\n--- [ 평점순 영화 목록 ] ---\n";
    if(movies.empty()) {
        cout << "등록된 영화가 없습니다." << endl;
        return;
    }


    vector<Movie> sortedMovies = movies;

    sort(sortedMovies.begin(), sortedMovies.end(), [](const Movie& a, const Movie& b) {
        return a.getAverageRating() > b.getAverageRating();
    });

    for (const Movie& m : sortedMovies) {
        m.display();
    }
    cout << "총 " << sortedMovies.size() << "편" << endl;
}
void MovieManager::addRatingToMovie(int mId, double score) {
    bool found = false;
    for (Movie& m : movies) { 
        if (m.getId() == mId) {
            m.addRating(score); 
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "ID가 " << mId << "인 영화를 찾을 수 없음." << endl;
    }
}