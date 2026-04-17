#pragma once
#include <vector>
#include "Movie.h"

class MovieManager{
private:    
    std::vector<Movie> movies;
public:
    void addMovie();
    void printAllMovies() const;
    void searchByTitle() const;
    void printSortedByRating() const;
    void addRatingToMovie(int mId, double score);
};