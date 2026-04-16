#pragma once
#include <vector>
#include "Rating.h"

class RatingManager{
private:
    std::vector<Rating> ratings;
public:
    void addRating();
    void printRatingsByMovie() const;
};