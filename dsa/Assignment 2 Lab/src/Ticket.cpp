#include "Ticket.h"
#include <iostream>
#include <iomanip>

Ticket::Ticket() : ticketID(0), customerName(""), issueDescription(""), priority(0) {}

Ticket::Ticket(int id, std::string name, std::string issue, int prio)
    : ticketID(id), customerName(std::move(name)), issueDescription(std::move(issue)), priority(prio) {}

int Ticket::getTicketID() const {
    return ticketID;
}

std::string Ticket::getCustomerName() const {
    return customerName;
}

std::string Ticket::getIssueDescription() const {
    return issueDescription;
}

int Ticket::getPriority() const {
    return priority;
}

void Ticket::setTicketID(int id) {
    ticketID = id;
}

void Ticket::setCustomerName(std::string name) {
    customerName = std::move(name);
}

void Ticket::setIssueDescription(std::string issue) {
    issueDescription = std::move(issue);
}

void Ticket::setPriority(int prio) {
    priority = prio;
}

void Ticket::printTicket() const {
    std::cout << "\033[1;32m"
              << std::left << std::setw(10) << ticketID
              << std::setw(20) << customerName
              << std::setw(40) << issueDescription
              << std::setw(10) << priority << "\033[0m" << std::endl;