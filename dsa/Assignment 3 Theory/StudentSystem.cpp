#include "StudentSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <algorithm>

StudentSystem::StudentSystem(const std::string& data_filename) : data_filename(data_filename) {
    loadData();
}

void StudentSystem::loadData() {
    std::ifstream file(data_filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << data_filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); 

    hashTable.clear();
    allStudents.clear();

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> seglist;

        while (std::getline(ss, segment, ',')) {
            seglist.push_back(segment);
        }

        if (seglist.size() == 4) {
            try {
                Student s(std::stoi(seglist[0]), seglist[1], std::stof(seglist[2]), seglist[3]);
                hashTable.insert(s);
                allStudents.push_back(s);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            }
        }
    }
    file.close();
    std::cout << "Loaded " << allStudents.size() << " student records from " << data_filename << std::endl;
}

Student* StudentSystem::searchStudentByHash(int rollNumber, long long& duration) {
    auto start = std::chrono::high_resolution_clock::now();
    Student* student = hashTable.search(rollNumber);
    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    return student;
}

Student StudentSystem::searchStudentByBinary(int rollNumber, long long& duration) {
    std::vector<Student> sortedStudents = allStudents;
    radixSort(sortedStudents);

    auto start = std::chrono::high_resolution_clock::now();
    int index = binarySearch(sortedStudents, rollNumber);
    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

    if (index != -1) {
        return sortedStudents[index];
    }
    return Student();
}

std::vector<Student> StudentSystem::sortStudentsByMarks(const std::string& sortType, long long& duration) {
    std::vector<Student> sortedStudents = allStudents;
    auto start = std::chrono::high_resolution_clock::now();
    if (sortType == "quick") {
        quickSort(sortedStudents, 0, sortedStudents.size() - 1);
    } else if (sortType == "heap") {
        heapSort(sortedStudents);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return sortedStudents;
}

std::vector<Student> StudentSystem::sortStudentsByRoll(long long& duration) {
    std::vector<Student> sortedStudents = allStudents;
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(sortedStudents);
    auto stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return sortedStudents;
}

void StudentSystem::getPerformanceMetrics(long long& quickSortTime, long long& heapSortTime, long long& radixSortTime) {
    sortStudentsByMarks("quick", quickSortTime);
    sortStudentsByMarks("heap", heapSortTime);
    sortStudentsByRoll(radixSortTime);
}

const std::vector<Student>& StudentSystem::getAllStudents() const {
    return allStudents;
}

void StudentSystem::quickSort(std::vector<Student>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int StudentSystem::partition(std::vector<Student>& arr, int low, int high) {
    float pivot = arr[high].marks;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j].marks > pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void StudentSystem::heapSort(std::vector<Student>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void StudentSystem::heapify(std::vector<Student>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l].marks > arr[largest].marks)
        largest = l;
    if (r < n && arr[r].marks > arr[largest].marks)
        largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void StudentSystem::radixSort(std::vector<Student>& arr) {
    if (arr.empty()) return;
    int m = getMaxRollNumber(arr);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, exp);
}

void StudentSystem::countSort(std::vector<Student>& arr, int exp) {
    std::vector<Student> output(arr.size());
    std::vector<int> count(10, 0);
    for (size_t i = 0; i < arr.size(); i++)
        count[(arr[i].rollNumber / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i].rollNumber / exp) % 10] - 1] = arr[i];
        count[(arr[i].rollNumber / exp) % 10]--;
    }
    for (size_t i = 0; i < arr.size(); i++)
        arr[i] = output[i];
}

int StudentSystem::getMaxRollNumber(const std::vector<Student>& arr) {
    int max_roll = arr[0].rollNumber;
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i].rollNumber > max_roll) {
            max_roll = arr[i].rollNumber;
        }
    }
    return max_roll;
}

int StudentSystem::binarySearch(const std::vector<Student>& arr, int targetRollNumber) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].rollNumber == targetRollNumber) {
            return mid;
        }
        if (arr[mid].rollNumber < targetRollNumber) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}