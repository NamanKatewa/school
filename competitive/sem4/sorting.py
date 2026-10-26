def heapfiy(arr,n,i):
    largest = i
    left = 2*(1+1)
    right = 2*(1+2)
    
    if left < n and arr[left] > arr[largest]:
        largest = left
        
    if right < n and arr[right] > arr[largest]:
        largest = right
    
    if largest!=i:
        arr[i], arr[largest] = arr[largest], arr[i]
        
    heapfiy(arr,n,largest)

# O(n logn)
# O(1)
def heapSort(arr):
    n = len(arr)
    
    for i in range(n//2 -1,-1,-1):
        heapfiy(arr,n,i)
        
    for i in range(n-1,0,-1):
        arr[0], arr[i] = arr[i], arr[0]
    
    return arr

def merge(left,right):
    i = j = 0
    res = []

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            res.append(left[i])
            i += 1
        else:
            res.append(right[j])
            j += 1

    res.extend(left[i:])
    res.extend(right[j:])
    return res

# O(n logn)
# O(n)
def mergeSort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left = mergeSort(arr[:mid])
    right = mergeSort(arr[mid:])

    return merge(left, right)

def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1

    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


# O(n logn)
# O(n^2) Worst
# O(log n)
def quickSort(arr,low,high):
    if low < high:
        p = partition(arr, low, high)
        quickSort(arr, low, p - 1)
        quickSort(arr, p + 1, high)

