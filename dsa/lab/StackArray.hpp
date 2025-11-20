#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

class StackArray {
private:
    int *data;
    int capacity;
    int top;

public:
    StackArray(int capacity);
    ~StackArray();

    bool isEmpty() const;
    bool isFull() const;

    void push(int value);
    int pop();
    int peek() const;

    void display() const;
};

#endif
