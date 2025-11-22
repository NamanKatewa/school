#ifndef TICKETLIST_H
#define TICKETLIST_H

#include "Ticket.h"

struct TicketNode {
    Ticket data;
    TicketNode *next;

    TicketNode(const Ticket& t) : data(t), next(nullptr) {}
};

class TicketList {
private:
    TicketNode *head;

public:
    TicketList();
    ~TicketList();

    void insertTicket(const Ticket &t);
    bool deleteTicket(int ticketID);
    Ticket* retrieveTicket(int ticketID);
    void printAllTicketsAsTable() const;
};

#endif 