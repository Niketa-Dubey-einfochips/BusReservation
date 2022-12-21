#ifndef _Ticket_IF_H_
#define _Ticket_IF_H_
#include <memory>
#include <list>
#include<vector>

class TicketIF
{
public:
    typedef std::shared_ptr<TicketIF> Ptr;
    const std::vector<std::string> status {
        "CONFIRMED",
        "WAITING",
        "CANCEL"
    };
    enum statusCode
    {           
        CNF=0,
        WL,
        CAN
    };
    TicketIF();
    struct Details
    {
        std::string m_PNR;
        std::string m_Name;
        int m_seatNo;
        statusCode m_status;
        Details();
        Details(std::string PNR, int seatNo, statusCode status,std::string name)
        {
            m_PNR = PNR;
            m_seatNo = seatNo;
            m_status = status;
            m_Name = name;
        }
        Details(Details &d)
        {
            m_PNR = d.m_PNR;
            m_seatNo = d.m_seatNo;
            m_status = d.m_status;
            m_Name = d.m_Name;
        }
    };
    virtual void updateDetalis(TicketIF::Details) = 0;
    virtual std::string getPNR() = 0;
    virtual bool isConfromed() = 0;
    virtual bool isWaiting() = 0;
    virtual bool isCancel()=0;
    virtual int getSeatNo() = 0;
    virtual std::string printDetails() = 0;
    virtual void CancelTicket()=0;
    virtual TicketIF::Details& getDetails()=0;
    virtual TicketIF::Details& PrintTicketDetails()=0;
    virtual ~TicketIF(){};
};
#endif