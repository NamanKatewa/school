import heapq
from collections import Counter

class Node:
    def __init__(self,freq,char=None, left=None,right=None):
        self.freq = freq
        self.char = char
        self.left = left
        self.right = right
    
    def __lt__(self,other):
        return self.freq < other.freq

def build_huffman_tree(text):
    freq = Counter(text)
    print(freq)
    heap = [Node(f,ch) for ch,f in freq.items()]
    heapq.heapify(heap)
    
    while len(heap) >1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        merged = Node(left.freq + right.freq, None,left,right)
        heapq.heappush(heap,merged)
    return heap[0]

def generate_codes(root, current="",codes=None):
    if codes is None:
        codes = {}
    
    if root.char is not None:
        codes[root.char] = current or "0"
        return codes
    
    generate_codes(root.left, current+"0",codes)
    generate_codes(root.right, current+"1",codes)
    return codes

def encode_text(text,codes):
    return "".join(codes[ch] for ch in text)

def decode_text(encoded, root):
    result = []
    node = root
    
    for bit in encoded:
        if bit == "0":
            node = node.left
        else:
            node = node.right

        if node.char is not None:
            result.append(node.char)
            node = root

    return "".join(result)

t1 = "aabbbcdddd"
root = build_huffman_tree(t1)
codes = generate_codes(root)
encoded = encode_text(t1,codes)
print(encoded)
print()
print("original bits:", len(t1) * 8)
print("compressed bits:", len(encoded))
print()
decoded = decode_text(encoded, root)
print(decoded)