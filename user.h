#pragma once
#include <string>

using namespace std;

class User{
private:
    int id;
    string name;
    string email;
public:
    User(int id, string nm, string mail);

    int getId() const;
    string getName() const;
    string getEmail() const;

    void display() const;
};
