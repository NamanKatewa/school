import time
import matplotlib.pyplot as plt

def constant_time_o_1(arr):
    if arr:
        return arr[0]
    return None

def logarithmic_time_o_logn(arr, x):
    l, r = 0, len(arr) - 1
    while l <= r:
        mid = (l + r) // 2
        if arr[mid] == x:
            return mid
        elif arr[mid] < x:
            l = mid + 1
        else:
            r = mid - 1
    return -1

def linear_time_o_n(arr):
    total = 0
    for num in arr:
        total += num
    return total

def quadratic_time_o_n2(arr):
    total = 0
    for i in arr:
        for j in arr:
            total += 1
    return total

if __name__ == '__main__':
    sizes = list(range(10, 1000, 20))
    
    times_o1 = []
    times_ologn = []
    times_on = []
    times_on2 = []

    _ = constant_time_o_1([1])
    _ = logarithmic_time_o_logn([1], -1)
    _ = linear_time_o_n([1])
    _ = quadratic_time_o_n2([1])
    
    for n in sizes:
        arr = list(range(n))
        runs = 10

        total_time_o1 = 0
        for _ in range(runs):
            start = time.perf_counter()
            constant_time_o_1(arr)
            total_time_o1 += time.perf_counter() - start
        times_o1.append(total_time_o1 / runs)

        total_time_ologn = 0
        for _ in range(runs):
            start = time.perf_counter()
            logarithmic_time_o_logn(arr, -1)
            total_time_ologn += time.perf_counter() - start
        times_ologn.append(total_time_ologn / runs)

        total_time_on = 0
        for _ in range(runs):
            start = time.perf_counter()
            linear_time_o_n(arr)
            total_time_on += time.perf_counter() - start
        times_on.append(total_time_on / runs)

        total_time_on2 = 0
        for _ in range(runs):
            start = time.perf_counter()
            quadratic_time_o_n2(arr)
            total_time_on2 += time.perf_counter() - start
        times_on2.append(total_time_on2 / runs)
        
    plt.figure(figsize=(10, 6))
    plt.plot(sizes, times_o1, marker='o', label='O(1)')
    plt.plot(sizes, times_ologn, marker='o', label='O(log N)')
    plt.plot(sizes, times_on, marker='o', label='O(N)')
    plt.plot(sizes, times_on2, marker='o', label='O(N^2)')
    
    plt.title('Time Complexities Comparison')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    plt.legend()
    plt.grid(True)
    
    plt.tight_layout()
    plt.yscale('log')
    plt.show()