import time
import tracemalloc
import matplotlib.pyplot as plt

def binary_search(arr, l, r, x):
    while l <= r:
        mid = l + (r - l) // 2
        if arr[mid] == x:
            return mid
        elif arr[mid] < x:
            l = mid + 1
        else:
            r = mid - 1
    return -1

if __name__ == '__main__':
    sizes = list(range(10000, 1000000, 20000))
    times = []
    spaces = []

    _ = binary_search([1], 0, 0, -1)
    tracemalloc.start()
    tracemalloc.stop()
    
    for n in sizes:
        arr = list(range(n))
        target = -1
        
        runs = 10
        total_time = 0
        total_space = 0
        
        for _ in range(runs):
            tracemalloc.start()
            start_time = time.perf_counter()
            if n > 0:
                binary_search(arr, 0, n - 1, target)
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
    plt.title('Binary Search - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Binary Search - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()