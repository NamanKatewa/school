#ifndef STUDENT_SYSTEM_H
#define STUDENT_SYSTEM_H

#include "Student.h"
#include <vector>
#include <string>
#include <list>

class StudentSystem {
public:
    StudentSystem(const std::string& data_filename);
    void loadData();
    Student* searchStudentByHash(int rollNumber, long long& duration);
    Student searchStudentByBinary(int rollNumber, long long& duration);
    std::vector<Student> sortStudentsByMarks(const std::string& sortType, long long& duration);
    std::vector<Student> sortStudentsByRoll(long long& duration);
    void getPerformanceMetrics(long long& quickSortTime, long long& heapSortTime, long long& radixSortTime);
    const std::vector<Student>& getAllStudents() const;

private:
    class HashTable {
    private:
        static const int TABLE_SIZE = 1000;
        std::list<Student> table[TABLE_SIZE];

        int hashFunction(int key) {
            return key % TABLE_SIZE;
        }

    public:
        void insert(Student s) {
            int index = hashFunction(s.rollNumber);
            table[index].push_back(std::move(s));
        }

        Student* search(int rollNumber) {
            int index = hashFunction(rollNumber);
            for (auto& s : table[index]) {
                if (s.rollNumber == rollNumber) {
                    return &s;
                }
            }
            return nullptr;
        }
        
        void clear() {
            for (int i = 0; i < TABLE_SIZE; ++i) {
                table[i].clear();
            }
        }
    };

    std::string data_filename;
    HashTable hashTable;
    std::vector<Student> allStudents;

    void quickSort(std::vector<Student>& arr, int low, int high);
    int partition(std::vector<Student>& arr, int low, int high);
    void heapSort(std::vector<Student>& arr);
    void heapify(std::vector<Student>& arr, int n, int i);
    void radixSort(std::vector<Student>& arr);
    void countSort(std::vector<Student>& arr, int exp);
    int getMaxRollNumber(const std::vector<Student>& arr);
    int binarySearch(const std::vector<Student>& arr, int targetRollNumber);
};

#endif