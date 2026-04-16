#pragma once
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
    Movie(int id, const string& title,
          const string& genre, int year);

    int getId() const;
    string getTitle() const;
    string getGenre() const;
    int getReleaseYear() const;  
    double getAverageRating() const;  
    int getRatingCount() const; 
    void addRating(double r);               
    void display() const;

    bool operator==(const Movie& o) const;
    bool operator!=(const Movie& o) const;
    bool operator<(const Movie& o) const;
    bool operator>(const Movie& o) const;
    bool operator<=(const Movie& o) const;
    bool operator>=(const Movie& o) const;
    
    friend ostream& operator<<(ostream& os, const Movie& m);
};