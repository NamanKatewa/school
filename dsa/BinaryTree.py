class Node():
    def __init__(self,data=None):
        self.left:Node = None
        self.right:Node = None
        self.data = data
        
class BinaryTree():
    def __init__(self):
        self.root:Node = Node()
    
    def traversalInorder(self,node:Node,res:list[int]=None):
        if list is None:
            list = []
        if node is None:
            return
        self.traversalInorder(node.left,res)
        res.append(node.data)
        self.traversalInorder(node.right,res)
        return res
    
    def traversalPreorder(self,node:Node,res:list[int]=None):
        if res is None:
            res = []
        if node is None:
            return
        res.append(node.data)
        self.traversalPreorder(node.left,res)
        self.traversalPreorder(node.right,res)
        return res
    
    def traversalPostorder(self,node:Node,res:list[int]=None):
        if res is None:
            res = []
        if node is None:
            return
        self.traversalPostorder(node.left,res)
        self.traversalPostorder(node.right,res)
        res.append(node.data)
        return res
        
test = BinaryTree()
test.root.data = 1
test.root.left = Node(2)
test.root.right = Node(3)
test.root.left.left=Node(4)
test.root.left.right=Node(5)
test.root.right.right=Node(6)

res = test.traversalPostorder(test.root)
print(res)