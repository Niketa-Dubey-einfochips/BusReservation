#ifndef _Ticket_H_
#define _Ticket_H_
#include<iostream>
#include<memory>
#include<list>
#include"Ticket_IF.h"

class Ticket:public TicketIF,public std::enable_shared_from_this<Ticket>
{
public:
       typedef std::shared_ptr<Ticket> Ptr;
        static TicketIF::Ptr CreateTicket(TicketIF::Details &);
        void updateDetalis(TicketIF::Details);
        bool isConfromed(); 
        bool isWaiting();
        bool isCancel();
        int getSeatNo();
        std::string getPNR();
        std::string printDetails();
        virtual void CancelTicket();
        virtual ~Ticket(){};

private:
    Ticket(TicketIF::Details);
    std::string GenratePNR();
    TicketIF::Details m_details;
    virtual TicketIF::Details& getDetails() override;
    virtual TicketIF::Details& PrintTicketDetails() override;
};
#endif
