#include "UndoStack.h"
#include <iostream>

UndoStack::UndoStack() : top(-1) {}

void UndoStack::push(const Ticket &t) {
    if (isFull()) {
        std::cout << "Undo stack is full. Cannot push." << std::endl;
        return;
    }
    history[++top] = t;
}

bool UndoStack::pop(Ticket &t) {
    if (isEmpty()) {
        return false;
    }
    t = history[top--];
    return true;
}

bool UndoStack::isEmpty() const {
    return top == -1;
}

bool UndoStack::isFull() const {
    return top == MAX_STACK_SIZE - 1;
}