class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.previous = None


class LinkedList:

    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0
    
    def isEmpty(self):
        return self.head is None
    
    def getSize(self):
        return self.size
    
    def prepend(self, data):
        newNode = Node(data)
        
        if self.isEmpty():
            self.head = self.tail = newNode
        else:
            newNode.next = self.head
            self.head.previous = newNode
            self.head = newNode
        
        self.size += 1
    
    def append(self, data):
        newNode = Node(data)
        
        if self.isEmpty():
            self.head = self.tail = newNode
        else:
            newNode.previous = self.tail
            self.tail.next = newNode
            self.tail = newNode
        
        self.size += 1
    
    def insert_at(self, index, data):
        if index < 0 or index > self.size:
            raise IndexError("Index out of range")
        
        if index == 0:
            self.prepend(data)
            return
        elif index == self.size:
            self.append(data)
            return
        
        newNode = Node(data)
        current = self.head
        
        for _ in range(index):
            current = current.next
        
        newNode.previous = current.previous
        newNode.next = current
        current.previous.next = newNode
        current.previous = newNode
        
        self.size += 1
    
    def delete_first(self):
        if self.isEmpty():
            raise IndexError("Cannot delete from empty list")
        
        data = self.head.data
        
        if self.size == 1:
            self.head = self.tail = None
        else:
            self.head = self.head.next
            self.head.previous = None
        
        self.size -= 1
        return data
    
    def delete_last(self):
        if self.isEmpty():
            raise IndexError("Cannot delete from empty list")
        
        data = self.tail.data
        
        if self.size == 1:
            self.head = self.tail = None
        else:
            self.tail = self.tail.previous
            self.tail.next = None
        
        self.size -= 1
        return data
    
    def delete_at(self, index):
        if index < 0 or index >= self.size:
            raise IndexError("Index out of range")
        
        if index == 0:
            return self.delete_first()
        elif index == self.size - 1:
            return self.delete_last()
        
        current = self.head
        for _ in range(index):
            current = current.next
        
        current.previous.next = current.next
        current.next.previous = current.previous
        self.size -= 1
        
        return current.data
    
    def search(self, data):
        current = self.head
        index = 0
        
        while current:
            if current.data == data:
                return index
            current = current.next
            index += 1
        
        return -1
    
    def get(self, index):
        if index < 0 or index >= self.size:
            raise IndexError("Index out of range")
        if index < self.size // 2:
            current = self.head
            for _ in range(index):
                current = current.next
        else:
            current = self.tail
            for _ in range(self.size - 1 - index):
                current = current.previous
        
        return current.data
    
    def reverse(self):
        """Reverse the doubly linked list in place."""
        current = self.head
        
        while current:
            current.next, current.previous = current.previous, current.next
            current = current.previous
        self.head, self.tail = self.tail, self.head
    
    def to_list(self):
        result = []
        current = self.head
        
        while current:
            result.append(current.data)
            current = current.next
        
        return result
    
    def to_list_reverse(self):
        result = []
        current = self.tail
        
        while current:
            result.append(current.data)
            current = current.previous
        
        return result
    
    def display(self):
        if self.isEmpty():
            print("Empty list")
            return
        
        elements = []
        current = self.head
        
        while current:
            elements.append(str(current.data))
            current = current.next
        
        print(" <-> ".join(elements))
    
    def display_reverse(self):
        if self.isEmpty():
            print("Empty list")
            return
        
        elements = []
        current = self.tail
        
        while current:
            elements.append(str(current.data))
            current = current.previous
        
        print(" <-> ".join(elements))
    
    def __str__(self):
        if self.isEmpty():
            return "LinkedList([])"
        
        elements = self.to_list()
        return f"LinkedList({elements})"
    
    def __len__(self):
        return self.size
