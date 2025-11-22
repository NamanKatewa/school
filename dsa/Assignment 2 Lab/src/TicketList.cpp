#include "TicketList.h"
#include <iostream>
#include <iomanip>

TicketList::TicketList() : head(nullptr) {}

TicketList::~TicketList() {
    TicketNode *current = head;
    while (current != nullptr) {
        TicketNode *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void TicketList::insertTicket(const Ticket &t) {
    TicketNode *newNode = new TicketNode(t);
    if (head == nullptr) {
        head = newNode;
    } else {
        TicketNode *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool TicketList::deleteTicket(int ticketID) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.getTicketID() == ticketID) {
        TicketNode *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    TicketNode *current = head;
    while (current->next != nullptr && current->next->data.getTicketID() != ticketID) {
        current = current->next;
    }

    if (current->next != nullptr) {
        TicketNode *temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }
    return false;
}

Ticket* TicketList::retrieveTicket(int ticketID) {
    TicketNode *current = head;
    while (current != nullptr) {
        if (current->data.getTicketID() == ticketID) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

void TicketList::printAllTicketsAsTable() const {
    if (head == nullptr) {
        std::cout << "No tickets to display." << std::endl;
        return;
    }

    std::cout << "\033[1;36m" // Bold Cyan header
              << std::left << std::setw(10) << "ID"
              << std::setw(20) << "Customer Name"
              << std::setw(40) << "Issue Description"
              << std::setw(10) << "Priority" << std::endl;
    std::cout << std::string(80, '-') << "\033[0m" << std::endl; // Reset color after separator

    TicketNode *current = head;
    while (current != nullptr) {
        current->data.printTicket();
        current = current->next;
    }
}