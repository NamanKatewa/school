import time
import tracemalloc
import matplotlib.pyplot as plt

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr

if __name__ == '__main__':
    sizes = list(range(10, 1000, 20))
    times = []
    spaces = []
    
    _ = bubble_sort([2, 1])
    tracemalloc.start()
    tracemalloc.stop()
    
    for n in sizes:
        arr_original = list(range(n, 0, -1))
        
        runs = 10
        total_time = 0
        total_space = 0
        
        for _ in range(runs):
            arr = arr_original.copy()
            tracemalloc.start()
            start_time = time.perf_counter()
            bubble_sort(arr)
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
    plt.title('Bubble Sort - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Bubble Sort - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()