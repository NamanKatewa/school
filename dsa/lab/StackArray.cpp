#include "StackArray.hpp"
#include <stdexcept>
#include <iostream>

StackArray::StackArray(int capacity) : capacity(capacity), top(-1) {
    if (capacity <= 0) {
        throw std::invalid_argument("Capacity must be a positive integer.");
    }
    data = new int[capacity];
}

StackArray::~StackArray() {
    delete[] data;
}

bool StackArray::isEmpty() const {
    return top == -1;
}

bool StackArray::isFull() const {
    return top == capacity - 1;
}

void StackArray::push(int value) {
    if (isFull()) {
        throw std::overflow_error("Stack is full.");
    }
    data[++top] = value;
}

int StackArray::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty.");
    }
    return data[top--];
}

int StackArray::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty.");
    }
    return data[top];
}

void StackArray::display() const {
    if (isEmpty()) {
        std::cout << "Stack is empty." << std::endl;
        return;
    }
    std::cout << "Stack (top to bottom): ";
    for (int i = top; i >= 0; --i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}
