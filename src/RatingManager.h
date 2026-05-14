#pragma once
#include <vector>
#include <string>
#include "Rating.h"
#include "BaseManager.h"

class RatingManager : public BaseManager{
private:
    std::vector<Rating> ratings;
public:
    Rating addRating();
    void printRatingsByMovie() const;
    const std::vector<Rating>& getRatings() const { return ratings; }

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override { return ratings.size(); }
};