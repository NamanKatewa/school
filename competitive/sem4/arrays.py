
# O(n)
# O(1)
def count(arr,x):
    count = 0
    
    for y in arr:
        if(x == y):
            count += 1
    
    return count

def firstNonRepeting(arr):
    freq = {}
    
    for x in arr:
        freq[x] = freq.get(x,0) + 1
        
    for x in arr:
        if freq[x] == 1:
            return x
    
    return None

def linearSearch(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    
    return -1

def binarySearch(arr,target):
    l=0
    r=len(arr)-1
    
    while l<=r:
        m = (l+r)//2
        
        if arr[m] == target:
            return m
        elif arr[m] < target:
            l = m+1
        else:
            r = m-1
    
    return -1


def maxSubArraySum(arr):
    best = arr[0]
    current = arr[0]
    
    for i in range(1, len(arr)):
        current = max(arr[i], current + arr[i])
        best = max(best, current)
    
    return best

def targetSum(arr,k):
    freq = {0:1}
    res = 0
    prefix = 0
    
    for x in arr:
        prefix += x
        res += freq.get(prefix-k,0)
        freq[prefix] = freq.get(prefix,0) + 1
    
    return res

def factorial(num):
    if num == 0:
        return 0
    if num == 1:
        return 1
    
    res = 1
    
    for x in range(2,num+1):
        res*=x
    
    return res

def numOfSubsets(n,k):
    result = factorial(n)/(factorial(k)*factorial(n-k))
    return int(result)

print(numOfSubsets(5,2))