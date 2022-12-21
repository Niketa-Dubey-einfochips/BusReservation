
#include<iostream>
#include<memory>
#include"Ticket_IF.h"
#include"Ticket_manager_IF.h"
#include"Ticket_manager.h"
#include"Ticket.h"
#include"BusIF.h"
#include"BusManagerIF.h"
#include"BusManager.h"
#include "eventHandler.h"
#include"Bus.h"
#include<map>
#include<list>
#include<iterator>
#include<vector>
#include"StationCode.h"

std::ostream &operator<<(std::ostream &os, const std::list<BusIF::Ptr> &list)
{
    for (auto const &i: list) {
        os << i << std::endl;
    }
    return os;
}
int main()
{
    int m_s;
    int m_d;
    int i;
    int pass_no;
    int bus;
    std::string m_name;   
    std::list<stationcode::stCode> stationlist2;
    BusManagerIF::Ptr B1= BusManager::CreateBusManager();
    EventHandler e1(B1);   
    std::list <BusIF::Ptr> buslist;
    std::list<BusIF::Ptr>::iterator it;
    stationlist2.push_back(stationcode::SUT);
    stationlist2.push_back(stationcode::PUN);
    std::cout<<std::endl;
    //BusIF::BusDetails details1("Bus2",stationlist1,4,5);
    int expression;
    int ch;
    int choice;
    std::string tp;
    std::ifstream fin("reservationNotification.txt");
   do
   {
    std::cout<<"------MAIN MENU-----"<<std::endl;
    std::cout<<"1.Admin Access"<<std::endl;
    std::cout<<"2.User Access"<<std::endl;
    std::cout<<"3. Quit"<<std::endl;
    std::cout<<"Enter the choice"<<std::endl;
    std::cin>>expression;
    switch (expression)
    {
        case 1: 
           
            do
            {
                std::cout<<"Welcome to admin access"<<std::endl;
                std::cout<<"1. Add Bus"<<std::endl;
                std::cout<<"2. Delete Bus"<<std::endl;
                std::cout<<"3. Prepared Chart"<<std::endl;
                std::cout<<"4. transtations"<<std::endl;
                std::cout<<"5. exit to main menu"<<std::endl;
                
                std::cin>>ch;
                switch (ch)
                {
                    case 1:
                    {
                        std::cout<<"------Add bus------"<<std::endl;
                        std::list<stationcode::stCode> stationlist1;
                        int stat;
                        int code;
                        int capacity;
                        std::cout<<"Add the stations you want add in busroute"<<std::endl;
                        i=0;
                        for (auto it = stationcode::Station.begin() ; it != stationcode::Station.end(); ++it)
                        {
                            std::cout <<i<< "\t" << *it<<std::endl;
                            i++;
                        }
                        std::cout<<"Enter the no of stations you need to add"<<std::endl;
                        std::cin>>stat;
                        for(int i=0;i<stat;i++)
                        {
                            std::cout<<"Add the station code"<<std::endl;
                            std::cin>>code;
                            stationlist1.push_back((stationcode::stCode)code);
                        }
                        std::cout<<"Enter the capacity of bus"<<std::endl;
                        std::cin>>capacity;
                        BusIF::BusDetails details("Bus1",stationlist1,capacity,capacity);
                        B1->AddBus(details);
                        //B1->AddBus(details1);
                    }
                        break;
                    case 2:
                        std::cout<<"---------Delete Bus-----"<<std::endl;
                        
                        break;
                    case 3:
                        std::cout<<"---------preparaed chart------"<<std::endl;
                        i=0;
                        buslist=B1->PrintBusList();
                        for(auto it=buslist.begin();it!=buslist.end();it++)
                        {
                            std::cout<<i<<"\t"<<(*it)->PrintBusDetails()<<std::endl;
                            i++;
                        }
                        std::cout<<"Select the bus"<<std::endl;
                        std::cin>>bus;
                        it = buslist.begin();
                        std::advance(it,bus);
                        std::cout<<(*it)->PreparedChart()<<std::endl;
                        break;
                    case 4:
                        std::cout<<"--------Transactions------"<<std::endl; 
                        while(getline(fin, tp)){  //read data from file object and put it into string.
                            std::cout << tp << std::endl; 
                        }
                        //fin>>str;   
                        fin.close();
                        break;
                    case 5:
                        std::cout<<"--------back to main menu------"<<std::endl;
                        break;
                    default:
                        std::cout<<"--------enter the valid choice-----"<<std::endl;
                        break;
                }    
            }while(ch!=5);
            break;
        case 2:
                std::cout<<"---------USER ACCESS---------"<<std::endl;
                    do
                    {   
                    std::cout<<"---------1. BOOK TICKET---------"<<std::endl;
                    std::cout<<"---------2. CANCEL TICKET---------"<<std::endl;
                    std::cout<<"---------3. QUIT--------------"<<std::endl;
                    std::cout<<"---------ENTER YOUR CHOICE---------"<<std::endl;
                    std::cin>>choice;
                    switch (choice)
                    {
                    case 1:
                    {
                        Ticket_manager_IF::JourneyDetails Journey;
                        std::cout<<"---------BOOK TICKET---------"<<std::endl;
                        i=0;
                        for (auto it = stationcode::Station.begin() ; it != stationcode::Station.end(); ++it)
                        {
                            std::cout <<i<< "\t" << *it<<std::endl;
                            i++;
                        }
                        std::cout<<"Enter the source"<<std::endl;
                        std::cin>>m_s;
                        Journey.source = (stationcode::stCode)m_s;
                        std::cout<<"Enter the destination"<<std::endl;
                        std::cin>>m_d;
                        Journey.destination = (stationcode::stCode)m_d;
                        buslist=B1->search((stationcode::stCode)m_s,(stationcode::stCode)m_d);
                        i=0;
                        if(!buslist.empty())
                        {
                            std::cout<<"List of bus that go from "<<stationcode::Station[m_s]<<" to "<<stationcode::Station[m_d]<<std::endl;
                            for(auto it=buslist.begin();it!=buslist.end();it++)
                            {
                                std::cout<<i<<"\t"<<(*it)->PrintBusDetails()<<std::endl;
                                i++;
                            }
                        }
                        else
                        {
                            std::cout<<"No bus avaiable for such route"<<std::endl;
                            break;
                        }
                        std::cout<<"Select the bus"<<std::endl;
                        std::cin>>bus;
                        it = buslist.begin();
                        std::advance(it,bus);
                        std::cout<<"How many passengers do you want to enter"<<std::endl;
                        std::cin>>pass_no;
                        for(int k=0;k<pass_no;k++)
                        {
                            std::cout<<"Enter the name "<<std::endl;
                            std::cin>>m_name;
                            Journey.pass_name.push_back(m_name);
                        }
                        std::cout<<(*it)->BookTicket(Journey)<<std::endl;

                    }                      
                        break;
                    case 2:
                    {
                        std::string PNR;
                        std::cout<<"---------CANCEL TICKET---------"<<std::endl;
                        std::cout<<"Enter the PNR no"<<std::endl;
                        std::cin>>PNR;
                        std::cout<<B1->CancelTicket(PNR)<<std::endl;
                        std::cout<<std::endl;
                    }
                        break;
                    case 3:
                        std::cout<<"---------------QUIT--------------"<<std::endl;
                        break;
                    default:
                        std::cout<<"ENTER VALID CHOICE"<<std::endl;
                        break;
                    }
                    } while (choice!=3);
                    break;
        case 3:
            std::cout<<"Quit "<<std::endl;
            break;

                
        default:
            std::cout<<"enter the valid choice"<<std::endl;
             break;
    }
   }while(expression!=3);
   return 0;
    
}
