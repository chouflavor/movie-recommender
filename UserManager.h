#pragma once
#include <vector>
#include "User.h"

class UserManager{
private:
    std::vector<User> users;
public:
    void addUser();
    void printAllUsers() const;
};