#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager{
private:    
    std::vector<Movie> movies;
public:
    void addMovie();
    void printAllMovies() const;
    void searchByTitle() const;
    void printSortedByRating() const;
    void addRatingToMovie(int mId, double score);

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override { return movies.size(); }

    void printMovieById(int id) const;
};