#include "MovieManager.h"
#include <iostream>
#include <string>

using namespace std;

void MovieManager::addMovie(){
    cout << "\n--- [ 영화 추가 ]---\n]";
    
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