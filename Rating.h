#pragma once

class Rating {
private:
    int userID;
    int movieID;
    double score;
public:
    Rating();
    Rating(int id, int mID, double score);

    int getUid() const;
    int getMid() const;
    double getScore() const;

    void display() const;
};