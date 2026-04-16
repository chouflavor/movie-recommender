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
    double totalRating;    
    int ratingCount; 

public:  
    Movie();               
    Movie(int id, const string& title, const string& genre, int releaseYear);


    int getId() const;
    string getTitle() const;
    string getGenre() const;
    double getRating()const;
    int getYear()const;
    double getAverageRating() const;  
    int getRatingCount() const; 

    void display() const;
    void addRating(double r);

};