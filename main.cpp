#include "Movie.h"
#include <iostream>
using namespace std;

int main() {
    Movie m1(1, "기생충",    "드라마", 2019);
    Movie m2(2, "인터스텔라", "SF",    2014);

    m1.addRating(4.8);
    m2.addRating(4.9);

    m1.display();
   
    m2.display();


    m1.addRating(5.0);
    m1.addRating(6.0);   

    cout << m1.getTitle() << ": " << m1.getAverageRating() << endl;
    
    return 0;
}