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
    
public:
    void printMenu() const;
    void run();
};