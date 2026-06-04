#include "MovieSystem.h"
#include <iostream>
#include "Recommender.h"

using namespace std;

void MovieSystem::printMenu() const {
    cout << "\n=== Movie Recommender ===\n";
    
    cout << "\n[ 영화 관리 ]\n";
    cout << " 1. 영화 추가\n 2. 제목으로 검색\n 3. 전체 목록 출력\n 4. 평점순 정렬 출력\n";
    
    cout << "\n[ 사용자 관리 ]\n";
    cout << " 5. 사용자 추가\n 6. 사용자 목록 출력\n";
    
    cout << "\n[ 평점 관리 ]\n";
    cout << " 7. 평점 입력\n 8. 영화별 평점 보기\n";

    cout << "\n[추천 시스템]\n";
    cout << " 9. 맞춤 영화 추천 \n";
    
    cout << "\n 0. 프로그램 종료\n";
    cout << "\n 선택 > ";
}
void MovieSystem::loadAllData() {
    movieMgr.loadFromFile("data/movies.csv");
    userMgr.loadFromFile("data/users.csv");
    ratingMgr.loadFromFile("data/ratings.csv");

    for (const Rating& r : ratingMgr.getRatings()) {
        movieMgr.addRatingToMovie(r.getMid(), r.getScore());
    }
}
void MovieSystem::saveAllData() const {
    movieMgr.saveToFile("data/movies.csv");
    userMgr.saveToFile("data/users.csv");
    ratingMgr.saveToFile("data/ratings.csv");
}
void MovieSystem::processAddRating() {
    Rating r = ratingMgr.addRating(); 
    movieMgr.addRatingToMovie(r.getMid(), r.getScore()); 
}
void MovieSystem::processRecommendation() {
    cout << "\n--- [ 맞춤 영화 추천 ] ---\n";
    int targetId;
    cout << "추천을 받을 유저 ID를 입력하세요: ";
    cin >> targetId;
    
    cin.ignore(); 
    string genre;
    cout << "선호하는 장르를 입력하세요 (전체 추천은 엔터): ";
    getline(cin, genre);

    Recommender rec(ratingMgr);

    vector<int> recommended = rec.recommend(targetId, movieMgr, genre);

    if (recommended.empty()) {
        cout << "데이터가 부족하거나 조건에 맞는 추천 영화가 없습니다." << endl;
    } else {
        cout << "[" << targetId << "]님의 추천 영화 " << recommended.size() << "편 추천:\n";
        for (int mId : recommended) {
            movieMgr.printMovieById(mId); 
        }
    }
}

void MovieSystem::showStatisticsMenu(){
    while(true){
        cout << "\n=== 통계 메뉴 ===\n";
        cout << "1. 전체 평균 평점\n";
        cout << "2. 장르별 평균 평점\n";
        cout << "3. Top 10 영화\n";
        cout << "0. 돌아가기\n";

        int choice;
        cin >> choice;

        try{
            switch (choice){
                case 1: movieMgr.getAverageRating(); break;
                case 2: movieMgr.getAverageRatingByGenre(); break;
                case 3: movieMgr.getTopN(10); break;
                case 0: return;
                default: cout << "잘못된 선택\n";
            }
        }catch (const std::exception& e){
            cerr << "오류: " << e.what() << "\n";
        }
    }
}
void MovieSystem::run(){
    loadAllData(); 

    int choice = -1;

    while(choice != 0){
        printMenu();

        cin >> choice;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }
        
        switch (choice){
            case 1: movieMgr.addMovie(); break; 
            case 2: movieMgr.searchByTitle(); break;
            case 3: movieMgr.printAllMovies(); break;
            case 4: movieMgr.printSortedByRating(); break;
            case 5: userMgr.addUser(); break;
            case 6: userMgr.printAllUsers(); break;
            case 7: processAddRating(); break;        
            case 8: ratingMgr.printRatingsByMovie(); break;
            case 9: processRecommendation(); break;    
            case 0: 
                cout << "프로그램을 종료합니다.\n";
                saveAllData();                         
                break;
            default: cout << "잘못된 입력\n";
        }
    }
}