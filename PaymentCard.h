//
// Created by ak on 6/22/23.
//

#ifndef EXPEDIA_PROJECT_PAYMENTCARD_H
#define EXPEDIA_PROJECT_PAYMENTCARD_H

#include <ostream>

class PaymentCard{
protected:
    string UserName, CardNumber, ExpiryDate;
    int Password;
public:
    const string &getUserName() const {
        return UserName;
    }

    void setUserName(const string &userName) {
        UserName = userName;
    }

    const string &getCardNumber() const {
        return CardNumber;
    }

    void setCardNumber(const string &cardNumber) {
        CardNumber = cardNumber;
    }

    const string &getExpiryDate() const {
        return ExpiryDate;
    }

    void setExpiryDate(const string &expiryDate) {
        ExpiryDate = expiryDate;
    }

    int getPassword() const {
        return Password;
    }

    void setPassword(int password) {
        Password = password;
    }
   virtual  PaymentCard *Clone()=0;
    virtual const string &ToString(){
        stringstream os;
        os << "UserName: " << UserName << " CardNumber: " << CardNumber << " ExpiryDate: " << ExpiryDate
           << " Password: " << Password;
        return os.str();
    }



};
class DebitCard: public PaymentCard{
private:
    string Address;
public:
    const string &getAddress() const {
        return Address;
    }
    void setAddress(const string &address) {
        Address = address;
    }
    PaymentCard * Clone() override{
        return new DebitCard(*this);
    }
    virtual const string & ToString()override{
        stringstream os;
        os<<"[Debit Card] "<<PaymentCard::ToString()<<" Address: "<<Address;
        return os.str();
    }
};
class CreditCard: public PaymentCard{
public:
    PaymentCard * Clone() override{
        return new CreditCard(*this);
    }
    virtual const string & ToString()override{
        stringstream os;
        os<<"[Credit Card]"<<PaymentCard::ToString();
        return os.str();
    }
};

#endif //EXPEDIA_PROJECT_PAYMENTCARD_H
