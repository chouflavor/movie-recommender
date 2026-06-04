#include "MovieManager.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

    auto it = find_if(movies.begin(), movies.end(), 
                      [&keyword](const Movie& m) { return m.getTitle() == keyword; });

    if (it != movies.end()) {
        it->display(); 
    } else {
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
    auto it = find_if(movies.begin(), movies.end(), 
                      [mId](const Movie& m) { return m.getId() == mId; });

    if (it != movies.end()) {
        it->addRating(score); 
    } else {
        cout << "ID가 " << mId << "인 영화를 찾을 수 없음." << endl;
    }
}

void MovieManager::loadFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << " 저장된 영화 데이터가 없습니다." << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, title, genre, yearStr;

        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, genre, ',');
        getline(ss, yearStr, ',');

        try {
            int id = stoi(idStr);
            int year = stoi(yearStr);

            Movie m(id, title, genre, year);
            movies.push_back(m);

        } catch (const std::exception& e) {
            cout << "경고: 영화 데이터 로드 중 형식 오류 발생. (해당 줄 건너뜀) -> " << line << endl;
        }
    }
    fin.close();
    cout << "영화 데이터 로드 완료! (총 " << movies.size() << "건)" << endl;
}

void MovieManager::saveToFile(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "파일 저장 실패: " << filename << endl;
        return;
    }

    for (const Movie& m : movies) {
        fout << m.getId() << "," 
             << m.getTitle() << "," 
             << m.getGenre() << "," 
             << m.getYear() << "\n";
    }
    fout.close();
    cout << "영화 데이터 저장 완료: " << filename << endl;
}
void MovieManager::printMovieById(int id) const {
    auto it = find_if(movies.begin(), movies.end(), 
                      [id](const Movie& m) { return m.getId() == id; });

    if (it != movies.end()) {
        it->display();
    }
}
std::vector<Movie> MovieManager::filterByGenre(const std::string& genre) const {
    std::vector<Movie> result;
    for (const auto& movie : movies) {
        if (movie.getGenre() == genre) {
            result.push_back(movie);
        }
    }
    return result;
}
