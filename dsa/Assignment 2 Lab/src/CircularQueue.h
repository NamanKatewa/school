#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "Ticket.h"

const int MAX_CIRCULAR_QUEUE_SIZE = 100;

class CircularQueue {
private:
    Ticket data[MAX_CIRCULAR_QUEUE_SIZE];
    int front, rear, count;

public:
    CircularQueue();

    bool enqueue(const Ticket &t);
    bool dequeue(Ticket &t);
    bool isEmpty() const;
    bool isFull() const;
};

#endif 