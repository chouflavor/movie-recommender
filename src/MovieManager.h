#pragma once
#include <vector>
#include <string>
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

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    void printMovieById(int id) const;
};