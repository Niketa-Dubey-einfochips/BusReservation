#include<iostream>
#include<memory>
#include<functional>
#include<map>
#include<list>
#include<set>
#include<bits/stdc++.h>
#include"StationCode.h"
#include"Ticket_manager_IF.h"
#include"Ticket_manager.h"
#include"Ticket.h"
#include"Ticket_IF.h"
#include"BusIF.h"
#include"BusManager.h"
#include"BusManagerIF.h"
#include"Bus.h"
#include "eventHandler.h"

TicketManager::TicketManager(int TotalSeats)
{
    Total_seats=TotalSeats;
    for(int i=1;i<=Total_seats;i++)
    {
        seatControl.push_back(i);
    }
}

Ticket_manager_IF::Ptr TicketManager::CreateManager(int TotalSeats)
{
    Ticket_manager_IF::Ptr pManager(new TicketManager(TotalSeats));
    return pManager;   
}

bool TicketManager::compare(TicketIF::Ptr P1,TicketIF::Ptr P2)
{
    if(P1->getSeatNo()<P2->getSeatNo())
    {
        return true;
    }
}

std::string TicketManager::BookTicket(Ticket_manager_IF::JourneyDetails JourneyDetails)
{
    std::string Print = " ";
    for(auto it = JourneyDetails.pass_name.begin();it!=JourneyDetails.pass_name.end();it++)
    {
        LastBookCount++;    
        TicketIF::Details Details("Ticket",0,TicketIF::statusCode::WL,*it);
        if(!seatControl.empty())
        {   
            Details.m_seatNo= seatControl.front();
            seatControl.pop_front();
            Details.m_status= TicketIF::CNF;    
        }
        else
        {
            Details.m_seatNo=LastBookCount-Total_seats;
        }    
        TicketIF::Ptr T1 = Ticket::CreateTicket(Details);
        m_passanger[Details.m_PNR]=T1;
        Print= Print +"\n" + T1->printDetails() + "\n"; 
        auto itr = m_passanger.begin();
        m_fn( Details); 
    }
    return Print;

}
std::list<TicketIF::Ptr> TicketManager::getFilterList(TicketIF::statusCode s, char Dir, int count)
{
    std::list<TicketIF::Ptr> filterList;
    for(auto it = m_passanger.begin();it!=m_passanger.end();it++)
    {
        if(s==TicketIF::CNF)
        {
            if(it->second->isConfromed()==true)
            {
                filterList.push_back(it->second);
            }
        }
        else if(s==TicketIF::WL)
        {
            if(it->second->isWaiting()==true)
            {
                std::cout<<it->first<<std::endl;
                filterList.push_back(it->second);
                
            }
            
        }
        else
        {
            if(it->second->isCancel()==true)
            {
                filterList.push_back(it->second);
            }
        }
    }
    if(!filterList.empty())
    {
        auto comp = std::bind(&TicketManager::compare,this,std::placeholders::_1,std::placeholders::_2);
        filterList.sort(comp);      
        if(Dir == 'D')
        {
            filterList.reverse();
            
        }
        
        if(count!=-1&&count<filterList.size())
        {
            filterList.resize(count);
        }
    }
    return filterList;
}

std::string TicketManager::CancelTicket(std::string PNR)
{
    std::list<TicketIF::Ptr> waitingList;
    auto it = m_passanger.find(PNR);
    if(it!=m_passanger.end())
    {
        if(it->second->isWaiting()==true)
        {
            it->second->CancelTicket();
            LastBookCount--;
            std::string printPNR = it->second->getPNR();
           std::cout<<"\nticket cancled for..\n:"+ printPNR;
            m_fn(it->second->getDetails());
            //m_fn(it->second->PrintTicketDetails());
            return "Done";
        }
        else if(it->second->isCancel()!=true)
        {

            seatControl.push_back(it->second->getSeatNo());
            it->second->CancelTicket();
            LastBookCount--;
            waitingList=getFilterList(TicketIF::WL,'A');
            std::string printPNR = it->second->getPNR();
            m_fn(it->second->getDetails());
            if(!waitingList.empty())
            {
                TicketIF::Ptr T1=waitingList.front();
                waitingList.pop_front();
                TicketIF::Details Details(T1->getPNR(),seatControl.front(),TicketIF::CNF,"book");
                T1->updateDetalis(Details);
                seatControl.pop_front();
                if(!waitingList.empty())
                {
                    for(auto it=waitingList.begin();it!=waitingList.end();it++)
                    {
        
                        TicketIF::Details newDetails((*it)->getPNR(),(*it)->getSeatNo()-1,(TicketIF::statusCode)1,"wait");
                        (*it)->updateDetalis(newDetails);
                    }
                }
            }
    
        }
        
    }
   return "Cancelation Done";   
}

bool TicketManager::SearchPNR(std::string PNR)
{
    auto it = m_passanger.find(PNR);
    return (it!=m_passanger.end());
}

void TicketManager::RegisterForTicketEvent(std::function<void(TicketIF::Details& )> fn)
{
    m_fn = fn;
}

#if 0
std::string TicketManager::BookTicket()
{
    ticket=Ticket::CreateTicket();
    std::string PNR;
    int book;
    std::cout<<"-------Intrested booking type--------"<<std::endl;
    std::cout<<"--------1. Normal booking ---------"<<std::endl;
    std::cout<<"--------2. Partial Booking -----------"<<std::endl;
    std::cout<<"Enter the choice"<<std::endl;
    std::cin>>book;
    switch(book)
    {
        case 1:
            std::cout<<"----------Normal booking--------"<<std::endl;
            
            PNR = ticket->setDetails();
            ticket->getDetails();
            passanger[PNR]=ticket;
            if(bookingNo<=Totalseats)
            {
                CNF_list.push_back(ticket);
            
            }
            else
            {
                Waiting_list.push_back(ticket);
                
            }
            bookingNo++;
            break;
        
        case 2:
            std::cout<<"-------partial booking-------"<<std::endl;
            //std::cout<<"Check avaiblity for partial booking"<<std::endl;
            // if(partialFlag==0)
            // {
                
                //std::cout<<"Yes "<<std::endl;
                std::cout<<"Enter the source"<<std::endl;
                std::cin>>src;
                std::cout<<"ENter the destination"<<std::endl;
                std::cin>>des;
                std::cout<<"booking ticket "<<src<<" to "<<des<<std::endl;

                PNR = ticket->setDetails_1(src);
                ticket->getDetails();
                passanger[PNR]=ticket;
                partial[PNR]=ticket;
                partialflag++;
                if(des==.back())
                {
                    bookingNo++;
                    if(bookingNo<=Totalseats)
                    {
                        CNF_list.push_back(ticket);
                    
                    }
                    else
                    {
                        Waiting_list.push_back(ticket);
                        
                    }
                }
                else
                {
                    if(bookingNo<=Totalseats)
                    {
                        CNF_list.push_back(ticket);
                    
                    }
                    else
                    {
                        Waiting_list.push_back(ticket);
                        
                    }
                }
                
                    
             break;
            
           
        default:
            break;
    }
    return PNR;
  
}
void TicketManager::CancelTicket()
{
    std::string PNR;
    std::cout<<"Enter the PNR no. "<<std::endl;
    std::cin>>PNR;
    std::map<std::string,TicketIF::Ptr>:: iterator it;
    for(auto it= passanger.begin(); it != passanger.end(); it++)
    {
        
        if(it->first==PNR)
        {
            auto tick=it->second;
            it=passanger.erase(it);
            std::map<std::string,TicketIF::Ptr>:: iterator itr;
            for(auto itr= partial.begin(); itr != partial.end(); itr++)
            {
        
                if(itr->first==PNR)
                {
                    itr=partial.erase(itr);
                    auto src.begin();
                    --idx;
                    std::advance(src,idx);
                    std::cout<<*src<<std::endl;
                    if(src==.begin())
                    {
                        bookingNo--;
                    }
                    std::list<TicketIF::Ptr>:: iterator itr2 = CNF_list.begin();
                    while (itr2 != CNF_list.end())
                    {
                        if (*itr2==tick) 
                        {
                            itr2 = CNF_list.erase(itr2);
                            std::cout<<"cancel"<<std::endl;
                            
                        }
                        else 
                        {
                            std::list<TicketIF::Ptr>:: iterator itr1 = Waiting_list.begin();
                            while (itr1 != Waiting_list.end())
                            {
                                if(*itr1==tick)
                                {
                                    itr1=Waiting_list.erase(itr1);
                                }
                                else
                                {
                                    itr1++;
                                }
                            }
                            itr2++;
                        }
                    }
                }
                else
                {
                    std::cout<<"in else part"<<std::endl;
                    std::list<TicketIF::Ptr>:: iterator itr2 = CNF_list.begin();
                    bookingNo--;
                    while (itr2 != CNF_list.end())
                    {
                        if (*itr2==tick) 
                        {
                            std::cout<<"cancel"<<std::endl;
                            itr2 = CNF_list.erase(itr2);
                        }
                        else 
                        {
                            std::list<TicketIF::Ptr>:: iterator itr1 = Waiting_list.begin();
                            while (itr1 != Waiting_list.end())
                            {
                                if(*itr1==tick)
                                {
                                    itr1=Waiting_list.erase(itr1);
                                }
                                else
                                {
                                    itr1++;
                                }
                            }
                            ++itr2;
                        }
                    }

                }
            }
        }
    }
    
    
            
    

        
}
void TicketManager::PreparedChart()
{
    do
    {
            
        if(bookingNo<=Totalseats)
        {
            auto wait = Waiting_list.front();
            CNF_list.push_back(wait);
            Waiting_list.erase(Waiting_list.begin());
            bookingNo++;
        }
        else
        {
            std::cout<<"No seats are avaiable"<<std::endl;
        }
    }while(bookingNo==Totalseats);
    std::cout<<"1 Booking list and partial list"<<std::endl;
    std::cout<<"2 Confrom list and waiting list"<<std::endl;
    int list;
    std::cout<<"Enter the list you want to see"<<std::endl;
    std::cin>>list;
    switch(list)
    {
        case 1:
            //std::map<std::string,TicketIF::Ptr>:: iterator it;
            int i;
            std::cout<<"--------- booking list --------"<<std::endl;
            std::cout<<"  PNR         "<<std::endl;
            i=0;
            for(auto it= passanger.begin(); it != passanger.end(); it++)
            {
                i++;
                std::cout <<i<<" "<<it->first << "       " << it->second<<"\n";
                std::cout<<"--------------------------------"<<std::endl;
            }


            std::cout<<"----------partial booking list--------"<<std::endl; 
            std::cout<<"  PNR         "<<std::endl;
            i=0;
            for(auto it= partial.begin(); it != partial.end(); it++)
            {
                i++;
                std::cout <<i<<" "<<it->first << "       " << it->second<<"\n";
                std::cout<<"--------------------------------"<<std::endl;
            }
            break;
        case 2:
            std::cout<<"---------------------"<<std::endl; 
            std::cout<<"Confromed list"<<std::endl;
            for (auto v : CNF_list)
                std::cout << v << "\n";
            // for(auto v : P_CNF_list)
            //     std::cout << v<<"\n";

        
            std::cout<<"----------------------------"<<std::endl;
            std::cout<<"Waiting list"<<std::endl;
            for (auto v : Waiting_list)
                std::cout << v << "\n";
            // for(auto v : P_Waiting_list)
            //     std::cout<<v<<"\n"; 
        break;

    }

   


            
           

          


    
            
}
#endif
