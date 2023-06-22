/*
 * expedia_payments_api.h
 *
 *  Created on: Sep 18, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_PAYMENTS_API_H_
#define EXPEDIA_PAYMENTS_API_H_



#include <bits/stdc++.h>
using namespace std;

#include "json.hpp"
using namespace json;


class PayPalCreditCard {
public:
	string name;
	string address;
	string id;
	string expiry_date;
	int ccv;
};

class PayPalOnlinePaymentAPI {
public:
	void SetCardInfo(const PayPalCreditCard* const card) {
	}
	bool MakePayment(double money) {
		return true;
	}
};

class StripeUserInfo {
public:
	string name;
	string address;
};

class StripeCardInfo {
public:
	string id;
	string expiry_date;
};

class StripePaymentAPI {
public:
	bool static WithDrawMoney(StripeUserInfo user, StripeCardInfo card, double money) {
		return true;
	}
};

class SquarePaymentAPI {
public:
	bool static WithDrawMoney(string JsonQuery) {
		//cout << JsonQuery << "\n";
		json::JSON obj = JSON::Load(JsonQuery);
		return true;
	}
};
////////////////////////////////////////
class TransactionInfo{
public:
    string name;
    string address;
    string id;
    string expiry_date;
    int ccv;
};

class IPay{
protected:
    TransactionInfo t;
public:
    IPay(const TransactionInfo &t):t(t){}
    virtual void setCardInfo()=0;
    virtual void setUserInfo()=0;
    virtual bool Withdraw(double val)=0;
};
class PreparePaypal: public IPay{
private:
    PayPalCreditCard p;
    PayPalOnlinePaymentAPI api;
public:
    using IPay::IPay;
    virtual void setCardInfo()override{
        p.ccv=t.ccv;
        p.id=t.id;
        p.expiry_date=t.expiry_date;
    }
    virtual void setUserInfo()override{
        p.name=t.name;
        p.address=t.address;
    }
    bool Withdraw(double val) override{
        api.SetCardInfo(&p);
      return  api.MakePayment(val);
    }
};
class PrepareStripe: public IPay{
private:
    StripeUserInfo stu;
    StripeCardInfo stCard;
public:
    using IPay::IPay;
    virtual void setCardInfo() override{
        stCard.expiry_date=t.expiry_date;
        stCard.id=t.id;
    }
    virtual void setUserInfo() override{
        stu.name=t.name;
        stu.address=t.address;
    }
    bool Withdraw(double val) override{
        return StripePaymentAPI::WithDrawMoney(stu, stCard, val);
    }
};
class PrepareSquare:public IPay{
public:
    using IPay::IPay;
    void setCardInfo() override{}
    void setUserInfo() override{}
    bool Withdraw(double val) override{
        json::JSON obj;
        obj["user_info"] = json::Array(t.name, t.address);
        obj["card_info"]["ID"] = t.id;
        obj["card_info"]["DATE"] = t.expiry_date;
        obj["card_info"]["CCV"] = t.ccv;
        obj["money"] = val;

        ostringstream oss;
        oss << obj;
        string json_query = oss.str();

        return SquarePaymentAPI::WithDrawMoney(json_query);
    }
};
class PaymentFactory{
public:
    static IPay* GetPaymentCard(const TransactionInfo &t, int num=1){
        if(num==1)return new PreparePaypal(t);
        else if(num==2)return new PrepareStripe(t);
        else if(num==3)return new PrepareSquare(t);
        return nullptr;
    }
};

#endif /* EXPEDIA_PAYMENTS_API_H_ */
