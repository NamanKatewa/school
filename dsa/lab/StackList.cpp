#include "StackList.hpp"
#include <stdexcept>
#include <iostream>

StackList::StackList() : top(nullptr), size(0) {}

StackList::~StackList() {
    while (!isEmpty()) {
        pop();
    }
}

bool StackList::isEmpty() const {
    return top == nullptr;
}

int StackList::getSize() const {
    return size;
}

void StackList::push(int value) {
    ListNode *newNode = new ListNode(value);
    newNode->next = top;
    top = newNode;
    size++;
}

int StackList::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty.");
    }
    int value = top->data;
    ListNode *temp = top;
    top = top->next;
    delete temp;
    size--;
    return value;
}

int StackList::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty.");
    }
    return top->data;
}

void StackList::display() const {
    if (isEmpty()) {
        std::cout << "Stack is empty." << std::endl;
        return;
    }
    std::cout << "Stack (top to bottom): ";
    ListNode *current = top;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
