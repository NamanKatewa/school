import matplotlib.pyplot as plt
import time

def linear_search(arr: list[int], key:int)->int:
    for x in range(len(arr)):
        if arr[x] == key:
            return x
    
    return -1

sizes = [100,500,1000,5000,10000]

best_cases=[]
average_cases=[]
worst_cases=[]

for n in sizes:
    arr=list(range(n))
    
    start = time.time()
    linear_search(arr,arr[0])
    end = time.time()
    best_cases.append(end-start)
    
    start = time.time()
    linear_search(arr, arr[n//2])
    end = time.time()
    average_cases.append(end-start)
    
    start=time.time()
    linear_search(arr,arr[-1])
    end=time.time()
    worst_cases.append(end-start)

plt.figure()
plt.plot(sizes, best_cases, label="Best Case (O(1))")
plt.plot(sizes, average_cases, label="Average Case (O(n))")
plt.plot(sizes, worst_cases, label="Worst Case (O(n))")

plt.xlabel("Input Size (n)")
plt.ylabel("Execution Time (seconds)")
plt.title("Linear Search: Best, Average, Worst Case Analysis")
plt.legend()
plt.show()