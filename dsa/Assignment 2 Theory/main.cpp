#include <iostream>
#include <fstream>
#include <sstream>
#include "HospitalSystem.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ANSI Color Codes
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";

void enableAnsi() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void addNewPatient(PatientList& records, UndoStack& undoHistory, EmergencyQueue& erQueue) {
    int id, priority;
    string name, date, treatment;

    cout << BOLD << CYAN << "Enter Patient ID: " << RESET;
    cin >> id;
    if (records.exists(id)) {
        cout << BOLD << RED << "Patient with this ID already exists." << RESET << endl;
        return;
    }
    cout << BOLD << CYAN << "Enter Name: " << RESET;
    cin.ignore();
    getline(cin, name);
    cout << BOLD << CYAN << "Enter Admission Date: " << RESET;
    getline(cin, date);
    cout << BOLD << CYAN << "Enter Treatment: " << RESET;
    getline(cin, treatment);
    cout << BOLD << CYAN << "Enter Priority (1-5): " << RESET;
    cin >> priority;

    records.insert(id, name, date, treatment, priority);
    undoHistory.recordOperation(id);
    erQueue.enqueue(id, priority);
    cout << BOLD << GREEN << "Patient added successfully." << RESET << endl;
}

void undoLastAction(PatientList& records, UndoStack& undoHistory) {
    if (!undoHistory.isEmpty()) {
        int lastId = undoHistory.undo();
        records.deleteById(lastId);
        cout << BOLD << YELLOW << "Undo Successful. Patient " << lastId << " removed." << RESET << endl;
    } else {
        cout << BOLD << RED << "No actions to undo." << RESET << endl;
    }
}

void loadData(PatientList& records, EmergencyQueue& erQueue) {
    ifstream file("data.csv");
    if (!file.is_open()) {
        cout << BOLD << RED << "Error: data.csv not found!" << RESET << endl;
        return;
    }
    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, name, date, treatment, priority_str;
        getline(ss, id_str, ',');
        getline(ss, name, ',');
        getline(ss, date, ',');
        getline(ss, treatment, ',');
        getline(ss, priority_str, ',');

        int id = stoi(id_str);
        int priority = stoi(priority_str);

        records.insert(id, name, date, treatment, priority);
        erQueue.enqueue(id, priority);
    }
    cout << BOLD << GREEN << "Patient data loaded from data.csv" << RESET << endl;
}

void evaluateInventory() {
    ifstream file("inventory.txt");
     if (!file.is_open()) {
        cout << BOLD << RED << "Error: inventory.txt not found!" << RESET << endl;
        return;
    }
    string line;
    cout << BOLD << MAGENTA << "--- Inventory Calculations ---" << RESET << endl;
    while (getline(file, line)) {
        cout << "Expression: " << line << ", Result: " << BOLD << HospitalMath::evaluateInventory(line) << RESET << endl;
    }
     cout << BOLD << MAGENTA << "----------------------------" << RESET << endl;
}

int main() {
    enableAnsi();
    PatientList records;
    UndoStack undoHistory;
    EmergencyQueue erQueue;

    int choice;
    do {
        cout << endl;
        cout << BOLD << MAGENTA << "--- Hospital Patient Record Management System ---" << RESET << endl;
        cout << YELLOW << "1. " << RESET << "Add New Patient" << endl;
        cout << YELLOW << "2. " << RESET << "Delete Patient by ID" << endl;
        cout << YELLOW << "3. " << RESET << "Display All Patients" << endl;
        cout << YELLOW << "4. " << RESET << "Undo Last Add" << endl;
        cout << YELLOW << "5. " << RESET << "Show Emergency Queue" << endl;
        cout << YELLOW << "6. " << RESET << "Process Emergency Patient" << endl;
        cout << YELLOW << "7. " << RESET << "Calculate Bill" << endl;
        cout << YELLOW << "8. " << RESET << "Evaluate Inventory" << endl;
        cout << YELLOW << "9. " << RESET << "Load Patient Data from CSV" << endl;
        cout << BOLD << RED << "0. " << RESET << "Exit" << endl;
        cout << BOLD << CYAN << "Enter your choice: " << RESET;
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                addNewPatient(records, undoHistory, erQueue);
                break;
            case 2: {
                int id;
                cout << BOLD << CYAN << "Enter Patient ID to delete: " << RESET;
                cin >> id;
                records.deleteById(id);
                cout << BOLD << YELLOW << "Patient with ID " << id << " deleted." << RESET << endl;
                break;
            }
            case 3:
                 cout << BOLD << MAGENTA << "--- All Patient Records ---" << RESET << endl;
                records.displayAll();
                 cout << BOLD << MAGENTA << "---------------------------" << RESET << endl;
                break;
            case 4:
                undoLastAction(records, undoHistory);
                break;
            case 5:
                 cout << BOLD << MAGENTA << "--- Emergency Room Queue ---" << RESET << endl;
                erQueue.displayQueue();
                 cout << BOLD << MAGENTA << "----------------------------" << RESET << endl;
                break;
            case 6:
                erQueue.dequeue();
                break;
            case 7: {
                int days;
                cout << BOLD << CYAN << "Enter number of days: " << RESET;
                cin >> days;
                cout << "Total bill: " << BOLD << GREEN << "$" << HospitalMath::calculateBill(days) << RESET << endl;
                break;
            }
            case 8:
                evaluateInventory();
                break;
            case 9:
                loadData(records, erQueue);
                break;
            case 0:
                cout << BOLD << GREEN << "Exiting program." << RESET << endl;
                break;
            default:
                cout << BOLD << RED << "Invalid choice. Please try again." << RESET << endl;
        }

#ifdef _WIN32
        system("pause"); // Wait for user input before clearing
        system("cls");   // Clear console for Windows
#else
        system("read -n 1 -s -p \"Press any key to continue...\""); // Wait for user input
        system("clear"); // Clear console for Unix-like systems
#endif
    } while (choice != 0);

    return 0;
}