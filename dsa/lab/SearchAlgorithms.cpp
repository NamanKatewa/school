#include "SearchAlgorithms.hpp"

int SearchAlgorithms::linearSearchFirst(const std::vector<int> &arr, int key, long long &comparisons) {
    for (size_t i = 0; i < arr.size(); ++i) {
        comparisons++;
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

std::vector<int> SearchAlgorithms::linearSearchAll(const std::vector<int> &arr, int key, long long &comparisons) {
    std::vector<int> indices;
    for (size_t i = 0; i < arr.size(); ++i) {
        comparisons++;
        if (arr[i] == key) {
            indices.push_back(i);
        }
    }
    return indices;
}

int SearchAlgorithms::binarySearchIterative(const std::vector<int> &arr, int key, long long &comparisons) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (arr[mid] == key) {
            return mid;
        }
        comparisons++;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int SearchAlgorithms::binarySearchRecursive(const std::vector<int> &arr, int key, long long &comparisons) {
    return binarySearchRecursiveHelper(arr, key, 0, arr.size() - 1, comparisons);
}

int SearchAlgorithms::binarySearchRecursiveHelper(const std::vector<int> &arr, int key, int left, int right, long long &comparisons) {
    if (left > right) {
        return -1;
    }
    int mid = left + (right - left) / 2;
    comparisons++;
    if (arr[mid] == key) {
        return mid;
    }
    comparisons++;
    if (arr[mid] < key) {
        return binarySearchRecursiveHelper(arr, key, mid + 1, right, comparisons);
    }
    return binarySearchRecursiveHelper(arr, key, left, mid - 1, comparisons);
}

int SearchAlgorithms::binarySearchFirst(const std::vector<int> &arr, int key, long long &comparisons) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (arr[mid] == key) {
            result = mid;
            right = mid - 1;
        } else {
            comparisons++;
            if (arr[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return result;
}

int SearchAlgorithms::binarySearchLast(const std::vector<int> &arr, int key, long long &comparisons) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (arr[mid] == key) {
            result = mid;
            left = mid + 1;
        } else {
            comparisons++;
            if (arr[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return result;
}
