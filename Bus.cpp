#include<iostream>
#include<memory>
#include<list>
#include<bits/stdc++.h>
#include<sstream>
#include"BusIF.h"
#include"Bus.h"
#include"Ticket_manager_IF.h"
#include"Ticket_manager.h"
#include"StationCode.h"
Bus::Bus(BusIF::BusDetails Details):m_BusDetails(Details),m_TicketManager(TicketManager::CreateManager(Details.m_capacity))
{  
      
}
BusIF::Ptr Bus::CreateBus(BusIF::BusDetails &Details)
{
    Bus::Ptr pbus(new Bus(Details));
    Details.m_BusNo = pbus->GenrateBusID();
    return pbus;
}
void Bus::updateDetalis(BusIF::BusDetails Details)
{
    m_BusDetails=Details;
}
void Bus::updateSeats(int seat)
{
    m_BusDetails.m_avaiableSeats=seat;
}
std::string Bus::GenrateBusID()
{
    static int BusNum=0;
    BusNum++;
    std::string mystr="BusID_";
    std::string Id = mystr + std::to_string(BusNum);
    m_BusDetails.m_BusNo=Id;
    return Id;
}
bool Bus::isStationAvailable(stationcode::stCode s)
{
   auto it = std::find(m_BusDetails.m_station.begin(),m_BusDetails.m_station.end(),s);
   return (it!=m_BusDetails.m_station.end());

   
}
std::string Bus::BookTicket(Ticket_manager_IF::JourneyDetails Journey)
{
    return m_TicketManager->BookTicket(Journey);
}
bool Bus::CancelTicket(std::string PNR)
{
   if(m_TicketManager->SearchPNR(PNR)==true)
   {
        std::cout<<m_TicketManager->CancelTicket(PNR)<<std::endl;
        return true;
   }
   else
   {
    return false;
   }
}
std::list<TicketIF::Ptr> Bus::getFilterList(TicketIF::statusCode s, char D ,int count)
{
    return m_TicketManager->getFilterList(s,D,count);
}
std::string Bus::PreparedChart()
{
    std::list<TicketIF::Ptr> statusList;
    std::stringstream ss;
    statusList = m_TicketManager->getFilterList(TicketIF::CNF,'A');
    std::string Confromed = "--------Confromed List------ ";
    for(auto it = statusList.begin();it!=statusList.end();it++)
    {
        Confromed = Confromed + "\n" + (*it)->printDetails();
    }
    statusList = m_TicketManager->getFilterList(TicketIF::WL,'A');
    std::string Waiting = "----------waiting list------";
    for(auto it = statusList.begin();it!=statusList.end();it++)
    {
        Waiting = Waiting + "\n" + (*it)->printDetails();
    }
    statusList = m_TicketManager->getFilterList(TicketIF::CAN,'A');
    std::string Cancel = "-------Cancel list------";
    for(auto it = statusList.begin();it!=statusList.end();it++)
    {
        Cancel = Cancel + "\n" + (*it)->printDetails();
    }
    ss<<Confromed<<"\n\n";
    ss<<Waiting<<"\n\n";
    ss<<Cancel<<"\n\n";
    return ss.str();    
}
std::string Bus::PrintBusDetails()
{

    std::stringstream ss;
    ss << "BusNo : " << m_BusDetails.m_BusNo<<" \t";
    auto i= m_BusDetails.m_station.begin();
    int x = *i;
    auto k = m_BusDetails.m_station.end();
    int y =*k;
    ss << "Station : "<<stationcode::Station[x]<<" to "<<stationcode::Station[y]<<" \t";
    ss << "Capacity : " << m_BusDetails.m_capacity<<"\t";
    //ss << "Avaiable Seats : "<<m_BusDetails.m_avaiableSeats<<"\t";
    return ss.str();
}


#if 0
std::string Bus::setDetails()
{
    std::string mystr="BusID_";
    BusNum++;
    BusIF::myBus.BusNo = mystr + std::to_string(BusNum);
    std::cout<<"Enter the source"<<std::endl;
    std::cin>>BusIF::myBus.source;
    std::cout<<"Enter the destination"<<std::endl;
    std::cin>>BusIF::myBus.destination;
    std::cout<<"Enter the total seats you want in bus"<<std::endl;
    std::cin>>BusIF::myBus.Total_avaiable_Seats;
    BusDetails.push_back(myBus);
    return BusIF::myBus.BusNo;
}
void Bus::getDetails()
{
    std::cout<<"BUSID : "<<BusIF::myBus.BusNo<<std::endl;
    std::cout<<"Source : "<<BusIF::myBus.source<<std::endl;
    std::cout<<"Destination : "<<BusIF::myBus.destination<<std::endl;
    std::cout<<"TOTALSEATS : "<<BusIF::myBus.Total_avaiable_Seats<<std::endl;
    
}
std::string Bus::Bus_search(std::string source,std::string destination)
{
    std::string busid;
     for(auto it=BusDetails.begin(); it != BusDetails.end(); it++)
     {
        if(it->source==source && it->destination==destination)
        {
            busid=it->BusNo;
        }
     }

    return busid;
    
}
#endif