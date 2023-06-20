//
// Created by ak on 6/18/23.
//
#ifndef EXPEDIA_PROJECT_MENU_H
#include<bits/stdc++.h>
#define el "\n"
using namespace std;

#define EXPEDIA_PROJECT_MENU_H
class ExpediaUtilities{
public:
    // return choice number
    // add vector of choices
   static int createMenu(const vector<string> &options){
        cout<< "Menu:\n ";
        for(int i=1;i<=options.size();i++){
            cout<<"\t"<<i<<":"<<options[i-1]<<el;
        }
        int choice=0;
        while(choice<1 or choice>options.size()) {
            cout << "Enter Number in Range[" << 1 << "-" << options.size() << "]: ";
            cin >> choice;
            if(choice<1 or choice>options.size())
                cout<<"Invalid Try Again.....\n";
        }

        return choice;
    }

};
#endif //EXPEDIA_PROJECT_MENU_H
