#ifndef _BusIF_H_
#define _BusIF_H_
#include<memory>
#include<iostream>
#include "StationCode.h"
#include "Ticket_manager_IF.h"
class BusIF
{
public:
    BusIF(){};
    typedef std::shared_ptr<BusIF> Ptr;
    struct BusDetails
    {
        std::string m_BusNo;
        std::list<stationcode::stCode> m_station;
        int m_capacity;
        int m_avaiableSeats;
        BusDetails(std::string BusNo, std::list<stationcode::stCode> station, int capacity,int AvaibleSeats)
        {
            m_BusNo=BusNo;
            m_station=station;
            m_capacity=capacity;
            m_avaiableSeats=AvaibleSeats;
        }
        BusDetails(BusDetails &bus)
        {
            m_BusNo=bus.m_BusNo;
            m_station=bus.m_station;
            m_capacity=bus.m_capacity;
            m_avaiableSeats=bus.m_avaiableSeats;
        }
    };
    virtual bool isStationAvailable(stationcode::stCode)=0;
    virtual std::string BookTicket(Ticket_manager_IF::JourneyDetails)=0;
    virtual std::string PrintBusDetails()=0;
    virtual void updateDetalis(BusIF::BusDetails)=0;
    virtual std::list<TicketIF::Ptr> getFilterList(TicketIF::statusCode, char, int)=0;
    virtual std::string PreparedChart()=0;
    virtual bool CancelTicket(std::string)=0;
    virtual void updateSeats(int)=0;
    virtual Ticket_manager_IF::Ptr GetTicketManager() = 0;
    virtual ~BusIF(){};

};
#endif
