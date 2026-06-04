#include "UserManager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void UserManager::addUser(){
    cout << "\n--- [ 사용자 추가 ]---\n";

    string name, mail;

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

void UserManager::loadFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) return; 
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, email;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        
        try {
            users.push_back(User(stoi(idStr), name, email));
        } catch (const std::exception& e) {
            cout << "경고: 유저 데이터 로드 중 형식 오류 발생. (해당 줄 건너뜀) -> " << line << endl;
        }
    }
    fin.close();
    cout << "유저 데이터 로드 완료 (" << users.size() << "명)\n";
}

void UserManager::saveToFile(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) return;
    for (const User& u : users) {
        fout << u.getId() << "," << u.getName() << "," << u.getEmail() << "\n";
    }
    fout.close();
}