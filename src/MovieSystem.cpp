#include "MovieSystem.h"
#include <iostream>
#include "Recommender.h"

using namespace std;

void MovieSystem::printMenu() const {
    cout << "\n=== Movie Recommender ===\n";
    
    cout << "\n[ 영화 관리 ]\n";
    cout << " 1. 영화 추가\n 2. 제목으로 검색\n 3. 전체 목록 출력\n 4. 영화 목록 정렬 출력\n";
    
    cout << "\n[ 사용자 관리 ]\n";
    cout << " 5. 사용자 추가\n 6. 사용자 목록 출력\n";
    
    cout << "\n[ 평점 관리 ]\n";
    cout << " 7. 평점 입력\n 8. 영화별 평점 보기\n";

    cout << "\n[ 추천 시스템 ]\n";
    cout << " 9. 맞춤 영화 추천 \n";

    cout << "\n[ 통계 ]\n";
    cout << " 10. 통계 보기 \n";
    
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

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "잘못된 입력입니다. 숫자를 입력해주세요.\n";
            continue; 
        }

        try{
            switch (choice){
                case 1: {
                    double avg = movieMgr.getAverageRating();
                    cout << "\n[ 전체 평균 평점 ]: " << avg << "점\n";
                    break;
                }
                case 2: {
                    auto avgByGenre = movieMgr.getAverageRatingByGenre();
                    cout << "\n[ 장르별 평균 평점 ]\n";
                    for(const auto& pair : avgByGenre) {
                        cout << "- " << pair.first << ": " << pair.second << "점\n";
                    }
                    break;
                }
                case 3: {
                    auto top10 = movieMgr.getTopN(10);
                    cout << "\n[ Top 10 영화 ]\n";
                    int rank = 1;
                    for(const auto& movie : top10) {
                        cout << rank++ << "위: ";
                        movie.display();
                    }
                    break;
                }
                case 0: return;
                default: cout << "잘못된 선택\n";
            }
        }catch (const std::exception& e){
            cerr << "오류: " << e.what() << "\n";
        }
    }
}
void MovieSystem::processSortMenu() {
    cout << "\n=== 정렬 옵션 ===\n";
    cout << "1. 평점 높은 순\n";
    cout << "2. 제목 가나다 순\n";
    cout << "3. 최신 개봉 순\n";
    cout << "선택 > ";
    
    int choice;
    cin >> choice;

    if(cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "잘못된 입력입니다.\n";
        return;
    }
    cin.ignore(1000, '\n');

    if (choice >= 1 && choice <= 3) {
        movieMgr.printSortedMovies(choice);
    } else {
        cout << "1~3 사이의 옵션을 선택해주세요.\n";
    }
}
void MovieSystem::waitAndClear() const {
    cout << "\n[ 메인 메뉴로 돌아가려면 엔터(Enter) 키를 누르세요 ]";
    cin.clear();
    cin.get(); 
    system("clear"); 
}
void MovieSystem::run(){
    loadAllData(); 

    int choice = -1;

    while(choice != 0){
        system("clear");
        printMenu();

        cin >> choice;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            system("clear");
            choice = -1;
        }
        cin.ignore(1000, '\n');

        switch (choice){
            case 1: movieMgr.addMovie(); waitAndClear(); break; 
            case 2: movieMgr.searchByTitle(); waitAndClear(); break;
            case 3: movieMgr.printAllMovies(); waitAndClear(); break;
            case 4: processSortMenu(); waitAndClear(); break;
            case 5: userMgr.addUser(); waitAndClear(); break;
            case 6: userMgr.printAllUsers(); waitAndClear(); break;
            case 7: processAddRating(); waitAndClear(); break;        
            case 8: ratingMgr.printRatingsByMovie(); waitAndClear(); break;
            case 9: processRecommendation(); waitAndClear(); break;
            case 10: showStatisticsMenu(); waitAndClear();break;    
            case 0: 
                cout << "프로그램을 종료합니다.\n";
                saveAllData();                         
                break;
            default: cout << "잘못된 입력\n"; waitAndClear(); break;
        }
    }
}