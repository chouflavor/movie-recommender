#pragma once
#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    int id;
    string title;
    string genre;
    int releaseYear;
    double averageRating;  

public:                 
    Movie(int id, const string& title, const string& genre, int releaseYear);

    int getId() const;
    void display() const;

    string getTitle() const;
    string getGenre() const;
    double getRating()const;
    int getYear()const;

    void addRating(double r);

};