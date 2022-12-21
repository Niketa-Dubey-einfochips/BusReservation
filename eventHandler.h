
#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <fstream>
#include <list>
#include "Bus.h"
#include "BusManager.h"
#include "StationCode.h"
#include "Ticket.h"
#include "Ticket_manager.h"
#include "Ticket_manager_IF.h"
#include "BusIF.h"
#include "BusManagerIF.h"

class EventHandler
{
    public:
        const std::vector<std::string> status {
            "CONFIRMED",
            "WAITING",
            "CANCELED"
        };
        EventHandler( BusManagerIF::Ptr bm );
        void AddBusCb( BusIF::Ptr bus ,BusIF::BusDetails& );
        void TicketEventCb( TicketIF::Details&);
};
