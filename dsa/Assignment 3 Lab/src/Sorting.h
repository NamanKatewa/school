#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include "Student.h" 

namespace Sorting {

    
    void bubbleSortByGrade(std::vector<Student>& arr);

    
    void insertionSortByGrade(std::vector<Student>& arr);

    
    void mergeSortByGrade(std::vector<Student>& arr);
    void merge(std::vector<Student>& arr, int left, int mid, int right);
    void mergeSortRecursive(std::vector<Student>& arr, int left, int right);


    
    void quickSortByGrade(std::vector<Student>& arr);
    int partition(std::vector<Student>& arr, int low, int high);
    void quickSortRecursive(std::vector<Student>& arr, int low, int high);

    
    void heapSortByGrade(std::vector<Student>& arr);
    void heapify(std::vector<Student>& arr, int n, int i);

} 

#endif 
