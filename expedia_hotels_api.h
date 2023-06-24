/*
 * expedia_hotels_api.h
 *
 *  Created on: Sep 22, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_HOTELS_API_H_
#define EXPEDIA_HOTELS_API_H_
#include "Itenirary.h"
class HiltonRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class HiltonHotelAPI {
public:
	static vector<HiltonRoom> SearchRooms(string country, string city, string from_date, string to_date, int adults, int children, int needed_rooms) {
		vector<HiltonRoom> rooms;

		rooms.push_back( { "Interior View", 6, 200.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "City View", 3, 300.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Deluxe View", 8, 500.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};

class MarriottFoundRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class MarriottHotelAPI {
public:
	static vector<MarriottFoundRoom> FindRooms(string from_date, string to_date, string country, string city, int needed_rooms, int adults, int children) {
		vector<MarriottFoundRoom> rooms;

		rooms.push_back( { "City View", 8, 320.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Interior View", 8, 220.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Private View", 5, 600.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};
////////////////////
class Room{
public:
    string HotelName;
    string room_type;
    int available;
    double price_per_night;
    string date_from;
    string date_to;
    const string &ToString(){
        stringstream ss;
        ss<<"Room Type: "<<room_type<<" Avaliable: "<<available
        <<" Price Per Night: "<<price_per_night<<" Date From: "<<date_from
        <<" Date To: "<<date_to;
    }

};
class RoomRequest{
public:
    string country;
    string city;
    string from_date;
    string to_date;
    int adults;
    int children;
    int needed_rooms;
};
class RoomReservation: public IteneraryItem{
protected:
    Room room;
    RoomRequest roomRequest;
public:
    virtual IteneraryItem *Clone()const
    override {
        return new RoomReservation(*this);
    }
    virtual double GetCost(){
        return room.price_per_night;
    }
    virtual const string &ToString(){
        return room.ToString();
    }
    Room GetRoom(){return room;}
};
class IHotelMgr{
protected:
    RoomRequest request;
public:
    void setInfo(const RoomRequest &r){request=r;}
    virtual vector<Room> SearchRoom()=0;
    virtual const string &getName()=0;
};
class HiltonMgr:public IHotelMgr{
public:
    vector<Room> SearchRoom()override{
        vector<HiltonRoom> v=HiltonHotelAPI::SearchRooms(request.country,request.city, request.from_date, request.to_date, request.adults, request.children, request.needed_rooms);

        vector<Room> rooms;
        for(auto i:v){
            Room room;
            room.price_per_night=i.price_per_night;
            room.date_to=i.date_to;
            room.date_from=i.date_from;
            room.available=i.available;
            rooms.push_back(room);
        }
        return rooms;

    }
    const string & getName() override{return "HiltonHotel";}
};
class MarriotMgr: public IHotelMgr{
public:
    virtual vector<Room> SearchRoom(){
        vector<MarriottFoundRoom> v=MarriottHotelAPI::FindRooms(request.from_date, request.to_date, request.country, request.city, request.needed_rooms, request.adults, request.children);
        vector<Room> rooms;
        for(auto i: v){
            Room room;
            room.price_per_night=i.price_per_night;
            room.available=i.available;
            room.date_from=i.date_from;
            room.date_to=i.date_to;
            room.room_type=i.room_type;
            rooms.push_back(room);
        }
        return rooms;
    }
    virtual const string &getName(){return "MarriotFond";}
};
class HotelFactory{
public:
    static vector<IHotelMgr*> getMgrs(){
        vector<IHotelMgr*> v;
        v.push_back(new HiltonMgr());
        v.push_back(new MarriotMgr());
        return v;
    }
    static IHotelMgr* getMgr(const string &name){
        for(auto i: HotelFactory::getMgrs()){
            if(i->getName()==name)
                return i;
        }
        return nullptr;
    }
};
#endif /* EXPEDIA_HOTELS_API_H_ */
