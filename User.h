//
// Created by ak on 6/18/23.
//

#ifndef EXPEDIA_PROJECT_USER_H
#include "Menu.h"
#include "Itenirary.h"
#define EXPEDIA_PROJECT_USER_H
class User{
private:
    string name; string Pass;
    Itenerary itenerary;
public:
    User(string n, string pass):
    name(n), Pass(pass){}
    // Getters and setters
    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        User::name = name;
    }

    const string &getPass() const {
        return Pass;
    }

    void setPass(const string &pass) {
        Pass = pass;
    }

};

#endif //EXPEDIA_PROJECT_USER_H
