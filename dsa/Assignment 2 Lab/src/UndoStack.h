#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include "Ticket.h"

const int MAX_STACK_SIZE = 100; 

class UndoStack {
private:
    Ticket history[MAX_STACK_SIZE];
    int top;

public:
    UndoStack();

    void push(const Ticket &t);
    bool pop(Ticket &t);
    bool isEmpty() const;
    bool isFull() const;
};

#endif 