#include "Movie.h"
#include <iostream>
using namespace std;

Movie::Movie(string t, string g, string d, int y, double r){
    title = t;
    genre = g;
    director = d;
    releaseYear = y;
    setRating(r);
}

void Movie::display()const{
    cout << title << " (" << releaseYear << ") [" << genre << "] " << "평점: " << rating << endl;
}

void Movie::setRating(double r){
    if (r < 0.0){
        r = 0.0;
    }
    if (r > 5.0){
        r = 5.0;
    }
    rating = r;
}

string Movie::getTitle()const{
    return title;
}

double Movie::getRating()const{
    return rating;
}

int Movie::getYear()const{
    return releaseYear;
}