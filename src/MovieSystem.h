#pragma once
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"

class MovieSystem{
private:
    MovieManager movieMgr;
    RatingManager ratingMgr;
    UserManager userMgr;

    void loadAllData();
    void saveAllData() const;
    void processAddRating();
    void processRecommendation();
    void showStatisticsMenu();
    
public:
    void printMenu() const;
    void run();
};