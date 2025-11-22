#include "CampusPlanner.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu() {
    std::cout << "\n\033[1;36mCampus Navigation and Utility Planner\033[0m\n";
    std::cout << "\033[1;33m-------------------------------------\033[0m\n";
    std::cout << "1. List Campus Locations\n";
    std::cout << "2. Show Campus Adjacency Table\n";
    std::cout << "3. Find Optimal Path\n";
    std::cout << "4. Plan Utility Layout (MST)\n";
    std::cout << "5. Evaluate Energy Expression\n";
    std::cout << "6. Add Building Record\n";
    std::cout << "7. Exit\n";
    std::cout << "\033[1;33m-------------------------------------\033[0m\n";
    std::cout << "\033[1;32mEnter your choice: \033[0m";
}

int main() {
    CampusPlanner planner;
    planner.loadBuildings();
    planner.constructCampusGraph();
    int choice;

    do {
        clearConsole();
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: {
                clearConsole();
                std::cout << "\n\033[1;36mList Campus Locations\033[0m\n";
                std::cout << "1. In-order traversal\n";
                std::cout << "2. Pre-order traversal\n";
                std::cout << "3. Post-order traversal\n";
                std::cout << "Enter traversal type: ";
                int traversalType;
                std::cin >> traversalType;
                clearConsole();
                planner.listCampusLocations(traversalType);
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 2: {
                clearConsole();
                std::cout << "\n\033[1;36mCampus Adjacency Table\033[0m\n";
                planner.printAdjacencyTable();
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 3: {
                clearConsole();
                std::cout << "\n\033[1;36mFind Optimal Path (Dijkstra's Algorithm)\033[0m\n";
                int start, end;
                std::cout << "Enter starting building ID: ";
                std::cin >> start;
                std::cout << "Enter ending building ID: ";
                std::cin >> end;
                clearConsole();
                planner.findOptimalPath(start, end);
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 4: {
                clearConsole();
                std::cout << "\n\033[1;36mUtility Layout (Kruskal's MST)\033[0m\n";
                planner.planUtilityLayout();
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 5: {
                clearConsole();
                std::cout << "\n\033[1;36mEvaluate Energy Expression\033[0m\n";
                std::cout << "Enter a postfix expression (e.g., 5 3 + 8 *): ";
                std::string line;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, line);
                
                std::stringstream ss(line);
                std::vector<std::string> tokens;
                std::string token;
                while (ss >> token) {
                    tokens.push_back(token);
                }
                
                clearConsole();
                planner.evaluateEnergyExpression(tokens);
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                break;
            }
            case 6: {
                clearConsole();
                std::cout << "\n\033[1;36mAdd Building Record\033[0m\n";
                int id;
                std::string name, details;
                std::cout << "Enter Building ID: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Building Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Location Details: ";
                std::getline(std::cin, details);
                planner.addBuildingRecord(id, name, details);
                planner.constructCampusGraph(); 
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                break;
            }
            case 7:
                std::cout << "\033[1;32mExiting...\033[0m\n";
                break;
            default:
                std::cout << "\033[1;31mInvalid choice. Please try again.\033[0m\n";
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
        }
    } while (choice != 7);

    return 0;
}
