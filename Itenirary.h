//
// Created by ak on 6/18/23.
//

#ifndef EXPEDIA_PROJECT_ITENIRARY_H
#include "Menu.h"

#define EXPEDIA_PROJECT_ITENIRARY_H
class IteneraryItem{
public:
    virtual IteneraryItem *Clone()=0;
    virtual double GetCost()=0;
    virtual const string &ToString()=0;
};
class Itenerary{
private:
    vector<IteneraryItem*> Items;
public:
    void AddIteneraryItem(IteneraryItem *item){
        Items.push_back(item->Clone());
    }
    double TotalCost(){
        double sum=0;
        for(auto item:Items){
            sum+=item->GetCost();
        }
    }
    void ListItenerary(){
        for(auto item:Items){
            cout<<"\t"<<item->ToString()<<"\n";
        }
    }
};



#endif //EXPEDIA_PROJECT_ITENIRARY_H
