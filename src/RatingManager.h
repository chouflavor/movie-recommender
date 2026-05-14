#pragma once
#include <vector>
#include "Rating.h"

class RatingManager{
private:
    std::vector<Rating> ratings;
public:
    Rating addRating();
    void printRatingsByMovie() const;
};