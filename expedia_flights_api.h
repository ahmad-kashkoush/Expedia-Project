/*
 * expedia_flights_api.h
 *
 *  Created on: Sep 18, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_FLIGHTS_API_H_
#include "Itenirary.h"
#define EXPEDIA_FLIGHTS_API_H_


#include <ostream>

using namespace std;


class AirCanadaCustomerInfo {

};

class AirCanadaFlight {
public:
	double price;
	string date_time_from;
	string date_time_to;
};

class AirCanadaOnlineAPI {
public:
	static vector<AirCanadaFlight> GetFlights(string from, string from_date, string to, string to_date, int adults, int childern) {
		vector<AirCanadaFlight> flights;

		flights.push_back( { 200, "25-01-2022", "10-02-2022" });
		flights.push_back( { 250, "29-01-2022", "10-02-2022" });
		return flights;
	}
	static bool ReserveFlight(const AirCanadaFlight& flight, const AirCanadaCustomerInfo &info) {
		return true;
	}
};

class TurkishFlight {
public:
	double cost;
	string datetime_from;
	string datetime_to;
};

class TurkishCustomerInfo {

};

class TurkishAirlinesOnlineAPI {
public:
	void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) {
	}
	void SetPassengersInfo(int infants, int childern, int adults) {
	}
	vector<TurkishFlight> GetAvailableFlights() const {
		vector<TurkishFlight> flights;

		flights.push_back( { 300, "10-01-2022", "10-02-2022" });
		flights.push_back( { 320, "12-01-2022", "10-02-2022" });
		return flights;
	}

	static bool ReserveFlight(const TurkishCustomerInfo &info, const TurkishFlight& flight) {
		return false;
	}
};

///////////////////////////////////////////////
class Flight{
private:
    string AirLineName;
    double cost;
    string datetime_from;
    string datetime_to;
public:
    const string &getAirLineName() const {
        return AirLineName;
    }

    void setAirLineName(const string &airLineName) {
        AirLineName = airLineName;
    }

    double getCost() const {
        return cost;
    }

    void setCost(double cost) {
        Flight::cost = cost;
    }

    const string &getDatetimeFrom() const {
        return datetime_from;
    }

    void setDatetimeFrom(const string &datetimeFrom) {
        datetime_from = datetimeFrom;
    }

    const string &getDatetimeTo() const {
        return datetime_to;
    }

    void setDatetimeTo(const string &datetimeTo) {
        datetime_to = datetimeTo;
    }

    const string &ToString() const{
        stringstream  ss;
        ss << "AirLineName: " << getAirLineName() << " cost: " << getCost() << " datetime_from: "
           << getDatetimeFrom() << " datetime_to: " << getDatetimeFrom();
        return ss.str();
    }

};
class FlightCustomerInfo{
private:
    int infants,  childern,  adults;
    string datetime_from,  from,  datetime_to,  to;
public:
    int getInfants() const {
        return infants;
    }

    void setInfants(int infants) {
        FlightCustomerInfo::infants = infants;
    }

    int getChildern() const {
        return childern;
    }

    void setChildern(int childern) {
        FlightCustomerInfo::childern = childern;
    }

    int getAdults() const {
        return adults;
    }

    void setAdults(int adults) {
        FlightCustomerInfo::adults = adults;
    }

    const string &getDatetimeFrom() const {
        return datetime_from;
    }

    void setDatetimeFrom(const string &datetimeFrom) {
        datetime_from = datetimeFrom;
    }

    const string &getFrom() const {
        return from;
    }

    void setFrom(const string &from) {
        FlightCustomerInfo::from = from;
    }

    const string &getDatetimeTo() const {
        return datetime_to;
    }

    void setDatetimeTo(const string &datetimeTo) {
        datetime_to = datetimeTo;
    }

    const string &getTo() const {
        return to;
    }

    void setTo(const string &to) {
        FlightCustomerInfo::to = to;
    }

    const string &ToString() const{
        stringstream os;
        os << "infants: " << getInfants() << " childern: " << getChildern() << " adults: " << getAdults()
           << " datetime_from: " << getDatetimeFrom() << " from: " << getFrom() << " datetime_to: " << getDatetimeTo()
           << " to: " << getTo();
        return os.str();
    }

};
// Now I want to map every turkish and canada flight to be generic flight
class FlightReservation: public IteneraryItem{
private:
    Flight flight;
    FlightCustomerInfo flightCustomerInfo;
public:
    virtual IteneraryItem *Clone()override{
        return  new FlightReservation(*this);
    }
    virtual double GetCost(){
        return flight.getCost();
    }
    virtual const string & ToString(){
       return flight.ToString();
    }

};
class IFlightMgr{
protected:
    FlightCustomerInfo  Info;
public:
    virtual string GetName()=0;
    virtual vector<Flight> FlightsVector()=0;
    virtual bool ReserveFlight(const FlightReservation &r)=0;
};
class FlightTurkishMgr: public IFlightMgr{
public:
    virtual  string GetName()override{return "Turkish Airline";}
    virtual vector<Flight> FlightsVector()override {
        vector<Flight> flights;
        TurkishAirlinesOnlineAPI at;
        at.SetFromToInfo(Info.getFrom(), Info.getDatetimeFrom(),
                         Info.getDatetimeTo(), Info.getTo());
        at.SetPassengersInfo(Info.getInfants(),Info.getChildern(), Info.getAdults());
        for (auto i: at.GetAvailableFlights()) {
            Flight flight;
            flight.setAirLineName(GetName());
            flight.setCost(i.cost);
            flight.setDatetimeFrom(i.datetime_from);
            flight.setDatetimeTo(i.datetime_to);
            flights.push_back(flight);
        }
        return flights;
    }
    virtual bool ReserveFlight(const FlightReservation& r)override{
        return TurkishAirlinesOnlineAPI::ReserveFlight(TurkishCustomerInfo(), TurkishFlight());
    }

};
class FlightCanada:public IFlightMgr{
public:
    virtual string GetName()override{return "Canada Airline";}
    virtual vector<Flight> FlightsVector(){
        vector<AirCanadaFlight> cFlights=AirCanadaOnlineAPI::GetFlights(Info.getFrom(), Info.getDatetimeFrom()
        , Info.getTo(), Info.getDatetimeTo(), Info.getAdults(), Info.getChildern());
        vector<Flight> Flights;
        for(auto i:cFlights){
            Flight flight;
            flight.setDatetimeTo(i.date_time_to);
            flight.setDatetimeFrom(i.date_time_from);
            flight.setCost(i.price);
            flight.setAirLineName(GetName());
            Flights.push_back(flight);
        }
        return Flights;
    }
    bool ReserveFlight(const FlightReservation &r) override{
        return AirCanadaOnlineAPI::ReserveFlight(AirCanadaFlight(), AirCanadaCustomerInfo());
    }
};
class FlightFactory{
public:
    static vector<IFlightMgr*> GetManagers(){
        vector<IFlightMgr*> mgrs;
        mgrs.push_back(new FlightTurkishMgr());
        mgrs.push_back(new FlightCanada());
        return mgrs;
    }
    static IFlightMgr* GetMgr(const string &name){
        for(auto i: FlightFactory::GetManagers()){
            if(i->GetName()==name)
                return i;
        }
        return nullptr;
    }

};
#endif /* EXPEDIA_FLIGHTS_API_H_ */
