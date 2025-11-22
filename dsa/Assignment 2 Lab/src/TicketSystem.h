#ifndef TICKETSYSTEM_H
#define TICKETSYSTEM_H

#include "TicketList.h"
#include "UndoStack.h"
#include "PriorityQueue.h"
#include "CircularQueue.h"
#include "Polynomial.h"
#include <vector>

class TicketSystem {
private:
    TicketList ticketList;
    UndoStack undoStack;
    PriorityQueue priorityQueue;
    CircularQueue roundRobinQueue;
    Polynomial billingHistory1;
    Polynomial billingHistory2;

public:
    TicketSystem();

    void addTicketRecord();
    void undoTicketOperation();
    void processPriorityTickets();
    void processRoundRobinTickets();
    void compareBillingHistory();
    void displayMenu();
    void loadTicketsFromFile(const std::string& filename);
};

#endif 