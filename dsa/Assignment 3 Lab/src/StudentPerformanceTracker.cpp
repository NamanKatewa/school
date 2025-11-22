#include "StudentPerformanceTracker.h"
#include <fstream>
#include <sstream>
#include <limits> 
#include <algorithm> 

StudentPerformanceTracker::StudentPerformanceTracker() : hashTable(100) { 
    
}



void StudentPerformanceTracker::addStudentRecord(const Student& s) {
    
    hashTable.insertStudent(s);

    
    studentArray.push_back(s);

    
    
    
}

void StudentPerformanceTracker::loadStudentsFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << RED << "Error: Could not open CSV file: " << filename << RESET << std::endl;
        return;
    }

    std::string line;
    
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> seglist;

        while(std::getline(ss, segment, ',')) {
            seglist.push_back(segment);
        }

        if (seglist.size() == 4) {
            try {
                int id = std::stoi(seglist[0]);
                std::string name = seglist[1];
                double grade = std::stod(seglist[2]);
                std::string course = seglist[3];

                Student s(id, name, grade, course);
                addStudentRecord(s); 
            } catch (const std::exception& e) {
                std::cerr << RED << "Error parsing line: " << line << " - " << e.what() << RESET << std::endl;
            }
        } else {
            std::cerr << RED << "Warning: Skipping malformed line in CSV: " << line << RESET << std::endl;
        }
    }
    file.close();
    std::cout << GREEN << "Students loaded from " << filename << RESET << std::endl;
}

void StudentPerformanceTracker::searchByStudent() {
    clearConsole();
    std::cout << BOLD << MAGENTA << "--- Search Student ---" << RESET << std::endl;
    std::cout << "Search by (1) ID or (2) Name? ";
    int choice;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << RED << "Invalid input. Please enter 1 or 2." << RESET << std::endl;
        Sleep(2000);
        return;
    }

    Student* foundStudent = nullptr;
    int index = -1;

    if (choice == 1) {
        std::cout << "Enter Student ID: ";
        int id;
        std::cin >> id;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << RED << "Invalid input. Please enter a number." << RESET << std::endl;
            Sleep(2000);
            return;
        }

        
        foundStudent = hashTable.searchStudentByID(id);
        if (foundStudent) {
            std::cout << GREEN << "Student found using Hash Table (ID: " << id << "):" << RESET << std::endl;
            printHeader();
            foundStudent->printRow();
        } else {
            
            
            
            std::cout << BLUE << "Student not found in hash table. Trying sequential search..." << RESET << std::endl;
            index = Search::sequentialSearchByID(studentArray, id);
            if (index != -1) {
                std::cout << GREEN << "Student found using Sequential Search (ID: " << id << "): " << RESET << std::endl;
                printHeader();
                studentArray[index].printRow();
            } else {
                std::cout << YELLOW << "Attempting Binary Search (requires sorted array)..." << RESET << std::endl;
                
                
                std::vector<Student> tempSortedArray = studentArray;
                std::sort(tempSortedArray.begin(), tempSortedArray.end(), [](const Student& a, const Student& b) {
                    return a.getStudentID() < b.getStudentID();
                });
                index = Search::binarySearchByID(tempSortedArray, id);
                if (index != -1) {
                    std::cout << GREEN << "Student found using Binary Search (ID: " << id << "): " << RESET << std::endl;
                    printHeader();
                    tempSortedArray[index].printRow();
                } else {
                    std::cout << RED << "Student with ID " << id << " not found." << RESET << std::endl;
                }
            }
        }
    } else if (choice == 2) {
        std::cout << "Enter Student Name: ";
        std::string name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::getline(std::cin, name);

        index = Search::sequentialSearchByName(studentArray, name);
        if (index != -1) {
            std::cout << GREEN << "Student found using Sequential Search (Name: " << name << "): " << RESET << std::endl;
            printHeader();
            studentArray[index].printRow();
        } else {
            std::cout << RED << "Student with name '" << name << "' not found." << RESET << std::endl;
        }
    } else {
        std::cout << RED << "Invalid choice." << RESET << std::endl;
    }
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void StudentPerformanceTracker::sortByGrades() {
    clearConsole();
    std::cout << BOLD << MAGENTA << "--- Sort Students by Grades ---" << RESET << std::endl;
    std::cout << "Select sorting algorithm:" << std::endl;
    std::cout << "1. Bubble Sort" << std::endl;
    std::cout << "2. Insertion Sort" << std::endl;
    std::cout << "3. Merge Sort" << std::endl;
    std::cout << "4. Quick Sort" << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << RED << "Invalid input. Please enter a number." << RESET << std::endl;
        Sleep(2000);
        return;
    }

    sortedList = studentArray; 

    auto start = std::chrono::high_resolution_clock::now();
    switch (choice) {
        case 1:
            Sorting::bubbleSortByGrade(sortedList);
            std::cout << GREEN << "Sorted using Bubble Sort." << RESET << std::endl;
            break;
        case 2:
            Sorting::insertionSortByGrade(sortedList);
            std::cout << GREEN << "Sorted using Insertion Sort." << RESET << std::endl;
            break;
        case 3:
            Sorting::mergeSortByGrade(sortedList);
            std::cout << GREEN << "Sorted using Merge Sort." << RESET << std::endl;
            break;
        case 4:
            Sorting::quickSortByGrade(sortedList);
            std::cout << GREEN << "Sorted using Quick Sort." << RESET << std::endl;
            break;
        default:
            std::cout << RED << "Invalid choice." << RESET << std::endl;
            Sleep(2000);
            return;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << YELLOW << "Sorting took: " << duration.count() << " ms" << RESET << std::endl;

    if (!sortedList.empty()) {
        printHeader();
        for (const auto& s : sortedList) {
            s.printRow();
        }
    } else {
        std::cout << YELLOW << "No students to display." << RESET << std::endl;
    }
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void StudentPerformanceTracker::rankByPerformance() {
    clearConsole();
    std::cout << BOLD << MAGENTA << "--- Rank Students by Performance (Heap Sort) ---" << RESET << std::endl;
    if (studentArray.empty()) {
        std::cout << YELLOW << "No students to rank." << RESET << std::endl;
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    std::vector<Student> rankedList = studentArray;
    auto start = std::chrono::high_resolution_clock::now();
    Sorting::heapSortByGrade(rankedList);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << YELLOW << "Heap Sort took: " << duration.count() << " ms" << RESET << std::endl;

    std::cout << GREEN << "Students ranked by performance (highest grade first):" << RESET << std::endl;
    printHeader();
    for (const auto& s : rankedList) {
        s.printRow();
    }
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void StudentPerformanceTracker::compareSortingComplexity() {
    clearConsole();
    std::cout << BOLD << MAGENTA << "--- Compare Sorting Algorithm Complexity ---" << RESET << std::endl;
    if (studentArray.empty()) {
        std::cout << YELLOW << "No students to compare." << RESET << std::endl;
        std::cout << std::endl << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    std::cout << BOLD << CYAN;
    std::cout << std::left << std::setw(20) << "Algorithm"
              << std::left << std::setw(15) << "Time (ms)" << std::endl;
    std::cout << "------------------------------------" << RESET << std::endl;

    std::vector<Student> tempArray;
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration;

    
    tempArray = studentArray;
    start = std::chrono::high_resolution_clock::now();
    Sorting::bubbleSortByGrade(tempArray);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << std::left << std::setw(20) << "Bubble Sort" << std::left << std::setw(15) << std::fixed << std::setprecision(4) << duration.count() << std::endl;

    
    tempArray = studentArray;
    start = std::chrono::high_resolution_clock::now();
    Sorting::insertionSortByGrade(tempArray);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << std::left << std::setw(20) << "Insertion Sort" << std::left << std::setw(15) << std::fixed << std::setprecision(4) << duration.count() << std::endl;

    
    tempArray = studentArray;
    start = std::chrono::high_resolution_clock::now();
    Sorting::mergeSortByGrade(tempArray);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << std::left << std::setw(20) << "Merge Sort" << std::left << std::setw(15) << std::fixed << std::setprecision(4) << duration.count() << std::endl;

    
    tempArray = studentArray;
    start = std::chrono::high_resolution_clock::now();
    Sorting::quickSortByGrade(tempArray);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << std::left << std::setw(20) << "Quick Sort" << std::left << std::setw(15) << std::fixed << std::setprecision(4) << duration.count() << std::endl;

    
    tempArray = studentArray;
    start = std::chrono::high_resolution_clock::now();
    Sorting::heapSortByGrade(tempArray);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << std::left << std::setw(20) << "Heap Sort" << std::left << std::setw(15) << std::fixed << std::setprecision(4) << duration.count() << std::endl;

    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void StudentPerformanceTracker::listAllStudents() const {
    clearConsole();
    std::cout << BOLD << MAGENTA << "--- All Students ---" << RESET << std::endl;
    if (studentArray.empty()) {
        std::cout << YELLOW << "No students to display." << RESET << std::endl;
    } else {
        printHeader();
        for (const auto& s : studentArray) {
            s.printRow();
        }
    }
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void StudentPerformanceTracker::displayMainMenu() {
    int choice;
    do {
        clearConsole();
        std::cout << BOLD << GREEN << "--- Student Performance Tracker CLI ---" << RESET << std::endl;
        std::cout << "1. Add New Student Record" << std::endl;
        std::cout << "2. Search Student" << std::endl;
        std::cout << "3. Sort Students by Grades" << std::endl;
        std::cout << "4. Rank Students by Performance" << std::endl;
        std::cout << "5. Compare Sorting Complexity" << std::endl;
        std::cout << "6. List All Students" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << BOLD << BLUE << "Enter your choice: " << RESET;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << RED << "Invalid input. Please enter a number from the menu." << RESET << std::endl;
            Sleep(2000);
            continue;
        }

        switch (choice) {
            case 1: {
                clearConsole();
                std::cout << BOLD << MAGENTA << "--- Add New Student Record ---" << RESET << std::endl;
                int id;
                std::string name, course;
                double grade;

                std::cout << "Enter Student ID: ";
                std::cin >> id;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << RED << "Invalid ID. Please enter an integer." << RESET << std::endl;
                    Sleep(2000);
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                std::cout << "Enter Student Name: ";
                std::getline(std::cin, name);

                std::cout << "Enter Grade: ";
                std::cin >> grade;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << RED << "Invalid Grade. Please enter a number." << RESET << std::endl;
                    Sleep(2000);
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                std::cout << "Enter Course Details: ";
                std::getline(std::cin, course);

                Student newStudent(id, name, grade, course);
                addStudentRecord(newStudent);
                std::cout << GREEN << "Student record added successfully!" << RESET << std::endl;
                Sleep(2000);
                break;
            }
            case 2:
                searchByStudent();
                break;
            case 3:
                sortByGrades();
                break;
            case 4:
                rankByPerformance();
                break;
            case 5:
                compareSortingComplexity();
                break;
            case 6:
                listAllStudents();
                break;
            case 0:
                std::cout << BOLD << YELLOW << "Exiting Student Performance Tracker. Goodbye!" << RESET << std::endl;
                break;
            default:
                std::cout << RED << "Invalid choice. Please try again." << RESET << std::endl;
                Sleep(2000);
                break;
        }
    } while (choice != 0);
}

