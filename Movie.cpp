#include "Movie.h"
#include <iostream>
using namespace std;


Movie::Movie(): id(0), releaseYear(0), totalRating(0.0), ratingCount(0){}

Movie::Movie(int id, const std::string& title,const std::string& genre, int year): 
    id(id), title(title), genre(genre), totalRating(0.0), ratingCount(0) {
        setYear(year);
    }

int Movie::getId() const {
    return id; 
}
string Movie::getTitle() const {
    return title; 
}
string Movie::getGenre() const { 
    return genre; 
}
int Movie::getYear() const {
    return releaseYear; 
}
int Movie::getRatingCount() const {
    return ratingCount; 
}

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;  
    return totalRating / ratingCount;
}

void Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) return;    
    totalRating += r;
    ratingCount++;
}

void Movie::display() const {           
    cout << id << ". " << title
              << " (" << releaseYear << ")"
              << "  평점: " << getAverageRating()
              << " (" << ratingCount << "건)"
              << endl;
}

void Movie::setYear(int year) {
    if (year >= 1888 && year <= 2100) {
        releaseYear = year;
    } 
    else {
        cout << "유효하지 않은 연도입니다. " << endl;
    }
}

bool Movie::operator==(const Movie& o) const{
    return title == o.title && releaseYear == o.releaseYear;
}
bool Movie::operator!=(const Movie& o) const{
    return !(*this == o);
}
bool Movie::operator<(const Movie& o) const {
    double thisRating = this->getAverageRating();
    double otherRating = o.getAverageRating();

    if (thisRating != otherRating) {
        return thisRating < otherRating;
    }
    
    return this->title < o.title;
}
bool Movie::operator>(const Movie& o) const{
    return o < *this;
}

bool Movie::operator<=(const Movie& o) const{
    return !(o < *this);
}

bool Movie::operator>=(const Movie& o) const{
    return !(*this < o);
}

ostream& operator<<(ostream& os, const Movie& m){
    os << "[" << m.title << "] " << m.releaseYear << "년, ⭐️" << m.getAverageRating();
    return os;
}
