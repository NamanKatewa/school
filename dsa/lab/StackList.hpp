#ifndef STACK_LIST_HPP
#define STACK_LIST_HPP

#include "SinglyLinkedList.hpp"

class StackList {
private:
    ListNode *top;
    int size;

public:
    StackList();
    ~StackList();

    bool isEmpty() const;
    int getSize() const;

    void push(int value);
    int pop();
    int peek() const;

    void display() const;
};

#endif
