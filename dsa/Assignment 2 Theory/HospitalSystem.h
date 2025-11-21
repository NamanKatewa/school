#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

struct Patient {
    int id;
    std::string name;
    std::string date;
    std::string treatment;
    int priority;
    Patient* next;
};

class PatientList {
private:
    Patient* head;
public:
    PatientList();
    ~PatientList();
    void insert(int id, std::string name, std::string date, std::string tx, int p);
    void deleteById(int id);
    void displayAll();
    bool exists(int id);
};

class UndoStack {
private:
    std::stack<int> history;
public:
    void recordOperation(int id);
    int undo();
    bool isEmpty();
};

struct QNode {
    int id;
    int priority;
    QNode* next;
};

class EmergencyQueue {
private:
    QNode* front;
public:
    EmergencyQueue();
    ~EmergencyQueue();
    void enqueue(int id, int priority);
    void dequeue();
    void displayQueue();
};

class HospitalMath {
public:
    static double calculateBill(int days);

    static int evaluateInventory(std::string expression);
};

#endif
