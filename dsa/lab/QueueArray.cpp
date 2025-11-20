#include "QueueArray.hpp"
#include <stdexcept>
#include <iostream>

QueueArray::QueueArray(int capacity) : capacity(capacity), front(-1), rear(-1), size(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Capacity must be a positive integer.");
    }
    data = new int[capacity];
}

QueueArray::~QueueArray() {
    delete[] data;
}

bool QueueArray::isEmpty() const {
    return size == 0;
}

bool QueueArray::isFull() const {
    return size == capacity;
}

void QueueArray::enqueue(int value) {
    if (isFull()) {
        throw std::overflow_error("Queue is full.");
    }
    if (isEmpty()) {
        front = 0;
    }
    rear = (rear + 1) % capacity;
    data[rear] = value;
    size++;
}

int QueueArray::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty.");
    }
    int value = data[front];
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % capacity;
    }
    size--;
    return value;
}

int QueueArray::getFront() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty.");
    }
    return data[front];
}

int QueueArray::getRear() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty.");
    }
    return data[rear];
}

void QueueArray::display() const {
    if (isEmpty()) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }
    std::cout << "Queue (front to rear): ";
    int i = front;
    for (int count = 0; count < size; ++count) {
        std::cout << data[i] << " ";
        i = (i + 1) % capacity;
    }
    std::cout << std::endl;
}
