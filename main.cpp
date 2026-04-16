#include "Movie.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Movie> movies;

    movies.push_back(Movie(1, "Inception", "Sci-Fi", 2010));
    movies.push_back(Movie(2,"Parasite", "Thriller", 2019));
    movies.push_back(Movie(3, "Interstellar", "Sci-FI", 2014));
    
    movies[0].addRating(4.8);
    movies[0].addRating(4.5);
    movies[1].addRating(5.0);

    for(const Movie& m : movies){
        m.display();
    }

    

    return 0;
}