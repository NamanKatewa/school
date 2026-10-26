import time
import tracemalloc
import matplotlib.pyplot as plt
import heapq

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq

def huffman_codes(text):
    if not text:
        return {}
    freq = {}
    for char in text:
        freq[char] = freq.get(char, 0) + 1

    pq = [Node(char, f) for char, f in freq.items()]
    heapq.heapify(pq)

    if len(pq) == 1:
        return {pq[0].char: "0"}

    while len(pq) > 1:
        left = heapq.heappop(pq)
        right = heapq.heappop(pq)
        merged = Node(None, left.freq + right.freq)
        merged.left = left
        merged.right = right
        heapq.heappush(pq, merged)

    root = pq[0]
    codes = {}
    
    def generate_codes(node, current_code):
        if node is None:
            return
        if node.char is not None:
            codes[node.char] = current_code
        generate_codes(node.left, current_code + "0")
        generate_codes(node.right, current_code + "1")

    generate_codes(root, "")
    return codes

if __name__ == '__main__':
    import sys
    sys.setrecursionlimit(20000)
    sizes = list(range(1000, 50000, 1000))
    times = []
    spaces = []

    _ = huffman_codes("ab")
    tracemalloc.start()
    tracemalloc.stop()
    
    for n in sizes:
        text = ''.join(chr(i % 256) for i in range(n))
        
        runs = 10
        total_time = 0
        total_space = 0
        
        for _ in range(runs):
            tracemalloc.start()
            start_time = time.perf_counter()
            huffman_codes(text)
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
    plt.title('Huffman Coding - Time Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Time (seconds)')
    
    plt.subplot(1, 2, 2)
    plt.plot(sizes, spaces, marker='o', color='r')
    plt.title('Huffman Coding - Space Complexity')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Peak Memory (bytes)')
    
    plt.tight_layout()
    plt.show()