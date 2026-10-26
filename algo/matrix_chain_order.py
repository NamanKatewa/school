import matplotlib.pyplot as plt
import time
import random
import sys

def matrix_chain_order(p: list[int]):
    n = len(p) - 1
    m = [[0] * (n + 1) for _ in range(n + 1)]
    s = [[0] * (n + 1) for _ in range(n + 1)]

    for chain_length in range(2, n + 1):
        for i in range(1, n - chain_length + 2):
            j = i + chain_length - 1
            m[i][j] = sys.maxsize
            for k in range(i, j):
                cost = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j])
                if cost < m[i][j]:
                    m[i][j] = cost
                    s[i][j] = k
    return m, s

sizes = [10, 50, 100, 150, 200, 250, 300, 350, 400]
execution_times = []

print("Starting matrix chain benchmarks...")

for n in sizes:
    p = [random.randint(10, 100) for _ in range(n + 1)]
    
    start = time.time()
    matrix_chain_order(p)
    end = time.time()
    
    exec_time = end - start
    execution_times.append(exec_time)
    print(f"Tested n={n:<3} matrices | Time: {exec_time:.4f} seconds")

print("Generating plot...")

plt.figure()
plt.plot(sizes, execution_times, marker='o', color='purple', label="Execution Time (O(n³))")
plt.xlabel("Number of Matrices (n)")
plt.ylabel("Execution Time (seconds)")
plt.title("Matrix Chain Order: Time Complexity Analysis")
plt.legend()
plt.grid(True)
plt.show()