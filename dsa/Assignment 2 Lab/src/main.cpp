#include "TicketSystem.h"
#include <iostream>

int main() {
    TicketSystem ts;
    ts.loadTicketsFromFile("data.csv"); // Load data from data.csv in the root directory
    ts.displayMenu();
    return 0;
}