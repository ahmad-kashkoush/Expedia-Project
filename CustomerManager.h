//
// Created by ak on 6/22/23.
//

#ifndef EXPEDIA_PROJECT_CUSTOMERMANAGER_H
#define EXPEDIA_PROJECT_CUSTOMERMANAGER_H
#include "ExpediaBackend.h"
#include "Customer.h"
class CustomerMgr{
private:
    Customer *customer;
    ExpediaBackend *backend;
public:
    const Customer &getCustomer(){return *customer;}
    vector<Flight> ListFlights(const FlightCustomerInfo &info){return backend->ListFlight(info);}
    vector<Room> ListRooms(const RoomRequest & request){return backend->ListRoom(request);}
    vector<string> ListPaymentChoices(){
        vector<string> Infos;
        for(auto card: customer->getCards())
            Infos.push_back(card->ToString());
        return Infos;
    }
    bool MakeReservation(const IteneraryItem&reservation,  PaymentCard &card){
        bool CanBePaied=backend->chargeCost(reservation.GetCost(), card);
        if(CanBePaied){
            cout<<"Confirmed Reservation\n";
            customer->AddReservation(reservation);
            return true;
        }else{
            cout<<"Failed to confirm,  cancelling....\n";
            backend->cancelReservation(reservation, card);
            return  false;
        }

    }
    vector<string> listIteneraries(){
        return customer->getIten().ListItenerary();
    }

};
#endif //EXPEDIA_PROJECT_CUSTOMERMANAGER_H
