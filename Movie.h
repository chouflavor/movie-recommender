#pragma once
#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    string title;
    string genre;
    string director;
    int releaseYear;
    double rating;  

public:                 
    Movie(string t, string g, string d, int y, double r);

    void display() const;

    string getTitle() const;
    double getRating()const;
    int getYear()const;

    void setRating(double r);

};