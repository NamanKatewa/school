#ifndef QUEUE_ARRAY_HPP
#define QUEUE_ARRAY_HPP

class QueueArray {
private:
    int *data;
    int capacity;
    int front;
    int rear;
    int size;

public:
    QueueArray(int capacity);
    ~QueueArray();

    bool isEmpty() const;
    bool isFull() const;

    void enqueue(int value);
    int dequeue();
    int getFront() const;
    int getRear() const;

    void display() const;
};

#endif
