#include <iostream>
#include <memory>
#include <map>
#include <fstream>
#include <list>
#include <sstream>
#include "Ticket.h"
#include "Ticket_IF.h"
#include "Ticket_manager_IF.h"
Ticket::Ticket(TicketIF::Details Details):m_details(Details)
{
   
}

TicketIF::Ptr Ticket::CreateTicket(TicketIF::Details &details)
{
    Ticket::Ptr pTickit(new Ticket(details));
    details.m_PNR=pTickit->GenratePNR();
    return pTickit;
}

void Ticket::updateDetalis(TicketIF::Details details)
{
    m_details=details;
}
std::string Ticket::GenratePNR()
{
    std::string PNR = "TicketPNR_";
    char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i = 0; i < 10; i++)
        PNR = PNR + letters[rand() % 26];
    m_details.m_PNR=PNR;
    return PNR;
}
std::string Ticket::getPNR()
{
    return m_details.m_PNR;
}
TicketIF::Details& Ticket::getDetails()
{
    return m_details;
}
bool Ticket::isConfromed()
{
    return m_details.m_status == statusCode::CNF;
}
bool Ticket::isWaiting()
{
    return m_details.m_status == statusCode::WL;
}
bool Ticket::isCancel()
{
    return m_details.m_status == statusCode::CAN;
}
int Ticket::getSeatNo()
{
    return m_details.m_seatNo;
}
void Ticket::CancelTicket()
{
    m_details.m_status=statusCode::CAN;
}
std::string Ticket::printDetails()
{
    std::stringstream ss;
    ss << "PNR : " << m_details.m_PNR<<"\t";
    if(m_details.m_status==(statusCode)0)
    {
        ss << "SeatNo. : " << m_details.m_seatNo<<"\t";
    }
    else if(m_details.m_status==(statusCode)1)
    {
        ss << "WaitingNo. : " << m_details.m_seatNo<<"\t";
    }
    else
    {
        ss << "CancelNo. : " << m_details.m_seatNo<<"\t";
    }
    ss << "Status : " << status[m_details.m_status]<<"\t";
    ss << "Name : " <<m_details.m_Name<<"\t";
    return ss.str();
}
TicketIF::Details& Ticket::PrintTicketDetails()
{
   
}