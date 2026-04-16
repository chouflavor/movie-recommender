#pragma once
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"

class MovieSystem{
private:
    MovieManager movieMG;
    RatingManager ratingMG;
    UserManager userMG;
    
    void printMenu() const;
public:
    void run();
};