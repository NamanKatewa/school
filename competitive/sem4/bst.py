class Node:
    def __init__(self,val):
        self.val = val
        self.left = None
        self.right = None

# Balanced BST
# O(log n)
# O(log n)
# Worst Case
# O(n)
# O(n)
def insert(node,val):
    if node in None:
        return Node(val)
    
    if val < node.val:
        node.left = insert(node.left,val)
    else:
        node.right = insert(node.right,val)
    return node

# O(n)
# O(h)
def height(node):
    if node is None:
        return 0
    return 1 + max(height(node.left),height(node.right))

# O(n)
# O(h)
def countNodes(node):
    if node is None:
        return 0
    return 1 + countNodes(node.left) + countNodes(node.right)

# O(1)
# O(1)
def isLeaf(node):
    return node is not None and node.left is None and node.right is None
    # (node != None) and (node.left == None) and (node.right ==None)

# O(n)
# O(h)
def printLeftLeaves(node):
    if node is None:
        return
    
    if isLeaf(node.left):
        print(node.left.val)
    
    printLeftLeaves(node.left)
    printLeftLeaves(node.right)

# O(n)
# O(h)
def inorder(node):
    if node is None:
        return
    
    inorder(node.left)
    print(node.val, end=" ")
    inorder(node.right)
    
