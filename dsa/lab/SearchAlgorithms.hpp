#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP

#include <vector>

class SearchAlgorithms {
public:
    static int linearSearchFirst(const std::vector<int> &arr, int key, long long &comparisons);
    static std::vector<int> linearSearchAll(const std::vector<int> &arr, int key, long long &comparisons);

    static int binarySearchIterative(const std::vector<int> &arr, int key, long long &comparisons);
    static int binarySearchRecursive(const std::vector<int> &arr, int key, long long &comparisons);

    static int binarySearchFirst(const std::vector<int> &arr, int key, long long &comparisons);
    static int binarySearchLast(const std::vector<int> &arr, int key, long long &comparisons);

private:
    static int binarySearchRecursiveHelper(const std::vector<int> &arr, int key, int left, int right, long long &comparisons);
};

#endif
