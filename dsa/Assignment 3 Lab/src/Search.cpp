#include "Search.h"
#include <algorithm> 

namespace Search {

    int sequentialSearchByID(const std::vector<Student>& arr, int id) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i].getStudentID() == id) {
                return i; 
            }
        }
        return -1; 
    }

    int sequentialSearchByName(const std::vector<Student>& arr, const std::string& name) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i].getStudentName() == name) {
                return i; 
            }
        }
        return -1; 
    }

    int binarySearchByID(const std::vector<Student>& arr, int id) {
        
        
        

        int low = 0;
        int high = arr.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid].getStudentID() == id) {
                return mid; 
            } else if (arr[mid].getStudentID() < id) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1; 
    }

} 
