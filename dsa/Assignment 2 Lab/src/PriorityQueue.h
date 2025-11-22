#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Ticket.h"

const int MAX_QUEUE_SIZE = 100; 

class PriorityQueue {
private:
    Ticket data[MAX_QUEUE_SIZE];
    int size;

public:
    PriorityQueue();

    void enqueue(const Ticket &t);
    bool dequeue(Ticket &t);
    bool isEmpty() const;
    bool isFull() const;
};

#endif 