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

    void display();

    string getTitle();
    double getRating();
    int getYear();

    void setRating(double r);

};