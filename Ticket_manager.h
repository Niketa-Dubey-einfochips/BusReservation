#ifndef _Ticket_manager_H_
#define _Ticket_manager_H_
#include<iostream>
#include<memory>
#include<map>
#include<functional>
#include<set>
#include"Ticket_manager_IF.h"
#include"BusIF.h"
#include"StationCode.h"
#include"Ticket_IF.h"

class TicketManager:public Ticket_manager_IF , public  std::enable_shared_from_this<TicketManager>
{
    private:
        TicketManager(int);
        int LastBookCount=0;
        int Total_seats;
        int m_bookCount=0;
        Ticket_manager_IF::JourneyDetails m_JourneyDetails;
        std::map<std::string,TicketIF::Ptr> m_passanger;
        bool compare(TicketIF::Ptr,TicketIF::Ptr);
        void updateSeats(int);
        std::list<int> seatControl;   
        std::function<void(TicketIF::Details&)> m_fn;
    public:
        typedef std::shared_ptr<TicketManager> Ptr;
        static Ticket_manager_IF::Ptr CreateManager(int);
        std::string BookTicket(Ticket_manager_IF::JourneyDetails);
        std::string CancelTicket(std::string);
        std::list<TicketIF::Ptr> getFilterList(TicketIF::statusCode s,char Dir,int count=-1);
        bool SearchPNR(std::string);
        virtual ~TicketManager(){};
        virtual void RegisterForTicketEvent(std::function<void(TicketIF::Details&)>) override;
    
};
#endif
