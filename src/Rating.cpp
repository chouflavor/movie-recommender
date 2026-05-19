#include "Rating.h"
#include <iostream>

using namespace std;

Rating::Rating(){
    userID = 0;
    movieID = 0;
    score = 0.0;
}

Rating::Rating(int id, int mID, double score){
    if (score < 0 || score > 5){
        this->userID = 0;
        this->movieID = 0;
        this->score = 0.0;
    }
    else{
        this->userID = id;
        this->movieID = mID;
        this->score = score;
    }
}

int Rating::getUid() const{
    return userID;
}

int Rating::getMid() const{
    return movieID;
}

double Rating::getScore() const{
    return score;
}

void Rating::display() const{
    cout << " 유저 ID [" << userID << "]  |  영화 ID [" << movieID << "]  |  평점: " << score << "점" << endl;
}