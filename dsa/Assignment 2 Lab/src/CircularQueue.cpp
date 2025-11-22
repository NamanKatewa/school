#include "CircularQueue.h"
#include <iostream>

CircularQueue::CircularQueue() : front(-1), rear(-1), count(0) {}

bool CircularQueue::enqueue(const Ticket &t) {
    if (isFull()) {
        std::cout << "Circular Queue is full. Cannot enqueue." << std::endl;
        return false;
    }

    if (isEmpty()) {
        front = 0;
    }
    rear = (rear + 1) % MAX_CIRCULAR_QUEUE_SIZE;
    data[rear] = t;
    count++;
    return true;
}

bool CircularQueue::dequeue(Ticket &t) {
    if (isEmpty()) {
        return false;
    }

    t = data[front];
    front = (front + 1) % MAX_CIRCULAR_QUEUE_SIZE;
    count--;

    if (isEmpty()) {
        front = -1;
        rear = -1;
    }
    return true;
}

bool CircularQueue::isEmpty() const {
    return count == 0;
}

bool CircularQueue::isFull() const {
    return count == MAX_CIRCULAR_QUEUE_SIZE;
}