import time
import tracemalloc
import matplotlib.pyplot as plt

def fractional_knapsack(W, arr):
    arr.sort(key=lambda x: x[0] / x[1] if x[1] != 0 else 0, reverse=True)
    final_value = 0.0
    for value, weight in arr:
        if weight <= W:
            W -= weight
            final_value += value
        elif weight > 0:
            final_value += value * (W / weight)
            break
    return final_value

if __name__ == '__main__':
    sizes = list(range(1000, 100000, 2000))
    times = []
    spaces = []
    
    _ = fractional_knapsack(10, [(10, 5)])
    tracemalloc.start()
    tracemalloc.stop()
    
    for n in sizes:
        arr_original = [(1, 1) for _ in range(n)]
        W = float('inf')
        
        runs = 10
        total_time = 0
        total_space = 0
        
        for _ in range(runs):
            arr = arr_original.copy()
            tracemalloc.start()
            start_time = time.perf_counter()
            fractional_knapsack(W, arr)
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
    plt.title('Fractional Knapsack - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Fractional Knapsack - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()