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
        return EnterRange(1, (int)options.size());
    }
    static int EnterRange(int start, int end){
        int choice=0;
        while(choice<start or choice>end) {
            cout << "Enter Number in Range[" << start << "-" << end << "]: ";
            cin >> choice;
            if(choice<start or choice>end)
                cout<<"Invalid Try Again.....\n";
        }
        return choice;
    }
    string GetCurrentTimeDate() {	// src: https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }

};
#endif //EXPEDIA_PROJECT_MENU_H
