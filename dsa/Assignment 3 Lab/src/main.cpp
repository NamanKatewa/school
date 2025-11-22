#include <iostream>
#include <string>
#include "StudentPerformanceTracker.h"

int main() {
    
    
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }

    StudentPerformanceTracker tracker;

    
    std::cout << "Loading student data from data.csv..." << std::endl;
    tracker.loadStudentsFromCSV("data.csv");
    Sleep(2000); 

    
    tracker.displayMainMenu();

    return 0;
}
