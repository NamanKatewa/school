import heapq

# O(n logk)
# O(k)
def kthLargest(arr,k):
    heap = []
    
    for x in arr:
        heapq.heappush(heap,x)
        
        if(len(heap)>k):
            heapq.heappop(heap)
    
    return heap[0]

# O(n logk)
# O(k)
def kthSmallest(arr,k):
    heap=[]
    
    for x in arr:
        heapq.heappush(heap,-x)
        
        if(len(heap)>k):
            heapq.heappop(heap)
    
    return -heap[0]

arr = [6,10,4,11,2,5,7]
k=8

print(kthLargest(arr,k))
