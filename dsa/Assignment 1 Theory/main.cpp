#include "WeatherSystem.h"
#include <limits>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include "colors.h"

std::string repeatString(const std::string& s, int count) {
    std::string result;
    for (int i = 0; i < count; ++i) {
        result += s;
    }
    return result;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader(const std::string& title) {
    const int totalWidth = 54; // Adjusted width for the header box
    std::cout << Color::BOLD << Color::MAGENTA << Color::BOX_TOP_LEFT << repeatString(Color::BOX_HORIZONTAL, totalWidth - 2) << Color::BOX_TOP_RIGHT << std::endl;
    // Calculate padding for centering the title
    int padding = (totalWidth - 2 - title.length()) / 2;
    std::cout << Color::BOX_VERTICAL << repeatString(" ", padding) << title << repeatString(" ", totalWidth - 2 - title.length() - padding) << Color::BOX_VERTICAL << std::endl;
    std::cout << Color::BOX_BOTTOM_LEFT << repeatString(Color::BOX_HORIZONTAL, totalWidth - 2) << Color::BOX_BOTTOM_RIGHT << Color::RESET << std::endl;
}

const std::vector<std::string> CITIES = {
    "New Delhi", "Mumbai", "Chennai", "Kolkata", "Bengaluru", "Hyderabad",
    "Pune", "Ahmedabad", "Jaipur", "Surat", "Lucknow", "Kanpur", "Nagpur",
    "Indore", "Thane", "Bhopal", "Visakhapatnam", "Patna", "Vadodara",
    "Ghaziabad", "Ludhiana", "Agra", "Nashik", "Ranchi", "Faridabad",
    "Meerut", "Rajkot", "Kalyan-Dombivli", "Vasai-Virar", "Varanasi",
    "Srinagar", "Aurangabad", "Dhanbad", "Amritsar", "Navi Mumbai",
    "Prayagraj", "Howrah", "Gwalior", "Jabalpur", "Coimbatore",
    "Vijayawada", "Jodhpur", "Madurai", "Raipur", "Kota",
    "Guwahati", "Chandigarh", "Solapur", "Hubli-Dharwad", "Mysuru"
};

void displayMainMenu() {
    printHeader("Weather Data System");
    const int width = 50;
    std::cout << Color::CYAN << Color::BOX_TOP_LEFT << repeatString(Color::BOX_HORIZONTAL, width) << Color::BOX_TOP_RIGHT << std::endl;

    std::cout << Color::BOX_VERTICAL << " " << Color::YELLOW << std::left << std::setw(width - 2) << "1. Load Data from CSV" << Color::CYAN << " " << Color::BOX_VERTICAL << std::endl;
    std::cout << Color::BOX_VERTICAL << " " << Color::YELLOW << std::left << std::setw(width - 2) << "2. Insert New Data" << Color::CYAN << " " << Color::BOX_VERTICAL << std::endl;
    std::cout << Color::BOX_VERTICAL << " " << Color::YELLOW << std::left << std::setw(width - 2) << "3. Delete Data" << Color::CYAN << " " << Color::BOX_VERTICAL << std::endl;
    std::cout << Color::BOX_VERTICAL << " " << Color::YELLOW << std::left << std::setw(width - 2) << "4. Retrieve Data" << Color::CYAN << " " << Color::BOX_VERTICAL << std::endl;
    std::cout << Color::BOX_VERTICAL << " " << Color::YELLOW << std::left << std::setw(width - 2) << "5. Print Row-Major Traversal" << Color::CYAN << " " << Color::BOX_VERTICAL << std::endl;
    std::cout << Color::BOX_VERTICAL << " " << Color::YELLOW << std::left << std::setw(width - 2) << "6. Print Column-Major Traversal" << Color::CYAN << " " << Color::BOX_VERTICAL << std::endl;
    std::cout << Color::BOX_VERTICAL << " " << Color::YELLOW << std::left << std::setw(width - 2) << "7. Generate Sparsity Report" << Color::CYAN << " " << Color::BOX_VERTICAL << std::endl;
    std::cout << Color::BOX_VERTICAL << " " << Color::RED << std::left << std::setw(width - 2) << "8. Exit" << Color::CYAN << " " << Color::BOX_VERTICAL << std::endl;

    std::cout << Color::BOX_BOTTOM_LEFT << repeatString(Color::BOX_HORIZONTAL, width) << Color::BOX_BOTTOM_RIGHT << Color::RESET << std::endl;
    std::cout << Color::BOLD << Color::GREEN << "Enter your choice: " << Color::RESET;
}

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pressEnterToContinue() {
    std::cout << "\n" << Color::BOLD << Color::GREEN << "Press Enter to continue..." << Color::RESET;
    std::cin.get();
}

int main() {
#ifdef _WIN32
    // Enable ANSI escape codes on Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    SetConsoleOutputCP(CP_UTF8);
#endif

    WeatherSystem sys(WS_START_YEAR, WS_END_YEAR, CITIES);
    int choice;
    std::string city;
    int year;
    double temperature;

    do {
        clearScreen();
        displayMainMenu();
        while (!(std::cin >> choice)) {
            std::cout << Color::BOLD << Color::RED << "Invalid input. Please enter a number: " << Color::RESET;
            std::cin.clear();
            clearInputBuffer();
        }
        clearInputBuffer();

        clearScreen();
        switch (choice) {
            case 1:
                printHeader("Load Data from CSV");
                sys.loadFromCSV("data.csv");
                pressEnterToContinue();
                break;
            case 2:
                printHeader("Insert New Data");
                std::cout << "Enter Year (e.g., 2000): ";
                while (!(std::cin >> year)) {
                    std::cout << Color::BOLD << Color::RED << "Invalid input. Please enter a number: " << Color::RESET;
                    std::cin.clear();
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Enter City (e.g., Mumbai): ";
                std::getline(std::cin, city);

                std::cout << "Enter Temperature (e.g., 25.5): ";
                while (!(std::cin >> temperature)) {
                    std::cout << Color::BOLD << Color::RED << "Invalid input. Please enter a number: " << Color::RESET;
                    std::cin.clear();
                    clearInputBuffer();
                }
                clearInputBuffer();
                sys.insertData(year, city, temperature);
                pressEnterToContinue();
                break;
            case 3:
                printHeader("Delete Data");
                std::cout << "Enter Year to delete data from: ";
                while (!(std::cin >> year)) {
                    std::cout << Color::BOLD << Color::RED << "Invalid input. Please enter a number: " << Color::RESET;
                    std::cin.clear();
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Enter City to delete data from: ";
                std::getline(std::cin, city);
                sys.deleteData(year, city);
                pressEnterToContinue();
                break;
            case 4:
                printHeader("Retrieve Data");
                std::cout << "Enter Year to retrieve data from: ";
                while (!(std::cin >> year)) {
                    std::cout << Color::BOLD << Color::RED << "Invalid input. Please enter a number: " << Color::RESET;
                    std::cin.clear();
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Enter City to retrieve data from: ";
                std::getline(std::cin, city);
                temperature = sys.retrieveData(year, city);
                if (temperature != WS_SENTINEL_VALUE) {
                    std::cout << Color::BOLD << Color::GREEN << "Temperature for " << city << " in " << year << ": "
                              << std::fixed << std::setprecision(2) << temperature << " C" << Color::RESET << std::endl;
                } else {
                    std::cout << Color::BOLD << Color::RED << "No data available for " << city << " in " << year
                              << " (or invalid input)." << Color::RESET << std::endl;
                }
                pressEnterToContinue();
                break;
            case 5:
                printHeader("Row-Major Traversal");
                sys.printRowMajor();
                pressEnterToContinue();
                break;
            case 6:
                printHeader("Column-Major Traversal");
                sys.printColumnMajor();
                pressEnterToContinue();
                break;
            case 7:
                printHeader("Sparsity Report");
                sys.generateSparsityReport();
                pressEnterToContinue();
                break;
            case 8:
                std::cout << Color::BOLD << Color::YELLOW << "Exiting program. Goodbye!" << Color::RESET << std::endl;
                break;
            default:
                std::cout << Color::BOLD << Color::RED << "Invalid choice. Please try again." << Color::RESET << std::endl;
                pressEnterToContinue();
        }
    } while (choice != 8);

    return 0;
}
