#include "user.h"
#include <iostream>

using namespace std;

User::User(int id, string nm, string mail) : id(id), name(nm), email(mail) {}

int User::getId() const{
    return id;
}
string User::getName() const{
    return name;
}
string User::getEmail() const{
    return email;
}

void User::display() const{
    cout << "[" << id << "], name: " << name << ", email: " << email << endl;
}