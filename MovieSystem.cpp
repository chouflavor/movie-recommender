#include "MovieSystem.h"
#include <iostream>

using namespace std;

void MovieSystem::printMenu() const {
    cout << "\n=== Movie Recommender ===\n";
    
    cout << "\n[ 영화 관리 ]\n";
    cout << " 1. 영화 추가\n 2. 제목으로 검색\n 3. 전체 목록 출력\n 4. 평점순 정렬 출력\n";
    
    cout << "\n[ 사용자 관리 ]\n";
    cout << " 5. 사용자 추가\n 6. 사용자 목록 출력\n";
    
    cout << "\n[ 평점 관리 ]\n";
    cout << " 7. 평점 입력\n 8. 영화별 평점 보기\n";
    
    cout << "\n 0. 프로그램 종료\n";
    cout << "\n 선택 > ";
}
void MovieSystem::run(){
    int choice = -1;

    while(choice != 0){
        printMenu();
        cin >> choice;

        switch (choice){
            case 1: movieMgr.addMovie(); break; 
            case 2: movieMgr.searchByTitle(); break;
            case 3: movieMgr.printAllMovies(); break;
            case 4: movieMgr.printSortedByRating(); break;
            case 5: userMgr.addUser(); break;
            case 6: userMgr.printAllUsers(); break;
            case 7: {
                Rating r = ratingMgr.addRating(); 
                movieMgr.addRatingToMovie(r.getMid(), r.getScore()); 
                break;
            }
            
            case 8: ratingMgr.printRatingsByMovie(); break;
            case 0: cout << "프로그램을 종료합니다.\n"; break;
            default: cout << "잘못된 입력\n";
        }
    }
}