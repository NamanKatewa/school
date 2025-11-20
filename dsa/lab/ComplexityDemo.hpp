#ifndef COMPLEXITY_DEMO_HPP
#define COMPLEXITY_DEMO_HPP

#include "Array.hpp"
#include "SearchAlgorithms.hpp"
#include <functional>
#include <string>
#include <vector>
#include <chrono>

namespace ComplexityDemo {

    struct CustomMetrics {
        long long memoryBytes = 0;
    };

    using PureTimeFunc = std::function<int(const Array&)>;
    using TimeAndOpsFunc = std::function<int(const Array&, long long&)>;
    using FullMetricsFunc = std::function<int(const Array&, long long&, CustomMetrics&)>;

    template <typename Func>
    long long measureTimeMillis(Func f) {
        auto start = std::chrono::high_resolution_clock::now();
        f();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    void runAllDemos();

    int constantTimeExample(const Array &arr);
    int linearMax(const Array &arr, long long &comparisonCount);
    int quadraticDummy(int n, long long &operationCount);
    int binarySearch(const std::vector<int> &arr, int key, long long &comparisonCount);
    void mergeSort(std::vector<int> &arr, long long &comparisonCount);

}

#endif
