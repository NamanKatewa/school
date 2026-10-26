import time
import tracemalloc
import matplotlib.pyplot as plt

def linear_search(arr, target):
    for i, val in enumerate(arr):
        if val == target:
            return i
    return -1

if __name__ == '__main__':
    sizes = list(range(1000, 500000, 10000))
    times = []
    spaces = []
    
    _ = linear_search([1], -1)
    tracemalloc.start()
    tracemalloc.stop()
    
    for n in sizes:
        arr = [1] * n
        target = -1
        
        runs = 10
        total_time = 0
        total_space = 0
        
        for _ in range(runs):
            tracemalloc.start()
            start_time = time.perf_counter()
            linear_search(arr, target)
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
    plt.title('Linear Search - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Linear Search - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()