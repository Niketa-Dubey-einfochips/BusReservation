#ifndef _Ticket_manager_IF_H_
#define _Ticket_manager_IF_H_
#include<iostream>
#include<memory>
#include<map>
#include<list>
#include <functional>
#include"Ticket_IF.h"
#include"StationCode.h"
class Ticket_manager_IF
{
public:

    struct JourneyDetails
    {
        stationcode::stCode source;
        stationcode::stCode destination;
        std::list<std::string> pass_name;
    };
    typedef std::shared_ptr<Ticket_manager_IF> Ptr;
    Ticket_manager_IF(){};
    virtual ~Ticket_manager_IF(){};
    virtual std::string BookTicket(Ticket_manager_IF::JourneyDetails)=0;
    virtual std::string CancelTicket(std::string)=0;
    virtual std::list<TicketIF::Ptr> getFilterList(TicketIF::statusCode s,char Dir,int count=-1)=0;
    virtual bool SearchPNR(std::string)=0;
    virtual void RegisterForTicketEvent(std::function<void(TicketIF::Details&)>) =0;
    
};
#endif

