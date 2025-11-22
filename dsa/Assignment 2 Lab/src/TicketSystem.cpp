#include "TicketSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <windows.h>
TicketSystem::TicketSystem() {}

void TicketSystem::addTicketRecord() {
    system("cls");
    std::cout << "\033[1;32m" << "--- Add New Ticket ---" << "\033[0m" << std::endl;

    int id, priority;
    std::string name, issue;

    std::cout << "Enter Ticket ID: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Issue Description: ";
    std::getline(std::cin, issue);

    std::cout << "Enter Priority (e.g., 1 for urgent, 2 for normal): ";
    std::cin >> priority;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Ticket newTicket(id, name, issue, priority);
    ticketList.insertTicket(newTicket);
    undoStack.push(newTicket);
    priorityQueue.enqueue(newTicket);
    roundRobinQueue.enqueue(newTicket);

    std::cout << "\n\033[1;32m" << "Ticket added successfully!" << "\033[0m" << std::endl;
    system("pause");
}

void TicketSystem::undoTicketOperation() {
    system("cls");
    std::cout << "\033[1;32m" << "--- Undo Last Ticket Operation ---" << "\033[0m" << std::endl;

    Ticket undoneTicket;
    if (undoStack.pop(undoneTicket)) {
        if (ticketList.deleteTicket(undoneTicket.getTicketID())) {
            std::cout << "\033[1;32m" << "Ticket ID " << undoneTicket.getTicketID() << " undone and removed from the system." << "\033[0m" << std::endl;
        } else {
            std::cout << "\033[1;31m" << "Could not find ticket " << undoneTicket.getTicketID() << " in the list to undo." << "\033[0m" << std::endl;
        }
    } else {
        std::cout << "\033[1;31m" << "Undo stack is empty. Nothing to undo." << "\033[0m" << std::endl;
    }
    system("pause");
}

void TicketSystem::processPriorityTickets() {
    system("cls");
    std::cout << "\033[1;32m" << "--- Processing Priority Tickets ---" << "\033[0m" << std::endl;

    Ticket processedTicket;
    if (priorityQueue.dequeue(processedTicket)) {
        std::cout << "\033[1;33m" << "Processing urgent ticket: " << processedTicket.getTicketID() << " - " << processedTicket.getIssueDescription() << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[1;31m" << "No priority tickets to process." << "\033[0m" << std::endl;
    }
    system("pause");
}

void TicketSystem::processRoundRobinTickets() {
    system("cls");
    std::cout << "\033[1;32m" << "--- Processing Round-Robin Tickets ---" << "\033[0m" << std::endl;

    Ticket processedTicket;
    if (roundRobinQueue.dequeue(processedTicket)) {
        std::cout << "\033[1;33m" << "Processing round-robin ticket: " << processedTicket.getTicketID() << " - " << processedTicket.getCustomerName() << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[1;31m" << "No round-robin tickets to process." << "\033[0m" << std::endl;
    }
    system("pause");
}

void TicketSystem::compareBillingHistory() {
    system("cls");
    std::cout << "\033[1;32m" << "--- Comparing Billing Histories ---" << "\033[0m" << std::endl;

    Polynomial emptyPoly;
    if (billingHistory1.compare(emptyPoly) == 0 && billingHistory2.compare(emptyPoly) == 0) {
        billingHistory1.insertTerm(5, 2);
        billingHistory1.insertTerm(3, 1);
        billingHistory1.insertTerm(10, 0);

        billingHistory2.insertTerm(4, 2);
        billingHistory2.insertTerm(3, 1);
        billingHistory2.insertTerm(12, 0);
    }
    

    std::cout << "\n\033[1;36m" << "Billing History 1:" << "\033[0m" << std::endl;
    billingHistory1.print();

    std::cout << "\n\033[1;36m" << "Billing History 2:" << "\033[0m" << std::endl;
    billingHistory2.print();

    int comparisonResult = billingHistory1.compare(billingHistory2);
    std::cout << "\n\033[1;33m";
    if (comparisonResult == 0) {
        std::cout << "Billing History 1 is equal to Billing History 2." << std::endl;
    } else if (comparisonResult > 0) {
        std::cout << "Billing History 1 is greater than Billing History 2." << std::endl;
    } else {
        std::cout << "Billing History 1 is smaller than Billing History 2." << std::endl;
    }
    std::cout << "\033[0m";
    system("pause");
}

void TicketSystem::loadTicketsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "\033[1;31m" << "Error: Could not open file: " << filename << "\033[0m" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> seglist;

        while(std::getline(ss, segment, ',')) {
            seglist.push_back(segment);
        }

        if (seglist.size() == 4) {
            int id = std::stoi(seglist[0]);
            std::string name = seglist[1];
            std::string issue = seglist[2];
            int priority = std::stoi(seglist[3]);
            Ticket newTicket(id, name, issue, priority);
            ticketList.insertTicket(newTicket);
            undoStack.push(newTicket);
            priorityQueue.enqueue(newTicket);
            roundRobinQueue.enqueue(newTicket);
        }
    }
    file.close();
}


void TicketSystem::displayMenu() {
    int choice;

    do {
        system("cls");
        std::cout << "\033[1;36m" << "--- Customer Support Ticket System ---" << "\033[0m" << std::endl;

        std::cout << "\033[1;32m" << "1. Add New Ticket" << std::endl;
        std::cout << "2. Undo Last Ticket Operation" << std::endl;
        std::cout << "3. Process Priority Tickets" << std::endl;
        std::cout << "4. Process Round-Robin Tickets" << std::endl;
        std::cout << "5. Compare Billing Histories" << std::endl;
        std::cout << "6. View All Tickets" << std::endl;
        std::cout << "7. Exit" << "\033[0m" << std::endl;

        std::cout << "\033[1;33m" << "Enter your choice: " << "\033[0m";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31m" << "Invalid input. Please enter a number." << "\033[0m" << std::endl;
            system("pause");
            continue;
        }

        switch (choice) {
            case 1:
                addTicketRecord();
                break;
            case 2:
                undoTicketOperation();
                break;
            case 3:
                processPriorityTickets();
                break;
            case 4:
                processRoundRobinTickets();
                break;
            case 5:
                compareBillingHistory();
                break;
            case 6:
                system("cls");
                ticketList.printAllTicketsAsTable();
                system("pause");
                break;
            case 7:
                std::cout << "\033[1;32m" << "Exiting Ticket System. Goodbye!" << "\033[0m" << std::endl;
                break;
            default:
                std::cout << "\033[1;31m" << "Invalid choice. Please try again." << "\033[0m" << std::endl;
                system("pause");
                break;
        }
    } while (choice != 7);
}
