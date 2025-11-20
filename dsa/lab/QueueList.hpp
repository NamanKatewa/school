#ifndef QUEUE_LIST_HPP
#define QUEUE_LIST_HPP

#include "SinglyLinkedList.hpp"

class QueueList {
private:
    ListNode *front;
    ListNode *rear;
    int size;

public:
    QueueList();
    ~QueueList();

    bool isEmpty() const;
    int getSize() const;

    void enqueue(int value);
    int dequeue();
    int getFront() const;
    int getRear() const;

    void display() const;
};

#endif
