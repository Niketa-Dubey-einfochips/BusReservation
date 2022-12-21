#include <iostream>
#include <memory>
#include <map>
#include <fstream>
#include <list>
#include <functional>
#include <string>
#include "Bus.h"
#include "BusIF.h"
#include "BusManager.h"
#include "StationCode.h"
#include "Ticket.h"
#include "Ticket_manager_IF.h"
#include "Ticket_manager.h"
#include "eventHandler.h"
#include "Ticket_IF.h"

EventHandler::EventHandler( BusManagerIF::Ptr bm )
{ 
    bm->RegisterForAddBus( std::bind( &EventHandler::AddBusCb,this, std::placeholders::_1,std::placeholders::_2 ));
}

void  EventHandler::TicketEventCb( TicketIF::Details& detail )
{

    std::cout << "Ticket activity : "<<std::endl;
    std::ofstream fout("reservationNotification.txt",std::ios::app);
    std::stringstream ss;
    ss << "PNR : " << detail.m_PNR<<"\t";
    ss << "Status : " << status[detail.m_status]<<"\t";
    ss << "Name : " <<detail.m_Name<<"\t";
    fout<<ss.str()<<"\n";
    fout.close();
}

void EventHandler::AddBusCb( BusIF::Ptr bus , BusIF::BusDetails& d )
{
    bus->GetTicketManager()->RegisterForTicketEvent(std::bind(&EventHandler::TicketEventCb,this, std::placeholders::_1 ));   
    std::ofstream fout("reservationNotification.txt",std::ios::app);
    std::stringstream ss;
    ss << "BusNo : " << d.m_BusNo<<"\t";
    ss << "Seats : " << d.m_avaiableSeats<<"\t";
    ss << "Capacity : " << d.m_capacity<<"\t";
    fout<<ss.str()<<"\n";
    fout.close();
}









