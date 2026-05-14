#pragma once
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"

class MovieSystem{
private:
    MovieManager movieMgr;
    RatingManager ratingMgr;
    UserManager userMgr;
    
public:
    void printMenu() const;
    void run();
};