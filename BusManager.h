#ifndef _BusManager_H_
#define _BusManager_H_
#include<iostream>
#include<memory>
#include<map>
#include<bits/stdc++.h>
#include<vector>
#include"BusManagerIF.h"
#include"BusIF.h"
class BusManager:public BusManagerIF , public  std::enable_shared_from_this<BusManager>
{
    private:
        BusManager();
        std::map<std::string,BusIF::Ptr> BusList;
        std::function<void(BusIF::Ptr,BusIF::BusDetails&)> m_fnBus;
    public:
        typedef std::shared_ptr<BusManager> Ptr;
        static BusManagerIF::Ptr CreateBusManager();
        void AddBus(BusIF::BusDetails);
        std::list<BusIF::Ptr> search(stationcode::stCode,stationcode::stCode);
        std::list<BusIF::Ptr> PrintBusList();
        std::string StringPrintBusList();
        bool CancelTicket(std::string);
        virtual void RegisterForAddBus( std::function<void(BusIF::Ptr,BusIF::BusDetails& )> ) override;
        virtual ~BusManager(){};        
};
#endif
