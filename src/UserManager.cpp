#include "UserManager.h"
#include <iostream>
#include <string>

using namespace std;

void UserManager::addUser(){
    cout << "\n--- [ 사용자 추가 ]---\n";

    string name, mail;

    cin.ignore();

    cout << "이름: ";
    getline(cin, name);

    cout << "이메일: ";
    getline(cin, mail);

    int uId = users.size() + 1;

    User newUser(uId, name, mail);
    users.push_back(newUser);

    cout << "사용자 추가 완료 " << endl;
}

void UserManager::printAllUsers() const{
    if(users.empty()){
        cout << "등록된 사용자가 없습니다." << endl;
        return;
    }
    for(const User& x : users){
            x.display();
        }
    cout << "총 " << users.size() << "명" << endl;
}