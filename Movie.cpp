#include "Movie.h"
#include <iostream>
using namespace std;



Movie::Movie(int id, const string& title, const string& genre, int year) : id(id), title(title), genre(genre), releaseYear(releaseYear), averageRating(0.0){}


void Movie::display()const{
    cout << id << ". " << title << " (" << releaseYear << ")" << endl;
}

void Movie::addRating(double r){
    if (r < 0.0){
        r = 0.0;
    }
    if (r > 5.0){
        r = 5.0;
    }
    averageRating = r;
}

int Movie::getId() const{
    return id;
}

string Movie::getTitle() const{
    return title;
}

string Movie::getGenre() const{
    return genre;
}

double Movie::getRating() const{
    return averageRating;
}

int Movie::getYear() const{
    return releaseYear;
}