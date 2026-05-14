#pragma once
#include <vector>
#include "Rating.h"

class RatingManager{
private:
    std::vector<Rating> ratings;
public:
    Rating addRating();
    void printRatingsByMovie() const;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    const std::vector<Rating>& getRatings() const { return ratings; }
};