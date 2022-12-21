#ifndef _BusManagerIF_H_
#define _BusManagerIF_H_
#include<iostream>
#include<memory>
#include<map>
#include<vector>
#include<list>
#include"BusIF.h"
#include"StationCode.h"
class BusManagerIF
{
public:    
    typedef std::shared_ptr<BusManagerIF> Ptr;
    BusManagerIF(){};
    virtual ~BusManagerIF(){};   
    virtual void AddBus(BusIF::BusDetails)=0;
    virtual std::list<BusIF::Ptr> search(stationcode::stCode,stationcode::stCode)=0;
    virtual std::list<BusIF::Ptr> PrintBusList()=0;
    virtual bool CancelTicket(std::string)=0;
    virtual void  RegisterForAddBus( std::function<void(BusIF::Ptr,BusIF::BusDetails& )> ) =0 ;   
};
#endif