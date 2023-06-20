//
// Created by ak on 6/20/23.
//
#include "SystemRunner.h"
#include "Itenirary.h"
void TestUser(){
    UserManager uMgr;
    vector<User> v=uMgr.getUsers();
    for(auto i:v){
        i.Print();
    }
   uMgr.Login();
    uMgr.GetCur().Print();
    uMgr.SignUP();
    uMgr.GetCur().Print();
    for(auto i:v){
        i.Print();
    }

}
void TestItenerary(){

}