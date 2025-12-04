class ArrayStack {
    private int[] arr;
    private int cap;
    private int top;

    public ArrayStack(int cap) {
        this.cap = cap;
        arr = new int[cap];
        top = -1;
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public boolean isFull() {
        return cap - 1 == top;
    }

    public void push(int x) {
        if (isFull()) {
            System.out.println("Overflow");
            return;
        }
        top++;
        arr[top] = x;
    }

    public int peek() {
        if (isEmpty()) {
            System.out.println("Empty");
            return Integer.MIN_VALUE;
        }
        return arr[top];
    }

    public int pop() {
        if (isEmpty()) {
            System.out.println("Underflow");
            return Integer.MIN_VALUE;
        }
        int x = arr[top];
        top--;
        return x;
    }
}