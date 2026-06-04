#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "BaseManager.h"
#include <map>

class MovieManager : public BaseManager{
private:    
    std::vector<Movie> movies;
public:
    void addMovie();
    void printAllMovies() const;
    void searchByTitle() const;
    void printSortedMovies(int sortOption) const;
    bool addRatingToMovie(int mId, double score);

    double getAverageRating() const;
    std::map<std::string, double> getAverageRatingByGenre() const;
    std::vector<Movie> getTopN(int n) const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override { return movies.size(); }

    void printMovieById(int id) const;
    std::vector<Movie> filterByGenre(const std::string& genre) const;
};
