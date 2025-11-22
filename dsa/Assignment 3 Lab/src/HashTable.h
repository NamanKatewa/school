#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include "Student.h" 

class HashTable {
private:
    std::vector<std::list<Student>> table;
    size_t capacity;

    
    size_t hashFunction(int studentID) const {
        return studentID % capacity;
    }

public:
    
    HashTable(size_t size = 100); 

    
    void insertStudent(const Student& s);

    
    Student* searchStudentByID(int studentID);
};

#endif 
