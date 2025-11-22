#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <string>
#include "Student.h" 

namespace Search {
    
    int sequentialSearchByID(const std::vector<Student>& arr, int id);

    
    int sequentialSearchByName(const std::vector<Student>& arr, const std::string& name);

    
    int binarySearchByID(const std::vector<Student>& arr, int id);
}

#endif 
