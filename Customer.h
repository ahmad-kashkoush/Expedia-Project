//
// Created by ak on 6/22/23.
//

#ifndef EXPEDIA_PROJECT_CUSTOMER_H
#define EXPEDIA_PROJECT_CUSTOMER_H
#include "User.h"
#include "expedia_payments_api.h"
#include "expedia_flights_api.h"
#include "expedia_hotels_api.h"
#include "PaymentCard.h"
class Customer: public User{
private:
    vector<PaymentCard *> cards;
    Itenerary iten;
public:
    const vector<PaymentCard *> &getCards() const {
        return cards;
    }
    const Itenerary getIten() const {
        return iten;
    }
    void AddCard(const PaymentCard &card){
        cards.emplace_back(card.Clone());
    }
    void AddReservation(const IteneraryItem &item){
        iten.AddIteneraryItem(item.Clone());
    }

};

#endif //EXPEDIA_PROJECT_CUSTOMER_H
