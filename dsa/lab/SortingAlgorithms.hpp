#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <vector>
#include <string>

class SortingAlgorithms {
public:
    static void bubbleSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &swaps);
    static void selectionSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &swaps);
    static void insertionSort(std::vector<int> &arr, bool ascending, long long &comparisons, long long &shifts);

    static void printStats(const std::string &name, int n, long long comparisons, long long moves);
};

#endif
