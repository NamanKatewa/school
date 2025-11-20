#include "QueueList.hpp"
#include <stdexcept>
#include <iostream>

QueueList::QueueList() : front(nullptr), rear(nullptr), size(0) {}

QueueList::~QueueList() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool QueueList::isEmpty() const {
    return front == nullptr;
}

int QueueList::getSize() const {
    return size;
}

void QueueList::enqueue(int value) {
    ListNode *newNode = new ListNode(value);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

int QueueList::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty.");
    }
    int value = front->data;
    ListNode *temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
    size--;
    return value;
}

int QueueList::getFront() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty.");
    }
    return front->data;
}

int QueueList::getRear() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty.");
    }
    return rear->data;
}

void QueueList::display() const {
    if (isEmpty()) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }
    std::cout << "Queue (front to rear): ";
    ListNode *current = front;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
