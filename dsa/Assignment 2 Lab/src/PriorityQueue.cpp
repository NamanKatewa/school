#include "PriorityQueue.h"
#include <iostream>

PriorityQueue::PriorityQueue() : size(0) {}

void PriorityQueue::enqueue(const Ticket &t) {
    if (isFull()) {
        std::cout << "Priority Queue is full. Cannot enqueue." << std::endl;
        return;
    }

    int i = size - 1;
    while (i >= 0 && t.getPriority() < data[i].getPriority()) {
        data[i + 1] = data[i];
        i--;
    }
    data[i + 1] = t;
    size++;
}

bool PriorityQueue::dequeue(Ticket &t) {
    if (isEmpty()) {
        return false;
    }
    t = data[0];
    for (int i = 0; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    return true;
}

bool PriorityQueue::isEmpty() const {
    return size == 0;
}

bool PriorityQueue::isFull() const {
    return size == MAX_QUEUE_SIZE;
}