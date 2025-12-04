class Node {
    int data;
    Node next;

    Node(int x) {
        data = x;
        next = null;
    }
}

class LinkedListStack {
    private Node top;

    LinkedListStack() {
        top = null;
    }

    public boolean isEmpty() {
        return top == null;
    }

    public void push(int x) {
        Node node = new Node(x);
        node.next = top;
        top = node;
    }

    public int peek() {
        if (isEmpty()) {
            System.out.println("Empty");
            return Integer.MIN_VALUE;
        }
        return top.data;
    }

    public int pop() {
        if (isEmpty()) {
            System.out.println("Underflow");
            return Integer.MIN_VALUE;
        }
        Node node = top;
        int x = node.data;
        top = top.next;
        node.next = null;
        return x;
    }
}
