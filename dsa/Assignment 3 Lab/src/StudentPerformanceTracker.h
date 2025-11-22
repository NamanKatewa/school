#ifndef STUDENT_PERFORMANCE_TRACKER_H
#define STUDENT_PERFORMANCE_TRACKER_H

#include <vector>
#include <string>
#include <iostream>
#include <chrono> 
#include <Windows.h> 

#include "Student.h"
#include "HashTable.h"
#include "Search.h"
#include "Sorting.h"


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define WHITE   "\033[37m"

class StudentPerformanceTracker {
private:
    HashTable hashTable;
    std::vector<Student> studentArray; 
    std::vector<Student> sortedList;   

    
    void clearConsole() const {
        system("cls"); 
    }

    
    void printHeader() const {
        std::cout << BOLD << CYAN;
        std::cout << std::left << std::setw(8) << "ID"
                  << std::left << std::setw(25) << "Name"
                  << std::left << std::setw(8) << "Grade"
                  << std::left << std::setw(20) << "Course Details" << std::endl;
        std::cout << "-------------------------------------------------------------" << RESET << std::endl;
    }

public:
    StudentPerformanceTracker();

    
    void addStudentRecord(const Student& s);

    
    void loadStudentsFromCSV(const std::string& filename);

    
    void searchByStudent();

    
    void sortByGrades();

    
    void rankByPerformance();

    
    void compareSortingComplexity();

    
    void displayMainMenu();

    
    void listAllStudents() const;
};

#endif 
