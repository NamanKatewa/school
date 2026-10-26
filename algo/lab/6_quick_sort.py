import time
import tracemalloc
import matplotlib.pyplot as plt
import random
import sys

def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def quick_sort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)
    return arr

if __name__ == '__main__':
    sys.setrecursionlimit(20000)
    sizes = list(range(100, 5000, 100))
    times = []
    spaces = []

    _ = quick_sort([2, 1], 0, 1)
    tracemalloc.start()
    tracemalloc.stop()
    
    for n in sizes:
        arr_original = [random.randint(1, 10000) for _ in range(n)]
        
        runs = 10
        total_time = 0
        total_space = 0
        
        for _ in range(runs):
            arr = arr_original.copy()
            tracemalloc.start()
            start_time = time.perf_counter()
            if n > 0:
                quick_sort(arr, 0, n - 1)
            end_time = time.perf_counter()
            current, peak = tracemalloc.get_traced_memory()
            tracemalloc.stop()
            
            total_time += (end_time - start_time)
            total_space += peak
            
        times.append(total_time / runs)
        spaces.append(total_space / runs)
        
    plt.figure(figsize=(12, 5))
    plt.subplot(1, 2, 1)
    plt.plot(sizes, times, marker='o', color='b')
    plt.title('Quick Sort - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Quick Sort - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()