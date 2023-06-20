//
// Created by ak on 6/18/23.
//

#ifndef EXPEDIA_PROJECT_USER_H
#include "Menu.h"
#define EXPEDIA_PROJECT_USER_H
class User{
private:
    string name; string Pass;
public:
    User(){}
    User(const string &n,const  string &pass):
    name(n), Pass(pass){}
    // Getters and setters
    const string &getName() const {
        return name;
    }
    void setName(const string &Name) {
       name = Name;
    }

    const string &getPass() const {
        return Pass;
    }

    void setPass(const string &pass) {
        Pass = pass;
    }
    bool check(const string &n, const string &pss){
        return n==getName() and pss==getPass();
    }
    void Print()const{
        cout<<getName()<<" "<<getPass()<<"\n";
    }
    void Enter(){
        cout<<"Enter UserName:";
        string n;cin>>n;
        setName(n);
        cout<<"Enter Password: ";
        cin>>n;
        setPass(n);

    }
};
class UserManager {
private:
    vector<User> users;
    User *cur;
    // [UserName->Itenerarires]
    map<string, vector<string> > UserToItenrary;// replace the second type **String** with Itenerary when creating it's class
public:
    UserManager() {
        cur = new User();
        users.push_back(User("Ahmed", "221"));
        users.push_back(User("Basem", "222"));
        users.push_back(User("conan", "223"));

    }

    void Login() {
        bool x = false;
        while (!x) {
            cur=new User();
            cur->Enter();
            for (auto i: users) {
                if (i.check(cur->getName(), cur->getPass())) {
                    x = true;
                    break;
                }
            }
            if (!x) cout << "Wrong Name or Password, Try Again ....\n";
        }
    }

    void SignUP() {
        bool x = false;
        while (!x) {
            cur=new User();
            cur->Enter();
            x = true;
            for (auto i: users) {
                if (i.check(cur->getName(), cur->getPass())) {
                    x = false;
                    break;
                }
            }
            if (!x)cout << "User already Exist.....";
        }
        users.push_back(*cur);
    }

    const vector<User> &getUsers() const {
        return users;
    }

    const User &GetCur() {
        return *cur;
    }

    void ListIteneraries() {
        if (cur == nullptr)return void(cout << "Error....\n");
        tempFillItenrary(GetCur().getName());
        for (auto i: UserToItenrary[GetCur().getName()]) {
            cout << i << "\n";// ? Need Update [Itenerary.ToString]
        }
    }
    void tempFillItenrary(const string &name){
        for(int i=0;i<10;i++)
            UserToItenrary[name].push_back("\t#"+name);
    }

    ~UserManager() {
        users.clear();
        UserToItenrary.clear();
        delete cur;
        cur = nullptr;

    }
};


#endif //EXPEDIA_PROJECT_USER_H
