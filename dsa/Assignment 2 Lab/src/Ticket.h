#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <iostream>

class Ticket {
private:
    int ticketID;
    std::string customerName;
    std::string issueDescription;
    int priority;

public:
    Ticket();
    Ticket(int id, std::string name, std::string issue, int prio);

    
    int getTicketID() const;
    std::string getCustomerName() const;
    std::string getIssueDescription() const;
    int getPriority() const;

    
    void setTicketID(int id);
    void setCustomerName(std::string name);
    void setIssueDescription(std::string issue);
    void setPriority(int prio);

    void printTicket() const;
};

#endif 