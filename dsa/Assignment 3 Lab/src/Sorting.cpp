#include "Sorting.h"
#include <algorithm> 

namespace Sorting {

    
    void bubbleSortByGrade(std::vector<Student>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j].getGrade() < arr[j+1].getGrade()) { 
                    std::swap(arr[j], arr[j+1]);
                }
            }
        }
    }

    
    void insertionSortByGrade(std::vector<Student>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            Student key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j].getGrade() < key.getGrade()) { 
                arr[j+1] = arr[j];
                j = j - 1;
            }
            arr[j+1] = key;
        }
    }

    
    void merge(std::vector<Student>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<Student> L(n1);
        std::vector<Student> R(n2);

        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];

        int i = 0; 
        int j = 0; 
        int k = left; 

        while (i < n1 && j < n2) {
            if (L[i].getGrade() >= R[j].getGrade()) { 
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    void mergeSortRecursive(std::vector<Student>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortRecursive(arr, left, mid);
            mergeSortRecursive(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void mergeSortByGrade(std::vector<Student>& arr) {
        mergeSortRecursive(arr, 0, arr.size() - 1);
    }

    
    int partition(std::vector<Student>& arr, int low, int high) {
        double pivot = arr[high].getGrade();
        int i = (low - 1);

        for (int j = low; j <= high - 1; ++j) {
            if (arr[j].getGrade() >= pivot) { 
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    void quickSortRecursive(std::vector<Student>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortRecursive(arr, low, pi - 1);
            quickSortRecursive(arr, pi + 1, high);
        }
    }

    void quickSortByGrade(std::vector<Student>& arr) {
        quickSortRecursive(arr, 0, arr.size() - 1);
    }

    
    void heapify(std::vector<Student>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left].getGrade() > arr[largest].getGrade())
            largest = left;

        if (right < n && arr[right].getGrade() > arr[largest].getGrade())
            largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void heapSortByGrade(std::vector<Student>& arr) {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; --i)
            heapify(arr, n, i);

        for (int i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

} 
