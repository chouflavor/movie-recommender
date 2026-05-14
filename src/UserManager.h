#pragma once
#include <vector>
#include "User.h"

class UserManager{
private:
    std::vector<User> users;
public:
    void addUser();
    void printAllUsers() const;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};