//
// Created by ak on 6/22/23.
//

#ifndef EXPEDIA_PROJECT_EXPEDIABACKEND_H
#define EXPEDIA_PROJECT_EXPEDIABACKEND_H
#include "expedia_hotels_api.h"
#include "expedia_flights_api.h"
#include "Itenirary.h"
#include "expedia_payments_api.h"
#include "PaymentCard.h"
class ExpediaBackend{
private:
    vector<IFlightMgr*> FlightMgrs;
    vector<IHotelMgr*> HotelMgrs;
    IPay *P;
public:
    ExpediaBackend(){
        FlightMgrs=FlightFactory::GetManagers();
        HotelMgrs=HotelFactory::getMgrs();
        P=PaymentFactory::GetPaymentCard(TransactionInfo());
    }
    vector<Flight> ListFlight(const FlightCustomerInfo&request){
        vector<Flight> ret;
        for(auto mgr: FlightMgrs){
            mgr->setInfo((request));
            vector<Flight> tmp=mgr->FlightsVector();
            ret.insert(ret.end(), tmp.begin(), tmp.end());
        }
        return ret;
    }
    vector<Room> ListRoom(const RoomRequest &request){
        vector<Room> ret;
        for(auto mgr: HotelMgrs){
            mgr->setInfo(request);
            vector<Room> tmp=mgr->SearchRoom();
            ret.insert(ret.end(),tmp.begin(), tmp.end());
        }
        return ret;
    }
    bool unchargeCost(double cost, PaymentCard &p){
        return true;
    }
    bool cancelReservation(const IteneraryItem &it){
        return true;
    }
    bool chargeCost(double cost, PaymentCard &pp){
        /*
            we use this functions **Why?
            1. to set IPay Info
         */

        CreditCard *c=nullptr;
        DebitCard *d=nullptr;
        /* It's Different data members between both , so we need to do downCast to set the difference of user info*/
        string address="";
        if((d=dynamic_cast<DebitCard*>(&pp)))
            address=d->getAddress();
        TransactionInfo t;
        t.name=pp.getUserName();
        t.address=address;
        t.expiry_date=pp.getExpiryDate();
        t.ccv=pp.getPassword();
        t.id="lablabla";
        if(P->Withdraw(cost))
            return true;
        return false;
    }

    bool confirmReservation(IteneraryItem &reservation){
        FlightReservation *flight=nullptr;
        IteneraryItem *cpy=reservation.Clone();
        if( (flight=dynamic_cast<FlightReservation*> (cpy))){
            IFlightMgr *mgr=FlightFactory::GetMgr(flight->GetFlight().getAirLineName());
            if(mgr!=nullptr and mgr->ReserveFlight(*flight))
                return true;
            return false;
        }
        RoomReservation *room=nullptr;
        if( (room=dynamic_cast<RoomReservation*>(cpy))){
            IHotelMgr *mgr=HotelFactory::getMgr(room->GetRoom().HotelName);
            if(mgr!=nullptr /*mgr->ReserveHotel*/)
                return true;
            return false;
        }


    }
};

#endif //EXPEDIA_PROJECT_EXPEDIABACKEND_H
