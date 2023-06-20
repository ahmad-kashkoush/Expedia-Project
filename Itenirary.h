//
// Created by ak on 6/18/23.
//

#ifndef EXPEDIA_PROJECT_ITENIRARY_H
#include "Menu.h"
#include "expedia_flights_api.h"
#include "expedia_hotels_api.h"
#define EXPEDIA_PROJECT_ITENIRARY_H
class IteneraryItem{
public:
    virtual IteneraryItem *Clone()=0;
    virtual double GetCost()=0;
    virtual const string &ToString()=0;
};
class IHotel: public IteneraryItem{
    double TotalNights;
    double PricePerNight;
public:
    IHotel(double a, double b):
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
