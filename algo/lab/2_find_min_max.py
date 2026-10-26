import time
import tracemalloc
import matplotlib.pyplot as plt
import sys

def find_min_max(arr, low, high):
    if low == high:
        return arr[low], arr[low]
    if high == low + 1:
        if arr[low] > arr[high]:
            return arr[high], arr[low]
        return arr[low], arr[high]
    
    mid = (low + high) // 2
    min1, max1 = find_min_max(arr, low, mid)
    min2, max2 = find_min_max(arr, mid + 1, high)
    
    return min(min1, min2), max(max1, max2)

if __name__ == '__main__':
    sys.setrecursionlimit(200000)
    sizes = list(range(1000, 100000, 2000))
    times = []
    spaces = []
    
    _ = find_min_max([1, 2], 0, 1)
    tracemalloc.start()
    tracemalloc.stop()
    
    for n in sizes:
        arr = list(range(n, 0, -1))
        
        runs = 10
        total_time = 0
        total_space = 0
        
        for _ in range(runs):
            tracemalloc.start()
            start_time = time.perf_counter()
            if n > 0:
                find_min_max(arr, 0, n - 1)
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
    plt.title('Find Min & Max - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Find Min & Max - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()