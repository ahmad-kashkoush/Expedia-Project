//
// Created by ak on 6/18/23.
//

#ifndef EXPEDIA_PROJECT_ITENIRARY_H
#include "Menu.h"
#define EXPEDIA_PROJECT_ITENIRARY_H
class IteneraryItem{
public:
    virtual double GetCost()=0;
    virtual IteneraryItem* Clone(){return nullptr;}
    virtual void AddInfo()=0;

};
class Flight: public IteneraryItem{
public:
   void AddInfo(){

   }
};
class Hotel: public IteneraryItem{
    double TotalNights;
    double PricePerNight;
public:
    Hotel(double a, double b):
    TotalNights(a), PricePerNight(b){}
    double GetCost(){
        return TotalNights*PricePerNight;
    }
    void AddInfo(){

    }

};
class Itenerary{
private:
    vector<IteneraryItem*> Items;
public:
    void AddIteneraryItem(IteneraryItem *item){
        Items.push_back(item->Clone());
    }

};



#endif //EXPEDIA_PROJECT_ITENIRARY_H
