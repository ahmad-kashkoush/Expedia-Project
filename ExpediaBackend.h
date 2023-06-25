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
    bool cancelReservation(const IteneraryItem &it, PaymentCard &pp){
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
        P->setT(t);
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
        Itenerary *itiniary = nullptr;
        if ((itiniary = dynamic_cast<Itenerary*>(cpy))) {
            vector<IteneraryItem*> confirmed_reservations;

            for (IteneraryItem* sub_reservation : itiniary->GetListIteneraries()) {
                bool is_confirmed = confirmReservation(*sub_reservation);
                if (is_confirmed)
                    confirmed_reservations.push_back(sub_reservation);
                else {
                    // If failed to reserve, cancel all what is confirmed so far!
                    for (IteneraryItem* conf_reservation : confirmed_reservations)
                        cancelReservation(*conf_reservation);
                    return false;
                }
            }
        } else
            assert(false);

        delete cpy;
        cpy=nullptr;
        return true;
    }
};

#endif //EXPEDIA_PROJECT_EXPEDIABACKEND_H
