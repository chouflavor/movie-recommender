#pragma once
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"
#include <cstdlib>

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
    void processSortMenu();
    void waitAndClear() const;

public:
    void printMenu() const;
    void run();
};