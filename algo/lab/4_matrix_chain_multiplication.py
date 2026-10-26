import time
import tracemalloc
import matplotlib.pyplot as plt
import sys

def matrix_chain_multiplication(p):
    n = len(p)
    if n == 0: return 0
    m = [[0 for _ in range(n)] for _ in range(n)]
    
    for L in range(2, n):
        for i in range(1, n - L + 1):
            j = i + L - 1
            m[i][j] = sys.maxsize
            for k in range(i, j):
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
                if q < m[i][j]:
                    m[i][j] = q
    return m[1][n - 1] if n > 1 else 0

if __name__ == '__main__':
    sizes = list(range(10, 200, 5))
    times = []
    spaces = []
    
    _ = matrix_chain_multiplication([10, 20, 30])
    tracemalloc.start()
    tracemalloc.stop()
    
    for n in sizes:
        p = [10] * n 
        
        runs = 10
        total_time = 0
        total_space = 0
        
        for _ in range(runs):
            tracemalloc.start()
            start_time = time.perf_counter()
            matrix_chain_multiplication(p)
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
    plt.title('Matrix Chain Multiplication - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Matrix Chain Multiplication - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()