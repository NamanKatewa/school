#include "SortingAlgorithms.hpp"
#include <iostream>
#include <utility>

void SortingAlgorithms::bubbleSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &swaps) {
    size_t n = arr.size();
    if (n < 2) return;

    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            comparisons++;
            bool shouldSwap = ascending ? (arr[j] > arr[j + 1]) : (arr[j] < arr[j + 1]);
            if (shouldSwap) {
                swaps++;
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void SortingAlgorithms::selectionSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &swaps) {
    size_t n = arr.size();
    if (n < 2) return;

    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_max_idx = i;
        for (size_t j = i + 1; j < n; ++j) {
            comparisons++;
            bool shouldUpdate = ascending ? (arr[j] < arr[min_max_idx]) : (arr[j] > arr[min_max_idx]);
            if (shouldUpdate) {
                min_max_idx = j;
            }
        }
        if (min_max_idx != i) {
            swaps++;
            std::swap(arr[i], arr[min_max_idx]);
        }
    }
}

void SortingAlgorithms::insertionSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &shifts) {
    size_t n = arr.size();
    if (n < 2) return;

    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            bool shouldShift = ascending ? (arr[j] > key) : (arr[j] < key);
            if (shouldShift) {
                arr[j + 1] = arr[j];
                shifts++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        if (j + 1 != (int)i) {
             shifts++;
        }
    }
}

void SortingAlgorithms::printStats(const std::string &name, int n, long long comparisons, long long moves) {
    std::cout << name << " (n=" << n << "): Comparisons=" << comparisons << ", Moves=" << moves << std::endl;
}
