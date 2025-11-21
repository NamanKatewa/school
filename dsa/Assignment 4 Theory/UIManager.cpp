#include "UIManager.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

void UIManager::setupConsole() {
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    #endif
}

void UIManager::clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void UIManager::pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void UIManager::displayMenu() {
    std::cout << "\n\n";
    std::cout << "\x1B[1;35m=================================================\x1B[0m\n";
    std::cout << "\x1B[1;36m           Smart City Navigation System          \x1B[0m\n";
    std::cout << "\x1B[1;35m=================================================\x1B[0m\n";
    std::cout << "\x1B[33m1. \x1B[0mFind Shortest Path (Dijkstra)\n";
    std::cout << "\x1B[33m2. \x1B[0mView All-Pairs Shortest Paths (Floyd-Warshall)\n";
    std::cout << "\x1B[33m3. \x1B[0mPlan Minimum Cost Network (Prim's MST)\n";
    std::cout << "\x1B[33m4. \x1B[0mView Construction Task Order (Topological Sort)\n";
    std::cout << "\x1B[33m5. \x1B[0mSearch for a City Zone by ID (AVL Tree)\n";
    std::cout << "\x1B[31m6. \x1B[0mExit\n";
    std::cout << "\x1B[1;35m=================================================\x1B[0m\n";
}

int UIManager::getUserChoice() {
    int choice;
    std::cout << "\x1B[36mEnter your choice: \x1B[0m";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    return choice;
}

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void UIManager::handleDijkstra(CityGraph& graph) {
    std::string startInput, endInput;
    int startID = -1, endID = -1;

    std::cout << "\nAvailable locations:\n";
    auto names = graph.getNodeNames();
    for(int i = 0; i < names.size(); ++i) {
        std::cout << i + 1 << ". " << names[i] << "\n";
    }

    std::cout << "\nEnter starting location (name or number): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, startInput);

    if(is_number(startInput)) {
        int index = std::stoi(startInput) - 1;
        if(index >= 0 && index < names.size()) {
            startID = graph.getId(names[index]);
        }
    } else {
        startID = graph.getId(startInput);
    }

    std::cout << "Enter destination location (name or number): ";
    std::getline(std::cin, endInput);

    if(is_number(endInput)) {
        int index = std::stoi(endInput) - 1;
        if(index >= 0 && index < names.size()) {
            endID = graph.getId(names[index]);
        }
    } else {
        endID = graph.getId(endInput);
    }

    if (startID != -1 && endID != -1) {
        graph.dijkstra(startID, endID);
    } else {
        std::cout << "\n\x1B[31mError: \x1B[0mOne or both locations are invalid.\n";
    }
}

void UIManager::handleAVLSearch(AVLTree& tree) {
    int id;
    std::cout << "\nEnter Zone ID to search for: ";
    std::cin >> id;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n\x1B[31mInvalid input. Please enter a number.\n";
        return;
    }

    CityNode* result = tree.search(id);
    if (result != nullptr) {
        std::cout << "\n\x1B[32mZone Found!\x1B[0m\n";
        std::cout << "----------\n";
        std::cout << "ID:   \x1B[33m" << result->id << "\x1B[0m\n";
        std::cout << "Name: \x1B[33m" << result->name << "\x1B[0m\n";
        std::cout << "Type: \x1B[33m" << result->zoneType << "\x1B[0m\n";
    } else {
        std::cout << "\n\x1B[31mZone with ID " << id << " not found.\n";
    }
}
