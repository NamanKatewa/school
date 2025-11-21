#include "StudentSystem.h"
#include "ConsoleColors.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>

void printStudents(const std::vector<Student>& students, const std::string& title = "Student Records") {
    ConsoleColors::setColor(ConsoleColors::CYAN);
    std::cout << "\n--- " << title << " (" << students.size() << " records) ---" << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);

    if (students.empty()) {
        std::cout << "No records to display." << std::endl;
        return;
    }

    ConsoleColors::setColor(ConsoleColors::YELLOW);
    std::cout << std::left << std::setw(12) << "Roll Number"
              << std::setw(25) << "Name"
              << std::setw(10) << "Marks"
              << std::setw(15) << "Course" << std::endl;
    std::cout << std::string(62, '-') << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);

    for (const auto& s : students) {
        std::cout << std::left << std::setw(12) << s.rollNumber
                  << std::setw(25) << s.name
                  << std::setw(10) << std::fixed << std::setprecision(2) << s.marks
                  << std::setw(15) << s.course << std::endl;
    }
    std::cout << std::string(62, '-') << std::endl;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void pauseScreen() {
    ConsoleColors::setColor(ConsoleColors::YELLOW);
    std::cout << "\nPress Enter to continue..." << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void handleHashSearch(StudentSystem& system) {
    int rollNum;
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "Enter Roll Number to search: ";
    ConsoleColors::setColor(ConsoleColors::RESET);
    std::cin >> rollNum;
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    long long duration;
    Student* foundStudent = system.searchStudentByHash(rollNum, duration);

    if (foundStudent) {
        ConsoleColors::setColor(ConsoleColors::GREEN);
        std::cout << "Student found (Hash Search) in " << duration << " ns:\n";
        ConsoleColors::setColor(ConsoleColors::RESET);
        std::vector<Student> result = {*foundStudent};
        printStudents(result, "Found Student");
    } else {
        ConsoleColors::setColor(ConsoleColors::RED);
        std::cout << "Student with Roll Number " << rollNum << " not found (Hash Search).\n";
        ConsoleColors::setColor(ConsoleColors::RESET);
    }
}

void handleBinarySearch(StudentSystem& system) {
    int rollNum;
    ConsoleColors::setColor(ConsoleColors::MAGENTA);
    std::cout << "Enter Roll Number to search: ";
    ConsoleColors::setColor(ConsoleColors::RESET);
    std::cin >> rollNum;
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    
    ConsoleColors::setColor(ConsoleColors::YELLOW);
    std::cout << "Sorting students by Roll Number for Binary Search..." << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);
    long long duration;
    Student foundStudent = system.searchStudentByBinary(rollNum, duration);

    if (foundStudent.rollNumber != 0) {
        ConsoleColors::setColor(ConsoleColors::GREEN);
        std::cout << "Student found (Binary Search) in " << duration << " ns:\n";
        ConsoleColors::setColor(ConsoleColors::RESET);
        std::vector<Student> result = {foundStudent};
        printStudents(result, "Found Student");
    } else {
        ConsoleColors::setColor(ConsoleColors::RED);
        std::cout << "Student with Roll Number " << rollNum << " not found (Binary Search).\n";
        ConsoleColors::setColor(ConsoleColors::RESET);
    }
}

void handleSortByMarks(StudentSystem& system, const std::string& sortType) {
    ConsoleColors::setColor(ConsoleColors::YELLOW);
    std::cout << "Sorting students by Marks using " << sortType << " Sort..." << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);
    long long duration;
    std::vector<Student> sortedStudents = system.sortStudentsByMarks(sortType, duration);
    ConsoleColors::setColor(ConsoleColors::GREEN);
    std::cout << sortType << " Sort completed in " << duration << " microseconds." << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);
    printStudents(sortedStudents, "Students Sorted by Marks (" + sortType + " Sort)");
}

void handleSortByRoll(StudentSystem& system) {
    ConsoleColors::setColor(ConsoleColors::YELLOW);
    std::cout << "Sorting students by Roll Number using Radix Sort..." << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);
    long long duration;
    std::vector<Student> sortedStudents = system.sortStudentsByRoll(duration);
    ConsoleColors::setColor(ConsoleColors::GREEN);
    std::cout << "Radix Sort completed in " << duration << " microseconds." << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);
    printStudents(sortedStudents, "Students Sorted by Roll Number (Radix Sort)");
}

void handlePerformanceAnalysis(StudentSystem& system) {
    ConsoleColors::setColor(ConsoleColors::CYAN);
    std::cout << "\n--- Performance Analysis ---" << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);

    std::cout << "Dataset Size: " << system.getAllStudents().size() << " records." << std::endl;

    long long qs_duration, hs_duration, rs_duration;
    system.getPerformanceMetrics(qs_duration, hs_duration, rs_duration);

    ConsoleColors::setColor(ConsoleColors::GREEN);
    std::cout << "Quick Sort Time: " << qs_duration << " microseconds" << std::endl;
    std::cout << "Heap Sort Time:  " << hs_duration << " microseconds" << std::endl;
    std::cout << "Radix Sort Time: " << rs_duration << " microseconds" << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);
}

void displayMenu() {
    ConsoleColors::setColor(ConsoleColors::BLUE);
    std::cout << "\n--- Student Management System Menu ---" << std::endl;
    ConsoleColors::setColor(ConsoleColors::RESET);
    std::cout << "1. Search Student by Roll Number (Hash Table)" << std::endl;
    std::cout << "2. Search Student by Roll Number (Binary Search)" << std::endl;
    std::cout << "3. Sort Students by Marks (Quick Sort) & Display" << std::endl;
    std::cout << "4. Sort Students by Marks (Heap Sort) & Display" << std::endl;
    std::cout << "5. Sort Students by Roll Number (Radix Sort) & Display" << std::endl;
    std::cout << "6. Display All Students (Current Order)" << std::endl;
    std::cout << "7. Performance Analysis of Sorting Algorithms" << std::endl;
    std::cout << "8. Reload Data (from data.csv)" << std::endl;
    std::cout << "0. Exit" << std::endl;
    ConsoleColors::setColor(ConsoleColors::BLUE);
    std::cout << "Enter your choice: ";
    ConsoleColors::setColor(ConsoleColors::RESET);
}

int main() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    StudentSystem system("data.csv");

    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        switch (choice) {
            case 1: handleHashSearch(system); pauseScreen(); clearScreen(); break;
            case 2: handleBinarySearch(system); pauseScreen(); clearScreen(); break;
            case 3: handleSortByMarks(system, "quick"); pauseScreen(); clearScreen(); break;
            case 4: handleSortByMarks(system, "heap"); pauseScreen(); clearScreen(); break;
            case 5: handleSortByRoll(system); pauseScreen(); clearScreen(); break;
            case 6: printStudents(system.getAllStudents(), "All Students (Original Order)"); pauseScreen(); clearScreen(); break;
            case 7: handlePerformanceAnalysis(system); pauseScreen(); clearScreen(); break;
            case 8: system.loadData(); pauseScreen(); clearScreen(); break;
            case 0:
                ConsoleColors::setColor(ConsoleColors::YELLOW);
                std::cout << "Exiting program. Goodbye!" << std::endl;
                ConsoleColors::setColor(ConsoleColors::RESET);
                break;
            default:
                ConsoleColors::setColor(ConsoleColors::RED);
                std::cout << "Invalid choice. Please try again." << std::endl;
                ConsoleColors::setColor(ConsoleColors::RESET);
                break;
        }
    } while (choice != 0);

    return 0;
}
