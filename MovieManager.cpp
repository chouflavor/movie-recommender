#include "MovieManager.h"
#include <iostream>
#include <string>

using namespace std;

void MovieManager::addMovie(){
    cout << "\n--- [영화 추가 ---\n]";
    
    int year;
    string title, genre;

    cin.ignore();

    cout << "제목: ";
    getline(cin, title);

    cout << "장르: ";
    getline(cin, title);

    cout << "출시 연도: ";
    cin >> year;

    int mId = movies.size() + 1;

    Movie newMovie(mId, title, genre, year);
    movies.push_back(newMovie);
}
void MovieManager::printAllMovies() const{
    cout << " ";
}