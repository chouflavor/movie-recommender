#include "MovieManager.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <numeric>
#include <algorithm> 
#include <cctype>    
#include <vector>

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

void MovieManager::searchByTitle() const {
    cout << "\n--- [ 제목으로 검색 ] ---\n";

    if(movies.empty()) {
        cout << "등록된 영화가 없습니다." << endl;
        return;
    }

    string keyword;

    cout << "검색할 영화 제목의 일부를 입력: "; 
    getline(cin, keyword);

    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    bool found = false; 
    int matchCount = 0; 

    for (const auto& m : movies) {
        string lowerTitle = m.getTitle();
        transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

        if (lowerTitle.find(lowerKeyword) != string::npos) {
            if (!found) {
                cout << "\n=== 검색 결과 ===\n";
                found = true;
            }
            m.display(); 
            cout << "------------------------\n";
            matchCount++;
        }
    }

    // 4. 결과 출력
    if (!found) {
        cout << "검색 결과가 없습니다." << endl; 
    } else {
        cout << "총 " << matchCount << "건의 영화를 찾았습니다.\n";
    }
}

void MovieManager::printSortedMovies(int sortOption) const {
    if(movies.empty()) {
        cout << "등록된 영화가 없습니다." << endl;
        return;
    }

    vector<Movie> sortedMovies = movies;

    switch(sortOption) {
        case 1: // 평점순 (내림차순)
            sort(sortedMovies.begin(), sortedMovies.end(), [](const Movie& a, const Movie& b) {
                return a.getAverageRating() > b.getAverageRating();
            });
            break;
        case 2: // 가나다순 (오름차순)
            sort(sortedMovies.begin(), sortedMovies.end(), [](const Movie& a, const Movie& b) {
                return a.getTitle() < b.getTitle();
            });
            break;
        case 3: // 최신순 (내림차순)
            sort(sortedMovies.begin(), sortedMovies.end(), [](const Movie& a, const Movie& b) {
                return a.getYear() > b.getYear();
            });
            break;
        default:
            cout << "잘못된 선택입니다." << endl;
            return;
    }

    cout << "\n--- [ 정렬된 영화 목록 ] ---\n";
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

double MovieManager::getAverageRating() const {

    if (movies.empty()) {
        throw std::runtime_error("영화 데이터가 없습니다.");
    }

    double sum = std::accumulate(
        movies.begin(), movies.end(), 0.0,
        [](double acc, const Movie& m) {
            return acc + m.getAverageRating(); 
        }
    );

    return sum / movies.size();
}

std::map<std::string, double> MovieManager::getAverageRatingByGenre() const {
    std::map<std::string, double> sumByGenre;
    std::map<std::string, int>    countByGenre;

    for (const auto& movie : movies) {
        sumByGenre[movie.getGenre()] += movie.getAverageRating(); // 기존 프로젝트 메서드명 반영
        countByGenre[movie.getGenre()]++;
    }

    std::map<std::string, double> avgByGenre;
    
    for (const auto& [genre, sum] : sumByGenre) { 
        avgByGenre[genre] = sum / countByGenre[genre];
    }
    
    return avgByGenre;
}

std::vector<Movie> MovieManager::getTopN(int n) const{
    auto sorted = movies;

    std::sort(sorted.begin(), sorted.end(),
        [](const Movie& a, const Movie& b) {
            return a.getAverageRating() > b.getAverageRating();
        });
    if (n > static_cast<int>(sorted.size())){
        n = sorted.size();
    }
    return std::vector<Movie>(sorted.begin(), sorted.begin() + n);
    
}