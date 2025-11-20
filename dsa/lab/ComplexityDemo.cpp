#include "ComplexityDemo.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <algorithm>

namespace ComplexityDemo {

    void printHeader(const std::string& functionName) {
        std::cout << "\n--- " << functionName << " ---" << std::endl;
        std::cout << std::left << std::setw(12) << "n"
                  << std::setw(15) << "Time (ms)"
                  << std::setw(20) << "Operations" << std::endl;
        std::cout << std::string(47, '-') << std::endl;
    }

    void runDemo(const std::string& name, 
                 const std::function<void(int, long long&, long long&)>& func, 
                 const std::vector<int>& sizes) {
        printHeader(name);
        for (int n : sizes) {
            long long time_ms = 0;
            long long operations = 0;
            
            time_ms = measureTimeMillis([&]() {
                func(n, operations, time_ms);
            });

            std::cout << std::left << std::setw(12) << n
                      << std::setw(15) << time_ms
                      << std::setw(20) << operations << std::endl;
        }
    }

    int constantTimeExample(const Array &arr) {
        if (arr.isEmpty()) return -1;
        return arr.getAt(0);
    }

    int linearMax(const Array &arr, long long &comparisonCount) {
        if (arr.isEmpty()) {
            throw std::logic_error("Array is empty.");
        }
        int max_val = arr.getAt(0);
        for (int i = 1; i < arr.getSize(); ++i) {
            comparisonCount++;
            if (arr.getAt(i) > max_val) {
                max_val = arr.getAt(i);
            }
        }
        return max_val;
    }

    int quadraticDummy(int n, long long &operationCount) {
        int dummy = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                operationCount++;
                dummy += 1;
            }
        }
        return dummy;
    }
    
    void runAllDemos() {
        std::vector<int> sizes = {100, 500, 1000, 5000, 10000, 50000, 100000};

        runDemo("Constant Time Example (getAt(0))", 
            [](int n, long long& ops, long long& time) {
                if (n == 0) return;
                Array arr(n);
                for(int i=0; i<n; ++i) arr.append(i);
                time = measureTimeMillis([&](){
                    constantTimeExample(arr);
                });
            }, 
            sizes);

        runDemo("Linear Time Example (linearMax)", 
            [](int n, long long& ops, long long& time) {
                if (n == 0) return;
                Array arr(n);
                for(int i=0; i<n; ++i) arr.append(i);
                time = measureTimeMillis([&](){
                    linearMax(arr, ops);
                });
            }, 
            sizes);

        runDemo("Logarithmic Time Example (binarySearch)",
            [](int n, long long& ops, long long& time) {
                if (n == 0) return;
                std::vector<int> vec(n);
                std::iota(vec.begin(), vec.end(), 0);
                time = measureTimeMillis([&](){
                    SearchAlgorithms::binarySearchIterative(vec, n / 2, ops);
                });
            },
            sizes);

        runDemo("Quadratic Time Example (quadraticDummy)", 
            [](int n, long long& ops, long long& time) {
                 time = measureTimeMillis([&](){
                    quadraticDummy(n, ops);
                });
            },
            {100, 200, 500, 1000, 2000});
    }

}
