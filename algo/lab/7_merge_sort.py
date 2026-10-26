import time
import tracemalloc
import matplotlib.pyplot as plt

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0

        while i < len(L) and j < len(R):
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1
    return arr

if __name__ == '__main__':
    sizes = list(range(1000, 50000, 1000))
    times = []
    spaces = []

    _ = merge_sort([2, 1])
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
            merge_sort(arr)
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
    plt.title('Merge Sort - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Merge Sort - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()