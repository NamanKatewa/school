#include "HospitalSystem.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <cmath>

const std::string RESET_COLOR = "\033[0m";
const std::string BOLD_TEXT = "\033[1m";
const std::string RED_TEXT = "\033[31m";
const std::string GREEN_TEXT = "\033[32m";
const std::string YELLOW_TEXT = "\033[33m";
const std::string BLUE_TEXT = "\033[34m";

PatientList::PatientList() : head(nullptr) {}

PatientList::~PatientList() {
    Patient* current = head;
    while (current != nullptr) {
        Patient* next = current->next;
        delete current;
        current = next;
    }
}

void PatientList::insert(int id, std::string name, std::string date, std::string tx, int p) {
    Patient* newNode = new Patient{id, name, date, tx, p, nullptr};
    if (head == nullptr || head->id >= newNode->id) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Patient* current = head;
    while (current->next != nullptr && current->next->id < newNode->id) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void PatientList::deleteById(int id) {
    if (head == nullptr) return;
    if (head->id == id) {
        Patient* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Patient* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }
    if (current->next != nullptr) {
        Patient* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

void PatientList::displayAll() {
    Patient* current = head;
    if(current == nullptr){
        std::cout << BOLD_TEXT << RED_TEXT << "No patient records available." << RESET_COLOR << std::endl;
        return;
    }

    std::cout << BOLD_TEXT << BLUE_TEXT
              << std::left << std::setw(8) << "ID"
              << std::setw(25) << "Name"
              << std::setw(15) << "Date"
              << std::setw(25) << "Treatment"
              << std::setw(10) << "Priority" << RESET_COLOR << std::endl;
    
    std::cout << BOLD_TEXT << BLUE_TEXT << std::string(83, '-') << RESET_COLOR << std::endl;

    while (current != nullptr) {
        std::cout << std::left << std::setw(8) << current->id
                  << std::setw(25) << current->name
                  << std::setw(15) << current->date
                  << std::setw(25) << current->treatment
                  << std::setw(10) << current->priority << std::endl;
        current = current->next;
    }
}

bool PatientList::exists(int id) {
    Patient* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void UndoStack::recordOperation(int id) {
    history.push(id);
}

int UndoStack::undo() {
    if (!history.empty()) {
        int id = history.top();
        history.pop();
        return id;
    }
    return -1;
}

bool UndoStack::isEmpty() {
    return history.empty();
}

EmergencyQueue::EmergencyQueue() : front(nullptr) {}

EmergencyQueue::~EmergencyQueue() {
    QNode* current = front;
    while (current != nullptr) {
        QNode* next = current->next;
        delete current;
        current = next;
    }
}

void EmergencyQueue::enqueue(int id, int priority) {
    QNode* newNode = new QNode{id, priority, nullptr};
    if (front == nullptr || priority < front->priority) {
        newNode->next = front;
        front = newNode;
        return;
    }
    QNode* current = front;
    while (current->next != nullptr && current->next->priority <= priority) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void EmergencyQueue::dequeue() {
    if (front != nullptr) {
        QNode* temp = front;
        front = front->next;
        std::cout << BOLD_TEXT << GREEN_TEXT << "Processing patient with ID: " << RESET_COLOR << temp->id 
                  << BOLD_TEXT << GREEN_TEXT << " and priority: " << RESET_COLOR << temp->priority << std::endl;
        delete temp;
    } else {
        std::cout << BOLD_TEXT << RED_TEXT << "Emergency queue is empty." << RESET_COLOR << std::endl;
    }
}

void EmergencyQueue::displayQueue() {
    QNode* current = front;
     if(current == nullptr){
        std::cout << BOLD_TEXT << RED_TEXT << "Emergency queue is empty." << RESET_COLOR << std::endl;
        return;
    }
    while (current != nullptr) {
        std::cout << BOLD_TEXT << YELLOW_TEXT << "ID: " << RESET_COLOR << current->id 
                  << BOLD_TEXT << ", Priority: " << RESET_COLOR << current->priority << std::endl;
        current = current->next;
    }
}

double HospitalMath::calculateBill(int days) {
    return 500 + 100 * days + 5 * pow(days, 2);
}

int HospitalMath::evaluateInventory(std::string expression) {
    std::stack<int> s;
    std::stringstream ss(expression);
    std::string token;
    while (ss >> token) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            s.push(std::stoi(token));
        } else {
            if(s.size() < 2) {
                std::cerr << BOLD_TEXT << RED_TEXT << "Invalid postfix expression: " << expression << RESET_COLOR << std::endl;
                return 0;
            }
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();
            switch (token[0]) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
                default:
                    std::cerr << BOLD_TEXT << RED_TEXT << "Invalid operator in expression: " << token << RESET_COLOR << std::endl;
                    return 0;
            }
        }
    }
     if(s.size() != 1) {
        std::cerr << BOLD_TEXT << RED_TEXT << "Invalid postfix expression: " << expression << RESET_COLOR << std::endl;
        return 0;
    }
    return s.top();
}