#include "HashTable.h"
#include <iostream>


HashTable::HashTable(size_t size) : capacity(size) {
    table.resize(capacity);
}


void HashTable::insertStudent(const Student& s) {
    size_t index = hashFunction(s.getStudentID());
    
    for (const auto& student : table[index]) {
        if (student.getStudentID() == s.getStudentID()) {
            std::cerr << "Error: Student with ID " << s.getStudentID() << " already exists." << std::endl;
            return; 
        }
    }
    table[index].push_back(s);
}


Student* HashTable::searchStudentByID(int studentID) {
    size_t index = hashFunction(studentID);
    for (auto& student : table[index]) {
        if (student.getStudentID() == studentID) {
            return &student; 
        }
    }
    return nullptr; 
}
