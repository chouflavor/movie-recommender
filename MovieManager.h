#pragma once
#include <vector>
#include "Movie.h"

class MovieManager{
private:    
    std::vector<Movie> movies;
public:
    void addMovie();
    void printAllMovies() const;
};